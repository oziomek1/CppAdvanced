//
// Created by Wojciech Ozimek on 09/03/2019.
//

#ifndef ZAAWANSOWANY_CPP_SELLER_HPP
#define ZAAWANSOWANY_CPP_SELLER_HPP

#include<iostream>
#include <string>
#include "Employee.hpp"

class Seller: public Employee {
protected:
    float _bonusRatio;
    int _newClientsNumber;
public:
    Seller(int workWeek, int salary, float bonusRatio, int newClientsNumber)
            : Employee(workWeek, salary), _bonusRatio(bonusRatio), _newClientsNumber(newClientsNumber) {}

    float getBonusRatio() const {
        return _bonusRatio;
    }

    int getNewClients() const {
        return _newClientsNumber;
    }

    virtual void payBonus() override {
        std::cout << "Seller bonus set to " << (1 * static_cast<float>(_newClientsNumber) / 2) * _bonusRatio * (_workWeek / 160) * _salary << std::endl;
    }
};

#endif //ZAAWANSOWANY_CPP_SELLER_HPP
