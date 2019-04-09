#include <iostream>
using std::cin;
using std::cout;

#include <list>
using std::list;

#include <vector>

#include <iterator>
#include <forward_list>
using std::iterator_traits;
using std::forward_iterator_tag;
using std::random_access_iterator_tag;


template <typename Iter>
int operacja_impl(Iter i, forward_iterator_tag)
{
    cout << "Iterator jednokierunkowy.\n";
    return 1;
}

// RozwiÄ�zanie zadania polegaĹ�o na dodaniu poniĹźszej funkcji.
template <typename Iter>
int operacja_impl(Iter i, std::bidirectional_iterator_tag)
{
    cout << "Iterator dwukierunkowy.\n";
    return 44;
}

template <typename Iter>
int operacja_impl(Iter i, random_access_iterator_tag)
{
    cout << "Iterator o swobodnym dostepie.\n";
    return 2;
}

template <typename Iter>
inline int operacja(Iter i)
{
    return operacja_impl(i,
                         typename iterator_traits<Iter>::iterator_category());
}


int main()
{
    std::forward_list<float> fl;
    operacja(fl.begin());

    list<int> l;
    operacja(l.begin());

    int t[3];
    operacja(t);

    return 0;
}