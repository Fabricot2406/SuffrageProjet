/** \\file */
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

Candidat *init_candidat(t_mat_char_star_dyn *matrice, int num_candidat);

List *init_tableau_candidat(t_mat_char_star_dyn *matrice);

void liberer_candidat(void *elem);

void liberer_liste_candidat(List *tab_candidat);


/******************* METHODE *********************/


int calculer_indice_mention(int nb_votes);

char *attribuer_mention(int mention);

char *rechercher_meilleure_mention(List *tab_candidat);

void calculer_vainqueur_jugement(List *tab_candidat);

void recalculer_mention (List *tab_candidat_reduit);

void test_affichage(List *tab_candidat);

/**
 * @brief Détermine le vainqueur du jugement en fonction des mentions de chaque candidat et affiche le nom du vainqueur.
 */
void determiner_vainqueur_jugement(t_mat_char_star_dyn *matrice,FILE *output);


#endif //__JUGEMENT_MAJORITAIRE_H__