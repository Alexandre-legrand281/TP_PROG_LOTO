// Auteur S. Villard
//Date de création : 25.5.2026
//Dernière modification : 1.6.2026

// Suppression avertissement C4996
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Librairies Personnels
#include "GestionFichier.h"
#include "main.h"
#include "GestionAffichage.h"
#include "InterfaceUser.h" 

//declaration structure
s_Valeur valeur;

//----------------------------------------------------------------------------------//
// Nom de la fonction : EcritureValeur
// Entrée / Sortie : nomFichier, valeur / -
// Description : Écrit à la suite de la liste de nombre un nouveau nombre
// Date modfification : le 1.06.2026
//----------------------------------------------------------------------------------//
void EcritureValeur(char nomFichier[])
{
    Recherche(nomFichier);

    // Variable locales
    int valWrite = 0;

    do
    {
        // Demande de valeur
        printf("\nQuel valeur souhaitez vous ecrire? (Valeur maximal: %d Valeur minimal: %d)\n\n>", valeur.valMax, valeur.valMin);

        // Récéption de la valeur souhaité
        scanf("%d", &valWrite);

        // Limitation de la valeur introduite
        if (valWrite > valeur.valMax)
        {
            // Message d'erreur
            printf("\nLa valeur que vous avez introduite est plus grande que la valeur maximal %d, veuillez reessayer!\n", valeur.valMax);
        }
        else if (valWrite < valeur.valMin)
        {
            // Message d'erreur
            printf("\nLa valeur que vous avez introduite est plus petite que la valeur minimal %d, veuillez reessayer!\n", valeur.valMin);
        }
    } while ((valWrite > valeur.valMax) || (valWrite < valeur.valMin));

    FILE* fichier = fopen(nomFichier, "a");
    if (fichier == NULL)
    {
        return;
    }

    fprintf(fichier, "%d\n", valWrite);
    fclose(fichier);

    // Message de valeur ajouté
    printf("\nLa valeur %d a ete ecrite\n", valWrite);
}

//----------------------------------------------------------------------------------//
// Nom de la fonction : ModificationVlaeur
// Entrée / Sortie : nomFichier, lastValeur / -
// Description : Modifie la dernière valeur dans le fichier
// Date modfification : le 1.06.2026
//----------------------------------------------------------------------------------//
void ModificationValeur(char nomFichier[])
{
    Recherche(nomFichier);

    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL)
    {
        printf("\n[ERREUR] Impossible d'ouvrir le fichier pour modification.\n");
        return;
    }

    // Lecture de toutes les lignes en mémoire
    char** lignes = NULL;
    int nbLignes = 0;
    char ligne[256];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        lignes = (char**)realloc(lignes, (nbLignes + 1) * sizeof(char*));
        lignes[nbLignes] = (char*)malloc((strlen(ligne) + 1) * sizeof(char));
        strcpy(lignes[nbLignes], ligne);
        nbLignes++;
    }
    fclose(fichier);

    if (nbLignes == 0)
    {
        free(lignes);
        return;
    }

    // Recherche de la dernière ligne non vide (la dernière valeur insérée)
    int derniereLigne = nbLignes - 1;
    while (derniereLigne >= 0 && strlen(lignes[derniereLigne]) <= 1)
    {
        derniereLigne--;
    }

    // SÉCURITÉ : Si la ligne trouvée est le séparateur "---", le fichier ne contient pas encore de numéros
    if (derniereLigne >= 0 && strstr(lignes[derniereLigne], "---") != NULL)
    {
        printf("\n[Erreur] Il n'y a encore aucune valeur inseree à modifier !\n");

        // Libération de la mémoire avant de quitter
        for (int i = 0; i < nbLignes; i++) free(lignes[i]);
        free(lignes);
        return;
    }

    // Si on a trouvé une valeur valide à modifier
    if (derniereLigne >= 0)
    {
        int nouvelleValeur = 0;

        do
        {
            // Demande de la nouvelle valeur à l'utilisateur directement dans la fonction
            printf("\nQuelle est la nouvelle valeur qui va remplacer la derniere? (Valeur maximal: %d Valeur minimal: %d)\n\n>", valeur.valMax, valeur.valMin);

            // Réception de la valeur remplacante
            scanf("%d", &nouvelleValeur);

            // Limitation de la valeur introduite
            if (nouvelleValeur > valeur.valMax)
            {
                // Message d'erreur
                printf("\nLa valeur que vous avez introduite est plus grande que la valeur maximal %d, veuillez reessayer!\n", valeur.valMax);
            }
            else if (nouvelleValeur < valeur.valMin)
            {
                // Message d'erreur
                printf("\nLa valeur que vous avez introduite est plus petite que la valeur minimal %d, veuillez reessayer!\n", valeur.valMin);
            }
            else
            {
                // Suppression de l'ancienne ligne en mémoire et remplacement
                free(lignes[derniereLigne]);
                lignes[derniereLigne] = (char*)malloc(16 * sizeof(char));
                snprintf(lignes[derniereLigne], 16, "%d\n", nouvelleValeur);
            }
        } while ((nouvelleValeur > valeur.valMax) || (nouvelleValeur < valeur.valMin));
    }

    // Réécriture du fichier complet avec la modification
    fichier = fopen(nomFichier, "w");
    if (fichier == NULL)
    {
        printf("\n[ERREUR] Impossible de sauvegarder les modifications.\n");
        for (int i = 0; i < nbLignes; i++) free(lignes[i]);
        free(lignes);
        return;
    }

    for (int i = 0; i < nbLignes; i++)
    {
        fputs(lignes[i], fichier);
        free(lignes[i]); // Libération de chaque ligne au fur et à mesure
    }

    free(lignes);
    fclose(fichier);

    printf("\nDerniere valeur modifiee avec succes dans le repertoire %s!\n", nomFichier);
}

