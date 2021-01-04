
#include "Fahren.h"
#include "Fahrzeug.h"
#include "Weg.h"
#include "Streckenende.h"
#include <cmath>

Fahren::Fahren(Weg& initWeg) :  Verhalten(initWeg)
{
}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitintervall)
{
	double dStreckeMoeglich;
	if ((dZeitintervall * aFzg.dGeschwindigkeit()) < (p_Weg.getLaenge() - aFzg.getAbschnittStrecke()))
	{
		dStreckeMoeglich = dZeitintervall * aFzg.dGeschwindigkeit();
	}
	
	else if (fabs(p_Weg.getLaenge() - aFzg.getAbschnittStrecke()) < dToleranz)
	{
		Streckenende exc(aFzg, p_Weg);
		throw exc;
	}
	else
	{
		dStreckeMoeglich = p_Weg.getLaenge() - aFzg.getGesamtStrecke();
	}
	return dStreckeMoeglich;
	
	return 0.0;
}
