//
// Created by Wojciech Ozimek on 02/03/2019.
//
#include <iostream>
//#include <string>

// 1)

template<typename T> T maksimum(T a, T b)
{
    return (a < b) ? b : a;
};

// 2)

template<typename C, typename S> C convert(S s)
{
    return static_cast <C> (s);
};

// 3)

template<size_t S, typename T> T dot_product(T *a, T *b)
{
    T value = 0.0;
    for (auto i = 0; i < S; i++)
    {
        value += a[i] * b[i];
    }
    return value;
};

// 4)

template<template<char N> class C, char K>
void f(C<K>)
{
    std::cout << K << std::endl;
};

template<char N> struct ExampleClass {};

// 5)

template<typename S> typename S::value_type sum(S s)
{
    typename S::value_type total;

    while(!s.is_empty())
    {
        total += s.pop();
    }
    return total;
}

template<typename T = int , size_t N = 2000> class Stack
{
private:
    T _stack[N];
    size_t _top;
public:
    typedef T value_type;

    Stack() : _top(0) {};

    void push(T val)
    {
        _stack[_top++] = val;
    }
    T pop()
    {
        return _stack[--_top];
    }
    bool is_empty() const
    {
        return (_top==0);
    }
};

int main()
{
    auto taskId = 0;
// 1)
    std::cout << "----------------------\n" << ++taskId << ")\n" << std::endl;

    std::cout << maksimum(-1.2, 2.32) << std::endl;
    std::cout << maksimum(3,2) << std::endl;
    std::cout << maksimum("text_small","TEXT_CAPS") << std::endl;
    /*
     * OUTPUT:
     * ----------------------
     * 2.32
     * 3
     * TEXT_CAPS
     * ----------------------
     */

// 2)
    std::cout << "----------------------\n" << ++taskId << ")\n" << std::endl;
    std::cout << convert<int>(9.87) << std::endl;
    std::cout << convert<float>('b') << std::endl;
    /*
     * OUTPUT:
     * ----------------------
     * 9
     * 98 // (ASCII decimal code)
     * ----------------------
     */

// 3)
    std::cout << "----------------------\n" << ++taskId << ")\n" << std::endl;

    double x[] = {0.1, 0.3, -1.2, 9.2, 3.5};
    double y[] = {0.5, 2.4, 0.7, -5.1, 1.1};

    std::cout << dot_product<sizeof(x) / sizeof(*x)>(x, y) << std::endl;
    /*
     * OUTPUT:
     * ----------------------
     * -43.14
     * ----------------------
     */

// 4)
    std::cout << "----------------------\n" << ++taskId << ")\n" << std::endl;

    ExampleClass<'a'>  exClass1;
    ExampleClass<'b'>  exClass2;

    f(exClass1);
    f(exClass2);
    /*
     * OUTPUT:
     * ----------------------
     * a
     * b
     * ----------------------
     */

// 5)
    std::cout << "----------------------\n" << ++taskId << ")\n" << std::endl;

    Stack<double, 5> s1;
    s1.push(3.14);
    s1.push(5);
    s1.push(99);
    std::cout << "Is empty? " << s1.is_empty() << std::endl;
    std::cout << sum(s1) << std::endl;
    std::cout << "Is empty? " << s1.is_empty() << std::endl;
    /*
     * OUTPUT:
     * ----------------------
     * 107.14
     * ----------------------
     */
}

