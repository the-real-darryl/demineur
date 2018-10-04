#pragma once

#ifndef MINE_SWEEPER_H
#define MINE_SWEEPER_H
#include "Case.h"
#include <string>
#include <vector>


class mine_sweeper
{
public:
	mine_sweeper();
	~mine_sweeper();
	void afficher();
	unsigned int* saisie_utilisateur();
	void premier_appel_traitement(unsigned int*);
	void verification_gagner();
	void rejouer_la_partie();

protected:
	void traitement_low_level(unsigned int*);
	void traitement_bombe(unsigned int*);
	void calculer_score();
	void afficher_premier_ligne();
	void lecture_fichier();
	void ecriture_fichier();
	void menu_quitter();

public:

	unsigned int quantite_bombe;
	unsigned int approximation_cellule, cellule, largeur, hauteur;
	bool teste;
	bool is_dead;
	bool as_won;
	Case** case_;
	unsigned char charactere_par_cellule_largeur, charactere_par_cellule_hauteur;

	unsigned short niveau;
	std::string nom_joueur;
	char date[26] = {};
	double score;
	unsigned int coups;
	bool quitter;
	unsigned int* historique_des_coup;
	bool connu;
};

#endif // !MINE_SWEEPER_H
