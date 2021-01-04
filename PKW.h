
#pragma once
#include "Fahrzeug.h"
#include <limits>



class PKW : public Fahrzeug
{
private:
	double p_dVerbrauch = 0;
	double p_dTankvolumen = 0;
	double p_dTankinhalt = 0;
public:
	PKW(string sName, double dMaxGeschwindigkeit, double dVerbrauch, double dTankvolumen = 55.0);


	//realisiert das Betanken des PKW mit Menge dMenge
	double dTanken(double dMenge = numeric_limits<double>::infinity()) override;

	//simuliert das PKWobjekt und aktualisiert entsprechende Attribute
	 void vSimulieren() override;

	//gibt PKW spezifische Daten aus
	void vAusgeben(ostream& out) const override;

	//gibt Attribut p_dMaxGeschwindigkeit zurück
	double dGeschwindigkeit() const override;

	//Überladung des =-Operators für Klasse PKW
	PKW& operator=(const PKW& pkw);

	void vZeichnen(const Weg&) const override;
};