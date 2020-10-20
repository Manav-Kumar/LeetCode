#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <stack>
#include <unordered_map>
#include <set>
#include <cmath>
#include <math.h>
#include <unordered_set>
#include <deque>
using namespace std;


class Student{
	int age;
	int rollno;
public:
	void display(){
		cout << age << " " << rollno << "\n";
	}
	//	Default Constructor
	Student(){
		//	Can't make explicitly defined constructor to be private otherwise object won't be able	
		//		to call
		cout << "Default Constructor is called\n";
	}
	Student(int r){
		cout << "Constructor 2 called! \n";
		rollno = r;
	}
	Student(int age,int rollno){
		cout << "Constructor 3 called! \n";
		this->age = age;
		this->rollno = rollno;
	}
};

class Details{
	int *a;
	int age;
public:
	Details(){
		age = -1;
	}
	Details(int b,int c){
		a = new int;
		*a = b;
		age = c;
	}
	void setA(int b){
		*a = b;
	}
	void display(){
		cout << *a << " " << age << "\n";
	}
};

class Fraction{
	public:
	int numerator, denominator;
public:
	Fraction(){
		numerator = 2,  denominator = 34;
		numerator = 90;
	}
	Fraction(int n,int d);
	// Fraction(int n,int d){
	// 	cout << "Parametreized Constructor is called\n";
	// 	numerator = n;
	// 	denominator = d;
	// }
	void simplify(){
		int gcd = 1;
		for(int i=1;i<=min(numerator, denominator);i++){
			if(numerator%i == 0 && denominator%i == 0) gcd = i;
		}
		numerator /= gcd;
		denominator /= gcd;
	}
	void add(Fraction const &f2) {
		int lcm = denominator * f2.denominator;
		int x = lcm/denominator;
		int y = lcm/f2.denominator;
		int num = lcm*x + lcm*y;
		numerator = num;
		denominator = lcm;
		simplify();
	}

	void multiply(Fraction const &f2){
		numerator *= f2.numerator;
		denominator *= f2.denominator;
		simplify();
	}

	void print() const{
		cout << this->numerator << " / " << denominator << "\n";
	}
	int getnumerator() const {
		return numerator;
	}
	
	int getdenominator() const;
	void setNumerator(int n){//	Applying constant to this fnc throws error, as it is changing the
		//	properties for this objects attributes 
		numerator = n;
	}
	void setDenominator(int d){
		denominator = d;
	}


	~Fraction(){
		cout << "Destructor is called\n";
	}
};

//	Defining Functions Outside of class, provided it is already declared in class before
Fraction::Fraction(int n,int d){
	cout << "Parametreized Constructor is called\n";
	numerator = n,denominator = d;
}

int Fraction::getdenominator() const{
	return denominator;
}

int main(){
	//	For Every object only single constructor will be called and that it also at the time of it's
	//		creation.
	// Student s1;
	// cout << sizeof(s1) << "\n";
	// Student s2(10,20);
	// cout << "S2: ";
	// s2.display();
	// Student s3(s2);
	// cout << "S3: ";
	// s3.display();
	// Student* s4 = new Student(s3);
	// cout << "S4: ";
	// s4->display();
	// Details d(2,3);
	// Details d2;
	// d2 = d;
	// cout << "D: ";
	// d.display();
	// cout << "D2: ";
	// d2.display();
	// d2.setA(45);
	// cout << "After Setting D2 Only \n";
	// d2.display();
	// d.display();
	// Details d3(d2);
	// d3.setA(90);
	// cout << "After Setting D3 Only \n";
	// d3.display();
	// d2.display();
	// d.display();

	// Student k1;//	Constructor is called
	// Student k2(101);//	Constructor 2 is called
	// Student k3(10, 23);//	Constructor 3 is called
	// Student k4(k3);//	Copy Constructor is called
	// k1 = k2;//	Copy Assignment Operator is called
	// Student k5 = k4;//	Here ideally we break it into statements first default constri should be
	// //		called then copy asssignment operator But compiler optimizes it by direcly calling 
	// //		copy constructor
	// Student k6 = k5;//	Copy Constructor is Called

	//	Constant Functions
	Fraction f1(10,2);
	Fraction const f2(3,1);
	//	Constant Objects can call only constant functions(Functions that do not change objects 
	//		properties or it's attributes)
	cout << f2.getnumerator() << " " << f2.getdenominator() << "\n";
	int const i = 2;
	cout << i << "\n";
	return 0;
}



