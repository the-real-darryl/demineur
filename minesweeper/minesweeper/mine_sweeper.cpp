#include "stdafx.h"
#include "mine_sweeper.h"
#include <iostream>
#include <math.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>

#define MAX_LARGEUR 50


using namespace std;

mine_sweeper::mine_sweeper()
{
	quitter = false;
	connu = false;
	is_dead = false;
	as_won = false;
	coups = 0;


	char temp[100];
DEBUT:
	cout << "souhaitez-vous commencer une nouvelle partie ? (O/o)/(N/n)" << endl;
	cin >> temp;

	switch (temp[0])
	{
	case 'O':
		break;;
	case 'o':
		break;
	case 'N':
		connu = true;
		lecture_fichier();
		break;
	case 'n':
		connu = true;
		lecture_fichier();
		break;
	default:
		cout << "s'il vous plait entrer l'un des charactere proposer, vous me rendez la vie difficile" << endl;
		goto DEBUT;
	}


	if (!connu)
	{
		cout << " veuillez entrer votre nom" << endl;
		cin >> nom_joueur;

		cout << "bonjour " << nom_joueur << endl;

		do
		{
			cout << " veuillez entrer un nombre de cellule .... " << endl;
			cin >> approximation_cellule;
			if (approximation_cellule < 9)
			{
				cout << "vous devez entrer au moin 9 case !" << endl << endl;
			}
		} while (approximation_cellule < 9);


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

		case_ = new Case*[hauteur];
		for (unsigned int i = 0; i < hauteur; i++)
		{
			case_[i] = new Case[largeur];
		}

		cout << " veuillez entrer le niveau de difficulter 1 ... 100 " << endl;
		cin >> niveau;

		quantite_bombe = static_cast<uint32_t>((static_cast<uint64_t>(niveau)*static_cast<uint64_t>(largeur)*static_cast<uint64_t>(hauteur)) / static_cast<uint64_t>(100));

		historique_des_coup = new unsigned int[((unsigned long long)largeur*(unsigned long long)hauteur - (unsigned long long)quantite_bombe) << 1];

		for (unsigned int b_counter = 0, coordone_l, coordone_h; b_counter < quantite_bombe;)
		{
			coordone_l = rand() % largeur;
			coordone_h = rand() % hauteur;

			if (!case_[coordone_h][coordone_l].get_is_bombe())
			{
				case_[coordone_h][coordone_l].set_is_bombe(true);
				//cout << b_counter << " " << "(" << coordone_h << "," << coordone_l << ") " << endl;
				b_counter++;
			}
		}
		cout << endl;
	}


	for (unsigned int quotient = largeur; quotient; charactere_par_cellule_largeur++)
	{
		quotient /= 10;
	}
	for (unsigned int quotient = hauteur; quotient; ++charactere_par_cellule_hauteur)
	{
		quotient /= 10;
	}
}


mine_sweeper::~mine_sweeper()
{
	for (unsigned int i = 0; i < hauteur; i++)
	{
		delete[] case_[i];
	}
	delete[] case_;
	delete[] historique_des_coup;
}

