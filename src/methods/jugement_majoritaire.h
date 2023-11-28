/**
 * @file jugement_majoritaire.h
 * @author Marco Regragui Martins
 * @brief Fichier de la méthode de scrutin du jugement majoritaire
 * @version 1.0
 * @date Date de création
 */

#ifndef JUGEMENT_MAJORITAIRE_H
#define JUGEMENT_MAJORITAIRE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/lecture_csv.h"
#include "../utils/dataStructure/listegen.h"
#include "../utils/utils_sd.h"

#define INCREMENT_COLONNE 4

/**
 * @brief Structure représentant un candidat dans le scrutin du jugement majoritaire.
 */
typedef struct s_candidat{
    char *nom;
    List *votesCandidat;
    int *mention;
}Candidat;

/**
 * @brief Affiche un élément.
 * @param elem : L'élément à afficher.
 */
void afficherElem(void *elem);

/**
 * @brief Trie les votes.
 * @param i : Premier vote à comparer.
 * @param j : Deuxième vote à comparer.
 * @return bool : Renvoie vrai si le premier vote doit venir avant le deuxième.
 */
bool trierVotes(void *i, void *j);

/**
 * @brief Calcule l'indice de mention.
 * @param nbVotes : Le nombre de votes.
 * @return int : L'indice de mention calculé.
 */
int calculerIndiceMention(int nbVotes);

/**
 * @brief Attribue une mention.
 * @param mention : La mention à attribuer.
 * @return char* : La mention attribuée sous forme de chaîne de caractères.
 */
char *attribuerMention(int mention);

/**
 * @brief Recherche la meilleure mention.
 * @param tabCandidat : La liste des candidats.
 * @return char* : La meilleure mention trouvée sous forme de chaîne de caractères.
 */
char *rechercherMeilleureMention(List *tabCandidat);

/**
 * @brief Initialise un candidat.
 * @param matrice : La matrice contenant les informations du candidat.
 * @param numCandidat : Le numéro du candidat.
 * @return Candidat* : Structure d'un candidat de l'élection.
 */
Candidat *initCandidat(t_mat_char_star_dyn *matrice, int numCandidat);

/**
 * @brief Initialise un tableau de candidats.
 * @param matrice : La matrice contenant les informations des candidats.
 * @return List* :  Liste des candidats de l'élection.
 */
List *initTableauCandidat(t_mat_char_star_dyn *matrice);

/**
 * @brief Libère un candidat.
 * @param elem : Le candidat à libérer.
 */
void libererCandidat(void *elem);

/**
 * @brief Calcule le vainqueur du jugement.
 * @param tabCandidat : La liste des candidats.
 */
void calculerVainqueurJugement(List *tabCandidat);

/**
 * @brief Recalcule la mention.
 * @param tabCandidatReduit : La liste réduite des candidats.
 */
void recalculerMention (List *tabCandidatReduit);
/**
 * @brief Teste l'affichage.
 * @param tabCandidat : La liste des candidats.
 */
void testAffichage(List *tabCandidat);

/**
 * @brief Libère une liste de candidats.
 * @param tabCandidat : La liste des candidats à libérer.
 */
void libererListeCandidat(List *tabCandidat);

/**
 * @brief Détermine le vainqueur du jugement.
 */
void determinerVainqueurJugement();


#endif