/**
 * @file utils_sd.c
 * @author Fabio
 * @brief Fonctions utilitaires pour les méthodes de suffrage
 * @version 1.0
 * @date 2023-11-25
 */

#ifndef UTILS_SD_H
#define UTILS_SD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Affiche le vainqueur d'un suffrage dépendant de la méthode choisie
 * @param methode Une chaine de caractères représentant le nom de la méthode employée
 * @param nbCandidats Le nombre de candidats d'une élection
 * @param nbVotants Le nombre de votants d'une élection
 * @param methode Une chaine de caractères représentant le nom du vainqueur
 * @param score Le score du candidat gagnant (à n'utiliser que lors d'uninominale 1 et 2)
 */
void afficherVainqueur(char * methode, int nbCandidats, int nbVotants, char * nomVainqueur, double score); // Affiche le vainqueur de n'importe quelle méthode

#endif