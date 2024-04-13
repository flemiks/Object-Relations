#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>

using namespace std;

class Fruit {
private:
	string name;
	string color;
public:
	Fruit(string name, string color): name(name), color(color){}

};

class Apple: public Fruit {
private:
	double filer;
public:
	Apple(string name, string color, double filer)  : Fruit(name, color), filer(filer) {}
	
};

class Banana : public Fruit {

public:
	Banana(string name, string color) : Fruit(name, color) {}

};

/*int main()
{
 
}*/
