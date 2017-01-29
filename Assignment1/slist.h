#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include "student.h"
#include <vector>
#include <string>


class StudentList{
private:
	static const size_t LIST_SIZE = 150; // the maximum items in the list
	Student *items; // items will point to the dynamically allocated array
	size_t numItems; // the number of items currently in the list

public:
	StudentList(std::vector<Student> vs = std::vector<Student>());
	StudentList(const StudentList & other);

        size_t size() const { return numItems; }

	bool hasStudentId(int id) const;

	// Perform a case sensitive check
	bool hasStudentFirstName(const std::string & name) const;
	bool hasStudentLastName(const std::string & name) const;

        // Returns false if the list has reached its maximal capacity
        bool append(const Student & s);

	Student & at(size_t index);
	Student & operator[](size_t index);
        
        void printStudentNames() const;        

	~StudentList();

};

#endif // STUDENTLIST_H