void mine_sweeper::afficher()
{
	if (is_dead)
	{
		afficher_premier_ligne();

		for (unsigned int hauteur_counter = 0, puissace_dix_hauteur = 1, c = 0; hauteur_counter < hauteur; hauteur_counter++)
		{
			if (hauteur_counter + 1 == 10 * puissace_dix_hauteur)
			{
				puissace_dix_hauteur *= 10;
				c++;
			}
			for (unsigned char i = c; i < charactere_par_cellule_hauteur; i++)
			{
				cout << " ";
			}
			cout << hauteur_counter + 1 << " ";
			for (unsigned int largeur_counter = 0; largeur_counter < largeur; largeur_counter++)
			{
				if (case_[hauteur_counter][largeur_counter].get_est_decouvert())
				{
					if (case_[hauteur_counter][largeur_counter].get_is_bombe())
					{
						cout << "*";
					}
					else
					{
						cout << (unsigned short)case_[hauteur_counter][largeur_counter].get_compteur_de_bombe();
					}
				}
				else
				{
					if (case_[hauteur_counter][largeur_counter].get_is_bombe())
					{
						cout << "*";
					}
					else
					{
						cout << "X";
					}
				}

				for (unsigned char i = 0; i < charactere_par_cellule_largeur; i++)
				{
					cout << " ";
				}
			}
			cout << endl;
		}

		cout << endl << "vous avez perdu ... retournez vous pratiquer" << endl << endl;
	}
	else if (as_won)
	{
		afficher_premier_ligne();

		for (unsigned int hauteur_counter = 0, puissace_dix_hauteur = 1, c = 0; hauteur_counter < hauteur; hauteur_counter++)
		{
			if (hauteur_counter + 1 == 10 * puissace_dix_hauteur)
			{
				puissace_dix_hauteur *= 10;
				c++;
			}
			for (unsigned char i = c; i < charactere_par_cellule_hauteur; i++)
			{
				cout << " ";
			}
			cout << hauteur_counter + 1 << " ";
			for (unsigned int largeur_counter = 0; largeur_counter < largeur; largeur_counter++)
			{
				if (case_[hauteur_counter][largeur_counter].get_est_decouvert())
				{
					if (case_[hauteur_counter][largeur_counter].get_is_bombe())
					{
						cout << "*";
					}
					else
					{
						cout << (unsigned short)case_[hauteur_counter][largeur_counter].get_compteur_de_bombe();
					}
				}
				else
				{
					if (case_[hauteur_counter][largeur_counter].get_is_bombe())
					{
						cout << "*";
					}
					else
					{
						cout << "X";
					}
				}

				for (unsigned char i = 0; i < charactere_par_cellule_largeur; i++)
				{
					cout << " ";
				}
			}
			cout << endl;
		}

		cout << endl << nom_joueur << " vous avez gagner ... vous etes incroyable !" << endl << endl;
		cout << "vous avez reussis en " << coups << " coups sur une grille de " << static_cast<unsigned long long> (largeur)*static_cast<unsigned long long>(hauteur) << " cellules " << endl << "voici votre score : " << score << " jouer le " << date << endl;
	}
	else if (quitter)
	{
		cout << "vous avez quitter ... lache!" << endl;
	}
	else
	{
		afficher_premier_ligne();

		for (unsigned int hauteur_counter = 0, puissace_dix_hauteur = 1, c = 0; hauteur_counter < hauteur; hauteur_counter++)
		{
			if (hauteur_counter + 1 == 10 * puissace_dix_hauteur)
			{
				puissace_dix_hauteur *= 10;
				c++;
			}
			for (unsigned char i = c; i < charactere_par_cellule_hauteur; i++)
			{
				cout << " ";
			}
			cout << hauteur_counter + 1 << " ";

			for (unsigned int largeur_counter = 0; largeur_counter < largeur; largeur_counter++)
			{
				if (case_[hauteur_counter][largeur_counter].get_est_decouvert())
				{
					cout << (unsigned short)case_[hauteur_counter][largeur_counter].get_compteur_de_bombe();
				}
				else
				{
					cout << "X";
				}

				for (unsigned char i = 0; i < charactere_par_cellule_largeur; i++)
				{
					cout << " ";
				}
			}
			cout << endl;
		}
	}
}

unsigned int* mine_sweeper::saisie_utilisateur()
{
	unsigned int* coordone = new unsigned int[2];
	do
	{
		char in[1000] = {};
		char* in_;

		coordone[0] = 0;
		coordone[1] = 0;
		cout << endl << "entrer une coordonne de valeurs 0 pour quitter" << endl << endl;
		cout << endl << "veuillez entrer une coordone hauteur entre 1 et " << hauteur << endl;
		cin >> in;
		coordone[0] = strtol(in, &in_, 10);

		if (coordone[0] == 0)
		{
			quitter = true;
			menu_quitter();
			return coordone;
		}


		cout << "veuillez entrer une coordone largeur entre 1 et " << largeur << endl;
		cin >> in;
		coordone[1] = strtol(in, &in_, 10);

		if (coordone[1] == 0)
		{
			quitter = true;
			menu_quitter();
			return coordone;
		}
	} while ((coordone[0] > hauteur || coordone[1] > largeur) && cout << endl << "entrer une coordonne possible!" << endl << endl);

	historique_des_coup[coups << 1] = --coordone[0];
	historique_des_coup[(coups << 1) + 1] = --coordone[1];

	coups++;

	return coordone;
}

