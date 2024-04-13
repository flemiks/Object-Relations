#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include "Date.h"

using namespace std;
int const SEC_IN_MINUTE = 60;
int const SEC_IN_HOUR = 3600;

//-----------Task1--------------

class Student {
private:
	string name;
	int age;
	string speciality;

public:
	Student() {};
	Student(string name, int age, string speciality) {
		setName(name);
		setAge(age);
		setSpeciality(speciality);
	};

	void setName(string name) {
		if (name.empty()) {
			throw invalid_argument("Name should not be empty");
		}
		this->name = name;
	}
	string getName() {
		return name;
	}
	void setAge(int age) {
		if (age < 18) {
			throw invalid_argument("Student should be older than 18");
		}
		this->age = age;
	}
	int getAge() {
		return age;
	}
	void setSpeciality(string speciality) {
		if (speciality.empty()) {
			throw invalid_argument("Name should not be empty");
		}
		this->speciality = speciality;
	}
	string getSpeciality() {
		return speciality;
	}
	void virtual print() {
		cout << "Name: " << name << " Age: " << age << " Speciality: " << speciality;
	}

};

class Aspirant : public Student {
private:
	string thesis;
public:
	Aspirant() = default;
	Aspirant(string name, int age, string speciality, string thesis) {
		setName(name);
		setAge(age);
		setSpeciality(speciality);
		setThesis(thesis);
	};
	void setThesis(string thesis) {
		if (thesis.empty()) {
			throw invalid_argument("Thesis title should not be empty");
		}
		this->thesis = thesis;
	}
	string getThesis() {
		return thesis;
	}
	void print() {
		Student::print();
		cout << " Thesis: " << thesis;
	}


};
//-----------Task2--------------

class Passport {
public:
	Passport() = default;
	Passport(string number, string name, Date birthDate) {
		setNumber(number);
		setName(name);
		setBirthDate(birthDate);
	}

	void setNumber(string number) {
		if (number.empty()) {
			throw invalid_argument("Number should not be empty");
		}
		this->number = number;
	}
	string getNumber() {
		return number;
	}
	void setName(string name) {
		if (name.empty()) {
			throw invalid_argument("Name should not be empty");
		}
		this->name = name;
	}
	string getName() {
		return name;
	}
	void setBirthDate(Date birthDate) {
		this->birthDate = birthDate;
	}
	Date getBirthDate() {
		return birthDate;
	}
	void virtual print() {
		cout << "Number: " << number << " Name: " << name << " Day of Birth: " << birthDate;
	}

private:
	string number;
	string name;
	Date birthDate;
};

class ForeignPassport : public Passport {
public:
	ForeignPassport() = default;
	ForeignPassport(string number, string name, Date birthDate, string numberForeign) {
		setNumber(number);
		setName(name);
		setBirthDate(birthDate);
		setNumberForeign(numberForeign);
		this->visaList = visaList;
	}
	void setNumberForeign(string numberForeign) {
		if (numberForeign.empty()) {
			throw invalid_argument("Number should not be empty");
		}
		this->numberForeign = numberForeign;
	}
	string geNumberForeign() {
		return numberForeign;
	}
	vector<string> getVisaList() {
		return visaList;
	}
	void addVisa(string newVisa) {
		this->visaList.push_back(newVisa);
	}
	void printVisa() {
		cout << " Visa List: ";
		for (string visa : visaList) {
			cout << visa << " : ";
		}
	}
	void print() {
		Passport::print();
		cout << " Number Foreign: " << numberForeign;
		printVisa();
	}

private:
	string numberForeign;
	vector<string> visaList;
};

//-----------Task3--------------

class Vehicle {
public:
	Vehicle() = default;
	Vehicle(int speed, int distance, int hourlyRate)  {
		setSpeed(speed);
		setDistance(distance);
		setHourlyRate(hourlyRate);
		setTime();
		setPrice();
	};
	void setSpeed(int speed) {
		if (speed <= 0) {
			throw invalid_argument("Speed should be more than 0");
		}
		this->speed = speed;
	}
	int getSpeed() {
		return speed;
	}
	void setDistance(int distance) {
		if (distance <= 0) {
			throw invalid_argument("Distnce should be more than 0");
		}
		this->distance = distance;
	}
	int getDistnce() {
		return distance;
	}
	void setHourlyRate(int hourlyRate) {
		if (hourlyRate <= 0) {
			throw invalid_argument("Houry Rate should be more than 0");
		}
		this->hourlyRate = hourlyRate;
	}
	int getHouryRate() {
		return hourlyRate;
	}
	void setTime() {
		time =static_cast<float> (distance) / speed;
		this->time = time;
	}
	void setPrice() {
		float hours = time / SEC_IN_HOUR;
		price = hours * hourlyRate;
		this->price = price;
	}
	void print() {
		cout << fixed << setprecision(2);
		cout << "Time: " << time << "Price: " << price << endl;
	}
private:
	int speed;
	int distance;
	int hourlyRate;
	float time;
	float price;
};

class Car : public Vehicle {
public:
	Car(int speed, int distance, int hourlyRate)
		: Vehicle(speed, distance, hourlyRate)
	{ };
};

class Bike :public Vehicle {
public:
	Bike(int speed, int distance, int hourlyRate)
		: Vehicle(speed, distance, hourlyRate)
	{ };
};

class Cart : public Vehicle {
public:
	Cart(int speed, int distance, int hourlyRate)
		: Vehicle(speed, distance, hourlyRate)
	{ };
};


int main()
{
	Aspirant aspirant1("Nikolay", 25, "IT", "C++");
	aspirant1.print();
	cout << endl;
	ForeignPassport fPassport("OM56564323", "Shevchenko Taras Hrihorovich ", Date(9, 3, 1814), " 656665643");
	fPassport.addVisa("Siberia");
	fPassport.print();
	cout << endl;
	Car car1(60, 1000, 25);
	car1.print();
	Bike bike1(30, 1000, 10);
	bike1.print();
	Cart cart1(10, 1000, 3);
	cart1.print();

}