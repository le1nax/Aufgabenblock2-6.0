#include "Fahrrad.h"
#include "Weg.h"
#include "SimuClient.h"
#include <cmath>
#include <iomanip>


extern double dGlobaleZeit;
extern double dToleranz;

Fahrrad::Fahrrad() :
	Fahrzeug()
{
	cout << "Fahrrad-Standardkonstruktor aufgerufen" << endl;
	cout << "Objekt der Klasse Fahrrad mit ID " << p_iID << " und Name " << p_sName << " erzeugt\n" << endl;
}

Fahrrad::Fahrrad(string initName, double dMaxGeschwindigkeit) :
	Fahrzeug(initName, dMaxGeschwindigkeit)
{
	cout << "Fahrrad-Konstruktor mit Parametern p_sName und p_dMaxGeschwindigkeit aufgerufen" << endl;
	cout << "Objekt der Klasse Fahrrad mit ID " << p_iID << " und Name " << p_sName << " erzeugt\n" << endl;
}


void Fahrrad::vAusgeben(ostream& out) const
{
	Fahrzeug::vAusgeben(out);
	out << "|" << setw(15) << "" << "|";
	out << "|" << setw(20) << "" << "|";
	out << "|" << setw(25) << setprecision(2) << setiosflags(ios::fixed) << this->dGeschwindigkeit() << "|";
}

double Fahrrad::dGeschwindigkeit() const
{
	double dAktuelleGeschwindigkeit = p_dMaxGeschwindigkeit;
	int iFrac = ((int)p_dGesamtStrecke / 20);

	//Alle 20 km wird die aktuelle Geschw. um 10 % kleiner
	for (int i = 1; i <= iFrac; i++)
	{
		dAktuelleGeschwindigkeit = dAktuelleGeschwindigkeit * 0.9;//exponentieller Verlust der Geschwindigkeit alle 20km
	}

	//Sorge dafür, dass die Geschwindigkeit mindestens 12 km/h ist
	if ((dAktuelleGeschwindigkeit + dToleranz) > 12)
	{
		return dAktuelleGeschwindigkeit;
	}
	else
	{
		return 12;
	}
}

void Fahrrad::vZeichnen(const Weg& weg) const
{
	bZeichneFahrrad(getName(), weg.getName(), getAbschnittStrecke() / weg.getLaenge(), dGeschwindigkeit());
}
