#include <iostream>
#include <string>
#include <fstream>
#include "Machine.pb.h"

using namespace std;

class Prototype {
protected:
    string type;
    string name;

public:
    virtual Prototype* clone() = 0;

    // getter's for type
    string getType() {
        return type;
    }
    // Getter for value
    string getName() {
        return name;
    }

    void setType(string type) {
        this->type = type;
    }

    void setName(string Name) {
        this->name = Name;
    }
};
// Machine1 class clones from prototype
class Machinetype1 : public Prototype
{
public:
    // Init
    Machinetype1(string utype, string ID) {
        type = utype;
        name = ID;
    }
    // clones this object
    Prototype* clone() {
        return new Machinetype1(*this);
    }

    // GETTERS
    string getType() {
        return type;
    }

    string getName() {
        return name;
    }

    // SETTERS
    void setName(string Name) {
        this->name = Name;
    }

    void setType(string type) {
        this->type = type;
    }
};

class Machinetype2 : public Prototype
{
public:
    // Init
    Machinetype2(string utype, string ID) {
        type = utype;
        name = ID;
    }
    // Clone for this machine
    Prototype* clone() {
        return new Machinetype2(*this);
    }
    // GETTERS
    string getType() {
        return type;
    }

    string getName() {
        return name;
    }
    // SETTERS
    void setName(string Name) {
        this->name = Name;
    }

    void setType(string type) {
        this->type = type;
    }
};

Prototype* machine1 = 0;
Prototype* machine2 = 0;

int main()
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    Prototype* demo[10];
    string machinetype[10];
    string id[10];
    string oldmachines[100];
    int i = 0;
    int index = 0;
    char* fname = "machinelists";
    machines::machinelist machine_list;
    machines::Machine* mach;

    {
        fstream input(fname, ios::in | ios::binary);
        if (!machine_list.ParseFromIstream(&input)) {
            cout << "No machines saved!" << endl;
        }
    }
    // Get users input in a semi-logical way
    while (machinetype[index] != "-1" || id[index] != "-1"){
        if (i > 1) {
            index++;
        }
        cout << "enter the machine type (1 or 2) and press return (-1 to quit)" << endl;
        cin >> machinetype[i];
        if (machinetype[i] == "-1") {
            break;
        }
        cout << "enter the id of the machine and press return (-1 to quit)" << endl;
        cin >> id[i];
        if (id[i] == "-1") {
            break;
        }
        i++;
    }

    // Declaration of prototypes for cloning
    static Prototype* machine1 = new Machinetype1("machine 1", "1");
    static Prototype* machine2 = new Machinetype2("machine 2", "2");

    // Allocate new machines via cloning the original prototypes. YAY
    for(int j = 0; j < i; j++){
        if (machinetype[j] == "1") {
            demo[j] = machine1->clone();
        } else {
            demo[j] = machine2->clone();
        }
        demo[j]->setName(id[j]);
    }

    // Prints out the machines info
    for (int j = 0; j < i; j++) {
        cout << "Machine type: " << demo[j]->getType() << " Machine ID: " << demo[j]->getName() << endl;
        mach = machine_list.add_machine();
        mach->set_id(demo[j]->getName());
        mach->set_type(demo[j]->getType());
    }
    // Write all machines to file
    {
        fstream output(fname, ios::out | ios::trunc | ios::binary);
        if (!machine_list.SerializeToOstream(&output)) {
            cerr << "Failed to write to address book." << endl;
            return -1;
        }
    }
    // Delete all objects allocated by protobuf
    google::protobuf::ShutdownProtobufLibrary();
}

