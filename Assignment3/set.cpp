#include "set.h"

Set::Set(int arr[], int num)
{
    size = num;
    ptr = new int[size];

    for ( size_t i =  0 ; i < size; ++i ) 
        ptr[i] = arr[i];
}

Set::Set(const Set &other)
{
    size = other.size;
    ptr = new int[size];
   
    for ( size_t i =  0 ; i < size; ++i ) 
        ptr[i] = other.ptr[i];
}

Set::~Set()
{
    delete[] ptr;
}

bool Set::contains(int element) const {
    for ( size_t i =  0 ; i < size; ++i ) 
        if ( ptr[i] == element )
            return true;
    return false;
}

bool Set::subsetOf(const Set& other) const {
    for ( size_t i =  0 ; i < size; ++i ) 
        if ( !other.contains(ptr[i]) )
            return false;
    return true;
}

Set & Set::operator=(const Set & other)
{
    if ( size != other.size ) {
        delete[] ptr;

        size = other.size;
        ptr = new int[size];
    }

    for ( size_t i = 0; i < size; ++i) 
        ptr[i] = other.ptr[i];

    return *this;
}

bool Set::operator==(const Set & other) const
{
    if ( size != other.size ) 
        return false;

    for ( size_t i = 0; i < size; ++i ) {
        if ( ptr[i] != other.ptr[i] )
            return false;
    }

    return true;

}

bool Set::operator!=(const Set & other) const 
{
    return !( *this == other );
}

bool Set::operator<(const Set& other) const 
{
    int sum_this = 0, sum_other = 0;

    for ( size_t i = 0; i < size; ++i) 
        sum_this +=  ptr[i];

    for (size_t i{ 0 }; i < other.size; ++i) 
        sum_other += other.ptr[i];
    
    return sum_this < sum_other;
}

bool Set::operator>(const Set& other) const 
{
    return other < *this;
}


Set & Set::operator++()
{
    for ( size_t i = 0; i < size; ++i)
        ++ptr[i];
    return *this;
}


Set Set::operator++(int)
{
    Set tmp(*this);
    ++(*this);
    return tmp;
}

Set & Set::operator--()
{
    for ( size_t i{ 0 }; i < size; ++i ) 
        --ptr[i]; 
    return *this;
}

Set Set::operator--(int)
{
    Set tmp(*this);
    --(*this);
    return tmp;
}

int Set::operator[](size_t index) const
{
    return ptr[index];
}

int & Set::operator[](size_t index)
{
    return ptr[index];
}

ostream& operator<<(ostream& out, const Set& s) 
{    
    for ( size_t i = 0; i < s.getSize(); ++i) {
        if ( (i != 0) && (i%5 == 0) )
            out << "\n";
        out << s[i] << (i==s.getSize()-1?"":",");
    }
    return out;
}

istream& operator >> (istream& in, Set& s) 
{
    for ( size_t i = 0; i < s.getSize(); ++i) 
        in >> s[i];
    
    return in;
}
