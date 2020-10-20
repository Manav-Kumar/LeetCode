#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class Vehicle{
private:
	int maxSpeed;
	
protected:
	int numTyres;
public:
	string color;
	Vehicle(){
		cout << "Vehicle's default Constructor\n";
	}

	Vehicle(int z){
		cout << "Vehicle's parameterized Constructor\n";
		maxSpeed = z;
	}
	void print(){
		cout << "Vehicle \n";
	}
	~Vehicle(){
		cout << "Vehicle's default Destructor\n";
	}
};

class Car: public Vehicle{
protected:
public:
	int numGears;
	Car(int x,int y): Vehicle(x) {//	Default Parent class constructor is called implicitly, to call parameterized,
		//	need to call in initialization list so that before entering Car constructor's we can call it's 
		//	parent class constructor
		cout << "Car's parameterized Constructor\n";
		numGears = y;
	}
	void print(){
		cout << "Car: \n";
	}

	~Car(){
		cout << "Car's default Destructor\n";
	}
};

class HondaCity: public Car{
protected: 
public:

	HondaCity(int x,int y): Car(x,y) {
		cout << "Honda City default Constructor\n";
	}
	void print(){
		cout << "Honda City\n";
	}
	~HondaCity(){
		cout << "Honda City Destructor\n";
	}
};


class Teacher{
public:
	string name;
	int age;
	Teacher(){
		cout << "Teacher default constructor\n";
	}
	void print(){
		cout << "Teacher \n";
	}
};

class Student{
public:
	string name;
	Student(){
		cout << "Student default constructor\n";
	}
	void print(){
		cout << "Student \n";
	}
};

class TA: public Teacher, public Student{
public:
	TA(){
		cout << "TA default constructor\n";
	}
	void print(){
		cout << "TA \n"; 
	}
};


int main(){
	// cout << "Size of Vehicle Class: " << sizeof(Vehicle) << "\n";
	// Vehicle v1;
	// cout << sizeof(v1) << "\n";
	// cout << "Size of Car Class: " << sizeof(Car) << "\n";
	// Car c(4,5);
	// cout << sizeof(c) << "\n";
	// c.numGears = 6;
	// c.color = "Black";
	// c.print();
	// HondaCity h(2,3);

	// HondaCity h(4,5);
	// h.print();
	// h.Car::print();
	// h.Vehicle::print();
	// h.Car::Vehicle::print();


	TA a;
	a.print();
	a.Teacher::print();
	a.Student::print();
	a.Teacher::name = "Manav";
	

	return 0;
}