void inline mine_sweeper::traitement_low_level(unsigned int* coordonne)
{
	if (!case_[coordonne[0]][coordonne[1]].get_est_decouvert())
	{
		traitement_bombe(coordonne);
	}
}

void mine_sweeper::traitement_bombe(unsigned int* coordonne)
{
	case_[coordonne[0]][coordonne[1]].set_est_decouvert(true);
	Case::increment_cellule_est_decouverte();

	if (coordonne[0] > 0)
	{
		if (case_[coordonne[0] - 1][coordonne[1]].get_is_bombe())//-1,0
		{
			case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
		}
		if (coordonne[1] > 0)
		{
			if (case_[coordonne[0]][coordonne[1] - 1].get_is_bombe())//0,-1
			{
				case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
			}
			if (case_[coordonne[0] - 1][coordonne[1] - 1].get_is_bombe())//-1,-1
			{
				case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
			}
			if (coordonne[0] < hauteur - 1)
			{
				if (case_[coordonne[0] + 1][coordonne[1]].get_is_bombe())//1,0
				{
					case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
				}
				if (case_[coordonne[0] + 1][coordonne[1] - 1].get_is_bombe())//1,-1
				{
					case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
				}
				if (coordonne[1] < largeur - 1)
				{
					/*
					---
					-0-
					---
					*/
					if (case_[coordonne[0]][coordonne[1] + 1].get_is_bombe())//0,1
					{
						case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
					}
					if (case_[coordonne[0] - 1][coordonne[1] + 1].get_is_bombe())//-1,1
					{
						case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
					}
					if (case_[coordonne[0] + 1][coordonne[1] + 1].get_is_bombe())//1,1
					{
						case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
					}

					if (!case_[coordonne[0]][coordonne[1]].get_compteur_de_bombe())
					{
						coordonne[0]--;//-1
						traitement_low_level(coordonne);//-1,0
						coordonne[0]++;//0
						coordonne[1]--;//-1
						traitement_low_level(coordonne);//0,-1
						coordonne[0]--;//-1
						traitement_low_level(coordonne);//-1,-1
						coordonne[0] += 2;//1
						coordonne[1]++;//0
						traitement_low_level(coordonne);//1,0
						coordonne[1]--;//-1
						traitement_low_level(coordonne);//1,-1
						coordonne[0]--;//0
						coordonne[1] += 2;//1
						traitement_low_level(coordonne);//0,1
						coordonne[0]--;//-1
						traitement_low_level(coordonne);//-1,1
						coordonne[0] += 2;//1
						traitement_low_level(coordonne);//1,1
						coordonne[0]--;//0
						coordonne[1]--;//0
					}
				}
				else
				{
					/*
					x--
					x-0
					x--
					*/

					if (!case_[coordonne[0]][coordonne[1]].get_compteur_de_bombe())
					{
						coordonne[0]--;//-1
						traitement_low_level(coordonne);//-1,0
						coordonne[0]++;//0
						coordonne[1]--;//-1
						traitement_low_level(coordonne);//0,-1
						coordonne[0]--;//-1
						traitement_low_level(coordonne);//-1,-1
						coordonne[0] += 2;//1
						coordonne[1]++;//0
						traitement_low_level(coordonne);//1,0
						coordonne[1]--;//-1
						traitement_low_level(coordonne);//1,-1
						coordonne[0]--;//0
						coordonne[1]++;//0
					}
				}
			}
			else
			{
				if (coordonne[1] < largeur - 1)
				{
					/*
					xxx
					---
					-0-
					*/
					if (case_[coordonne[0]][coordonne[1] + 1].get_is_bombe())//0,1
					{
						case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
					}
					if (case_[coordonne[0] - 1][coordonne[1] + 1].get_is_bombe())//-1,1
					{
						case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
					}

					if (!case_[coordonne[0]][coordonne[1]].get_compteur_de_bombe())
					{
						coordonne[0]--;//-1
						traitement_low_level(coordonne);//-1,0
						coordonne[0]++;//0
						coordonne[1]--;//-1
						traitement_low_level(coordonne);//0,-1
						coordonne[0]--;//-1
						traitement_low_level(coordonne);//-1,-1
						coordonne[0]++;//0
						coordonne[1] += 2;//1
						traitement_low_level(coordonne);//0,1
						coordonne[0]--;//-1
						traitement_low_level(coordonne);//-1,1
						coordonne[0]++;//0
						coordonne[1]--;//0
					}
				}
				else
				{
					/*
					xxx
					x--
					x-0
					*/
					if (case_[coordonne[0] - 1][coordonne[1]].get_is_bombe())//-1,0
					{
						case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
					}

					if (!case_[coordonne[0]][coordonne[1]].get_compteur_de_bombe())
					{
						coordonne[0]--;//-1
						traitement_low_level(coordonne);//-1,0
						coordonne[0]++;//0
						coordonne[1]--;//-1
						traitement_low_level(coordonne);//0,-1
						coordonne[0]--;//-1
						traitement_low_level(coordonne);//-1,-1
						coordonne[0]++;//0
						coordonne[1]++;//0
					}
				}
			}
		}
		else
		{
			if (coordonne[0] < hauteur - 1)
			{
				if (coordonne[1] < largeur - 1)
				{
					/*
					--x
					0-x
					--x
					*/
					if (case_[coordonne[0] + 1][coordonne[1]].get_is_bombe())//1,0
					{
						case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
					}
					if (case_[coordonne[0]][coordonne[1] + 1].get_is_bombe())//0,1
					{
						case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
					}
					if (case_[coordonne[0] - 1][coordonne[1] + 1].get_is_bombe())//-1,1
					{
						case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
					}
					if (case_[coordonne[0] + 1][coordonne[1] + 1].get_is_bombe())//1,1
					{
						case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
					}

					if (!case_[coordonne[0]][coordonne[1]].get_compteur_de_bombe())
					{
						coordonne[0]--;//-1
						traitement_low_level(coordonne);//-1,0
						coordonne[0] += 2;//1
						traitement_low_level(coordonne);//1,0
						coordonne[0]--;//0
						coordonne[1]++;//1
						traitement_low_level(coordonne);//0,1
						coordonne[0]--;//-1
						traitement_low_level(coordonne);//-1,1
						coordonne[0] += 2;//1
						traitement_low_level(coordonne);//1,1
						coordonne[0]--;//0
						coordonne[1]--;//0
					}
				}
			}
			else
			{
				if (coordonne[1] < largeur - 1)
				{
					/*
					xxx
					--x
					0-x
					*/
					if (case_[coordonne[0]][coordonne[1] + 1].get_is_bombe())//0,1
					{
						case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
					}
					if (case_[coordonne[0] - 1][coordonne[1] + 1].get_is_bombe())//-1,1
					{
						case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
					}

					if (!case_[coordonne[0]][coordonne[1]].get_compteur_de_bombe())
					{
						coordonne[0]--;//-1
						traitement_low_level(coordonne);//-1,0
						coordonne[0]++;//0
						coordonne[1]++;//1
						traitement_low_level(coordonne);//0,1
						coordonne[0]--;//-1
						traitement_low_level(coordonne);//-1,1
						coordonne[0]++;//0
						coordonne[1]--;//0
					}
				}
			}
		}
	}
	else
	{
		if (coordonne[1] > 0)
		{
			if (case_[coordonne[0]][coordonne[1] - 1].get_is_bombe())//0,-1
			{
				case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
			}
			if (coordonne[0] < hauteur - 1)
			{
				if (case_[coordonne[0] + 1][coordonne[1]].get_is_bombe())//1,0
				{
					case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
				}
				if (case_[coordonne[0] + 1][coordonne[1] - 1].get_is_bombe())//1,-1
				{
					case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
				}
				if (coordonne[1] < largeur - 1)
				{
					/*
					-0-
					---
					xxx
					*/
					if (case_[coordonne[0]][coordonne[1] + 1].get_is_bombe())//0,1
					{
						case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
					}
					if (case_[coordonne[0] + 1][coordonne[1] + 1].get_is_bombe())//1,1
					{
						case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
					}

					if (!case_[coordonne[0]][coordonne[1]].get_compteur_de_bombe())
					{
						coordonne[1]--;//-1
						traitement_low_level(coordonne);//0,-1
						coordonne[0]++;//1
						coordonne[1]++;//0
						traitement_low_level(coordonne);//1,0
						coordonne[1]--;//-1
						traitement_low_level(coordonne);//1,-1
						coordonne[0]--;//0
						coordonne[1] += 2;//1
						traitement_low_level(coordonne);//0,1
						coordonne[0]++;//1
						traitement_low_level(coordonne);//1,1
						coordonne[1]--;//0
						coordonne[0]--;//0
					}
				}
				else
				{
					/*
					x-0
					x--
					xxx
					*/

					if (!case_[coordonne[0]][coordonne[1]].get_compteur_de_bombe())
					{
						coordonne[1]--;//-1
						traitement_low_level(coordonne);//0,-1
						coordonne[0]++;//1
						coordonne[1]++;//0
						traitement_low_level(coordonne);//1,0
						coordonne[1]--;//-1
						traitement_low_level(coordonne);//1,-1
						coordonne[1]++;//0
						coordonne[0]--;//0
					}
				}
			}
		}
		else
		{
			/*
			0-x
			--x
			xxx
			*/
			if (case_[coordonne[0] + 1][coordonne[1]].get_is_bombe())//1,0
			{
				case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
			}
			if (case_[coordonne[0]][coordonne[1] + 1].get_is_bombe())//0,1
			{
				case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
			}
			if (case_[coordonne[0] + 1][coordonne[1] + 1].get_is_bombe())//1,1
			{
				case_[coordonne[0]][coordonne[1]].increment_compteur_de_bombe();
			}

			if (!case_[coordonne[0]][coordonne[1]].get_compteur_de_bombe())
			{
				coordonne[0]++;//1
				traitement_low_level(coordonne);//1,0
				coordonne[0]--;//0
				coordonne[1]++;//1
				traitement_low_level(coordonne);//0,1
				coordonne[0]++;//1
				traitement_low_level(coordonne);//1,1
				coordonne[0]--;//0
				coordonne[1]--;//0
			}
		}
	}


	return;
}

