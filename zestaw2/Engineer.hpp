//
// Created by Wojciech Ozimek on 09/03/2019.
//

#ifndef ZAAWANSOWANY_CPP_ENGINEER_HPP
#define ZAAWANSOWANY_CPP_ENGINEER_HPP

#include<iostream>
#include <string>
#include "Employee.hpp"

class Engineer: public Employee {
protected:
    float _bonusRatio;
public:
    Engineer(int workWeek, int salary, float bonusRatio)
            : Employee(workWeek, salary), _bonusRatio(bonusRatio)  {}

    float getBonusRatio() const
    {
        return _bonusRatio;
    }

    virtual void payBonus()
    {
        std::cout << "Engineer bonus set to " << _bonusRatio *  (_workWeek / 160) * _salary << std::endl;
    }

};

#endif //ZAAWANSOWANY_CPP_ENGINEER_HPP
