//
// Created by Wojciech Ozimek on 13/04/2019.
//

#include <iostream>
using std::cin;
using std::cout;

#include "kolor.h"
//#include "fab_kol.h"
#include "abort_on_error_policy.h"
#include "no_checking_policy.h"
#include "static_table_allocator.h"
#include "expandable_new_allocator.h"


//1)

template <int r, int g, int b>
struct MojaPolityka
{
    Kolor nieznanyKolor(std::string nazwa)
    {
        return Kolor(r, g, b);
    }
};

typedef MojaPolityka<255,255,255> Bialy;
//FabrykaKolorow<Bialy> fabryka;
//FabrykaKolorow<MojaPolityka> moja_fabryka;


//2 & 3)

template <typename T = int, size_t N = 100,
        typename Checking_policy = No_checking_policy,
        template <typename U, size_t M> class Allocator_policy = Static_table_allocator>
class Stack {
private:
    T _rep[N];
    size_t _top;
public:
    Stack(size_t n = N) : _top(0) {};

    void push(const T &val)
    {
        Checking_policy::check_push(_top, N);
        _rep[_top++] = val;
    }
    void pop()
    {
        Checking_policy::check_pop(_top);
        --_top;
    }
    const T& top() const
    {
        Checking_policy::check_top(_top);
        return &_rep[_top - 1];
    }
    T& top()
    {
        return &_rep[_top - 1];
    }
    bool is_empty()
    {
        return !_top;
    }
};

int main()
{

//    1)
//    try {
//        cout << fabryka.zwrocKolor("zielony") << '\n';
//        cout << fabryka.zwrocKolor("green") << '\n';
//    } catch(...) {
//        cout << "Zlapano wyjatek.\n";
//    }
//
//    cout << moja_fabryka.zwrocKolor("zielony") << '\n';
//    cout << moja_fabryka.zwrocKolor("green") << '\n';


//    2 & 3)
    Stack<int,10>                                                           default__no_check__allocator_static;
    Stack<double ,100, No_checking_policy, Expandable_new_allocator>        policy_no_check__allocator_expandable;
    Stack<int *,25, Abort_on_error_policy, Static_table_allocator>          policy_abort__allocator_static;

    return 0;
}