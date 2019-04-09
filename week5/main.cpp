//
// Created by Wojciech Ozimek on 09/04/2019.
//

#include <iostream>
#include <vector>
#include<deque>

using namespace std;

//1))
template <typename T> class Is_class {
    typedef char one;
    typedef struct {
        char c[2];
    } two;
    template <typename U> static one test(int U::*);
    template <typename U> static two test(...);

public:
    enum {
        yes = (sizeof(test<T>(0)) == sizeof(one))
    };
};

struct X {};

//2))
template<typename T> class has_value_type {
    typedef char one;
    typedef struct {
        char c[2];
    } two;
    template<typename U> static one test(typename  U::value_type );
    template<typename U> static two test(...);
public:
    enum {
        yes = (sizeof(test<T>(0))==sizeof(one) )
    };
};

//3))
template<typename T,typename U> class Is_convertible {
    typedef char one;
    typedef struct {
        char c[2];
    } two;
    static one test(U) ;
    static two test(...);
    static T makeT();

public:
    enum {
        yes = sizeof(test(makeT()) )==sizeof(one),
        same_type=false
    };
};

template<typename T> class Is_convertible<T,T> {
public:
    enum {
        yes = true,
        same_type=true
    };
};


int main()
{
//1))
    cout << "TASK 1" << endl;
    cout << Is_class<int>::yes << endl;
    cout << Is_class<X>::yes << endl;
    cout << Is_class<vector<double> >::yes << endl;

//2))
    cout << "TASK 2" << endl;
    cout << has_value_type<int>::yes << endl;
    cout << has_value_type<X>::yes << endl;
    cout << has_value_type<vector<double> >::yes << endl;

//3))
    cout << "TASK 3" << endl;
    cout << Is_convertible<int,double>::yes << endl;
    cout << Is_convertible<double,int>::yes << endl;

    cout << Is_convertible<double,int>::same_type << endl;

    cout << Is_convertible<size_t,unsigned int>::same_type << endl;
    cout << Is_convertible<vector<double>::value_type,
            double >::same_type << endl;

    cout << Is_convertible<vector<double>::iterator,
            double *>::same_type << endl;
}