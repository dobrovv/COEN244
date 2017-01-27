#include "slist.h"
#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<Student> sv;
	sv.push_back( Student(1, "Ted", "Tedson") );
	
	StudentList sl = sv;
	sl.printStudentNames();
	
	return 0;
}
