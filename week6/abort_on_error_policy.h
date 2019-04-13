//
// Created by Wojciech Ozimek on 13/04/2019.
//

#ifndef ZAAWANSOWANY_CPP_ABORT_NO_ERROR_POLICY_H
#define ZAAWANSOWANY_CPP_ABORT_NO_ERROR_POLICY_H

struct Abort_on_error_policy
{
    static void check_push(size_t top, size_t size)
    {
        if (top >= size)
        {
            std::cerr << "full stack for push: aborting" << std::endl;
            abort();
        }
    };
    static void check_pop(size_t top)
    {
        if (top == 0)
        {
            std::cerr << "empty stack for pop: aborting" << std::endl;
            abort();
        }
    };
    static void check_top(size_t top)
    {
        if (top == 0)
        {
            std::cerr << "empty stack for top: aborting" << std::endl;
            abort();
        }
    };
};

#endif //ZAAWANSOWANY_CPP_ABORT_NO_ERROR_POLICY_H
