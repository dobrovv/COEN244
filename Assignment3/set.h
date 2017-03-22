#ifndef SET_GUARD
#define SET_GUARD

#include <iostream>

using namespace std;

class Set {
public:
    Set(int[], int);    // default constructor
    Set(const Set&);    //copy constructor
    ~Set();     //destructor
    inline int getSize() const {return size;}; // return size

    bool contains(int element) const ;
    bool subsetOf(const Set& other) const;
    
    Set& operator=(const Set& other);

    bool operator==(const Set& other) const;
    bool operator!=(const Set&other) const;
    bool operator<(const Set& other) const;
    bool operator>(const Set& other) const;


    Set& operator++();
    Set operator++(int);
    Set& operator--();
    Set operator--(int);

    int operator[](size_t index) const;
    int& operator[](size_t index);

private:
    int size; // set size
    int *ptr; //pointer to first element of set

};

ostream& operator<<(ostream &out, const Set & other);
istream& operator >> (istream& in, Set& other);


#endif // !SET_GUARD
