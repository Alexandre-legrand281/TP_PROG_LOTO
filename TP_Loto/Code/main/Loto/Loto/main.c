//-----------------------------------------------------------------------------------//
// Nom du projet 		: Loto
// Nom du fichier 		: main.c
// Date de création 	: 22.05.2026
// Date de modification : 08.06.2026
//
// Auteur 				: AOD
//
// Description          : Ce fichier est le programme principal de mon projet. Il va
//						  principallement faire des appel de fonctions des autres fichiers
//						  .c de ce projet
//
// Remarques			: 
//
//----------------------------------------------------------------------------------//

#define _CRT_SECURE_NO_WARNINGS

// Librairies Standars
#include <stdio.h>		// pour usage printf
#include <stdint.h>		// uniformation du type entier 
#include <stdbool.h>
#include <time.h> // pour randomizer nombre
#include <stdlib.h> // pour srand ( randomizer nombre)

// Librairies personnelle
#include "main.h"
#include "GestionFichier.h"
#include "GestionAffichage.h"
#include "InterfaceUser.h" 

int main(void)
{
	// Initialisation de la variable locale
	int optionUser = 0;
	char reponseUser = 0;
	char lotoName[41] = "";
	char cheminLog[60] = "Logs/";

	do
	{
		// Affichage menu
		printf("\n========================================================================\n");
		printf("			   ANALYSEUR DE LOTO\n");
		printf("			   Par: AOD, SVD, VMD\n");
		printf("========================================================================\n\n");

		// Selection du type nom du loto
		printf("Veuillez ecrire le nom du loto que vous voulez analyser (Sans Espaces):\n");
		printf("(Appuyer sur Q si vous voulez quitter le programme)\n\n>");
		
		// Récéption du loto ecrit par l'utilisateur
		scanf("%40s", &lotoName);

		// Si la valeur reçu n'est pas celle de quitter
		if ((lotoName[0] != Quitter) && (lotoName[1] != 0))
		{
			// Si l'utilisateur tape un nom de loto qui existe, alors le chemin seras Logs/logNomDuLoto.txt
			snprintf(cheminLog, sizeof(cheminLog), "Logs/log%s.txt", lotoName);

			// On essaie d'ouvrir le fichier en mode lecture read
			FILE* fichierLog = fopen(cheminLog, "r");

			// Si ce fichier peut etre lu, alors on rentre dans le programme principal
			if (fichierLog != NULL)
			{
				fclose(fichierLog);

				printf("\nVeuillez choisir une des options suivantes:\n");
				printf("(1) Afficher la valeur la plus gagnante\n");
				printf("(2) Afficher la valeur la moins gagnante\n");
				printf("(3) Afficher les 6 meilleurs numeros\n");
				printf("(4) Afficher les 6 moins bon numeros\n");
				printf("(5) Insertion d'une valeur\n");
				printf("(6) Supprimer la derniere valeur inseree\n");
				printf("(7) Modifier la derniere valeur inseree\n");
				printf("(8) Simuler des valeurs de loto\n\n>");

				// Récéption de la valeur souhaité
				scanf("%d", &optionUser);

				// Appel a la fonction selon le choix de l'utilisateur
				switch (optionUser)
				{
					// Afficher la valeur la plus gagnante
				case OPTION_1:
					// Appel de la fonction d'affichage de la valeur la plus gagnante
					TheBestWinnumber(cheminLog);
					break;

					// Afficher la valeur la moins gagnante
				case OPTION_2:
					// Appel de la fonction d'affichage de la valeur la moins gagnante
					TheBadestNumber(cheminLog);
					break;

					// Afficher les 6 meilleurs numeros
				case OPTION_3:
					// Appel de la fonction des 6 meilleurs numeros
					WinNumbers(cheminLog);
					break;

					// Afficher les 6 moins bon numeros
				case OPTION_4:
					// Appel de la fonction des 6 moins bon numeros
					LoseNumbers(cheminLog);
					break;

					// Insertion d'une valeur
				case OPTION_5:
					// Appel de la fonction d'insertion d'une valeur
					EcritureValeur(cheminLog);
					break;

					// Supprimer la derniere valeur inseree
				case OPTION_6:
					// Appel de la fonction de suppression de la derniere valeur
					SupressionValeur(cheminLog);
					break;

					// Modifier la derniere valeur inseree
				case OPTION_7:
					// Appel de la fonction de modificateur de la derniere valeur
					ModificationValeur(cheminLog);
					break;

					// Simuler des valeurs de loto
				case OPTION_8:
					// Appel de la fonction de Simulation
					Simulation(cheminLog);
					break;

					// En cas de defaut
				default:
					// Message d'erreur
					printf("\nNous n'avons pas pu determiner quel option vous souhaiteriez, veuillez reessayer! \n\n");
					break;
				}
			}
			// Si le fichier ne peut pas etre lu, alors on demande s'il souhaite crée un loto
			else
			{
				do
				{
					// Message de demande de création de Loto
					printf("\nCe loto n'existe pas! Voulez vous cree un nouveau Loto? (O = Oui; N = Non)\n\n>");

					// Récéption de la reponse de l'utilisateur
					scanf(" %c", &reponseUser);

					// Vérification de la reponse
					if ((reponseUser == OUI) || (reponseUser == oui))
					{
						// Appel a la fonction de création d'un nouveau Loto
						NouveauLoto(cheminLog, lotoName);
					}
					else if ((reponseUser == NON) || (reponseUser == non))
					{
						// Message de retour
						printf("\nRetour au menu\n");
					}
					else
					{
						// Message d'erreur
						printf("\nNous n'avons pas compris votre reponse veuillez reessayer!\n");
					}
				} while ((reponseUser != OUI) && (reponseUser != oui) && (reponseUser != NON) && (reponseUser != non));
			}
		}
		else
		{
			// Message de fermeture
			printf("\nFermeture du programme!");
		}
	} while ((lotoName[0] != Quitter) && (lotoName[1] != 0));
}