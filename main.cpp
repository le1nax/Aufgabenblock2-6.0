#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include <vector>
#include <random>

#include "Simulationsobjekt.h"
#include "Weg.h"
#include "Fahrzeug.h"
#include "Fahrrad.h"
#include "PKW.h"
#include "SimuClient.h"
#include "vertagt_liste.h"

using namespace std;

//Funktionsdeklarationen (keine Definitionen!):
void vAufgabe_1();
void vAufgabe_1a();
void vAufgabe_2();
void vAufgabe_3();
void vAufgabe_4();
void vAufgabe_5();
void vAufgabe_6();
void vAufgabe_6a();


//globale Uhr
double dGlobaleZeit = 0.0;

//Rundungstoleranz bei double-Vergleichen: Wähle hinreichend kleines Epsilon
double dToleranz = 0.001;

int main()
{
	vAufgabe_6();
	
	return 0;
}

void vAufgabe_1()
{
	Fahrzeug tFahrzeug;
	Fahrzeug tFahrrad("Fahrrad");

	Fahrzeug* pFahrzeug = new Fahrzeug();
	Fahrzeug* pMotorrad = new Fahrzeug("Motorrad");
	delete pFahrzeug;
	delete pMotorrad;

	auto pRoller =  make_unique<Fahrzeug>("Roller");
	auto pCamper =  make_unique<Fahrzeug>("Camper");

	auto pSportwagen =  make_shared<Fahrzeug>("Sportwagen");
	auto pLaster =  make_shared<Fahrzeug>();

	// Erzeugen eines zweiten Pointers auf Laster.
	auto pLaster2 = pLaster;
	 cout << "Anzahl der Laster-Referenzen: " << pLaster.use_count() <<  endl;

	auto pCamper2 =  move(pCamper);

	 vector< unique_ptr<Fahrzeug>> uVector;
	uVector.push_back( move(pRoller));
	uVector.push_back( move(pCamper2));
	 cout << "Clear Vektor aus  unique_ptr<Fahrzeug>" <<  endl;
	// Löscht den Roller und den Camper.
	uVector.clear();

	 vector< shared_ptr<Fahrzeug>> sVector;
	// Neuer shared_ptr auf Sportwagen im Vektor.
	sVector.push_back(pSportwagen);
	 cout << "Anzahl der Sportwagen-Referenzen: " << pSportwagen.use_count() <<  endl;
	// Der shared_ptr von pLaster wird in den Vektor verschoben.
	sVector.push_back( move(pLaster));
	 cout << "Anzahl der Laster-Referenzen (mit Vektor und move): " << pLaster2.use_count() <<  endl;
	 cout << "Clear Vektor aus  shared_ptr<Fahrzeug>" <<  endl;
	// Der zweite shared_ptr und der verschobene pLaster wird gelöscht.
	sVector.clear();

	// Scope endet und damit wird der letzte shared_ptr auf Sportwagen und auf Laster gelöscht -> die Objekte werden ebenfalls gelöscht.
	 cout << "Scope Ende" <<  endl;
}

void vAufgabe_1a()
{
	 vector< unique_ptr<Fahrzeug>> vector;

	vector.push_back( make_unique<Fahrzeug>("PKW1", 40.0));
	vector.push_back( make_unique<Fahrzeug>("AUTO3", 30.0));
	vector.push_back( make_unique<Fahrzeug>("LKW2", 25.0));
	 cout <<  endl;

	double intervals[5] = { 0.2, 0.5, 1.0, 0.1, 0.7 };
	for (auto dInterval : intervals) {
		dGlobaleZeit += dInterval;

		Fahrzeug::vKopf();
		for ( unique_ptr<Fahrzeug>& fahrzeug : vector) {
			fahrzeug->vSimulieren();
			//fahrzeug->vAusgeben();
			 cout <<  endl;
		}
		 cout <<  endl;
	}
}

double dRandInRange(double dMin, double dMax)
{
	double dRand = ((double) rand() / (double)RAND_MAX);
	return dRand * (dMax - dMin) + dMin;
}

void vAufgabe_2()
{
	int iAnzahlPKWs, iAnzahlFahrraeder;

	 cout << "Wieviele PKWs sollen erstellt werden?" <<  endl;
	 cin >> iAnzahlPKWs;
	 cout << "Wieviele Fahrr" << (unsigned char)132 << "der sollen erstellt werden?" <<  endl;
	 cin >> iAnzahlFahrraeder;

	 vector< unique_ptr<Fahrzeug>> fahrzeugVector;

	for (int i = 0; i < iAnzahlPKWs; i++) {
		fahrzeugVector.push_back( make_unique<PKW>(
			"PKW" +  to_string(i + 1),
			dRandInRange(60.0, 180.0),
			dRandInRange(4.0, 13.8),
			dRandInRange(35.0, 80.7)
			));
	}

	for (int i = 0; i < iAnzahlFahrraeder; i++) {
		fahrzeugVector.push_back( make_unique<Fahrrad>(
			"RAD" +  to_string(i + 1),
			dRandInRange(12.0, 39.6)
			));
	}

	bool bGetankt = false;
	while (dGlobaleZeit < 4.0) {
		dGlobaleZeit += dRandInRange(0.1, 0.7);

		if (!bGetankt and dGlobaleZeit >= 3.0) {
			for ( unique_ptr<Fahrzeug>& fahrzeug : fahrzeugVector) {
				fahrzeug->dTanken( numeric_limits<double>::infinity());	
			}
			bGetankt = true;
		}

		 cout <<  endl << "Globale Zeit: " <<  setprecision(2) <<  setiosflags( ios::fixed) << dGlobaleZeit <<  endl;
		Fahrzeug::vKopf();
		for ( unique_ptr<Fahrzeug>& fahrzeug : fahrzeugVector) {
			fahrzeug->vSimulieren();
			//fahrzeug->vAusgeben();
			 cout <<  endl;
		}
	}
}

