//
// Created by Wojciech Ozimek on 13/04/2019.
//

#ifndef ZAAWANSOWANY_CPP_STATIC_TABLE_ALLOCATOR_H
#define ZAAWANSOWANY_CPP_STATIC_TABLE_ALLOCATOR_H

template<typename T,size_t N = 0> struct Static_table_allocator
{
    typedef T rep_type[N];
    void init(rep_type &,size_t) {};
    void expand_if_needed(rep_type &,size_t) {};
    void shrink_if_needed(rep_type &,size_t) {};
    void dealocate(rep_type &){};
    static size_t size() {return N;};
};

#endif //ZAAWANSOWANY_CPP_STATIC_TABLE_ALLOCATOR_H
