#include "stdafx.h"
#include "mine_sweeper_multijoueurs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#define FILE_NAME "mine_sweeper.bin"

mine_sweeper_multijoueurs::mine_sweeper_multijoueurs()
{
}


mine_sweeper_multijoueurs::~mine_sweeper_multijoueurs()
{
}

void mine_sweeper_multijoueurs::write_file()
{
	//concatenating the name of the file based on where we are in the loop
	std::string file_name = FILE_NAME;
	std::fstream flux;// = new fstream(file_name.c_str());
	flux.open(file_name.c_str(), std::ios::binary | std::ios::in);

	//calculating the size of the file
	std::streampos begin = flux.tellg();
	flux.seekg(0, std::ios::end);
	std::streampos end = flux.tellg();
	std::streampos size = end - begin;

	uint8_t* raw_input = new uint8_t[size];
	unsigned int input_reader = 0;

	//reading the file
	flux.read(reinterpret_cast<char *>(raw_input), size);

	joueurs = *((unsigned int*)raw_input);
	input_reader += sizeof(joueurs);


	longueur_nom = new unsigned short[joueurs];
	dates = new DATE*[joueurs];
	coups_ = new unsigned int*[joueurs];
	scores = new double*[joueurs];
	taille_jeux = new unsigned long long*[joueurs];
	coordonne_meilleur_partit_par_joueur = new unsigned int[joueurs];
	partit_par_joueur = new unsigned int[joueurs];

	for (unsigned int joueur_counter = 0; joueur_counter < joueurs; joueur_counter++)
	{
		longueur_nom[joueur_counter] = *((unsigned int*)(raw_input + input_reader));
		input_reader += sizeof(longueur_nom[joueur_counter]);

		memcpy(noms, (unsigned int*)(raw_input + input_reader), longueur_nom[joueur_counter]);
		input_reader += longueur_nom[joueur_counter] * sizeof(*noms);

		coordonne_meilleur_partit_par_joueur[joueur_counter] = *((unsigned int*)(raw_input + input_reader));
		input_reader += sizeof(coordonne_meilleur_partit_par_joueur[joueur_counter]);

		partit_par_joueur[joueur_counter] = *((unsigned int*)(raw_input + input_reader));
		input_reader += sizeof(partit_par_joueur[joueur_counter]);

		for (unsigned int partit_counter = 0; partit_counter < partit_par_joueur[joueur_counter]; partit_counter++)
		{
			memcpy(dates[joueur_counter][partit_counter], (char*)(raw_input + input_reader), LONGUEUR_DATE);
			input_reader += sizeof(DATE);

			coups_[joueur_counter][partit_counter] = *((unsigned int*)(raw_input + input_reader));
			input_reader += sizeof(coups_[joueur_counter][partit_counter]);

			scores[joueur_counter][partit_counter] = *((double*)(raw_input + input_reader));
			input_reader += sizeof(scores[joueur_counter][partit_counter]);

			taille_jeux[joueur_counter][partit_counter] = *((unsigned int*)(raw_input + input_reader));
			input_reader += sizeof(taille_jeux[joueur_counter][partit_counter]);
		}

	}

	flux.close();
	delete[] raw_input;
}

void mine_sweeper_multijoueurs::read_file()
{
	//concatenating the name of the file based on where we are in the loop
	std::string file_name = FILE_NAME;
	std::fstream flux;// = new fstream(file_name.c_str());
	flux.open(file_name.c_str(), std::ios::binary | std::ios::in);

	//calculating the size of the file
	std::streampos begin = flux.tellg();
	flux.seekg(0, std::ios::end);
	std::streampos end = flux.tellg();
	std::streampos size = end - begin;

	uint8_t* raw_input = new uint8_t[size];
	unsigned int input_reader = 0;

	//reading the file
	flux.read(reinterpret_cast<char *>(raw_input), size);

	joueurs = *((unsigned int*)raw_input);
	input_reader += sizeof(joueurs);


	longueur_nom = new unsigned short[joueurs];
	dates = new DATE*[joueurs];
	coups_ = new unsigned int*[joueurs];
	scores = new double*[joueurs];
	taille_jeux = new unsigned long long*[joueurs];
	coordonne_meilleur_partit_par_joueur = new unsigned int[joueurs];
	partit_par_joueur = new unsigned int[joueurs];

	for (unsigned int joueur_counter = 0; joueur_counter < joueurs; joueur_counter++)
	{
		longueur_nom[joueur_counter] = *((unsigned int*)(raw_input + input_reader));
		input_reader += sizeof(longueur_nom[joueur_counter]);

		memcpy(noms, (unsigned int*)(raw_input + input_reader), longueur_nom[joueur_counter]);
		input_reader += longueur_nom[joueur_counter] * sizeof(*noms);

		coordonne_meilleur_partit_par_joueur[joueur_counter] = *((unsigned int*)(raw_input + input_reader));
		input_reader += sizeof(coordonne_meilleur_partit_par_joueur[joueur_counter]);

		partit_par_joueur[joueur_counter] = *((unsigned int*)(raw_input + input_reader));
		input_reader += sizeof(partit_par_joueur[joueur_counter]);

		for (unsigned int partit_counter = 0; partit_counter < partit_par_joueur[joueur_counter]; partit_counter++)
		{
			memcpy(dates[joueur_counter][partit_counter], (char*)(raw_input + input_reader), LONGUEUR_DATE);
			input_reader += sizeof(DATE);

			coups_[joueur_counter][partit_counter] = *((unsigned int*)(raw_input + input_reader));
			input_reader += sizeof(coups_[joueur_counter][partit_counter]);

			scores[joueur_counter][partit_counter] = *((double*)(raw_input + input_reader));
			input_reader += sizeof(scores[joueur_counter][partit_counter]);

			taille_jeux[joueur_counter][partit_counter] = *((unsigned int*)(raw_input + input_reader));
			input_reader += sizeof(taille_jeux[joueur_counter][partit_counter]);
		}

	}

	flux.close();
	delete[] raw_input;
}

void mine_sweeper_multijoueurs::comparer()
{
}

void mine_sweeper_multijoueurs::menu()
{
}
