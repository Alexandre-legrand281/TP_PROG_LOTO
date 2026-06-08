/*
GestionAffichage.h
autheur: VMD
*/

#ifndef GESTIONAFFICHAGE_H
#define GESTIONAFFICHAGE_H

#include <stdio.h>

/****Prototype****/

void TheBestWinnumber(char cheminLog[]);
void TheBadestNumber (char cheminLog[]);
void WinNumbers (char cheminLog[]);
void AffichageSimulation (int* randomTable, int nbValeurs, int* randomComp, int nbComp);
void LoseNumbers (char cheminLog[]);

#endif