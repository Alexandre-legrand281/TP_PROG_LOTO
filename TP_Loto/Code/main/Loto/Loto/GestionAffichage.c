/*
GestionAffichage.c

autheur: VMD

*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>		// pour usage printf
#include <stdint.h>		// uniformation du type entier 
#include <stdbool.h>

#include "main.h"
#include "GestionFichier.h"
#include "GestionAffichage.h"
#include "InterfaceUser.h" 

/*
les fonction en char ou en void
                                 */

//declaration structure
s_Valeur valeur;

void TheBestWinnumber(char cheminLog[])
{
	// Appel fonction de recherche de la meilleur valeur
	Recherche(cheminLog);

	// Affichage de la meilleur valeur
	printf("\nLa meilleur valeur est : %d\n", valeur.meilleurValeur);
}

void TheBadestNumber (char cheminLog[])
{
	// Appel fonction de recherche de la pire valeur
	Recherche(cheminLog);

	// Affichage de la meilleur valeur
	printf("\nLa pire valeur est : %d\n", valeur.pireValeur);
}

void WinNumbers (char cheminLog[])
{
	// Appel fonction de recherche de la pire valeur
	Recherche(cheminLog);

	//appel fonction recherche ou utilisation Structure
	printf("\nLes numeros les plus gagnant sont: %d, %d, %d, %d, %d, %d\n", 
	valeur.numeroGagnant[0], valeur.numeroGagnant[1], valeur.numeroGagnant[2], valeur.numeroGagnant[3], 
	valeur.numeroGagnant[4], valeur.numeroGagnant[5]);
}

void AffichageSimulation(int* randomTable, int nbValeurs, int* randomComp, int nbComp)
{
	printf("\n----------------- Resultats de la Simulation -----------------\n");

	// Affichage des numéros principaux
	printf("Numeros principaux : ");
	for (int i = 0; i < nbValeurs; i++)
	{
		printf("[%d] ", randomTable[i]);
	}
	printf("\n");

	// Affichage des numéros complémentaires (s'il y en a eu de générés)
	if (randomComp != NULL && nbComp > 0)
	{
		printf("Numeros complementaires : ");
		for (int i = 0; i < nbComp; i++)
		{
			printf("{%d} ", randomComp[i]);
		}
		printf("\n");
	}

	printf("--------------------------------------------------------------\n\n");
}

void LoseNumbers (char cheminLog[])
{
	// Appel fonction de recherche de la pire valeur
	Recherche(cheminLog);

	//appel fonction recherche ou utilisation Structure
	printf("\nLes numeros perdant sont: %d, %d, %d, %d, %d, %d\n",
	valeur.numeroPerdant[0], valeur.numeroPerdant[1], valeur.numeroPerdant[2], valeur.numeroPerdant[3],
	valeur.numeroPerdant[4], valeur.numeroPerdant[5]);
}