
#include "Losfahren.h"
#include "Fahrzeug.h"
#include "Weg.h"


Losfahren::Losfahren(Fahrzeug& initFahrzeug, Weg& initWeg) : Fahrausnahme(initFahrzeug, initWeg)
{
}

void Losfahren::vBearbeiten() const
{
	std::cout << "Fahrzeug " << p_pFahrzeug.getName() << " faehrt nun auf " << p_pWeg.getName() << "\n" ;
	auto tempFahrzeug = p_pWeg.pAbgabe(p_pFahrzeug);
	p_pWeg.vAnnahme(move(tempFahrzeug));
}