void mine_sweeper::premier_appel_traitement(unsigned int* coordonne)
{
	if (!quitter)
	{
		if (case_[coordonne[0]][coordonne[1]].get_is_bombe())
		{
			case_[coordonne[0]][coordonne[1]].set_est_decouvert(true);
			is_dead = true;
		}
		else
		{
			if (!case_[coordonne[0]][coordonne[1]].get_est_decouvert())
			{
				traitement_bombe(coordonne);
			}
			else
			{
				cout << "Cette case est deja decouverte !" << endl << endl;
			}
		}
	}

	delete[] coordonne;

	return;
}

void mine_sweeper::verification_gagner()
{
	if (!is_dead)
	{
		if (Case::cellule_decouverte + quantite_bombe == largeur * hauteur)
		{
			as_won = true;
			calculer_score();

			time_t now = time(0);

			ctime_s(date, sizeof(date), &now);
		}
	}
}

void mine_sweeper::rejouer_la_partie()
{
	if (connu)
	{
		for (unsigned int i = 0; i < coups; i++)
		{
			unsigned int* c = new unsigned int[2];
			c[0] = historique_des_coup[i << 1];
			c[1] = historique_des_coup[(i << 1) + 1];

			premier_appel_traitement(c);
			verification_gagner();
			cout << endl << endl << "hauteur " << c[0] << "  largeur " << c[1] << endl << endl;
			afficher();
		}
	}
}

