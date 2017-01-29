#include "slist.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>
using namespace std;

const size_t StudentList::LIST_SIZE;

StudentList::StudentList(vector<Student> vs) {
	items = new Student[LIST_SIZE];
	numItems = min(LIST_SIZE, vs.size()); // ensure that at most 'LIST_SIZE' students are copied
	
	for ( size_t i=0; i < numItems; ++i )
		items[i] = vs[i];
}

StudentList::StudentList(const StudentList & other) {
    this->items = new Student[LIST_SIZE];
    this->numItems = other.numItems;

    for ( size_t i = 0; i < numItems; ++i ) {
        this->items[i] = other.items[i];
    }
    
}
	
	
void StudentList::printStudentNames() const {
	for ( size_t i = 0; i < numItems; ++i )
		cout << setw(3) << i << setw(15) << items[i].getFirstName() << setw(15) << items[i].getLastName() << endl;
}

bool StudentList::hasStudentId(int id) const {
	for ( size_t i = 0; i < numItems; ++i )
		if ( items[i].getId() == id )
			return true;
	
	return false;
}

bool StudentList::hasStudentFirstName(const string& name) const {
	
	for ( size_t i = 0; i < numItems; ++i )
		if ( items[i].getFirstName() == name )
			return true;

	return false;
}

bool StudentList::hasStudentLastName(const string& name) const {
	
	for ( size_t i = 0; i < numItems; ++i )
		if ( items[i].getLastName() == name )
			return true;

	return false;
}

Student & StudentList::at(size_t index) {
	if ( index >= numItems )
		throw std::out_of_range("StudentList::at(): index out of range");
	return items[index];
}

Student & StudentList::operator[](size_t index) {
	return items[index];
}

bool StudentList::append(const Student &s) {
    if ( numItems >= LIST_SIZE )
        return false;
    items[numItems++] = s;
    return true;
}

StudentList::~StudentList() {
	delete [] items;
}
	

