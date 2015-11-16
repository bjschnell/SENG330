#include <QCoreApplication>
#include <iostream>
#include <string>

using namespace std;

class Prototype {
protected:
    std::string type;
    int value;

public:
    virtual Prototype* clone() = 0;

    // getter's for type
    std::string getType() {
        return type;
    }
    // Getter for value
    int getValue() {
        return value;
    }

};
// Machine1 class clones from prototype
class Machinetype1 : public Prototype
{
public:
    // Init
    Machinetype1(int ID) {
        type = "Machine Type 1";
        value = ID;
    }
    // clones this object
    Prototype* clone() {
        return new Machinetype1(*this);
    }
};

class Machinetype2 : public Prototype
{
public:
    Machinetype2(int ID) {
        type = "Machine Type 2";
        value = ID;
    }

    Prototype* clone() {
        return new Machinetype2(*this);
    }
};

class Factory {
    static Prototype* machine1;
    static Prototype* machine2;
    static Prototype* machine3;
    static Prototype* machine4;

public:
    // Initialize the factory with 4 machines
    static void init() {
        machine1 = new Machinetype1(1);
        machine2 = new Machinetype1(2);
        machine3 = new Machinetype2(3);
        machine4 = new Machinetype2(4);
    }
    // getters using clones of the initalized machines
    static Prototype* getMachine1() {
        return machine1->clone();
    }

    static Prototype* getMachine2() {
        return machine2->clone();
    }

    static Prototype* getMachine3() {
        return machine3->clone();
    }

    static Prototype* getMachine4() {
        return machine4->clone();
    }
};

Prototype* Factory::getMachine1() = 0;
Prototype* Factory::getMachine2() = 0;
Prototype* Factory::getMachine3() = 0;
Prototype* Factory::getMachine4() = 0;


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    Factory::init();
    Prototype* demo;

    // all the following objects should be created via cloning of the prototype
    demo = Factory::getMachine1();
    cout << "Machine Type:" << demo->getType() << " ID: " << demo->getValue() << endl;


    demo = Factory::getMachine2();
    cout << "Machine Type:" << demo->getType() << " ID: " << demo->getValue() << endl;


    demo = Factory::getMachine3();
    cout << "Machine Type:" << demo->getType() << " ID: " << demo->getValue() << endl;


    demo = Factory::getMachine4();
    cout << "Machine Type:" << demo->getType() << " ID: " << demo->getValue() << endl;

    return a.exec();
}

