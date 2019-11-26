# C1 Interpreter

在第一关中完成了对 genfib 的生成，对 llvm 的接口有了了解之后，完成 C1 Interpreter 的设计就相对比较简单了。文档中也对给出框架的 Architecture 有了一个比较详细的介绍，理解了之后剩下的问题也不多，以下也就只介绍一下实现细节遇到的一些问题。

## Code Design

### Evaluation of expression

在 `constexpr_expected` 为真或假时，表达式的求值是不同的。

在 C1 中，对于一个 `constexpr`，其值应该在编译的时候就确定，所以需要使用 `int_const_result` 和 `float_const_result` 来存储子表达式的中间计算结果，经过合适的类型转换后（这里的类型转换不应该生成指令）来静态得到表达式的结果，在整个表达式计算完成后，通过一个 `Constant` 来表示最终的结果。这种情况只会在全局变量的初始化和数组声明指定数组大小时出现。

而对于并非 `constexpr` 的情况，则需要生成一系列的计算指令，哪怕是 `2 * 3` 这样的表达式也是一样的（大概是为了降低难度所以不要求我们对这样的表达式进行静态求值），而且还需要适时插入类型转换的指令。

由于这些操作经常用到，我设计了一系列 `calc_expr` 的重载作为工具函数，例如 `int calc_expr(binop op, int lhs, int rhs)`, `double calc_expr(binop op, double lhs, double rhs)`, `Value *calc_expr(IRBuilder<> &builder, binop op, Value *lhs, Value *rhs, bool is_int)` 等等。

### Implicit type conversion

在求值和在之后的赋值中，需要进行类型转换。例如，在计算表达式时，若操作符的两边一边是 `int`, 一边是 `float`,  则表达式的类型应是 `float`，其中的 `int` 需要被转化成 `float` 类型。因此 `result_is_int = lhs_is_int && rhs_is_int`.

我写了一个 `auto_conversion` 函数，用于进行类型转换:

```cpp
Value *auto_conversion(IRBuilder<> &builder, LLVMContext &context, Value *v, bool from, bool to) {
    if (from == to) {
        return v;
    }
    if (from) { // int -> float
        return builder.CreateSIToFP(v, Type::getDoubleTy(context));
    } else { // float -> int
        return builder.CreateFPToSI(v, Type::getInt32Ty(context));
    }
}
```

通过这样的函数，能避免实现过程中繁杂的类型判断。

### Control flow

#### if

要生成三个或两个基本块，`then`, `else`, `next`. 对于每个块需要递归的 visit 其对应的子结点。例如对于 `then_body`:

```cpp
builder.SetInsertPoint(then_body);
node.then_body->accept(*this);
builder.CreateBr(next);
```

在生成 `then_body` 基本块后，设置指令插入点，生成 `then_body` 的代码，之后再通过 `CreateBr` 跳转到 `next` 基本块。在处理完 if 之后，通过：

`builder.SetInsertPoint(next)` 设置新的插入点。

#### while

