#include "slist.h"
#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

int main() {
    vector<Student> sv;
    sv.push_back( Student(1, "Name1", "Fam1") );
    sv.push_back( Student(2, "Name2", "Fam2") );
    sv.push_back( Student(3, "Name3", "Fam3") );

    StudentList slist( sv );
    cout << slist.size() << endl;
    slist.printStudentNames();

    slist.append(Student(4, "Ted", "Tedson"));
    cout << slist.hasStudentId(4) << endl;
    cout << slist.hasStudentLastName("Tedson") << endl;
    cout << slist.hasStudentLastName("tEDson") << endl;

    cout << slist[3].getFirstName() << endl;
    
    try {
       slist.at(999999);
    } catch (out_of_range & range) {
        cout << range.what() << endl;
    }

    StudentList slist_copy(slist);
    slist_copy[0].setId(65);

    cout << slist[0] << endl;
    cout << slist_copy[0] << endl;

    return 0;
}