void mine_sweeper::lecture_fichier()
{
	cout << "entrer un  nom de fichier" << endl;
	string nom_fichier;
	cin >> nom_fichier;
	nom_fichier += ".dat";

	std::fstream flux(nom_fichier.c_str(), std::ios::binary | std::ios::in);// = new fstream(file_name.c_str());
	if (flux)
	{
		connu = true;
		flux.read((char*)&largeur, sizeof(largeur));
		flux.read((char*)&hauteur, sizeof(hauteur));
		flux.read((char*)&quantite_bombe, sizeof(quantite_bombe));
		flux.read((char*)&niveau, sizeof(niveau));

		case_ = new Case*[hauteur];

		for (unsigned int h = 0; h < hauteur; h++)
		{
			case_[h] = new Case[largeur];
			for (unsigned int l = 0; l < largeur; l++)
			{
				flux.read((char*)&case_[h][l], sizeof(Case));
			}
		}

		size_t s;
		flux.read((char*)&s, sizeof(s));

		char* temp = new char[s + 1];


		flux.read(temp, s);

		temp[s] = '\0';

		nom_joueur = temp;

		delete[] temp;

		flux.read((char*)&coups, sizeof(coups));

		historique_des_coup = new unsigned int[2 * coups];
		flux.read((char*)historique_des_coup, 2 * coups * sizeof(historique_des_coup));
	}
	else
	{
		connu = false;
	}
	flux.close();
}

