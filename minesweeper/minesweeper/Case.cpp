#include "stdafx.h"
#include "case.h"



Case::Case()
{
	is_bombe = false;
	compteur_de_bombe = 0;
	est_decouvert = false;
	cellule_decouverte = 0;
}

Case::~Case()
{

}

bool Case::get_is_bombe()
{
	return is_bombe;
}

void Case::set_is_bombe(bool thrueth)
{
	is_bombe = thrueth;
}

unsigned char Case::get_compteur_de_bombe()
{
	return compteur_de_bombe;
}

void Case::increment_compteur_de_bombe()
{
	compteur_de_bombe++;
}

bool Case::get_est_decouvert()
{
	return est_decouvert;
}

void Case::set_est_decouvert(bool thrut)
{
	est_decouvert = thrut;
}

void Case::increment_cellule_est_decouverte()
{
	cellule_decouverte++;
}
