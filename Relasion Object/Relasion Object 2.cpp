#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>

using namespace std;

class Worker {
private:
    string name;

public:
    Worker(string name) : name(name) {}

    string getName() {
        return name;
    }
};

class Department {
private:
    vector<Worker> workerList;

public:
    void add(Worker& worker) {
        workerList.push_back(worker);
    }
};