#include <iostream>
using namespace std;

class Student{
	static int totalStu;
public:
	int roll, age;
	Student(){
		totalStu++;
	}

	static int getCount(){
		//	Here this keyword is not available
		return totalStu;
	}
};

int Student::totalStu = 0;

int main(){
	Student s1, s2, s3;
	cout << s1.getCount() << " " << s2.getCount() << "\n";
	//cout << Student::getCount() << "\n";
	return 0;
}
 
