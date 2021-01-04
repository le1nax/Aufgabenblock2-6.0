#pragma once
#include "Verhalten.h"

class Parken : public Verhalten
{
protected:
	double p_dStart;

public:
	Parken(Weg& initWeg, double initStart);
	double dStrecke(Fahrzeug& aFzg, double dZeitintervall) override;

};