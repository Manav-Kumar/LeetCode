#include <iostream>
using namespace std;

class DynamicArray{
	static int totalArrays;
public:
	int capacity, nextIdx;
	int *data;
	DynamicArray(){
		data = new int[5];
		nextIdx = 0;
	}

	void add(int ele){
		if(nextIdx == capacity){
			int *newdata = new int[2*capacity];
			for(int i=0;i<capacity;i++) newdata[i] = data[i];
			delete []data;
			data = newdata;
			capacity *= 2;
		}
		data[nextIdx] = ele;
		nextIdx++;
	}

	int getEle(int i) const {
		if(i >= 0 && i < nextIdx){
			return data[i];
		}
		return -1;
	}

	void updateValue(int i,int value){
		if(i < nextIdx){
			data[i] = value;
		}
		else if(i == nextIdx){
			add(value);
		}
		return ;
	}

	//	Copy Constructor
	DynamicArray(DynamicArray const &d2){
		//	Default Copy Constructor provides Shallow Copy so to avoid it we explicitly deep copy has been defined
		this->data = new int[d2.capacity];
		for(int i=0;i<d2.nextIdx;i++) this->data[i] = d2.data[i];
		this->nextIdx = d2.nextIdx;
		this->capacity = d2.capacity;
	}

	void operator=(DynamicArray const &d2){

		//	By default Copy assignment operator also provides Shallow Copy so to use Deep Copy, Assignment 
		//		Operator has been overloaded
		if(data) delete []data;
		this->data = new int[d2.capacity];
		for(int i=0;i<d2.nextIdx;i++) this->data[i] = d2.data[i];
		this->nextIdx = d2.nextIdx;
		this->capacity = d2.capacity;
	}
};

int DynamicArray::totalArrays = 0;


class Student{
public:
	char *name;
	int age, rollNo;;
	Student(int r,int a){
		rollNo = r;
		age = a;
	}

	int getRollNo() const {
		return rollNo;
	}

	Student(char *str){
		this->name = str;
	}


};



int main(){
	//	ShallowCopy Proven Below
	Student s1(101, 23);
	Student const s2(s1);
	cout << s2.getRollNo() << "\n";
	char name[] = "ma";
	Student s4(name);
	name[0] = 'n';
	cout << &(name[0]) << " " << &(s4.name[0]) << "\n";
	int *a = (int *)s4.name;
	int *b = (int *)name;
	cout << a << " " << b << "\n";
	int *c = (int *)(&name);
	int *d = (int *)&(s4.name);
	cout << c << " " << d << "\n";
	cout << *c << "\n";
	return 0;
}




