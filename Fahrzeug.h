#pragma once 

#include "Simulationsobjekt.h"
#include "Verhalten.h"
#include <memory>

using namespace std;

class Fahrzeug : public Simulationsobjekt
{

protected:
	double p_dMaxGeschwindigkeit = 30.0;
	double p_dGesamtStrecke = 0;
	double p_dGesamtZeit = 0;
	double p_dAbschnittStrecke = 0;

	unique_ptr<Verhalten> p_pVerhalten;

public:
	Fahrzeug();	//Standardkonstruktor
	Fahrzeug(string sName);
	Fahrzeug(string sName, double dMaxGeschwindigkeit);

	void vAusgeben(ostream& out) const override; //gibt fahrzeugspezifische Daten aus
	virtual double getGesamtZeit() const;
	static void vKopf(); //gibt einen Header für die Ausgabe der Fahrzeugdaten aus
	virtual void vSimulieren() override;	//simuliert das Fahrzeugobjekt und aktualisiert entsprechende Attribute
	virtual double dTanken(double dMenge = numeric_limits<double>::infinity());	//realsisiert das Auftanken eines Fahrzeugs mit Menge dMenge
	virtual double getGesamtStrecke() const; // gibt die Gesamtstrecke zurück
	virtual double getAbschnittStrecke() const; //gibt die Abschnitts Strecke zurück
	virtual double dGeschwindigkeit() const; //gibt die aktuelle Geschwindigkeit des Fahrzeugs zurück
	void vNeueStrecke(Weg&, double dStartZeit = numeric_limits<double>::infinity());
	virtual void vZeichnen(const Weg&) const;


	bool operator<(const Fahrzeug& fahrzeug) const; //überlädt den <-Operator: gibt true zurück, 
													//falls p_dGesamtStrecke von 1.Operanden kleiner als die des rechten Operanden
	Fahrzeug& operator=(const Fahrzeug& fahrzeug); 	//überlädt den =-Operator: Zuweisung eines Objekts zu einem anderen
};

//überladung des Ausgabestream-operators für die Klasse Fahrzeug
//Überladung im globalen Bereich, das sonst der erste Parameter ein this-Zeiger wäre, was in diesem Fall nicht sinnvoll ist
ostream& operator<<(ostream& out, const Fahrzeug& fahrzeugReference);
