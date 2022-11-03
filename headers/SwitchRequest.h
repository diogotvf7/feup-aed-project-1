//
// Created by diogotvf7 on 03-11-2022.
//

#ifndef AED_TP1_SWITCHREQUEST_H
#define AED_TP1_SWITCHREQUEST_H

#include "Request.h"
#include "Student.h"
#include "Class.h"
#include "Slot.h"

class SwitchRequest : public Request {

public:
    /**
     * @brief Constructor for the SwitchRequest class;
     * @param student pointer to the Student who placed the request;
     * @param current pointer to  the Class the Student want to leave;
     * @param intended pointer to  the Class the Student wants to join;
     */
    SwitchRequest(Student *s, Class *current, Class *intended);
    /**
     * @brief Get function for the SwitchRequest's Student pointer;
     * @return returns a pointer to the Student who placed the request;
     */
    Student *getStudent() const;
    /**
     * @brief Get function for the SwitchRequest's current Class pointer;
     * @return returns a pointer to the Class the Student is in currently;
     */
    Class *getCurrentClass() const;
    /**
     * @brief Get function for the SwitchRequest's intended Class pointer;
     * @return returns a pointer to the Class the Student wants to join;
     */
    Class *getIntendedClass() const;
    /**
     *
     * @return
     */
    bool isPossible() const;
private:
    Student *student;
    Class *current;
    Class *intended;
};

#endif //AED_TP1_SWITCHREQUEST_H