#include "Employee.h"


int main(){
    Employee e( 1, "Name1", "Position1", 12);
    Administrator a(2, "Name2", "Admin", 12, 8);
    Employee e3(a);
    e3.setID(3);

    e.print();
    cout << endl;
    a.print();
    cout << endl;
    e3.print();

    vector<Employee> es;
    es.push_back(e);
    es.push_back(a);
    es.push_back(e3);

    Company c("Company Name", "Address", es);
    c.removeEmployee(2);
    c.print();
    cout << endl;
    
    for ( size_t i = 0; i < c.size(); ++i ) {
        c[i].print();
        cout << endl;
    }

}
