//
// Created by Wojciech Ozimek on 13/04/2019.
//

#ifndef ZAAWANSOWANY_CPP_EXPANDABLE_NEW_ALLOCATOR_H
#define ZAAWANSOWANY_CPP_EXPANDABLE_NEW_ALLOCATOR_H

template <typename T, size_t N> struct Expandable_new_allocator
{
    typedef T * rep_type;
    size_t _size;
    void init(rep_type &rep, size_t n)
    {
        _size = n;
        rep = new T[_size];
    };
    void expand_if_needed(rep_type & rep, size_t top)
    {
        if (top == _size){
            _size *= 2;
            T *tmp = new T[_size];
            std::copy(rep, &rep[top], tmp);
            delete [] rep;
            rep = tmp;
        }
    };
    void shrink_if_needed(rep_type &size_t) {};
    void dealocate(rep_type &rep)
    {
        delete [] rep;
    };
    size_t size() const
    {
        return _size;
    }
};

#endif //ZAAWANSOWANY_CPP_EXPANDABLE_NEW_ALLOCATOR_H
