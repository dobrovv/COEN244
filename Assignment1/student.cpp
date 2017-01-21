#include "student.h"

Student::Student() : 
    id(0), firstName("Unknown"), lastName("Unknown"), 
    gender('?'), major("?"), gpa(0.0)
{}

Student::Student(const Student &other) : 
    id(other.id), firstName(other.firstName), lastName(other.lastName),
    gender(other.gender), major(other.major), gpa(other.gpa) 
{}

Student::~Student()
{

}

