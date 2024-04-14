#define _USE_MATH_DEFINES

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

class Employer {
public:
    virtual ~Employer() {};

    void setName(const string& name) {
        if (name.empty()) {
            throw invalid_argument("Name should not be empty");
        }
        this->name = name;
    }
    const string& getName() const {
        return name;
    }
    void setAge(int age) {
        if (age < 18) {
            throw invalid_argument("Employer should be older than 18");
        }
        this->age = age;
    }
    int getAge() const {
        return age;
    }

    virtual void print() const = 0;

protected:
    string name;
    int age;
};

class Worker : public Employer {
public:
    Worker(const string& name, int age, const string& position) {
        setName(name);
        setAge(age);
        setPosition(position);
    }
    ~Worker() override = default;
    void setPosition(const string& position) {
        if (position.empty()) {
            throw invalid_argument("Position should not be empty");
        }
        this->position = position;
    }
    void print() const override {
        cout << "Name: " << name << " Age: " << age << " Position: " << position << endl;
    }

private:
    string position;
};

class Manager : public Employer {
public:
    Manager(const string& name, int age, int teamSize) {
        setName(name);
        setAge(age);
        setTeamSize(teamSize);
    }
    ~Manager() override = default;
    void setTeamSize(int teamSize) {
        if (teamSize <= 0) {
            throw invalid_argument("Team side should be greater than 0");
        }
        this->teamSize = teamSize;
    }
    void print() const override {
        cout << "Name: " << name << " Age: " << age << " Team side: " << teamSize << endl;
    }

private:
    int teamSize;
};

class President : public Employer {
public:
    President(const string& name, int age, const string& department) {
        setName(name);
        setAge(age);
        setDepartment(department);
    }
    ~President() override = default;
    void setDepartment(const string& department) {
        if (department.empty()) {
            throw invalid_argument("Department should not be empty");
        }
        this->department = department;
    }
    void print() const override {
        cout << "Name: " << name << " Age: " << age << " Department: " << department << endl;
    }

private:
    string department;
};

//-------------------------


class Shape {
public:
    virtual ~Shape() {}

    virtual double area() const = 0;
    virtual void print() const {
        cout << area() << " : ";
    }
};

class Rectangle : public Shape {
public:
    Rectangle(int side1, int side2) : side1(side1), side2(side2) {
        if (side1 <= 0 || side2 <= 0) {
            throw invalid_argument("Side size should be greater than 0");
        }
    }
    double area() const override {
        return side1 * side2;
    }
private:
    int side1;
    int side2;
};

class Circle : public Shape {
public:
    Circle(int radius) : radius(radius) {
        if (radius <= 0) {
            throw invalid_argument("Radius should be greater than 0");
        }
    }
    double area() const override {
        return M_PI * pow(radius, 2);
    }
private:
    int radius;
};

class RightTriangle : public Shape {
public:
    RightTriangle(int leg1, int leg2) : leg1(leg1), leg2(leg2) {
        if (leg1 <= 0 || leg2 <= 0) {
            throw invalid_argument("Leg size should be greater than 0");
        }
    }
    double area() const override {
        return (leg1 * leg2) / 2.0;
    }
private:
    int leg1;
    int leg2;
};

class Trapezoid : public Shape {
public:
    Trapezoid(int side1, int side2, int height) : side1(side1), side2(side2), height(height) {
        if (side1 <= 0 || side2 <= 0 || height <= 0) {
            throw invalid_argument("All dimensions should be greater than 0");
        }
    }
    double area() const override {
        return (side1 + side2) * height / 2.0;
    }
private:
    int side1;
    int side2;
    int height;
};


int main() {
    Worker worker("John Doe", 25, "Technician");
    Manager manager("Jane Smith", 30, 5);
    President president("Alice Johnson", 45, "Engineering");

    worker.print();
    manager.print();
    president.print();

    //------------------

    Trapezoid trapezoid1(5, 3, 2);
    Rectangle rectangle1(6, 2);
    RightTriangle triangle1(5, 8);
    Circle circle1(6);

    vector<Shape*> MyShapeList{ &trapezoid1,&rectangle1, &triangle1, &circle1 };
    cout << "Shape areas: ";
    for (Shape* shape : MyShapeList) {
        shape->print();
    }

    return 0;
}