要生成三个基本块，`pred`, `loop_body`, `next`. 在下面的 [Bug fix](#Missing-br-before-while-prediction) 中有详细介绍，因为那处地方导致了我一个 bug。 

### Lval: addressing & evaluation

对左值需要根据其 `lval_as_rval` 结果的不同进行求地址或求值，对于数组，需要通过 `getelementptr` 获取对应元素的指针。

因此需要在对普通变量和数组变量分别求得指针 `var_ptr` 后，需要添加：

```cpp
if (lval_as_rval) {
    value_result = builder.CreateLoad(var_ptr);
} else {
    value_result = var_ptr;
}
```

来考虑是否进行求值。值得注意的是数组的 index 也需要进行求值，对应的是 `visit(expr_syntax &node)`.

另外，需要考虑到，如果 `lval_as_rval == false` 而 `is_const == true` 时，意味着我们在对一个常量进行赋值。需要抛出错误。

### Error Handling

在进行处理时，有许多情况下我们需要考虑抛出错误。在我的实现中，有以下几种情况

- 函数重定义
  - 发生条件：`visit(func_def_stmt_syntax)` 开始时 `functions.count(node.name) == 1`
  - 错误：`Function named {node.name} already exists`
- 不支持的操作符
  - 发生条件：在 `float` 类型上使用 `%` 操作符
  - 错误：`Modulo operator not supported on float`
- 变量出现在常量表达式中
  - 发生条件：`visit(lval_syntax &node)` 开始时 `constexpr_expected == true`
  - 错误：`Expected a constexpr but found a left value`
- 对 const value 进行赋值
  - 发生条件：`visit(lval_syntax &node)` 开始时 `is_const & !lval_as_rval`
  - 错误：`const value can't be assigned`
- 数组引用没有 index
  - 发生条件：`visit(lval_syntax &node)` 时 `is_array && node.array_index == nullptr` 
  - 错误：`Expected index but not found`
- 数组 index 不为整数
  - 发生条件：在定义或引用数组时，`array_index` 或 `array_length` 访问的结果是 `is_result_int == false`
  - 错误：`Array index must be an integer`/ `Array length must be an integer`
- 初始化列表长度大于数组长度
  - 发生条件：定义数组时 `length < node.initializers.size()`，其中 length 是访问 `array_length` 的结果。
  - 错误：`Array length shorter than the initializer list`
- 变量重定义
  - 发生条件：`declare_variable` 返回值为 `false`
  - 错误：`Variable named {node.name} already exists`
- 引用不存在的函数或变量

## Bug fix

### Global value has to be initialized

全局变量不进行初始化会发生糟糕的情况。在 C 的标准中全局变量应进行默认初始化，对于 int 和 float 都应初始化为 0. 在最开始实现时我传给 `GlobalValue` 一个 `nullptr` 的 `initialzer`，这样，生成的 IR 会将该变量声明为一个 `external global`。因为对于没有初始化的 `GlobalValue`，llvm 会认为是通过 `extern` 声明的变量。这样，在之后使用时，就会出现找不到符号的错误。（在 debug 时，由于错误信息比较模糊，报的是 dynamic library 加载的错误，所以我是通过 **二分法** 一段段的删 IR 代码，直到删到只剩对全局变量的赋值才 debug 出来）。

**Fix**：将没有显示初始化的全局变量初始化为 0。

### Initialializer list can be shorter than array length

虽然没让我们考虑截断，但对于没有对应初始化列表的数组元素，也需要进行默认初始化。

所以就分为以下的情况：

- `in_global == true`: 数组无论怎样都应进行初始化

- `in_global == false`: 数组 `!intializers.empty()` 时需要进行初始化，并对超过初始化列表的元素进行默认初始化。`initialzer.empty()` 的情况则不进行初始化。

  由于框架的设计没法区分 `int a[3] = {}` 和 `int a[3]` 的情况，所以我就不考虑这种情况了。

### Missing `br` before `while` prediction

对于 `while` 控制流，我们应该有生成三个基本快，一个由 prediction 开始，跳转到 loop body 或 while 下一条指令。其中 loop body 结尾需要跳转到 prediction. 在生成这三个基本快的时候，如果忘记了在 prediction 之前的基本块中插入 `br prediction`，上一个基本块就是非法的了。对于 `if` 由于不用在 prediction 之前生成一个基本块所以不需要考虑这种情况。

### C++17 isn't enabled

所以没有 structure binding XD：

```cpp
auto [var_ptr, is_const, is_array, is_int] = lookup_variable(node.name);
```

**Fix**:

```cpp
#if __cplusplus >= 201703L
    auto [var_ptr, is_const, is_array, is_int] = lookup_variable(node.name);
#else
    Value *var_ptr;
    bool is_const, is_array, is_int;
    std::tie(var_ptr, is_const, is_array, is_int) = lookup_variable(node.name);
#endif
```



