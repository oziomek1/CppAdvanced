//
// Created by Wojciech Ozimek on 18/03/2019.
//

#include <iostream>
#include <set>
#include <functional>
#include <vector>


using namespace std;

//1.
//a)
template <typename T>
T max(T a, T b)
{
    cout << "T & T -> ";
    return (a > b) ? a : b;
}

//b)
template <typename T>
T max(T *a, T *b)
{
    cout << "T* & T* -> ";
    return ((*a) > (*b)) ? *a : *b;
}

//c)
template <typename T>
T max(T * data, size_t n)
{
    cout << "T* & size -> ";
    T value = data[0];
    for(size_t i = 0; i < n; i++)
    {
        if(data[i] > value)
        {
            value = data[i];
        }
    }
    return value;
}

//d)
template <>
char * max(char *a, char *b)
{
    cout << "char * & char * -> ";
    return strcmp(a, b) > 0 ? a : b;
}

//e)
template <>
const char * max(const char *a, const char *b)
{
    cout << "const char * & const char * -> ";
    return strcmp(a, b) > 0 ? a : b;
}

//f)
template<typename T>
const T* max(T *a, const T*b)
{
    cout << "char * & const char * -> ";
    return (*a) > (*b) ? a : b;
}

//2.
template<typename T,typename U>
T convert(U u)
{
    cout << u << " -> ";
    return static_cast<T>(u);
}

//3.
template<typename T,int N = 100> class Stack
{
public:
    Stack() {
        cout << "Stack<T, N>" << endl;
    }
};

template <typename T> class Stack<T, 666>
{
public:
    Stack() {
        cout << "Stack<T, 666>" << endl;
    }
};

template <typename T, int N> class Stack<T*, N>
{
public:
    Stack() {
        cout << "Stack<T*, N>" << endl;
    }
};

template <int N> class Stack<double ,N>
{
public:
    Stack() {
        cout << "Stack<double, N>" << endl;
    }
};

template <int N> class Stack<int *, N>
{
public:
    Stack() {
        cout << "Stack<int *, N>" << endl;
    }
};

template <> class Stack<double,666>
{
public:
    Stack() {
        cout << "Stack<double, 666>" << endl;
    }
};

template<> class Stack<double *,44>
{
public:
    Stack() {
        cout << "Stack<double *, 44>" << endl;
    }
};

//4.
template<typename T,int N = 100, typename R = T*> class SuperStack;

template<typename T,int N> class SuperStack<T, N, T*>
{
    T _repr[N];
    unsigned int _top;
public:
    SuperStack() : _top(0) {};
    void push(T v)
    {
        _repr[_top++] = v;
    }
    T pop()
    {
        return _repr[--_top];
    }
};
//
//template <typename T, int N, template<typename E> class Sequence>
//class SuperStack<T, N, Sequence<T, std::allocator<T>> >
//{
//    Sequence<T> _repr;
//public:
//    void push(T v)
//    {
//        _repr.push_bask(v);
//    }
//    T pop()
//    {
//        T top =  _repr.top();
//        _repr.pop_back();
//        return top;
//    }
//    bool is_empty() const
//    {
//        return _repr.empty();
//    }
//};



//5.
template <typename Iterator>
void print(Iterator begin, Iterator end)
{
    for(; begin != end; ++ begin)
    {
        cout << *begin << ' ';
    }
    cout << endl;
}

int main() {
//    1)
    int size = 4;
    char *s1 = new char[size];
    char *s2 = new char[size];
    strncpy(s1, "adam", size);
    strncpy(s2, "john", size);
    int extraLarge = 123456789;

    cout << ::max(size, extraLarge) << endl;
    cout << ::max(&size, &extraLarge) << endl;
    cout << ::max(s1, size) << endl;

    cout << ::max(s1, s2) << endl;
    cout << ::max("adam", "john") << endl;
    cout << ::max(s2, "adam") << endl;

//    2)
    cout << ::convert<int>(32.93012) << endl;
    cout << ::convert<double>(32.93012) << endl;
    cout << ::convert<bool>(32.93012) << endl;

//    3)
    Stack<int, 20>      stack0;
    Stack<int, 666>     stack1;
    Stack<double *, 30> stack2;
    Stack<double , 30>  stack3;
    Stack<double *, 44> stack4;
    Stack<int *, 20>    stack5;
    Stack<double, 666>  stack6;

//    4)
    SuperStack<int,100,int *>            s_table;
    SuperStack<int,100>                  s_default ;
//    SuperStack<int,0,std::vector<int> >  s_container;

//    5)
    set<int, greater<int> > mySet;
    mySet.insert(18);
    mySet.insert(123);
    mySet.insert(8);
    print(mySet.begin(), mySet.end());
}