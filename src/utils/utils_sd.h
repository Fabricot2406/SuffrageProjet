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
#include <stdbool.h>
#include <assert.h>

typedef struct uni_data_s{
    int *vainqueurUn;
    int *vainqueurDeux;
    int *votes;
} uni_data;

/**
 * @brief Affiche le vainqueur d'un suffrage dépendant de la méthode choisie
 * @param methode Une chaine de caractères représentant le nom de la méthode employée
 * @param nbCandidats Le nombre de candidats d'une élection
 * @param nbVotants Le nombre de votants d'une élection
 * @param methode Une chaine de caractères représentant le nom du vainqueur
 * @param score Le score du candidat gagnant (à n'utiliser que lors d'uninominale 1 et 2)
 */
void afficherVainqueur(char * methode, int nbCandidats, int nbVotants, char * nomVainqueur, double score); // Affiche le vainqueur de n'importe quelle méthode

/**
 * @brief Crée une structure de données uni_data
 * @param vainqueurUn Pointeur vers le vainqueur du premier tour
 * @param vainqueurDeux Pointeur vers le vainqueur du deuxième tour
 * @param votes Pointeur vers le tableau de votes
 * @return uni_data* Pointeur vers la structure de données uni_data
 */
uni_data *creer_uni_data(int *vainqueurUn, int *vainqueurDeux, int *votes);

/**
 * @brief Fonction de réduction pour uninominale 2
 * @param elem Un élément de la liste
 * @param data La structure de données uni_data
 * @return int 1 si le candidat est le vainqueur du premier ou du deuxième tour, 0 sinon
 */
int uni_reduce(void *elem, void *data);

/**
 * @brief Calcule le score d'un candidat
 * @param nbVotants Le nombre de votants d'une élection
 * @param nbVotes Le nombre de votes d'un candidat
 * @return double Le score du candidat
 */
double calculerScore(int nbVotants, int nbVotes);

#endif