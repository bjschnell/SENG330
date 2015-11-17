#include "gtest/gtest.h"
#include <iostream>
#include <fstream>
#include "Machine.pb.h"

using namespace std;

//! Prototype class
/*! Basis for making new machines.
*/
class Prototype {
/*! Variable delcarations for prototype */
protected:
    string type;
    string name;
/*! Function declarations for prototype */
public:
    virtual Prototype* clone() = 0;

    /*! Getters for the type */
    string getType() {
        return type;
    }
    /*! Getter for name(ID) value */
    string getName() {
        return name;
    }
    /*! Setters for the name and the type */
    void setType(string type) {
        this->type = type;
    }
    /*! Setter for name for prototype */
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

/*! Type 2 of machine cloned via prototype */
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

/*! Initalization of machines */
Prototype* machine1 = 0;
Prototype* machine2 = 0;

/*! test case #1 Clone and create a new machine of type 1. */
TEST(Makenewmachine,newmachine) {
	Prototype* demo;
	static Prototype* machine1 = new Machinetype1("machine 1", "1");
	demo = machine1->clone();
	EXPECT_EQ(machine1->getType(),demo->getType());
	EXPECT_EQ(machine1->getName(),demo->getName());
	demo->setName("1234");
	EXPECT_EQ(demo->getName(), "1234");
}

/*! test case #2 Create 10 different machines that all have hello as name */
TEST(multiplemachines, machinelist) {
	Prototype* demo[10];
	static Prototype* machine1 = new Machinetype1("machine 1", "1");
	static Prototype* machine2 = new Machinetype2("machine 2", "2");

	for (int i =0; i < 10; i++){
		if (i % 2 != 0) {
			demo[i] = machine1->clone();
			EXPECT_EQ(machine1->getType(),demo[i]->getType());
			EXPECT_EQ(machine1->getName(),demo[i]->getName());
		} else {
			demo[i] = machine2->clone();
			EXPECT_EQ(machine2->getType(),demo[i]->getType());
			EXPECT_EQ(machine2->getName(),demo[i]->getName());
		}
		demo[i]->setName("hello");
	}

	for (int i=0; i < 10; i++){
		EXPECT_EQ(demo[i]->getName(), "hello");
	}
}

/* Test #3 - Create totally different machines and ensure they are different */
TEST(differentmachines, diff){
	Prototype* demo[2];
	static Prototype* machine1 = new Machinetype1("machine 1", "1");
	static Prototype* machine2 = new Machinetype2("machine 2", "2");
	demo[0] = machine1->clone();
	demo[1] = machine2->clone();
	EXPECT_NE(demo[0]->getType(),demo[1]->getType());
	demo[0]->setName("123123");
	demo[1]->setName("123321");
	EXPECT_NE(demo[0]->getName(), demo[1]->getName());
}

/* Test #4 - Create same, change to diff then change NAME field to same */
TEST(startSameEndDiff, samediff){
	Prototype* demo[2];
	static Prototype* machine1 = new Machinetype1("machine 1", "1");
	static Prototype* machine2 = new Machinetype2("machine 2", "2");
	demo[0] = machine1->clone();
	demo[1] = machine1->clone();
	EXPECT_EQ(demo[0]->getType(),demo[1]->getType());
	EXPECT_EQ(demo[0]->getName(),demo[1]->getName());
	demo[1] = machine2->clone();
	EXPECT_NE(demo[0]->getType(),demo[1]->getType());
	EXPECT_NE(demo[0]->getName(),demo[1]->getName());
	demo[1]->setName("1");
	EXPECT_NE(demo[0]->getName(),demo[1]->getName());
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}