#include "Verhalten.h"
#include "Fahrzeug.h"
#include "Weg.h"



extern double dToleranz;

Verhalten::Verhalten(Weg& initWeg) :  p_Weg(initWeg)
{
}

Weg& Verhalten::getWeg() const
{
	return p_Weg;
}

