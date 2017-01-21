#ifndef STUDENT_H
#define STUDENT_H

#include <string>

#ifdef major
#undef major
#endif

class Student
{
    long id;
    std::string firstName;
    std::string lastName;
    char gender;
    std::string major;
    float gpa;

public:
    Student() ; //Constructor
    Student( const Student & ) ; //Copy Constructor
    ~Student() ; //Destructor
};

#endif // STUDENT_H 
