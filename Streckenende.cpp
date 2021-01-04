#include "Streckenende.h"


Streckenende::Streckenende(Fahrzeug& aFzg, Weg& aWeg) : Fahrausnahme(aFzg, aWeg)
{
}


void Streckenende::vBearbeiten() const
{
	std::cout << "Fahrzeug " << p_pFahrzeug.getName() << " auf" << p_pWeg.getName() << " geendet.\n";

	p_pWeg.pAbgabe(p_pFahrzeug);

}

