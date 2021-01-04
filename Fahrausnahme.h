#pragma once

#include <exception>
#include "Fahrzeug.h";
#include "Weg.h";

class Fahrausnahme : public exception
{
protected:
	Fahrzeug& p_pFahrzeug;
	Weg& p_pWeg;


public:
	Fahrausnahme(Fahrzeug& initFzg, Weg& initWeg);
	virtual void vBearbeiten() const = 0;
};

