#ifndef FUNKCJE_H
#define FUNKCJE_H


#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>




struct Danelotu
{
	std::string nrlotu;
	std::string lotnisko;
	std::string data;
};


struct Osoba
{
	Danelotu dane;
	std::string nazwisko;
	int miejsce;
};

/**
Element listy
*/
struct lista
{	
	Osoba pasazer;
	lista *pNext;	
};


/**
Wezel drzewa poszukiwan binarnych
*/
struct wezel
{
	Danelotu danelotu;
	lista *pasazerowie;
	wezel *pLewy;
	wezel *pPrawy;
};

/**
Funkcja dodaje pasazera na poczatek listy.
@param pKorzen korzen drzewa
@param osoba pasazer do dodania
*/
void dodajpocz(wezel *&pKorzen, Osoba osoba);
/**
Funkcja wykorzystujac algorytm sortowania babelkowego uklada w porzadku rosnacym osoby wedlug numeru siedzenia. Funkcja zamienia elementy listy kopiujac je.
@param pHead glowa listy
*/
void sortuj(lista *&pHead);
/**
Funkcja wstawia rekurencyjnie pasazerow do drzewa tworzac jednoczesnie w wezle listy pasazerow
@param pKorzen korzen drzewa
@param osoba pasazer do wpisania do drzewa
@return true, kiedy udalo sie wstawic do drzewa, false, jezeli nie udalo sie
*/
bool wstaw(Osoba osoba, wezel*&pKorzen);
/**
Funkcja usuwa liste pasazerow z wezla drzewa
@param pHead glowa listy
*/
void  usunliste(lista *&pHead);
/**
Funkcja sprawdza, czy plik jest pusty(czy sa jakies znaki do odczytania), jezeli nie, to zwraca falsz.
@param plik plik wejsciowy
@return poprawnosc pliku
*/
bool pustyplik(std::ifstream &plik);
/**
Funkcja stwierdza, czy wprowadzone miejsce nie powtarza sie u innego pasazera danego lotu
@param miejsce miejsce pasazera
@param pHead glowa listy
@return true, jezeli miejsc ejest unikalne, false, jezeli sie powtarza
*/
bool sprawdzmiejsce(int miejsce, lista *&pHead);
/**
Funkcja stwierdza poprawnosc odczytanego nazwiska, sprawdzajac, czy wszystkie znaki z nazwiska nie sa liczbami, jezeli nie, to zwraca falsz.
@param nazwisko nazwisko pasazera
@return true, jezeli nazwisko jest poprawne, false jezeli przeciwnie
*/
bool sprawdznazwisko(std::string &nazwisko);
/**
Funkcja stwierdza poprawnosc odczytanej daty, sprawdzajac jej dlugosc, pozycje myslnikow, nastepnie konwertujac date na typ int sprawdza poprawnosc dnia w stosunku do wprowadzonej daty, uwzgledniajac tez lata przestepne, jezeli nie, to zwraca falsz.
@param data data lotu
@return true, jezeli data jest poprawna, false jezeli przeciwnie
*/
bool sprawdzdate(std::string data);
/**
Funkcja przyjmuje dane z pliku i wpisuje je do struktury pasazera, jednoczesnie wywolujac funkcje sprawdzajace poprawnosc danych.
@param pKorzen korzen drzewa
@param przelacznik przelacznik do pliku z rezerwacjami
@return true, jezeli uda sie odczytac plik, false, jezeli przeciwnie lub dane sa nieprawidlowe
*/
bool odczytaj(wezel *&pKorzen, std::string przelacznik);
/**
Funkcja usuwa rekurencyjnie drzewo i wywoluje funkcje usuwajaca liste nalezaca do wezla.
@param pKorzen korzen drzewa
*/
void usunwycieki(wezel *&pKorzen);
/**
Funkcja zliczajaca elementy w liscie
@param pHead glowa listy
@return ilosc elementow w liscie
*/
int liczliste(lista *&pHead);
/**
Funkcja tworzy nowe pliki i zapisuje do nich kolejne wezly drzewa binarnego
@param pKorzen korzen drzewa
@return true, jezeli udalo sie zapisac do pliku, false, jezeli nie udalo sie
*/
bool zapisz(wezel *&pKorzen);


#endif
