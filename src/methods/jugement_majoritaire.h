/**
 * @file jugement_majoritaire.h
 * @author Marco
 * @brief Fichier de la méthode de scrutin du jugement majoritaire
 * @date 2023-11-28
 */

#ifndef __JUGEMENT_MAJORITAIRE_H__
#define __JUGEMENT_MAJORITAIRE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/lecture_csv.h"
#include "../utils/dataStructure/listegen.h"
#include "../utils/utils_sd.h"

/******************* STRUCTURE *********************/

/**
 * @brief Structure représentant un candidat dans le scrutin du jugement majoritaire.
 */
typedef struct s_candidat Candidat;

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
 * @brief Libère une liste de candidats.
 * @param tabCandidat : La liste des candidats à libérer.
 */
void libererListeCandidat(List *tabCandidat);


/******************* METHODE *********************/

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
 * @brief Calcule le vainqueur du jugement.
 * @param tabCandidat : La liste des candidats.
 */
void calculerVainqueurJugement(List *tabCandidat);

/**
 * @brief Recalcule la mention.
 * @param tabCandidatReduit : La liste réduite des candidats.
 */
void recalculerMention(List *tabCandidatReduit);
/**
 * @brief Teste l'affichage.
 * @param tabCandidat : La liste des candidats.
 */
void testAffichage(List *tabCandidat);

/**
 * @brief Détermine le vainqueur du jugement.
 * @param matrice : La matrice contenant les informations des candidats.
 * @param output : Le fichier de sortie dans lequel on écrit le résultat.
 */
void determinerVainqueurJugement(t_mat_char_star_dyn *matrice, FILE *output);


#endif //__JUGEMENT_MAJORITAIRE_H__