#pragma once
#include "Fahrausnahme.h"


class Losfahren : public Fahrausnahme
{
public:
	Losfahren(Fahrzeug&, Weg&);
	void vBearbeiten() const override;
};

