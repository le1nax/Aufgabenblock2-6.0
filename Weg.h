#pragma once

#include "Simulationsobjekt.h"
#include "Tempolimit.h"
#include "vertagt_liste.h"

#include <memory>
#include <limits>


extern double dToleranz;

class Fahrzeug;

class Weg : public Simulationsobjekt

{
protected:
	Tempolimit p_eTempolimit = Tempolimit::autobahn;
	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;
	//list<unique_ptr<Fahrzeug>>::iterator it;

	double p_dLaenge = 0;

	

public:
	Weg();
	Weg(string initName, double initLaenge, Tempolimit initTempolimit = Tempolimit::autobahn);
	const double getTempolimit() const;
	const double getLaenge() const;
	unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug&);
	void vSimulieren() override;
	void vAnnahme(unique_ptr<Fahrzeug> aFzg, double dStartZeit = numeric_limits<double>::infinity());
	virtual void vAusgeben(ostream& out = cout) const override;
	static void vKopf();
};
	