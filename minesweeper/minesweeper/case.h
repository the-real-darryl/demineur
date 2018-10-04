#pragma once
class Case
{
public:
	Case();
	~Case();
	bool get_is_bombe();
	void set_is_bombe(bool);

	unsigned char get_compteur_de_bombe();
	void increment_compteur_de_bombe();

	bool get_est_decouvert();
	void set_est_decouvert(bool);
	static void increment_cellule_est_decouverte();


private:
	bool is_bombe;
	unsigned char compteur_de_bombe;
	bool est_decouvert;
public:
	static unsigned long long cellule_decouverte;
	//static unsigned int bombe_decouverte;
};

