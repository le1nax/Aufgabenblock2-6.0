#pragma once 

#include "Fahrzeug.h"

class Fahrrad : public Fahrzeug
{
public:
	Fahrrad();
	Fahrrad(string sName, double dMaxGeschwindigkeit);
	
	//Funktion gibt fahrradspezifische Daten aus
	void vAusgeben(ostream& out) const override;

	//Funktion gibt aktuelle Geschwindigkeit zurück: pro 20 km nimmt die Geschw. um 10% ab, ist minimal jedoch bei 10 km/h
	double dGeschwindigkeit() const override;

	void vZeichnen(const Weg&) const override;
};

