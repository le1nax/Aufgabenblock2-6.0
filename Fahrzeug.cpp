
#include "Fahrzeug.h"
#include "Weg.h"
#include "Fahren.h"
#include "Parken.h"
#include <iomanip>

int Fahrzeug::p_iMaxID = 0;
extern double dGlobaleZeit;
extern double dToleranz;

Fahrzeug::Fahrzeug() : Simulationsobjekt() 
	
{
	cout << "Fahrzeug-Standardkonstruktor aufgerufen" << endl;
	cout << "Objekt der Klasse Fahrzeug mit ID " << p_iID << " und Name " << p_sName << " erzeugt\n" << endl;
}

Fahrzeug::Fahrzeug(string initName) : Simulationsobjekt(initName)
{
	cout << "Fahrzeug-Konstruktor mit Parameter p_sName aufgerufen" << endl;
	cout << "Objekt der Klasse Fahrzeug mit ID " << p_iID << " und Name " << p_sName << " erzeugt\n" << endl;
}

Fahrzeug::Fahrzeug(string initName, double dMaxGeschwindigkeit) : Simulationsobjekt(initName), p_dMaxGeschwindigkeit((dMaxGeschwindigkeit >= 0) ? dMaxGeschwindigkeit : 0.0)
{
	cout << "Fahrzeug-Konstruktor mit Parameter p_sName, p_dMaxGeschwindigkeit aufgerufen" << endl;
	cout << "Objekt der Klasse Fahrzeug mit ID " << p_iID << ", Name " << p_sName << " und Geschwindigkeit " << p_dMaxGeschwindigkeit << " km/h erzeugt\n" << endl;
}

void Fahrzeug::vAusgeben(ostream& out) const
{
	out << "|" << setw(20) << resetiosflags(ios::left) << setiosflags(ios::right) << setprecision(2) << setiosflags(ios::fixed) << p_dMaxGeschwindigkeit << "|";
	out << "|" << setw(15) << setprecision(2) << setiosflags(ios::fixed) << p_dGesamtStrecke << "|";
	out << "|" << setw(20) << setprecision(2) << setiosflags(ios::fixed) << p_dAbschnittStrecke << "|";
}

double Fahrzeug::getGesamtZeit() const
{
	return p_dGesamtZeit;
}

void Fahrzeug::vKopf()
{
	cout << "|" << setw(3) << resetiosflags(ios::left) << setiosflags(ios::right) << "ID" << "|";
	cout << "|" << "  " << "|";
	cout << "|" << setw(20) << resetiosflags(ios::right) << setiosflags(ios::left) << "Name" << "|";
	cout << "|" << setw(20) << resetiosflags(ios::left) << setiosflags(ios::right) << "MaxGeschwindigkeit" << "|";
	cout << "|" << setw(15) << "Gesamtstrecke" << "|";
	cout << "|" << setw(20) << "Abschnittsstrecke" << "|";
	cout << "|" << setw(15) << "Tankinhalt" << "|";
	cout << "|" << setw(20) << "Gesamtverbrauch" << "|";
	cout << "|" << setw(25) << "aktuelle Geschwindigkeit" << "|" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------------------";
	cout << endl;
}

void Fahrzeug::vSimulieren()
{
	//prüfe, ob Fahzeug schonmal in diesem Simulationsschritt bearbeitet wurde und schließe den ersten Simulationsschritt aus
	double dAbstand = fabs(p_dZeit - dGlobaleZeit);
	if ((dAbstand < dToleranz) && (p_dZeit != 0.0) && (dGlobaleZeit != 0.0))
	{
		cout << "Fahrzeug wurde in diesem Schritt schonmal simuliert." << endl;
		return;
	}
	
	//ermittle Zeit seit letztem Simulationsschritt
	double dVerstricheneZeit = dGlobaleZeit - p_dZeit;

	p_dGesamtStrecke += (p_pVerhalten->dStrecke(*this, dVerstricheneZeit));
	p_dAbschnittStrecke += (p_pVerhalten->dStrecke(*this, dVerstricheneZeit));

	p_dZeit = dGlobaleZeit;
	p_dGesamtZeit = p_dGesamtZeit + dVerstricheneZeit;


}

double Fahrzeug::dTanken(double dMenge)
{
	return 0.0;
}

double Fahrzeug::getGesamtStrecke() const
{
	return p_dGesamtStrecke;
}

double Fahrzeug::getAbschnittStrecke() const
{
	return p_dAbschnittStrecke;
}

double Fahrzeug::dGeschwindigkeit() const
{
	return p_dMaxGeschwindigkeit;
}


void Fahrzeug::vNeueStrecke(Weg& initWeg, double dStartZeit)
{
	
	p_dAbschnittStrecke = 0;
	// operator=() löscht altes Objekt und weist neues Verhalten zu.

	p_pVerhalten = std::numeric_limits<double>::infinity() == dStartZeit ? 
		(unique_ptr<Verhalten>) make_unique<Fahren>(initWeg) :
		make_unique<Parken>(initWeg, dStartZeit);
	
}

bool Fahrzeug::operator<(const Fahrzeug& fahrzeug) const
{
	//Vergleiche Anhand der Gesamtstrecke
	if (this->p_dGesamtStrecke < (fahrzeug.p_dGesamtStrecke + dToleranz))
	{
		return true;
	}
	else
	{
		return false;
	}
}

Fahrzeug& Fahrzeug::operator=(const Fahrzeug& fahrzeug)
{
	//p_iID wird nicht zugewiesen, da das neue Fahrzeugobjekt schon vor der Zuweisung erstellt werden sollte und die ID durch den Konstruktor schon erhöht wurde
	this->p_sName = fahrzeug.p_sName + "K";
	this->p_dMaxGeschwindigkeit = fahrzeug.p_dMaxGeschwindigkeit;

	//Nicht zwingend notwendig, da Objekt schon vorher erstellt wurde
	this->p_dGesamtStrecke = 0.0;
	this->p_dGesamtZeit = 0.0;
	this->p_dZeit = 0.0;

	return *this;
}

//Definition Ausgabeoperator für Fahrzeug Klasse
ostream& operator<<(ostream& out, const Fahrzeug& fahrzeugReference)
{
	fahrzeugReference.vAusgeben(out);
	return out;
}


void Fahrzeug::vZeichnen(const Weg&) const
{
}