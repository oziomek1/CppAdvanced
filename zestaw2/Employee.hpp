//
// Created by Wojciech Ozimek on 09/03/2019.
//

#ifndef ZAAWANSOWANY_CPP_GASSTATION_HPP
#define ZAAWANSOWANY_CPP_GASSTATION_HPP

#include <string>

class Employee
{
protected:
    float _workWeek;
    float _salary;
public:
    Employee(int workWeek, int salary)
            : _workWeek(workWeek), _salary(salary) {};

    float get_workWeek() const
    {
        return _workWeek;
    }

    float get_salary() const
    {
        return _salary;
    }

    float getPayPerHour()
    {
        return _salary / _workWeek;
    }

    virtual void payBonus() = 0;

    virtual ~Employee() {};
};

#endif //ZAAWANSOWANY_CPP_GASSTATION_HPP
