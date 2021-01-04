#pragma once
class Weg;
class Fahrzeug;

class Verhalten
{
protected:
	Weg& p_Weg;

public:
	Verhalten(Weg& initWeg);
	Weg& getWeg() const;
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitintervall) = 0 ;

};