//
// Created by Wojciech Ozimek on 09/03/2019.
//

#include <iostream>
#include <functional>
#include <vector>
#include <list>

#include "Employee.hpp"
#include "Engineer.hpp"
#include "Seller.hpp"

// 2) a.
void payBonuses(Employee * table[], size_t n) {
    for (size_t e = 0; e < n; e++)
    {
        table[e] -> payBonus();
    }
}

// 2) b.
template <typename T> void payBonuses_template (T table[], size_t n) {
    for (size_t e = 0; e < n; e++)
    {
        table[e].payBonus();
    }
}

// 3)
template <class Iterator, class T>
T accumulate(Iterator first, Iterator last, T init)
{
    T sum = init;
    for (; first != last; ++ first)
    {
        sum += *first;
    }
    return sum;
};

//4)
template <typename T> class SequenceGen
{
    T _start;
    T _step;
public:
    SequenceGen(T start = T(), T step = 1) :
            _start(start), _step(step) {};

    T operator()()
    {
        T tmp = _start;
        _start += _step;
        return tmp;
    }
};

template <class OutputIterator, class Size, class Generator>
OutputIterator generate_n(OutputIterator first, Size n, Generator generator);

template <class InputIterator, class Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate predicate);

int main() {

    // 2) a.

    Employee *list[2];
    list[0]=new Seller(36,6000,0.15, 3);
    list[1]=new Engineer(40,8000,0.2);
    payBonuses(list,2);

    // 2) b.

    Engineer engineers[1] =
            {
                    Engineer(40, 7000, 0.22)
            };

    Seller sellers[2] =
            {
                    Seller(32, 5000, 0.17, 2),
                    Seller(42, 7100, 0.19, 5)
            };
    payBonuses_template(engineers, 1);
    payBonuses_template(sellers, 2);

    // 3)

    std::list<int> _list = {};
    _list.push_back(1);
    _list.push_back(2);
    _list.push_front(0);

    std::cout << accumulate(_list.begin(), _list.end(), 0) << std::endl;

    std::vector<float> _vector = {};
    _vector.push_back(1.12);
    _vector.push_back(2.423);
    _vector.push_back(1.321);

    std::cout << accumulate(_vector.begin(), _vector.end(), static_cast<float >(0)) << std::endl;

    // 4)

    const size_t n = 20;
    std::vector<int> _vector2(n);
    std::generate_n(_vector2.begin(), n, SequenceGen<int>(1,2));

    std::vector<int>::iterator it = std::find_if(_vector2.begin(), _vector2.end(), std::bind2nd(std::greater<int>(), 4));
    std::cout << *it << std::endl;
}

