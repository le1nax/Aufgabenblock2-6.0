#pragma once
#include "Fahrausnahme.h"

class Streckenende : public Fahrausnahme
{
public:
	Streckenende(Fahrzeug& aFzg, Weg& aWeg);
	void vBearbeiten() const override;

};

