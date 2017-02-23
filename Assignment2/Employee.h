#ifndef EMPLOYEE_GUARD
#define EMPLOYEE_GUARD

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

class Employee {

protected:
	int id;
	string name;
	string position;
	int seniority;

public: 
	Employee() 
        : id(0), name("N/A"), position("N/A"), seniority(0) {}

	Employee(int id, string name, string position, int seniority) 
        : id(id), name(name), position(position), seniority(seniority) {}

	Employee(const Employee &other)
        : id(other.id), name(other.name), position(other.position), seniority(other.seniority) {}

	int getID() const {return id;}
    string getName() const {return name;}
    string getPosition() const {return position;}
    int getSeniority() const {return seniority;}

    void setID(int id) {this->id = id;}
    void setName(const string & name) {this->name = name;}
    void setPosition(const string & position) {this->position = position;}
    void setSeniority(int seniority) {this->seniority = seniority;}

    virtual void print() const {cout << "Id: " << id << " Name: " << name << " Position: " << position << " Seniority: " << seniority; }

	virtual ~Employee() {};
};

class Researcher : public Employee{

private:
	string title;
	string expertise;

public:
    Researcher() 
        : Employee(), title("N/A"), expertise("N/A") {}

    Researcher(int id, string name, string position, int seniority, string title, string expertise) 
        : Employee(id, name, position, seniority), title(title), expertise(expertise) {}

    Researcher(const Researcher & other)
        : Employee(other), title(other.title), expertise(other.expertise) {}
          
    string getTitle() const {return title;}
    void setTitle(const string & title) {this->title = title;}
    
    string getExpertise() const {return expertise;}
    void setExpertise(const string & expertise) {this->expertise = expertise;}

    virtual void print() const {Employee::print(); cout << " Title: " << title << " Expertise: " << expertise; }

    virtual ~Researcher() {}

};

class Administrator : public Employee {

private:
	int num_employee;

public:

	Administrator() 
        : Employee(), num_employee(0) {}

    Administrator(int id, string name, string position, int seniority, int num_employee) 
        : Employee(id, name, position, seniority), num_employee(num_employee) {}

    Administrator(const Administrator & other)
        : Employee(other), num_employee(other.num_employee) {} 
          
    int getEmployeesNumber() const {return num_employee;}
    void setEmployeesNumber(int num_employee) {this->num_employee = num_employee;}
    
    virtual void print() const {Employee::print(); cout << " Number of Employees: " << num_employee; }

	virtual ~Administrator(){}
};


class Company {

private:
	string company_name;
	string address;
	vector<Employee> array;

public:
	Company() 
        : company_name("N/A"), address("N/A"), array() {}

	Company(string name, string address, const vector<Employee> & employees) 
        : company_name(name), address(address), array(employees) {}

	Company(const Company & other)
        : company_name(other.company_name), address(other.address), array(other.array) {}

	~Company(){}

    size_t size() const { return array.size(); }
    Employee & operator[](size_t i) {return array[i];}
    
    string getName() const {return company_name;}
    void setName(const string & name) {this->company_name = name;}
    
    string getAddress() const {return address;}
    void setAddress(const string & address) {this->address = address;}
    

	bool hasID(int id) const {
		for ( size_t i = 0; i < size(); ++i )
			if (id == array[i].getID() )
				return true;
		return false;
	}

	void addEmployee(const Employee & e) {
		if ( hasID(e.getID()) == false )
			array.push_back(e);
		else
			cout << "The employee already exists in the list. " << endl;
	}

	void removeEmployee(int id) {
		
        // find the index of the employee if he exists
        int ix = -1;
		for ( size_t i = 0; i < array.size(); i++)
			if ( array[i].getID() == id )
				ix = i;

        // if the employee is in the company list
        // remove him from the list and move succeding elements
        // one position back
		if ( ix != -1 ) { 
			cout << "The employee exists already exists in the list" << endl;
			for (size_t i = ix; i < array.size() - 1; ++i)
				array[i] = array[i + 1];
			array.pop_back();
		}

	}

    vector<string> getEmployeeNames() const {
        vector<string> names;
        for ( auto & e : array )
            names.push_back(e.getName());
        return names;
    }

	void print() const { cout << "Company Name: " << company_name << " Address: " << address; }

};

#endif // !EMPLOYEE_GUARD
