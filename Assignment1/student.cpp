#include "student.h"

#include <iomanip> 
using namespace std;

Student::Student(int id, const std::string & firstName, const std::string & lastName, char gender, const std::string & major, double gpa) :
    id(id), firstName(firstName), lastName(lastName), 
    gender(gender), major(major), gpa(gpa)
{}


Student::Student(const Student &other) : 
    id(other.id), firstName(other.firstName), lastName(other.lastName),
    gender(other.gender), major(other.major), gpa(other.gpa) 
{}


Student::~Student() {}

// Make Student class printable by ostream objects
std::ostream & operator<<(std::ostream &os, const Student & s) {
    
    os  << left << setw(10) << s.getFirstName() << setw(10) << s.getLastName() 
        << "'" << s.getGender() << "' #" << setw(10) << s.getId() 
        << "Program:" << setw(10) << s.getMajor() << " GPA:" << s.getGpa();

    return os;
}


                                      
