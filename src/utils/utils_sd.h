/**
 * @file utils_sd.h
 * @authors Anthony, Marco et Fabio
 * @brief Fonctions utilitaires pour les méthodes de suffrage
 * @date 2023-11-25
 */

#ifndef UTILS_SD_H
#define UTILS_SD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "./dataStructure/ballot.h"
#include "./dataStructure/arc.h"
#include "./dataStructure/listegen.h"
#include "string_builder.h"

#define INCREMENT_COLONNE 4
#define INCREMENT_LIGNE 1

#define BUFFER_SIZE 1024

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
 * @param output Le fichier de sortie dans lequel on écrit le résultat
 */
void retourner_vainqueur(char * methode, int nbCandidats, int nbVotants, char * nomVainqueur, double score, FILE *output);

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
double calculer_score(int nb_votants, int nb_votes);

/**
 * @brief Affiche un élément. Cet élément est un pointeur sur un entier.
 * @param elem : L'élément à afficher.
 */
void afficher_int_ptr(void *elem);

/**
 * @brief Trie les votes. Les paramètres sont castés en int.
 * @param i : Premier vote à comparer.
 * @param j : Deuxième vote à comparer.
 * @return bool : Renvoie vrai si le premier vote doit venir avant le deuxième.
 */
bool cmp_inferieur_egal(void *i, void *j);

bool est_vainqueur(List *list_arc, int candidat);

/**
 * @brief Fonction permettant de déterminer si il y a un vainqueur de Condorcet
 * @param list_arc La liste des arcs représentant les paires de duel
 * @param vainqueur Pointeur vers le vainqueur de Condorcet, s'il existe il sera modifié
 */
bool vainqueur_condorcet(larc *list_arc, int *vainqueur);


/**
 * @brief Affichage du classement des candidats.
 * @details Utilisation de la fonction list_reduce pour afficher les candidats dans l'ordre du classement.
 *          La fonction de réduction est une fonction qui affiche le candidat passé en paramètre et sa position dans le classement.
 * @pre La liste des arcs est non vide, triée par ordre décroissant de score.
 * @param classement La liste des candidats du classement à afficher.
 */
void afficher_classement(List *classement);

#endif