void mine_sweeper::ecriture_fichier()
{
	cout << "entrer un  nom de fichier" << endl;
	string nom_fichier;
	cin >> nom_fichier;
	nom_fichier += ".dat";

	std::fstream flux(nom_fichier.c_str(), std::ios::binary | std::ios::out | std::ios::trunc);// = new fstream(file_name.c_str());

	if (!(as_won || is_dead))
	{
		//unsigned char* data = new unsigned char[1 + sizeof(nom_joueur.length()) + sizeof(coups) + 2 * coups * sizeof(historique_des_coup)];
		flux.write((const char*)&largeur, sizeof(largeur));
		flux.write((const char*)&hauteur, sizeof(hauteur));
		flux.write((const char*)&quantite_bombe, sizeof(quantite_bombe));
		flux.write((const char*)&niveau, sizeof(niveau));

		for (unsigned int h = 0; h < hauteur; h++)
		{
			for (unsigned int l = 0; l < largeur; l++)
			{
				flux.write((const char*)&case_[h][l], sizeof(Case));
			}
		}

		size_t s = nom_joueur.length();
		flux.write((const char*)&s, sizeof(s));

		flux.write(nom_joueur.c_str(), nom_joueur.length());

		flux.write((const char*)&coups, sizeof(coups));

		flux.write((const char*)historique_des_coup, 2 * coups * sizeof(historique_des_coup));
	}
	flux.close();
}

void mine_sweeper::menu_quitter()
{
	char reponse[1000] = {};
DEBUT:
	cout << nom_joueur << " desirer vous sauveguarder ? (O/o)/(N/n)" << endl;
	cin >> reponse;

	switch (reponse[0])
	{
	case 'O':
		ecriture_fichier();
		return;;
	case 'o':
		ecriture_fichier();
		return;
	case 'N':
		return;
	case 'n':
		return;
	default:
		cout << "s'il vous plait entrer l'un des charactere proposer, vous me rendez la vie difficile" << endl;
		goto DEBUT;
	}
}

void mine_sweeper::calculer_score()
{
	score = (static_cast<double>(largeur)*static_cast<double>(hauteur) / static_cast<double>(coups))*(static_cast<double>(1) + static_cast<double>(niveau) / static_cast<double>(100));
}

void mine_sweeper::afficher_premier_ligne()
{
	for (unsigned char a = 0; a < charactere_par_cellule_hauteur; a++)
	{
		cout << " ";
	}
	for (unsigned int i = 0, puissance_dix_largeur = 1, d = 0; i < largeur + 1; i++)
	{
		if (i != 0)
		{
			if (i == 10 * puissance_dix_largeur)
			{
				puissance_dix_largeur *= 10;
				d++;
			}
			for (unsigned char i1 = d; i1 < charactere_par_cellule_largeur; i1++)
			{
				cout << " ";
			}

			cout << i;
		}
	}
	cout << endl;
}

unsigned long long Case::cellule_decouverte = 0;

int main()
{

	mine_sweeper the_game;


	the_game.rejouer_la_partie();

	while (!the_game.is_dead && !the_game.as_won && !the_game.quitter)
	{
		the_game.premier_appel_traitement(the_game.saisie_utilisateur());
		the_game.verification_gagner();
		the_game.afficher();
	}

	return 0;
}