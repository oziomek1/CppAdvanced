//
// Created by Wojciech Ozimek on 13/04/2019.
//

#ifndef ZAAWANSOWANY_CPP_KOLOR_H
#define ZAAWANSOWANY_CPP_KOLOR_H

#include "string"

class Kolor
{
private:
    int _red;
    int _green;
    int _blue;
public:
    Kolor(int red, int green, int blue) :
            _red(red), _green(green), _blue(blue) { }

    std::string zwrocKolor(std::string nazwaKoloru)
    {
        if (nazwaKoloru.compare("zielony")) {
            return "(0, 255, 0)";
        } else if (nazwaKoloru.compare("green")) {
            return "(0, 255, 0)";
        } else {
            throw std::runtime_error("Nieznany kolor");
        }
    }
};

#endif //ZAAWANSOWANY_CPP_KOLOR_H
