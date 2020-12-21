#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>

using namespace std;

class A{
public:
	A() {cout << "A\n";}
};
class B{
public:
	B() {cout << "B\n";}
	B(int a) {cout << "Parameterized\n";}
};
class C{
public:
	C() {cout << "C\n";}
};
class D{
public:
	D() {cout << "D\n";}
};
class E: D{
public:
	E() {cout << "E\n";}
};

class F: A, B{
public:
	C c; D d; E e;
	F(): B(23), A(), d(), c(), e() {cout << "F\n";}
};

int fun(int arg[][3]){
	cout << "Start Printing array elements\n";
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++) cout << arg[i][j] << " ";
		cout << "\n";
	}
	return 0;
}

int main(){
	int a[5] = {1,2,3,4,5};
	cout << a << " " << &a << "\n";
	// int *ptr;
	// int *ptr2;
	// ptr = (int*)(&a + 1);
	// ptr2 = (int*)(&a);
	// cout << (*ptr2) << "\n";
	int *ptr;
	ptr = (a + 1);
	cout << ptr << " " << *(ptr - 1) << "\n";
	int b[2][3] = {{1,2,3}, {4,5,6}};
	cout << b << " " << (b + 1) << " " << &b << " " << (&b + 1) << "\n";
	cout << fun(b) << "\n";

	cout << "Dynamically Allocated Array Printed\n";
	int **v = new int*[3];
	for(int i=0;i<3;i++){
		v[i] = new int[2];
		for(int j=0;j<2;j++){
			v[i][j] = 2*i + j;
			cout << v[i][j] << " ";
		}
		cout << "\n";
	}
	cout << sizeof(b) << "\n";
	cout << v << " " << (v + 1) << " " << *(*(v + 2) + 1) << "\n";
	
	for(int i=0;i<3;i++) delete []v[i];
	delete []v;
	return 0;
}



