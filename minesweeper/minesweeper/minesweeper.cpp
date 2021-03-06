// MINE_SWEEPER.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <stdlib.h>

#define MAX_LARGEUR 80

using namespace std;

class mine_sweeper
{
public:
	mine_sweeper();
	~mine_sweeper();
	void afficher();
	unsigned int* saisie_utilisateur();
	void traitement_bombe(unsigned int* coordonne);
	void premier_appel_traitement(unsigned int* coordonne);

public:
	bool** is_bombe;
	unsigned int quantite_bombe;
	unsigned int approximation_cellule, cellule, largeur, hauteur;
	bool **est_decouvert, teste;
	bool is_dead;

	unsigned char** compteur_de_bombe;
	unsigned short niveau;
};

int main()
{
	mine_sweeper the_game;

	while (!the_game.is_dead)
	{
		the_game.premier_appel_traitement(the_game.saisie_utilisateur());
		the_game.afficher();
	}

	return 0;
}

mine_sweeper::mine_sweeper()
{
	cout << " veuillez entrer un nombre de cellule .... " << endl;
	cin >> approximation_cellule;

	largeur = sqrtl(approximation_cellule);
	if (largeur > MAX_LARGEUR)
	{
		largeur = MAX_LARGEUR;
		hauteur = approximation_cellule / MAX_LARGEUR;
	}
	else
	{
		hauteur = largeur;
	}

	is_bombe = new bool*[hauteur];
	est_decouvert = new bool*[hauteur];
	compteur_de_bombe = new unsigned char*[hauteur];

	for (unsigned int row_count = 0; row_count < hauteur; row_count++)
	{
		is_bombe[row_count] = new bool[largeur]();
		est_decouvert[row_count] = new bool[largeur]();
		compteur_de_bombe[row_count] = new unsigned char[hauteur]();
	}

	cout << " veuillez entrer le niveau de difficulter 1 ... 100 " << endl;
	cin >> niveau;

	quantite_bombe = static_cast<uint32_t>((static_cast<uint64_t>(niveau)*static_cast<uint64_t>(largeur)*static_cast<uint64_t>(hauteur)) / static_cast<uint64_t>(100));

	for (unsigned int b_counter = 0, coordone_l, coordone_h; b_counter < quantite_bombe;)
	{
		coordone_l = rand() % largeur;
		coordone_h = rand() % hauteur;

		if (!is_bombe[coordone_h][coordone_l])
		{
			is_bombe[coordone_h][coordone_l] = true;
			cout << b_counter << " " << "(" << coordone_h << "," << coordone_l << ") " << endl;
			b_counter++;
		}
	}
	cout << endl;
	is_dead = false;
}


mine_sweeper::~mine_sweeper()
{
	for (unsigned int row_count = 0; row_count < hauteur; row_count++)
	{
		delete[] is_bombe[row_count];
		delete[] est_decouvert[row_count];
		delete[] compteur_de_bombe[row_count];
	}
	delete[] is_bombe;
	delete[] est_decouvert;
	delete[] compteur_de_bombe;
}

void mine_sweeper::afficher()
{
	if (is_dead)
	{
		for (unsigned int hauteur_counter = 0; hauteur_counter < hauteur; hauteur_counter++)
		{
			for (unsigned int largeur_counter = 0; largeur_counter < largeur; largeur_counter++)
			{
				if (est_decouvert[hauteur_counter][largeur_counter])
				{
					if (is_bombe[hauteur_counter][largeur_counter])
					{
						cout << "*";
					}
					else
					{
						cout << (unsigned short)compteur_de_bombe[hauteur_counter][largeur_counter];
					}
				}
				else
				{
					if (is_bombe[hauteur_counter][largeur_counter])
					{
						cout << "*";
					}
					else
					{
						cout << "X";
					}
				}
			}
			cout << endl;
		}

		cout << endl << "vous avez perdu ... retourne te pratiquer entre une valeur pour terminer" << endl;
	}
	else
	{
		for (unsigned int hauteur_counter = 0; hauteur_counter < hauteur; hauteur_counter++)
		{
			for (unsigned int largeur_counter = 0; largeur_counter < largeur; largeur_counter++)
			{
				if (est_decouvert[hauteur_counter][largeur_counter])
				{
					cout << (unsigned short)compteur_de_bombe[hauteur_counter][largeur_counter];
				}
				else
				{
					cout << "X";
				}
			}
			cout << endl;
		}
	}

}

unsigned int* mine_sweeper::saisie_utilisateur()
{
	unsigned int* coordone = new unsigned int[2];

	cout << endl << "veuillez entrer une coordone horizontal entre 0 et " << largeur << endl;
	cin >> coordone[0];

	cout << endl << "veuillez entrer une coordone vertical entre 0 et " << hauteur << endl;
	cin >> coordone[1];

	return coordone;
}

