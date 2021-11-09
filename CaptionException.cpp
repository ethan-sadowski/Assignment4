//
// Created by steve on 11/9/2021.
//
#include <iostream>
#include <exception>
using namespace std;

class CaptionException: public exception {
public:
    const char* what() const noexcept {
        return "A caption must be entered";
    }
};
