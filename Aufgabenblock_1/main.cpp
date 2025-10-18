/*
 * Source.cpp
 *
 *  Created on: 18 Oct 2025
 *      Author: mikitabianko
 */
#include <iostream>

using namespace std;

class Fahrzeug {
private:
	const string p_sName;
	const int p_iID;
	static inline int p_iMaxID = 0;
public:
	Fahrzeug() : p_sName(""), p_iID(p_iMaxID) {
		++p_iMaxID;
		cout << "Wurde ein Farzeig mit der Name: \"" << p_sName << "\", und dem Id: " << p_iID << " erstellt\n";
	}
	Fahrzeug(string name) : p_sName(name), p_iID(p_iMaxID) {
		++p_iMaxID;
		cout << "Wurde ein Farzeig mit der Name: \"" << p_sName << "\", und dem Id: " << p_iID << " erstellt\n";
	}

	~Fahrzeug() {
		cout << "Wurde ein Farzeig mit der Name: \"" << p_sName << "\", und dem Id: " << p_iID << " gelöscht\n";
	}
};

void vAufgabe_1() {
	// Teil 1
	{
		Fahrzeug obj1;
		Fahrzeug obj2("BMW");

		auto ptr1 = new Fahrzeug();
		auto ptr2 = new Fahrzeug("Tesla");

		delete ptr1;
		delete ptr2;

		// Wurde ein Farzeig mit der Name: "", und dem Id: 0 erstellt
		// Wurde ein Farzeig mit der Name: "BMW", und dem Id: 1 erstellt
		// Wurde ein Farzeig mit der Name: "", und dem Id: 2 erstellt
		// Wurde ein Farzeig mit der Name: "Tesla", und dem Id: 3 erstellt
		// Wurde ein Farzeig mit der Name: "", und dem Id: 2 gelöscht
		// Wurde ein Farzeig mit der Name: "Tesla", und dem Id: 3 gelöscht
		// Wurde ein Farzeig mit der Name: "BMW", und dem Id: 1 gelöscht
		// Wurde ein Farzeig mit der Name: "", und dem Id: 0 gelöscht
	}
}

int main() {

	vAufgabe_1();

	return 0;
}
