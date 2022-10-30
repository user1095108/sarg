# sarg
`sarg` is a simple command-line parser. It can parse command line arguments in the format:

`sarg --key=value -kvalue -- operands...`

# build instructions
re2c sarg.re -o sarg.hpp
g++ -std=c++20 sarg.cpp -o sarg
