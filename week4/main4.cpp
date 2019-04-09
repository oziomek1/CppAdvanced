//
// Created by Wojciech Ozimek on 26/03/2019.
//

#include <iostream>

using namespace std;

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

template <typename II>
typename sum_traits<typename iterator_traits<II>::value_type>::sum_type
sum(II begin, II end)
{
    typedef typename iterator_traits<II>::value_type value_type;
    typedef typename sum_traits<value_type>::sum_type sum_type;
    sum_type total = sum_traits<value_type>::zero();
    while (begin != end)
    {
        total += *begin;
        begin++;
    }
    return total;
}

int main() {
//1)
    char name[] = "$ $ $";
    int length = strlen(name);

    cout << sum(name, &name[length]) << endl;


}