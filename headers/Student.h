//
// Created by diogotvf7 on 28-10-2022.
//

#ifndef AED_TP1_STUDENT_H
#define AED_TP1_STUDENT_H

#include <ostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

#include "Class.h"
#include "Request.h"

class Class;

class Student {

public:
    /**
     * @brief Constructor for Student object;
     * @param code string for the Student's code which will be converted to an int;
     * @param name string for the Student's name;
     * @param status boolean that determines whether a Student has a special status or not (default is false);
     */
    Student(std::string code, std::string name, bool status = false);
    /**
     * @brief Get function for the Student's Code;
     * @return returns an int with the Student's Code;
     */
    int getCode() const;
    /**
     * @brief Get function for the Student's name;
     * @return returns a string with the Student's name;
     */
    std::string getName() const;
    /**
     * @brief Get function for the Student's Classes;
     * @return returns a list with all the Student's Classes;
     */
    std::vector<Class*> getClasses() const;
    /**
     * @brief Get function for the Student's Requests;
     * @return return a queue with all the Student's Requests;
     */
    std::queue<Request*> getRequests() const;
    /**
     * @brief Function that adds a Class to the Student's classes;
     * @param c the Class to be added;
     */
    void addClass(Class *c);
    /**
     * @brief Function that removes a Class from the Student's classes;
     * @param c the Class to be removed;
     */
    void removeClass(Class *c);
    /**
     * @brief Overload of operator== to check equality between Student objects;
     * @param s the right hand side Student;
     * @return return true if both Student objects have the same Student Code and Name, returns false otherwise;
     */
    bool operator==(const Student &s) const;
    /**
     * @brief Overload of operator<< to output Student's info;
     * @param os the output stream to which we want to output the Student's info;
     * @param s the Student that whose info we want to output;
     * @return returns a reference to the original output stream;
     */
    friend std::ostream& operator<<(std::ostream& os, const Student& s);

private:
    int code;
    std::string name;
    bool status;
    std::vector<Class*> classes;
    std::queue<Request*> requests;
};


#endif //AED_TP1_STUDENT_H
