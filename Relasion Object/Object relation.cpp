#include <iostream>
#include <fstream>
#include <cstring>
#include <stdexcept>
#include <string.h>
#include <errno.h>
#include <bitset>


using namespace std;

class MyData {
public:
    MyData() : path(nullptr) {}

    MyData(const MyData& other) : path(nullptr) {
        setPath(other.path);
    }

    MyData& operator=(const MyData& other) {
        if (this != &other) {
            setPath(other.path);
        }
        return *this;
    }

    virtual ~MyData() {
        delete[] path;
    }

    void setPath(const char* path) {
        if (strlen(path) == 0) {
            throw std::invalid_argument("Path should not be empty");
        }
        delete[] this->path;
        this->path = new char[strlen(path) + 1];
        errno_t err = strcpy_s(this->path, strlen(path) + 1, path);
        if (err != 0) {
            delete[] this->path;
            throw std::runtime_error("Failed to copy path");
        }
    }

    char* getPath() const {
        return path;
    }

    virtual void Display() {
        if (!path) {
            cout << "Path is not set." << endl;
            return;
        }
        ifstream file(path);
        char ch;
        if (file.is_open()) {
            while (file.get(ch)) {
                cout << ch;
            }
        }
        else {
            cout << "Cannot open file: " << path << endl;
        }
        file.close();
    }

protected:
    char* path;
};

class MyDataASCII : public MyData {
public:
    using MyData::MyData;

    virtual void Display() override {
        if (!path) {
            cout << "Path is not set." << endl;
            return;
        }
        ifstream file(path);
        char ch;
        if (file.is_open()) {
            while (file.get(ch)) {
                cout << static_cast<int>(ch) << " ";
            }
        }
        else {
            cout << "Cannot open file: " << path << endl;
        }
        file.close();
    }
};

class MyDataBinary : public MyData {
public:
    using MyData::MyData;

    virtual void Display() override {
        if (!path) {
            cout << "Path is not set." << endl;
            return;
        }
        ifstream file(path);
        char ch;
        if (file.is_open()) {
            while (file.get(ch)) {
                cout << bitset<8>(ch).to_string() << " ";
            }
        }
        else {
            cout << "Cannot open file: " << path << endl;
        }
        file.close();
    }
};


/*int main() {
    char filepath[] = "Task1.txt";
    MyData data1;
    data1.setPath(filepath);
    data1.Display();
    cout << endl;
    MyDataASCII data2;
    data2.setPath(filepath);
    data2.Display();
    cout << endl;
    MyDataBinary data3;
    data3.setPath(filepath);
    data3.Display();

    return 0;
}*/
