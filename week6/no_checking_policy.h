//
// Created by Wojciech Ozimek on 13/04/2019.
//

#ifndef ZAAWANSOWANY_CPP_NO_CHECKING_POLICY_H
#define ZAAWANSOWANY_CPP_NO_CHECKING_POLICY_H

struct No_checking_policy
{
    static void check_push(size_t, size_t) {};
    static void check_pop(size_t) {};
    static void check_top(size_t) {};
};

#endif //ZAAWANSOWANY_CPP_NO_CHECKING_POLICY_H
