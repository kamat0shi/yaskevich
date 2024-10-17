#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

class Person {
public:
    virtual ~Person() = default; 

    virtual std::string getRole() const = 0;

    virtual void displayInfo() const {
        std::cout << "Person Info" << std::endl;
    }
};

#endif