#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrausnahme.h"

Weg::Weg():Simulationsobjekt(""), p_dLaenge(0.0), p_eTempolimit(Tempolimit::autobahn)
{
}

Weg::Weg(string initName, double initLaenge, Tempolimit initTempolimit) : Simulationsobjekt(initName),
p_dLaenge(initLaenge), p_eTempolimit(initTempolimit)
{
}




const double Weg::getTempolimit() const 
{
	double dLimit = (double)(p_eTempolimit);
	return dLimit;
}

const double Weg::getLaenge() const
{ 
	return p_dLaenge;
}

void Weg::vSimulieren()
{
	p_pFahrzeuge.vAktualisieren();

	for (auto& pFahrzeug : p_pFahrzeuge) {
		try {
			pFahrzeug->vSimulieren();
			pFahrzeug->vZeichnen(*this);
			
		}
		catch (const Fahrausnahme& exc) {
			exc.vBearbeiten();
		}
	}

	p_pFahrzeuge.vAktualisieren();
}


void Weg::vAnnahme(unique_ptr<Fahrzeug> aFzg, double dStartZeit)
{
	(*aFzg).vNeueStrecke(*this, dStartZeit);


	if (std::numeric_limits<double>::infinity() == dStartZeit) {
		p_pFahrzeuge.push_back(std::move(aFzg));
	}
	else {
		p_pFahrzeuge.push_front(std::move(aFzg));
	}
}


std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& pFahrzeug)
{
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++) {
		if (*(*it) == pFahrzeug) {
			auto pDel = move(*it);
			p_pFahrzeuge.erase(it);
			return pDel;
		}
	}

	throw runtime_error("Fahrzeug für pAbgabe befindet sich nicht auf dem Weg!");
}

void Weg::vAusgeben(ostream& out) const 
{
	cout << "|" << setw(3) << resetiosflags(ios::left) << setiosflags(ios::right) << p_iID << "|";
	cout << "|" << "  " << "|";
	cout << "|" << setw(20) << resetiosflags(ios::left) << setiosflags(ios::right) << p_sName << "|";
	cout << "|" << setw(20) << resetiosflags(ios::left) << setiosflags(ios::right) << p_dLaenge << "||";

	if (auto it = p_pFahrzeuge.empty())
	{
	}
	else
	{

		cout << setw(23) << resetiosflags(ios::left) << setiosflags(ios::right) << "(";
		for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); it++)
		{
			cout << (*it)->getName();
			if (it != p_pFahrzeuge.end())
			{
				cout << ", ";
			}
			else
			{
				cout << ")" << "\n";
			}
		}
	}

}

void Weg::vKopf()
{
	cout << "|" << setw(3) << resetiosflags(ios::right) << setiosflags(ios::left) << "ID" << "|";
	cout << "|" << "  " << "|";
	cout << "|" << setw(20) << resetiosflags(ios::right) << setiosflags(ios::left) << "Name" << "|";
	cout << "|" << setw(20) << resetiosflags(ios::right) << setiosflags(ios::left) << "Laenge" << "|";
	cout << "|" << setw(23) << resetiosflags(ios::right) << setiosflags(ios::left) << "Fahrzeuge" << "\n";
}

