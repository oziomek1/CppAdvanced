//
// Created by Wojciech Ozimek on 26/03/2019.
//

#include <iostream>

using namespace std;

//1)
template <typename T> struct sum_traits;

template <> struct sum_traits<char>
{
    typedef int sum_type;
//    2)
    static sum_type zero()
    {
        return 0;
    }
};

template <> struct sum_traits<int>
{
    typedef long int sum_type;
    //    2)
    static sum_type zero()
    {
        return 0;
    }
};

template <> struct sum_traits<float>
{
    typedef double sum_type;
    //    2)
    static sum_type zero()
    {
        return 0.0;
    }
};

template <> struct sum_traits<double>
{
    typedef double sum_type;
    //    2)
    static sum_type zero()
    {
        return 0.0;
    }
};

template <typename Traits, typename T>
typename Traits::sum_type sum(T *begin, T *end)
{
    typedef typename Traits::sum_type sum_type;
//    2)
    sum_type total = sum_traits<T>::zero();
    while (begin != end)
    {
        total += *begin;
        begin++;
    }
    return total;
}

template <typename T>
typename sum_traits<T>::sum_type sum(T *begin, T *end)
{
    return sum<sum_traits<T>, T>(begin, end);
}

struct char_sum
{
    typedef char sum_type;
};

int main() {
//1)
    char name[] = "$ $ $";
    int length = strlen(name);

    cout << (int)sum(name, &name[length]) << endl;

    cout << (int)sum<char_sum>(name,&name[length]) << endl;

    cout << (int)sum<char>(name,&name[length]) << endl;
}