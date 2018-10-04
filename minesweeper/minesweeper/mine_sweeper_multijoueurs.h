#pragma once
#include "mine_sweeper.h"
#define LONGUEUR_DATE 26
typedef char DATE[LONGUEUR_DATE];

class mine_sweeper_multijoueurs :
	public mine_sweeper
{
public:
	mine_sweeper_multijoueurs();
	~mine_sweeper_multijoueurs();
	void write_file();
	void read_file();
	void comparer();
	void menu();

public:
	char **noms;
	unsigned short *longueur_nom;
	DATE **dates;
	unsigned int joueurs, coordonne_joueurs_actif, *partit_par_joueur, **coups_, *coordonne_meilleur_partit_par_joueur;
	unsigned long long **taille_jeux;
	double **scores;
	bool **terminer;
};

