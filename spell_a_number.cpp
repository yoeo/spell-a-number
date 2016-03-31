/*
* Par: SOMDA Yandaar Déogracias Eric
* La nuit du 3 au 4 mars 2011.
*
* Traduction de nombre en lettres.
* Permet de traduire les nombres positifs, négatifs, reels
* vers leur écriture francaise.
*
* Remarques:
*    La traduction utilise «l'échelle longue» (numérotation française),
*    ainsi 1000 milliard = 1 billion.
*    Les méssages ne sont pas accentués, pour éviter d'éventuels bugs
*    d'affichage.
*/

#include<iostream>
#include<string>
#include<math.h>

// Nombre de noms repertoriés
#define MAX_NOMBRE 33
// Précision des nombres rééls
#define PRECISION 10

// Mille et Cent sont particuliers!
// Il n'y a pas de "un" qui les précède.
#define MILLE 1000
#define CENT 100

// Les mots spéciaux
#define SEPARATEUR " "
#define VIRGULE "virgule"
#define MOINS "moins"

using namespace std;
string convertir(double nbr);

string nom_nombre[] =
{
	"trillion", "billiard", "billion", "milliard", "million", "mille", "cent",
	"quatre-vingt", "soixante", "cinquante", "quarante", "trente", "vingt",
	"dix neuf", "dix huit", "dix sept",
	"seize", "quinze", "quatorze", "treize", "douze", "onze", "dix",
	"neuf", "huit", "sept", "six", "cinq", "quatre", "trois", "deux", "un",
	"zero"
};
double val_nombre[] =
{
	1e18, 1e15, 1e12, 1e9, 1e6, 1e3, 100,
	80, 60, 50, 40, 30, 20,
	19, 18, 17,
	16, 15, 14, 13, 12, 11, 10,
	9, 8, 7, 6, 5, 4, 3, 2, 1,
	0
};

int main()
{
	double nbr = 0;
	cout << endl;
	cout << "Nombres en toutes lettres ;)" << endl;
	cout << "Ce programme traduit les nombres en lettres!" << endl;
	cout << "ecrivez un nombre puis pressez <ENTRER>" << endl;
	while(1)
	{
		cout << endl;
		cout << "=> ";
		cin >> nbr;
		cout << convertir(nbr) << endl;
	}
	return 0;
}

string convertir(double nbr)
{
	string nombre = "";
	
	// Cas des nombres négatifs
	if (nbr < 0)
	{
		double postfix = -nbr;

		nombre.append(MOINS);
		nombre.append(SEPARATEUR);
		nombre.append(convertir(postfix));
	}
	// Cas des nombres à virgule
	// arondir la partie décimale pour éviter le bug de la virgule flotante.
	else if (nbr > floor(nbr))
	{
		double prefix = 0;
		double postfix = modf(nbr, &prefix);

		nombre.append(convertir(prefix));
		nombre.append(VIRGULE);
		nombre.append(SEPARATEUR);
		// 1 - epsilon: encore le bug de la virgule flotante X(
		while(postfix * 10 < 1 - 1e-10)
		{
			nombre.append(convertir(0.0));
			postfix *= 10;
		}
		postfix = fabs(round(postfix * pow(10, PRECISION)));
		while(fmod(postfix, 10.0) == 0) postfix /= 10;
		nombre.append(convertir(postfix));
	}
	else
	{
		for(int i = 0; i < MAX_NOMBRE; i++)
		{
			double val = val_nombre[i];
			string nom = nom_nombre[i];
		
			if(nbr >= val)
			{
				double prefix = floor(nbr / val);
				double postfix = nbr - (prefix * val);
	
				bool cond_prefix = !(
					(prefix == 1 && (val == MILLE || val <= CENT)) || prefix == 0);
				bool cond_postfix = !(postfix == 0);
			
				if(cond_prefix) nombre.append(convertir(prefix));
				nombre.append(nom);
				nombre.append(SEPARATEUR);
				if(postfix != 0) nombre.append(convertir(postfix));
				break;
			}
		}
	}
	return nombre;
}
