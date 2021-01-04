
#include "Fahrausnahme.h"
#include "Fahrzeug.h"
#include "Weg.h"


Fahrausnahme::Fahrausnahme(Fahrzeug& initFzg, Weg& initWeg) : exception(""), p_pFahrzeug(initFzg), p_pWeg(initWeg)
{
}
