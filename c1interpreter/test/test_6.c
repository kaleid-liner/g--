int in_fib;
int ret_fib;
void fib()
{
        if (in_fib == 0)
                ret_fib = 0;
        else if (in_fib == 1)
                ret_fib = 1;
        else
        {
                int self_in = in_fib;
                in_fib = self_in - 1;
                fib();
                int tmp = ret_fib;
                in_fib = self_in - 2;
                fib();
                ret_fib = tmp + ret_fib;
        }
}

void main()
{
        in_fib = 10;
        fib();
}
