#include "Parken.h"
#include "Losfahren.h"
#include <iostream>

extern double dToleranz;

Parken::Parken(Weg& initWeg, double initStart) :Verhalten(initWeg), p_dStart(initStart)
{
}

double Parken::dStrecke(Fahrzeug& aFzg, double dZeitintervall)
{
	if (aFzg.getGesamtZeit() < p_dStart)
	{
		return 0.0;
	}
	if (fabs(aFzg.getGesamtZeit() - p_dStart)< dToleranz)
	{
		Losfahren exc(aFzg, p_Weg);
		throw exc;
	}

}
