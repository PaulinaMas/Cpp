#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "funkcje.h"
#include <vld.h>


void dodajpocz(wezel *&pKorzen, Osoba osoba)
{
	pKorzen->pasazerowie = new lista{ osoba, pKorzen->pasazerowie };
}

void sortuj(lista *&pHead)
{

	if (pHead)
	{
		for (lista *p = pHead; p != nullptr; p = p->pNext)
		{
			for (lista *pp = p; pp != nullptr; pp = pp->pNext)
			{
				if (pp->pasazer.miejsce < p->pasazer.miejsce)
				{
					Osoba pomoc = pp->pasazer;
					pp->pasazer.nazwisko = p->pasazer.nazwisko;
					pp->pasazer.miejsce = p->pasazer.miejsce;

					p->pasazer.nazwisko = pomoc.nazwisko;
					p->pasazer.miejsce = pomoc.miejsce;

				}
			}
		}
	}
}

bool sprawdzmiejsce(int miejsce, lista *&pHead)
{
	if (pHead != nullptr)
	{
		if (miejsce == pHead->pasazer.miejsce)
			return false;
		else
		{
			sprawdzmiejsce(miejsce, pHead->pNext);
		}
	}
	return true;
}

bool wstaw(Osoba osoba, wezel*&pKorzen)
{
	if (pKorzen == nullptr)
	{
		pKorzen = new wezel;
		pKorzen->danelotu.nrlotu = osoba.dane.nrlotu;
		pKorzen->danelotu.data = osoba.dane.data;
		pKorzen->danelotu.lotnisko = osoba.dane.lotnisko;
		pKorzen->pLewy = nullptr;
		pKorzen->pPrawy = nullptr;
		pKorzen->pasazerowie = new lista{ osoba, nullptr };
	}
	else if (pKorzen->danelotu.nrlotu < osoba.dane.nrlotu)
	{
		if (!wstaw(osoba, pKorzen->pLewy))
			return false;
	}
	else if (pKorzen->danelotu.nrlotu > osoba.dane.nrlotu)
	{
		if (!wstaw(osoba, pKorzen->pPrawy))
			return false;
	}
	else if (pKorzen->danelotu.nrlotu == osoba.dane.nrlotu && pKorzen->danelotu.data == osoba.dane.data && pKorzen->danelotu.lotnisko == osoba.dane.lotnisko)
	{
		if (!(sprawdzmiejsce(osoba.miejsce, pKorzen->pasazerowie)))
			return false;
		dodajpocz(pKorzen, osoba);
	}
	else
	{
		return false;
	}
	return true;
}

void  usunliste(lista *&pHead)
{
	if (pHead)
	{
		usunliste(pHead->pNext);
		delete pHead;
	}
	pHead = nullptr;
}

bool pustyplik(std::ifstream &plik)
{
	return plik.peek() == std::ifstream::traits_type::eof();
}

bool sprawdznazwisko(std::string &nazwisko)
{
	for (int i = 0; i < nazwisko.length(); i++)
	{
		if (isdigit(nazwisko[i]))
			return false;
	}
	return true;
}

bool sprawdzdate(std::string data)
{
	if (data.length() != 10)
	{

		return false;
	}

	if (data[4] != '-' || data[7] != '-')
	{

		return false;
	}

	int rok, miesiac, dzien;
	char x;
	std::stringstream as;
	as << data;
	as >> rok >> x >> miesiac >> x >> dzien;
	if (as.fail())
		return false;

	if (rok == 0)
		return false;
	if (miesiac == 1 || miesiac == 3 || miesiac == 5 || miesiac == 7 || miesiac == 8 || miesiac == 10 || miesiac == 12)
	{
		if (!(dzien > 0 && dzien < 32))
			return false;
	}
	else if (miesiac == 4 || miesiac == 6 || miesiac == 9 || miesiac == 11)
	{
		if (!(dzien > 0 && dzien < 31))
			return false;
	}
	else if (miesiac == 2)

		if ((rok % 100) == 0 || (rok % 4) == 0)
		{

			if (!(dzien > 0 && dzien < 30))
				return false;
		}



		else if (!(dzien > 0 && dzien < 29))
			return false;



	return true;
}

bool odczytaj(wezel *&pKorzen, std::string przelacznik)
{
	Osoba osoba;
	std::ifstream plik;
	plik.open(przelacznik, std::ios::in);
	if (plik)
	{
		if (pustyplik(plik))
			return false;
		else
		{
			while (plik >> osoba.dane.nrlotu >> osoba.dane.lotnisko >> osoba.dane.data)
			{

				if (!(sprawdzdate(osoba.dane.data)))
				{
					usunwycieki(pKorzen);
					return false;
				}
				plik >> osoba.nazwisko;
				if (!sprawdznazwisko(osoba.nazwisko))
				{
					usunwycieki(pKorzen);
					return false;
				}
				plik >> osoba.miejsce;
				if (plik.fail())
				{
					usunwycieki(pKorzen);
					return false;
				}

				if (!wstaw(osoba, pKorzen))
				{
					usunwycieki(pKorzen);
					return false;
				}
			}

		}
		plik.close();
		return true;
	}
	else
		return false;

}

void usunwycieki(wezel *&pKorzen)
{


	if (pKorzen)
	{
		usunwycieki(pKorzen->pLewy);
		usunliste(pKorzen->pasazerowie);
		usunwycieki(pKorzen->pPrawy);

		delete pKorzen;
		pKorzen = nullptr;
	}

}

int liczliste(lista *&pHead)
{
	if (!pHead)
		return 0;
	return 1 + liczliste(pHead->pNext);
}

bool zapisz(wezel *&pKorzen)
{


	std::ofstream plik;
	if (pKorzen)
	{
		plik.open(pKorzen->danelotu.nrlotu + ".txt");

		if (plik.good())
		{
			sortuj(pKorzen->pasazerowie);
			zapisz(pKorzen->pLewy);
			plik << std::setw(13) <<std::left<< "symbol lotu: " << pKorzen->danelotu.nrlotu;
			plik << std::setw(15) << std::left << " \nlotnisko: " <<pKorzen->pasazerowie->pasazer.dane.lotnisko;
			plik << std::setw(14) << std::left << "\ndata: " << pKorzen->pasazerowie->pasazer.dane.data << "\n\nlista pasazerow: \n";
			lista*wsk = pKorzen->pasazerowie;
			while (wsk != nullptr)
			{
				if (wsk->pasazer.miejsce < 10)
					plik << "0" << wsk->pasazer.miejsce;
				else
					plik << wsk->pasazer.miejsce;
				plik << "  " << wsk->pasazer.nazwisko << std::endl;
				wsk = wsk->pNext;
			}
			plik << "\nliczba rezerwacji: " << liczliste(pKorzen->pasazerowie);

			zapisz(pKorzen->pPrawy);
			plik.close();
			return true;

		}

		else
		{
			plik.close();
			return false;
		}
		
	}
	return false;
}