//----------------------------------------------------------------------------------//
// Nom de la fonction : SupressionValeur
// Entrée / Sortie : nomFichier / -
// Description : Suprime la dernière valeur dans le fichier
// Date modfification : le 1.06.2026
//----------------------------------------------------------------------------------//
void SupressionValeur(char nomFichier[])
{
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL)
    {
        return;
    }

    // Lecture de toutes les lignes en mémoire
    char** lignes = NULL;
    int nbLignes = 0;
    char ligne[256];

    while (fgets(ligne, sizeof(ligne), fichier) != NULL)
    {
        lignes = (char**)realloc(lignes, (nbLignes + 1) * sizeof(char*));
        lignes[nbLignes] = (char*)malloc((strlen(ligne) + 1) * sizeof(char));
        strcpy(lignes[nbLignes], ligne);
        nbLignes++;
    }
    fclose(fichier);

    if (nbLignes == 0)
    {
        free(lignes);
        return;
    }

    // Suppression de la dernière ligne non vide
    int derniereLigne = nbLignes - 1;
    while (derniereLigne >= 0 && strlen(lignes[derniereLigne]) <= 1)
    {
        derniereLigne--;
    }

    if (derniereLigne >= 0)
    {
        free(lignes[derniereLigne]);
        lignes[derniereLigne] = NULL;
        nbLignes = derniereLigne; // On tronque à cette ligne exclue
    }

    // Réécriture du fichier sans la dernière valeur
    fichier = fopen(nomFichier, "w");
    if (fichier == NULL)
    {
        for (int i = 0; i < derniereLigne; i++) free(lignes[i]);
        free(lignes);
        return;
    }

    for (int i = 0; i < nbLignes; i++)
    {
        fputs(lignes[i], fichier);
        free(lignes[i]);
    }

    free(lignes);
    fclose(fichier);

    // Message de suppression de valeur
    printf("\nLa derniere valeur a bien ete suprimee dans le repertoire %s!\n", nomFichier);
}

//----------------------------------------------------------------------------------//
// Nom de la fonction : NewGamblingAddiction
// Entrée / Sortie : lotoName, valMin, valMax, complementaire, valMaxComp, valMinComp / status
// Description : Génère un fichier texte complet avec une nomenclature pour pouvoir 
// reconaître le type de fichier lors d'une lecture ainsi que les espacements géré 
// automatiquement pour la lecture et écriture des valeurs
// Date modfification : le 1.06.2026
//----------------------------------------------------------------------------------//
char NewGamblingAddiction(char cheminLog[], char lotoName[], char valMin, char valMax, char complementaire, char valCompMin, char valCompMax)
{
    // Construction du nom de fichier : "log<lotoName>.txt" à la racine du projet
    snprintf(cheminLog, 60, "Logs/log%s.txt", lotoName);

    FILE* fichier = fopen(cheminLog, "w");
    if (fichier == NULL)
    {
        return false;
    }

    // Écriture de l'entête du fichier
    fprintf(fichier, "LOTO:%s\n", lotoName);
    fprintf(fichier, "MIN:%d MAX:%d\n", valMin, valMax);

    if ((complementaire == OUI) || (complementaire == oui))
    {
        fprintf(fichier, "COMPLEMENTAIRE:OUI MIN:%d MAX:%d\n", valCompMin, valCompMax);
    }
    else
    {
        fprintf(fichier, "COMPLEMENTAIRE:NON\n");
    }

    // Séparateur entre l'entête et la zone des valeurs
    fprintf(fichier, "---\n");

    fclose(fichier);

    // Message de confirmation de création du fichier
    printf("\nLe fichier log%s.txt a bien ete cree!\n", lotoName);
}