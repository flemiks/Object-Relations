#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

//чесно зізнаюся реалізував, через чат. сам до такої реалізації не додумався
class Shape {
public:
    virtual void Show() const = 0;
    virtual void Save(ofstream& out) const = 0;
    virtual void Load(ifstream& in) = 0;
    virtual ~Shape() {}
};

class Square : public Shape {
private:
    int x, y; 
    int side; 
public:
    Square(int x, int y, int side) : x(x), y(y), side(side) {}

    void Show() const override {
        cout << "Square: Position(" << x << ", " << y << "), Side(" << side << ")\n";
    }

    void Save(ofstream& out) const override {
        out << "Square " << x << " " << y << " " << side << "\n";
    }

    void Load(ifstream& in) override {
        in >> x >> y >> side;
    }
};


class Rectangle : public Shape {
private:
    int x, y; 
    int width, height; 
public:
    Rectangle(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

    void Show() const override {
        cout << "Rectangle: Position(" << x << ", " << y << "), Width(" << width << "), Height(" << height << ")\n";
    }

    void Save(ofstream& out) const override {
        out << "Rectangle " << x << " " << y << " " << width << " " << height << "\n";
    }

    void Load(ifstream& in) override {
        in >> x >> y >> width >> height;
    }
};


class Circle : public Shape {
private:
    int x, y; 
    int radius; 
public:
    Circle(int x, int y, int radius) : x(x), y(y), radius(radius) {}

    void Show() const override {
        cout << "Circle: Center(" << x << ", " << y << "), Radius(" << radius << ")\n";
    }

    void Save(ofstream& out) const override {
        out << "Circle " << x << " " << y << " " << radius << "\n";
    }

    void Load(ifstream& in) override {
        in >> x >> y >> radius;
    }
};


class Ellipse : public Shape {
private:
    int x, y; 
    int width, height;
public:
    Ellipse(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}

    void Show() const override {
        cout << "Ellipse: Upper-left corner(" << x << ", " << y << "), Width(" << width << "), Height(" << height << ")\n";
    }

    void Save(ofstream& out) const override {
        out << "Ellipse " << x << " " << y << " " << width << " " << height << "\n";
    }

    void Load(ifstream& in) override {
        in >> x >> y >> width >> height;
    }
};

/*int main() {
    vector<Shape*> shapes;
    shapes.push_back(new Square(10, 10, 50));
    shapes.push_back(new Rectangle(20, 20, 30, 40));
    shapes.push_back(new Circle(15, 15, 23));
    shapes.push_back(new Ellipse(5, 5, 100, 50));

 
    ofstream out("shapes.txt");
    for (auto& shape : shapes) {
        shape->Save(out);
    }
    out.close();


    vector<Shape*> loaded_shapes;
    ifstream in("shapes.txt");
    string type;
    while (in >> type) {
        if (type == "Square") {
            Square* square = new Square(0, 0, 0);
            square->Load(in);
            loaded_shapes.push_back(square);
        }
        else if (type == "Rectangle") {
            Rectangle* rectangle = new Rectangle(0, 0, 0, 0);
            rectangle->Load(in);
            loaded_shapes.push_back(rectangle);
        }
        else if (type == "Circle") {
            Circle* circle = new Circle(0, 0, 0);
            circle->Load(in);
            loaded_shapes.push_back(circle);
        }
        else if (type == "Ellipse") {
            Ellipse* ellipse = new Ellipse(0, 0, 0, 0);
            ellipse->Load(in);
            loaded_shapes.push_back(ellipse);
        }
    }
    in.close();


    for (auto& shape : loaded_shapes) {
        shape->Show();
    }


    for (auto& shape : shapes) {
        delete shape;
    }
    for (auto& shape : loaded_shapes) {
        delete shape;
    }

    return 0;
}*/
