#include <iostream>
#include <stack>
#include <queue>
using namespace std;

class Convence{
public:
	
	Convence(int z){
		cout << "Convence parameterized constructor\n";
		cout << z << "\n";
	}
	~Convence(){
		cout << "Convence destructor\n";
	}
};

class Vehicle: virtual public Convence{
	int maxSpeed;
protected:
	int numTyres, numGears;
public:
	Vehicle(): Convence(12){
		cout << "Vehicle's constructor\n";
	}
	Vehicle(int z): Convence(14){
		cout << "Vehicle's parameterized constructor\n";
		cout << z << "\n";
		maxSpeed = z;
	}
	void print(){
		cout << "Vehicle\n";
	}
	~Vehicle(){
		cout << "Vehicle's destructor\n";
	}
	string color;
};

// class Car:virtual public Vehicle{
// public:
// 	int numGears;
// 	Car(): Vehicle(){
// 		cout << "Car's constructor\n";
// 	}
// 	void print(){
// 		cout << "Car\n";
// 	}
// 	~Car(){
// 		cout << "Car's destructor\n";
// 	}
// };

class Truck:virtual public Vehicle{
public:
	Truck(): Convence(2), Vehicle(1){
		cout << "Truck's constructor\n";
	}
	~Truck(){
		cout << "Truck's destructor\n";
	}
	
};

class TATA: public Truck{
public:
	TATA(): Convence(90), Vehicle(89){
		cout << "TATA's constructor\n";
	}
	~TATA(){
		cout << "TATA's destructor\n";
	}
};

// class Bus: public Car, public Truck{
// public:
// 	Bus(): Vehicle(4){
// 		cout << "Bus's constructor\n";
// 	}
// 	~Bus(){
// 		cout << "Bus's destructor\n";
// 	}
// };
//	Diamond Problem

//	VIRTUAL INHERITANCE
//		This concept is introduced to avoid multiple copies of single class during inheritance, a perfect eg
//		in case of diamond inheritance problem, usually child class can only call the constructor of immediate 
//		parent but in this case if any class inherited virtually then it becomes the duty of child class to call
//		its parent class then it could be immediate or not. 

//	In case there is class which has been inherited virtually so as to avoid it's multiple copies, its constructor
//		would called in begining before others may be by the derived class who is object is being created and it
//		is at very several layers below others.

int main(){
	// Bus b;//	So here it is found that twice constructor and destructor has been called for Class Vehicle
	// //	It means 2 copies of Vehicle has been made, waste
	// b.print();
	// b.Car::print();
	// b.Truck::print();
	TATA t;

	return 0;
}






