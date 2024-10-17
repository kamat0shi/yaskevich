#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

class Person {
public:
    virtual ~Person() = default; // Деструктор по умолчанию

    // Чистая виртуальная функция для получения роли
    virtual std::string getRole() const = 0;

    // Виртуальная функция для отображения информации
    virtual void displayInfo() const {
        std::cout << "Person Info" << std::endl;
    }
};

#endif