void mine_sweeper::traitement_bombe(unsigned int* coordonne)
{
	/*teste coin inferieur gauche
	XXX
	-XX
	--X
	*/

	est_decouvert[coordonne[0]][coordonne[1]] = true;
	if (coordonne[0] > 0)// on peut verifier coordonne[0] - 1
	{
		if (is_bombe[coordonne[0] - 1][coordonne[1]])
		{
			compteur_de_bombe[coordonne[0]][coordonne[1]]++;
		}

		if (coordonne[1] > 0)// on peut verifier coordonne[1] - 1
		{
			if (is_bombe[coordonne[0]][coordonne[1] - 1])
			{
				compteur_de_bombe[coordonne[0]][coordonne[1]]++;
			}
			if (is_bombe[coordonne[0] - 1][coordonne[1] - 1])
			{
				compteur_de_bombe[coordonne[0]][coordonne[1]]++;
			}
		}
	}
	else// on ne peut peut pas verifier coordonne[0] - 1
	{
		if (coordonne[1] > 0)// on peut verifier coordonne[1] - 1
		{
			if (is_bombe[coordonne[0]][coordonne[1] - 1])
			{
				compteur_de_bombe[coordonne[0]][coordonne[1]]++;
			}
		}
	}

	/*teste coin superieur droit
	X--
	XX-
	XXX
	*/
	if (coordonne[0] < hauteur - 1)// on peut verifier coordonne[0] - 1
	{
		if (is_bombe[coordonne[0] + 1][coordonne[1]])
		{
			compteur_de_bombe[coordonne[0]][coordonne[1]]++;
		}

		if (coordonne[1] < largeur - 1)// on peut verifier coordonne[1] - 1
		{
			if (is_bombe[coordonne[0]][coordonne[1] + 1])
			{
				compteur_de_bombe[coordonne[0]][coordonne[1]]++;
			}
			if (is_bombe[coordonne[0] + 1][coordonne[1] + 1])
			{
				compteur_de_bombe[coordonne[0]][coordonne[1]]++;
			}
		}
	}
	else// on ne peut peut pas verifier coordonne[0] - 1
	{
		if (coordonne[1] < largeur - 1)// on peut verifier coordonne[1] - 1
		{
			if (is_bombe[coordonne[0]][coordonne[1] + 1])
			{
				compteur_de_bombe[coordonne[0]][coordonne[1]]++;
			}
		}
	}

	/*teste coin superieur gauche
	-XX
	XXX
	XXX
	*/
	if (coordonne[0] < hauteur - 1)// on peut verifier coordonne[0] - 1
	{
		if (coordonne[1] > 0)// on peut verifier coordonne[1] - 1
		{
			if (is_bombe[coordonne[0] + 1][coordonne[1] - 1])
			{
				compteur_de_bombe[coordonne[0]][coordonne[1]]++;
			}
		}
	}

	/*teste coin inferieur droit
	XXX
	XXX
	XX-
	*/
	if (coordonne[0] > 0)// on peut verifier coordonne[0] - 1
	{
		if (coordonne[1] < largeur - 1)// on peut verifier coordonne[1] - 1
		{
			if (is_bombe[coordonne[0] - 1][coordonne[1] + 1])
			{
				compteur_de_bombe[coordonne[0]][coordonne[1]]++;
			}
		}
	}

	if (compteur_de_bombe[coordonne[0]][coordonne[1]] == 0)
	{
		if (coordonne[0] > 0)// on peut verifier coordonne[0] - 1
		{
			if (!est_decouvert[coordonne[0] - 1][coordonne[1]])
			{
				unsigned int*coordonne_ = new unsigned int[2];
				coordonne_[0] = coordonne[0] - 1;
				coordonne_[1] = coordonne[1];

				traitement_bombe(coordonne_);

				delete[] coordonne_;
			}
		}


		if (coordonne[0] < hauteur - 1)// on peut verifier coordonne[0] - 1
		{
			if (!est_decouvert[coordonne[0] + 1][coordonne[1]])
			{
				unsigned int*coordonne_ = new unsigned int[2];
				coordonne_[0] = coordonne[0] + 1;
				coordonne_[1] = coordonne[1];

				traitement_bombe(coordonne_);

				delete[] coordonne_;
			}
		}


		if (coordonne[1] < largeur - 1)// on peut verifier coordonne[0] - 1
		{
			if (!est_decouvert[coordonne[0]][coordonne[1] + 1])
			{
				unsigned int*coordonne_ = new unsigned int[2];
				coordonne_[0] = coordonne[0];
				coordonne_[1] = coordonne[1] + 1;

				traitement_bombe(coordonne_);

				delete[] coordonne_;
			}
		}

		if (coordonne[1] > 0)// on peut verifier coordonne[0] - 1
		{
			if (!est_decouvert[coordonne[0]][coordonne[1] - 1])
			{
				unsigned int*coordonne_ = new unsigned int[2];
				coordonne_[0] = coordonne[0];
				coordonne_[1] = coordonne[1] - 1;

				traitement_bombe(coordonne_);

				delete[] coordonne_;
			}

		}
	}

	return;
}

void mine_sweeper::premier_appel_traitement(unsigned int* coordonne)
{
	est_decouvert[coordonne[0]][coordonne[1]] = true;
	if (is_bombe[coordonne[0]][coordonne[1]])
	{
		is_dead = true;
	}
	else
	{
		traitement_bombe(coordonne);
	}
	delete[] coordonne;
}
