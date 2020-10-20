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
public:
	static int totalStudents;//	As these properties are static & belong to a class not object
	//	their initialization is always outside of a class
	int age, rollno;//	Bydefault properties are non static which belongs to an object
	Student(int a = 0,int r = 0){
		age = a, rollno = r;
		totalStudents += 1;
	}
	static int getTotalStudents(){//	Static functions can only access static properties whether 
		//	static data members	or static functions, nonstatic can't be accessed
		cout << "Inside Static Function\n";
		//cout << this << " ";// gives error
		return totalStudents;
	}
	void display();
};

//	Static members are always initialized outside of the class
int Student::totalStudents = 0;
void Student::display(){
	cout << age << " " << rollno << "\n";
}

//	Operator Overloading
class Fraction{
	int numerator, denominator;
public:

	Fraction(int n = 0,int d = 0) {
		numerator = n, denominator = d;
	}

	void simplify(){
		int gcd = 1;
		for(int i=1;i<=min(numerator, denominator);i++){
			if(numerator%i == 0 && denominator%i == 0) gcd = i;
		}
		numerator /= gcd;
		denominator /= gcd;
	}
	Fraction operator+(Fraction const &f2) const{
		int lcm = denominator*f2.denominator;
		int x = lcm/denominator;
		int y = lcm/f2.denominator;
		int num = x*numerator + y*f2.numerator;
		Fraction Fnew(num, lcm);
		Fnew.simplify();
		return Fnew;
	}

	Fraction operator*(Fraction const &f2) const{
		int num = numerator*f2.numerator;
		int den = denominator*f2.denominator;
		Fraction Fnew(num, den);
		Fnew.simplify();
		return Fnew;
	}

	bool operator==(Fraction const &f2) const{//	To allow constant objects to call this func
		return numerator == f2.numerator && denominator == f2.denominator;
	}

	//	PreIncrement, Unary Operator so no argument is required
	Fraction& operator++(){
		numerator += denominator;
		simplify();
		return (*this);
	}

	//	Post Increment
	Fraction operator++(int){
		Fraction temp = *this;
		numerator += denominator;
		simplify();
		temp.simplify();
		return temp;
	}

	Fraction& operator+=(Fraction const &f2){
		int lcm = denominator*f2.denominator;
		int x = lcm/denominator;
		int y = lcm/f2.denominator;
		int num = x*numerator + y*f2.numerator;
		numerator = num;
		denominator = lcm;
		simplify();
		return *this;
	}

	void print() const{
		cout << numerator << " / " << this->denominator << "\n";
	}
};

int main(){
	cout << sizeof(Student) << "\n";
	Student s1;
	cout << sizeof(s1) << "\n";
	cout << Student::totalStudents << " " << s1.totalStudents << "\n";
	cout << Student::getTotalStudents() << " " << s1.getTotalStudents() << "\n";

	Fraction f1(10,2);
	Fraction f2(15,4);
	Fraction f3 = f1 + f2;//	Object present before operator will be responsible for calling the 
	//	function or its address would be passed in this, and post operator object will be passed as
	//	argument
	Fraction f4 = f1*f2;
	f1.print();
	f2.print();
	f3.print();
	f4.print();
	return 0;
}



