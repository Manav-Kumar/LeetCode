#include <iostream>
using namespace std;

class Truck;

class Bus{
public:
	void print(Truck &t);
};

class Tempo;


class Truck{
private:
	int x;

protected:
	int y;
public:
	int z;
	Truck(int x,int y,int z): x(x), y(y), z(z) {}
	void display() const{
		cout << x << " " << y << " " << z << "\n";
	}

	friend void Bus::print(Truck &t);//Can be declared below any type of access specifier
	friend class Tempo;//	We can make a whole class as a friend
};

void Bus::print(Truck &t){
	t.x = 90;
	t.y = 23;
	t.z = 12;
}

class Tempo{
public:
	void print(Truck t){
		cout << t.x << " " << t.y << "\n";
	}
	void tc(Truck t){
		cout << t.x << " " << t.y << " " << t.z << "\n";
	}
};


int main(){
	Bus b;
	Truck t(1,2,3);
	t.display();
	b.print(t);
	t.display();
	Tempo k;
	k.tc(t);
	return 0;
}

