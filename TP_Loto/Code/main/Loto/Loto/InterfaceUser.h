#pragma once
//-----------------------------------------------------------------------------------//
// Nom du projet 		: Loto
// Nom du fichier 		: InterfaceUser.h
// Date de création 	: 18.05.2026
// Date de modification : 01.06.2026
//
// Auteur 				: VMD
//
// Description          : Fichier header file pour l'InterfaceUser.c
//
// Remarques			: 
//
//----------------------------------------------------------------------------------//

#ifndef INTERFACEUSER
#define INTERFACEUSER

// Librairies Standars
#include <stdio.h>		// pour usage printf
#include <stdint.h>		// uniformation du type entier 
#include <stdbool.h>

// Structures
//structure Valeur

typedef struct {
    char meilleurValeur;
    char pireValeur;
    char numeroGagnant[6];
    char numeroPerdant[6];
    char valMin;
    char valMax;
    char b_complementaire;
    char compMin;
    char compMax;
} s_Valeur;

// Variables externes
extern s_Valeur valeur;

// Prototypes
void Recherche(char cheminLog[]);
char NouveauLoto(char cheminLog[], char lotoName[]);
void Simulation(char cheminLog[]);

#endif