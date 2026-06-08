//-----------------------------------------------------------------------------------//
// Nom du projet 		: Loto
// Nom du fichier 		: InterfaceUser.c
// Date de création 	: 18.05.2026
// Date de modification : 05.06.2026
//
// Auteur 				: VMD
//
// Description          : Ce fichier a pour but de generer l'interface d'utilisateur
//						  afin d'afficher un menu pour l'utilisateur, et le proposer
//						  s'il souhaite rechercher une valeur, faire une simulation
//						  ou de crée un nouveau Loto
//
// Remarques			: 
//
//----------------------------------------------------------------------------------//

// Librairies Standars
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>		// pour usage printf
#include <stdint.h>		// uniformation du type entier
#include <stdlib.h> // pour srand )randomizer nombre
#include <time.h> // pour randomizer nombre
#include <stdbool.h>
#include <string.h> // pour les string

// Librairies personnelle
#include "GestionFichier.h"
#include "main.h"
#include "GestionAffichage.h"
#include "InterfaceUser.h" 

//declaration structure
s_Valeur valeur;

// Fonction de Recherche
void Recherche(char cheminLog[])
{
    FILE* fichier = fopen(cheminLog, "r");
    if (fichier == NULL)
    {
        printf("\n[ERREUR] Impossible d'ouvrir le fichier : %s\n", cheminLog);
        return;
    }

    int compteur[101] = { 0 }; // Tableau de marge (jusqu'à 100 numéros max)
    char ligne[256];

    // Lecture de l'en tete (Jusqu'à "---")
    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        // Si on croise le séparateur, l'en-tête est fini, on sort de la boucle de config
        if (strncmp(ligne, "---", 3) == 0)
        {
            break;
        }

        // Si la ligne contient les infos du loto principal (et pas complémentaire)
        if (strstr(ligne, "MIN:") != NULL && strstr(ligne, "COMPLEMENTAIRE:") == NULL)
        {
            sscanf(ligne, "MIN:%d MAX:%d", &valeur.valMin, &valeur.valMax);
        }

        // Si la ligne gère les numéros complémentaires
        if (strstr(ligne, "COMPLEMENTAIRE:") != NULL)
        {
            if (strstr(ligne, "OUI") != NULL)
            {
                valeur.b_complementaire = 'o';
                // On extrait le MIN et MAX complémentaire en se calant après le mot "OUI"
                sscanf(strstr(ligne, "MIN:"), "MIN:%d MAX:%d", &valeur.compMin, &valeur.compMax);
            }
            else
            {
                valeur.b_complementaire = 'n';
            }
        }
    }

    // Sécurité au cas où le fichier lise une valeur aberrante
    if (valeur.valMax > 100) valeur.valMax = 100;
    
    // Lecture de toutes les valeurs
    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        int num;
        if (sscanf(ligne, "%d", &num) == 1)
        {
            // Utilisation dynamique des variables lues dans l'en-tête !
            if (num >= valeur.valMin && num <= valeur.valMax)
            {
                compteur[num]++;
            }
        }
    }
    fclose(fichier);

    // Recherche des 6 meilleurs numéro
    int compteur_copie_top[101];
    memcpy(compteur_copie_top, compteur, sizeof(compteur));

    for (int rang = 0; rang < 6; rang++)
    {
        int max_occurrences = -1;
        int meilleur_num = -1;

        // La boucle s'adapte automatiquement à valMax
        for (int i = valeur.valMin; i <= valeur.valMax; i++)
        {
            if (compteur_copie_top[i] > max_occurrences)
            {
                max_occurrences = compteur_copie_top[i];
                meilleur_num = i;
            }
        }

        if (meilleur_num != -1)
        {
            valeur.numeroGagnant[rang] = (char)meilleur_num;
            if (rang == 0) valeur.meilleurValeur = (char)meilleur_num;
            compteur_copie_top[meilleur_num] = -1;
        }
        else
        {
            valeur.numeroGagnant[rang] = 0;
            if (rang == 0) valeur.meilleurValeur = 0;
        }
    }

    // Recherche des 6 pires numeros
    int compteur_copie_flop[101];
    memcpy(compteur_copie_flop, compteur, sizeof(compteur));

    for (int rang = 0; rang < 6; rang++)
    {
        int min_occurrences = 999999;
        int pire_num = -1;

        // La boucle s'adapte automatiquement à valMax
        for (int i = valeur.valMin; i <= valeur.valMax; i++)
        {
            if (compteur_copie_flop[i] > 0 && compteur_copie_flop[i] < min_occurrences)
            {
                min_occurrences = compteur_copie_flop[i];
                pire_num = i;
            }
        }

        if (pire_num != -1)
        {
            valeur.numeroPerdant[rang] = (char)pire_num;
            if (rang == 0) valeur.pireValeur = (char)pire_num;
            compteur_copie_flop[pire_num] = 999999;
        }
        else
        {
            valeur.numeroPerdant[rang] = 0;
            if (rang == 0) valeur.pireValeur = 0;
        }
    }
}

