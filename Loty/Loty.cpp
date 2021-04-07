#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>

#include "funkcje.h"


int main(int argc, char*argv[])
{
	wezel *pKorzen = nullptr;
	std::string przel;
	if (argv[1])
		przel = argv[1];
	if (argc < 2 || przel!= "-i")
		return 0;
	if(argv[2])
	przel = argv[2];
	if (!odczytaj(pKorzen, przel))
	{
		return 0;
	}
	zapisz(pKorzen);
	usunwycieki(pKorzen);
	return 0;	
}