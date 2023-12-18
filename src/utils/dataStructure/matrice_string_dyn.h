/**
 * @file matrice_string_dyn.h
 * @authors Marco, Anthony
 * @brief Structure de donnée correspondant à une matrice dynamique contenant des chaines de caractères.
 * @date 2023-10-17
 */

#ifndef __MATRICE_STRING_DYN_H__
#define __MATRICE_STRING_DYN_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

/******************* STRUCTURE *********************/

/**
 * @struct t_mat_char_star_dyn
 * @brief Structure pour allocation matrice dynamique.
 */
typedef struct t_mat_char_star_dyn{
    int nbLignes; // Nombre de lignes de la matrice
    int nbColonnes; // Nombre de colonnes de la matrice
    char ***tab; // Tableau de pointeurs de pointeurs de caractères
}t_mat_char_star_dyn;

/******************* CONSTRUCTEUR *********************/

/**
 * @brief Fonction pour initialiser la matrice.
 * @return Pointeur vers la matrice créée.
 */
t_mat_char_star_dyn *mat_char_create();

/******************* OPERATEUR *********************/

/**
 * @brief Fonction qui trouve la ligne et la colonne d'un element dans un fichier CSV.
 * @param matrice Pointeur vers la matrice à afficher.
 * @param elem Chaine de caractère à trouver.
 * @param ligne Ligne où se trouve l'element.
 * @param colonne Colonne où se trouve l'element.
 * @return 1 si element trouvé, 0 sinon.
*/
int mat_char_search_elem(t_mat_char_star_dyn *matrice, char *elem, int *ligne, int *colonne);

/**
 * @brief Fonction pour libérer la matrice.
 * @param matrice Pointeur vers la matrice à libérer.
 */
void mat_char_delete(t_mat_char_star_dyn *matrice);


/******************* UTILITAIRE *********************/

/**
 * @brief Fonction qui affiche la matrice.
 * @param matrice Pointeur vers la matrice à afficher.
 */
void mat_char_display(t_mat_char_star_dyn *matrice);

/**
 * @brief Fonction qui affiche une ligne du fichier CSV.
 * @param matrice Pointeur vers la matrice à afficher.
 * @param ligne Ligne à afficher.
 */
void mat_char_display_row(t_mat_char_star_dyn *matrice, int ligne);

#endif // __MATRICE_STRING_DYN_H__
