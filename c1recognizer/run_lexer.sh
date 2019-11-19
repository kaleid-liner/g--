#!/bin/bash
# change to your /full/path/to/antlr-4.7.2-complete.jar
export CLASSPATH='.:/usr/local/lib/antlr-4.7.2-complete.jar:$CLASSPATH'
antlr4='java org.antlr.v4.Tool'
grun='java org.antlr.v4.gui.TestRig'

if [[ $# != 1 ]]; then
    echo "Usage: ./run.sh java|cpp"
    echo "Example: cat test/test_cases/simple.c1 | ./run.sh java"
fi

rm -rf build
mkdir -p build

if [[ $1 == "java" ]]; then
    cd grammar
    $antlr4 C1Lexer.g4 -o ../build
    cd ../build
    javac *.java
    $grun C1Lexer tokens -tokens
elif [[ $1 == "cpp" ]]; then
    cd grammar
    $antlr4 C1Lexer.g4 -Dlanguage=Cpp -o ../build
    cd ../build
    # uncomment below if you run this file on your machine
    #g++ -std=c++11 ../test/lexer.cpp C1Lexer.cpp -I../include/antlr4-runtime -I. -L../Libs_for_c1r_ref/ -lantlr4-runtime -o c1lexer
    #LD_LIBRARY_PATH=../Libs_for_c1r_ref ./c1lexer
    # comment below if you run this file on your machine
    g++ -std=c++11 ../test/lexer.cpp C1Lexer.cpp -I../include/antlr4-runtime -I. -lantlr4-runtime -o c1lexer
    ./c1lexer
fi