void vTriggerCopyConstructor(Fahrzeug fahrzeug)
{
}

void vAufgabe_3()
{
	auto pkw1 =  make_unique<PKW>("PKW1", 129.9, 7.6, 55.0);
	auto pkw2 =  make_unique<PKW>("PKW2", 95.7, 6.1, 60.0);
	auto rad =  make_shared<Fahrrad>("RAD1", 18.5);

	dGlobaleZeit = 0.5;
	pkw1->vSimulieren();
	pkw2->vSimulieren();
	rad->vSimulieren();

	Fahrzeug::vKopf();
	 cout << *pkw1 <<  endl
		<< *pkw2 <<  endl
		<< *rad <<  endl;

	if (*pkw2 < *pkw1) {
		 cout <<  endl << "PKW2 < PKW1" <<  endl;
	}

	if (*rad < *pkw2) {
		 cout << "RAD < PKW2" <<  endl;
	}

	*pkw2 = *pkw1;

	 cout <<  endl << "Gleichsetzen von PKW2 und PKW1:" <<  endl;
	Fahrzeug::vKopf();
	 cout << *pkw1 <<  endl
		<< *pkw2 <<  endl
		<< *rad <<  endl <<  endl;

	//vTriggerCopyConstructor(*rad); //Error
}

void vAufgabe_4()
{
	auto weg =  make_unique<Weg>("WEG1", 356.9);

	Weg::vKopf();
	 cout << *weg <<  endl;
}

void vAufgabe_5()
{
	auto weg =  make_unique<Weg>("WEG1", 30);
	weg->vAnnahme( make_unique<Fahrrad>("RAD1", 15));
	weg->vAnnahme( make_unique<Fahrrad>("RAD2", 25), 2.0);
	weg->vAnnahme( make_unique<PKW>("PKW1", 100, 5, 60));

	while (dGlobaleZeit < 4.0) {
		dGlobaleZeit += 0.5;

		weg->vSimulieren();

		Weg::vKopf();
		 cout << *weg <<  endl;
	}
}

void vAufgabe_6()
{
	bInitialisiereGrafik(1600, 1000);
	int iKoordinaten[4] = { 700, 250, 200, 250 };
	bZeichneStrasse("WEG1", "WEG2", 500, 2, iKoordinaten);

	auto weg1 =  make_unique<Weg>("WEG1", 500, Tempolimit::autobahn);
	weg1->vAnnahme( make_unique<Fahrrad>("FAHRRAD1", 15), 2.0);
	weg1->vAnnahme( make_unique<PKW>("PKW1", 150, 7, 80));
	weg1->vAnnahme( make_unique<Fahrrad>("FAHRRAD2", 23));

	auto weg2 =  make_unique<Weg>("WEG2", 500, Tempolimit::ausserorts);
	weg2->vAnnahme( make_unique<PKW>("PKW2", 75, 8, 20));
	weg2->vAnnahme( make_unique<PKW>("PKW3", 155, 7, 70), 3.0);
	weg2->vAnnahme( make_unique<Fahrrad>("FAHRRAD3", 23));

	Weg::vKopf();
	 cout << *weg1 <<  endl
		<< *weg2 <<  endl;

	while (dGlobaleZeit < 10.0) {
		dGlobaleZeit += 0.05;
		vSetzeZeit(dGlobaleZeit);
		 cout <<  endl << "Globale Zeit: " <<  setprecision(2) << dGlobaleZeit <<  endl;

		weg1->vSimulieren();
		weg2->vSimulieren();

	}
}

void vAufgabe_6a()
{
	vertagt::VListe<int> liste;

	static mt19937 device(0);
	uniform_int_distribution <int> dist(0, 10);

	for (int i = 0; i < 7; i++) {
		liste.push_back(dist(device));
	}

	liste.vAktualisieren();

	 cout << "Liste:" <<  endl;
	for (auto& iValue : liste) {
		 cout << iValue <<  endl;
	}

	for (auto it = liste.begin(); it != liste.end(); it++) {
		if (*it > 5) {
			liste.erase(it);
		}
	}

	 cout <<  endl << "Liste:" <<  endl;
	for (auto& iValue : liste) {
		 cout << iValue <<  endl;
	}

	liste.vAktualisieren();

	 cout <<  endl << "Liste:" <<  endl;
	for (auto& iValue : liste) {
		 cout << iValue <<  endl;
	}

	liste.push_front(dist(device));
	liste.push_front(dist(device));
	liste.push_back(dist(device));
	liste.push_back(dist(device));
	liste.vAktualisieren();

	 cout <<  endl << "Liste:" <<  endl;
	for (auto& iValue : liste) {
		 cout << iValue <<  endl;
	}
}