// Fonction de Simulation
void Simulation(char cheminLog[])
{
    int nbValeurs = 0;
    int nbComp = 0;

    // Appel de la recherche pour charger les configurations du loto actuel
    Recherche(cheminLog);

    // Boucle 
    do
    {
        // Gestion des numéros principales
        printf("\nCombien de valeurs principales souhaitez-vous randomizer? (La valeur introduite doit etre au minimum = 1)\n\n>");
        scanf("%d", &nbValeurs);

        if (nbValeurs < 1)
        {
            printf("\nValeur introduite = 0 ou inferieur, veuillez recommencer!\n");
        }
    } while (nbValeurs == 0);

    // Allocation dynamique du tableau principal
    int* randomTable = (int*)malloc(nbValeurs * sizeof(int));
    if (randomTable == NULL)
    {
        printf("Erreur d'allocation memoire pour randomTable !\n");
        return;
    }

    // Remplissage du tableau avec des valeurs aléatoires
    for (int i = 0; i < nbValeurs; i++)
    {
        randomTable[i] = (rand() % (valeur.valMax - valeur.valMin + 1)) + valeur.valMin;
    }

    // Gestion des numeéros complémentaires
    int* randomComp = NULL; // On l'initialise à vide par sécurité

    if (valeur.b_complementaire == OUI || valeur.b_complementaire == oui)
    {
        do
        {
            printf("\nCe loto possede des numeros complementaires. Combien souhaitez-vous en randomizer? (La valeur introduite doit etre au minimum = 1)\n\n>");
            scanf("%d", &nbComp);

            if (nbComp < 1)
            {
                // Message d'erreur
                printf("\nValeur introduite = 0 ou inferieur, veuillez recommencer!\n");
            }
        } while (nbComp == 0);

        // Allocation dynamique du tableau complémentaire
        randomComp = (int*)malloc(nbComp * sizeof(int));
        if (randomComp == NULL)
        {
            printf("Erreur d'allocation memoire pour randomComp !\n");
            free(randomTable); // On libère le premier tableau avant de quitter !
            return;
        }

        // Remplissage du tableau complémentaire
        for (int i = 0; i < nbComp; i++)
        {
            randomComp[i] = (rand() % (valeur.compMax - valeur.compMin + 1)) + valeur.compMin;
        }
    }

    // Ecriture des valeurs randomizer dans le fichier
    FILE* fichier = fopen(cheminLog, "a");
    if (fichier == NULL)
    {
        return;
    }
    for (int i = 0; i < nbValeurs; i++)
    {
        fprintf(fichier, "%d\n", randomTable[i]);
    }
    
    // Fermeture du fichier
    fclose(fichier);

    // On passe les tableaux ET leurs tailles à la fonction d'affichage
    AffichageSimulation(randomTable, nbValeurs, randomComp, nbComp);

    // On rend obligatoirement la mémoire au système
    free(randomTable);
    if (randomComp != NULL)
    {
        free(randomComp);
    }
}

// Fonction de Nouveau Loto
char NouveauLoto(char cheminLog[], char lotoName[])
{
    // Variables locales
    int valMin = 0;
    int valMax = 0;
    int valMinComp = 0;
    int valMaxComp = 0;
    char reponseUser = 0;
    char reset = 0;

    do
    {
        // Demande a l'utilisateur les valeurs minimum du loto
        printf("\nQuel est la valeur minimum de votre loto? (La valeur doit etre superieur a 0)\n\n>");

        // Récéption de la valeur souhaité
        scanf("%d", &valMin);

        // Vérification si la valeur est supérieur a 0
        if (valMin > 0)
        {
            // Demande a l'utilisateur les valeurs maximum du loto
            printf("\nQuel est la valeur maximum de votre loto?\n\n>");

            // Récéption de la valeur souhaité
            scanf("%d", &valMax);

            // Fin de boucle
            reset = 0;
        }
        else
        {
            // Message d'erreur
            printf("\nVotre valeur est inferieur ou egal a 0, veuillez recommencer!\n");

            // Reset de la boucle
            reset = 1;
        }
    } while (reset == 1);

    // Demande a l'utilisateur si des valeurs complementaires existe
    printf("\nVotre loto contient des valeurs complementaires?(O = Oui)\n\n>");

    // Récéption de la reponse de l'utilisateur
    scanf(" %c", &reponseUser);

    // Si la reponse est oui
    if ((reponseUser == OUI) || (reponseUser == oui))
    {
        do
        {
            // Demande a l'utilisateur les valeurs minimum complementaire du loto
            printf("\nQuel est la valeur minimum complementaire de votre loto? (La valeur doit etre superieur a 0)\n\n>");

            // Récéption de la valeur souhaité
            scanf("%d", &valMinComp);

            // Vérification si la valeur complementaire est supérieur a 0
            if (valMinComp > 0)
            {
                // Demande a l'utilisateur les valeurs maximum du loto
                printf("\nQuel est la valeur maximum complementaire de votre loto?\n\n>");

                // Récéption de la valeur souhaité
                scanf("%d", &valMaxComp);

                // Fin de boucle
                reset = 0;
            }
            else
            {
                // Message d'erreur
                printf("\nVotre valeur est inferieur ou egal a 0, veuillez recommencer!\n");

                // Reset de la boucle
                reset = 1;
            }
        } while (reset == 1);
    }

    // Appel a la fonction de création de fichier
    NewGamblingAddiction(cheminLog, lotoName, valMin, valMax, reponseUser, valMinComp, valMaxComp);
}