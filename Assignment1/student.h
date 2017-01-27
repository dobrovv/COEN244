#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <ostream>

#ifdef major
#undef major //major was defined as a macro in gcc (Ubuntu 5.4.0)
#endif



class Student
{
    int id;
    std::string firstName;
    std::string lastName;
    char gender;
    std::string major;
    double gpa;

public:
    Student(int id = 0, const std::string & firstName = "Unknown", const std::string & lastName = "Unknown", char gender='?', const std::string & major = "?", double gpa = 0.0);  // Default Constructor
    Student( const Student & ); //Copy Constructor
    ~Student(); //Destructor

	/* Getters */
    int getId() const { return id; } 
	std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    char getGender() const  { return gender; }
    std::string getMajor() const { return major; }

	/* Setters */
    // All setters return a reference to 'this' to allow  method chainig
    Student& setId(int id) { this->id = id; return *this; }
    Student& setFirstName(const std::string &firstName) { this->firstName = firstName; return *this; }
    Student& setLastName(const std::string &lastName) { this->lastName = lastName; return *this; }
    Student& setGender(char gender) { this->gender = gender; return *this; }
    Student& setMajor(const std::string & major) { this->major = major; return *this;}

    double getGpa() const { return gpa; }
    Student& setGpa(double gpa) { this->gpa = gpa; return *this; }

};

// Make Student class printable by ostream objects
std::ostream & operator<<(std::ostream &os, const Student & s);



#endif // STUDENT_H 
