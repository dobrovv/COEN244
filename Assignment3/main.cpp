#include "set.h"
#include <iostream>

using namespace std;

int main() {

    int elems[] = { 1, 2, 3, 4, 5 };
    int size = 5;
    
    Set s1(elems, size);
    Set s2(nullptr, 0);

    cout << "Set::operator=" << endl;
    cout << (s2=s1) << endl;
    cout << "Set::operator==" << endl;
    cout << (s1==s2) << endl;
    cout << "Set::operator!=" << endl;
    cout << (s1!=s2) << endl;
    
    cout << "Set::operator[]" << endl;
    cout << (s1[0]=3) << endl << s1 << endl;

    cout << "Set::operator<" << endl;
    cout << (s1<s2) << endl;
    cout << "Set::operator>" << endl;
    cout << (s1>s2) << endl;
    cout << "Set::operator++" << endl;
    cout << (++s1) << endl;
    cout << "Set::operator--" << endl;
    cout << (--s1) << endl;

    cout << "operator>>" << endl;
    int arr[3] = {1,2,3};
    Set in(arr, 3);
    cin >> in;
    cout << endl << in << endl;
}
