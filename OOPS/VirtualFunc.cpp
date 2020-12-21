#include <iostream>
#include <queue>
#include <stack>
using namespace std;

//	Any Class containing atleast one pure virtual fn is called ABSTRACT CLASS
class Vehicle{
public:
	int b;
	virtual void print() = 0;//	syntax for defining PURE VIRTUAL FUNCTION
};

class Car: public Vehicle{
public:
	void print(){
		cout << "Car\n";
	}
	void temp(){
		cout << "Temp Car\n";
	}
};


//	Virtual can be added to only non static member functions
class Employee{
public:
	int b = 90;
	virtual void print(){
		cout << "Employee\n";
	}
	void temp(){
		cout << "Employee temp\n";
	}
	
};

class HR:public Employee{
public:
	int b=3, a = 89;
	void print(){
		cout << "HR\n";
	}
};

int main(){
	Employee e;
	HR h;
	e.print();
	h.print();
	Employee *ee = new Employee();
	Employee *hh = new HR();
	ee->print();
	hh->print();
	//	Base Class Pointer can call the Child Class Functions
	Vehicle *v = new Car();
	v->print();
	return 0;	
}



