#include "Simulationsobjekt.h"


Simulationsobjekt::Simulationsobjekt() : p_iID(p_iMaxID++), p_sName("")
{
}

Simulationsobjekt::Simulationsobjekt(string initName) : p_iID(p_iMaxID++), p_sName(initName)
{
}

Simulationsobjekt::~Simulationsobjekt()
{
	cout << "Simulationsobjekt-Destruktor aufgerufen" << endl;
	cout << "Objekt der Klasse Simulationsobjekt mit ID " << p_iID << " und Name " << p_sName << " geloescht\n" << endl;
}

void Simulationsobjekt::vAusgeben(ostream& out) const
{
	out << "|" << setw(3) << resetiosflags(ios::left) << setiosflags(ios::right) << p_iID << "|";
	out << "|" << "  " << "|";
	out << "|" << setw(20) << resetiosflags(ios::right) << setiosflags(ios::left) << p_sName << "|";
}

int Simulationsobjekt::getID() const
{
	return p_iID;
}

string Simulationsobjekt::getName() const
{
	return p_sName;
	
}

Simulationsobjekt& Simulationsobjekt::operator=(const Simulationsobjekt& simObj)
{
	//p_iID wird nicht zugewiesen, da das neue Fahrzeugobjekt schon vor der Zuweisung erstellt werden sollte und die ID durch den Konstruktor schon erhöht wurde
	this->p_sName = simObj.p_sName + "K";

	//Nicht zwingend notwendig, da Objekt schon vorher erstellt wurde
	this->p_dZeit = 0.0;

	return *this;
}

bool operator==(const Simulationsobjekt& obj1, const Simulationsobjekt& obj2)
{
	return obj1.getID() == obj2.getID();
}


std::ostream& operator<<(std::ostream& out, const Simulationsobjekt& objekt)
{
	objekt.vAusgeben(out);

	return out;
}