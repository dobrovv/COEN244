#include <iostream>
#include <iomanip> 

#include "student.h"

using namespace std;



void main() {
    
    // Test 1 expected result: 
    // Unknown   Unknown   '?' #0         Program:?          GPA:0
    Student s;
    cout << s << endl;


    // Test 2 expected result: 
    // Ted       Tedson    'M' #25493056  Program:COEN       GPA:3.6 
    s.setFirstName("Ted").setLastName("Tedson").setGender('M').setMajor("COEN");
    s.setId(25493056).setGpa(3.6);
    cout << s << endl;


    // Test 3 expected result: 
    // Ted       Johnson   'M' #25493057  Program:COEN       GPA:3.6
    Student s2(s);
    s2.setLastName( s2.getLastName().replace(0,3, "John") );
    s2.setId( s2.getId() + 1 );
    cout << s2 << endl;

	return 0;
}
