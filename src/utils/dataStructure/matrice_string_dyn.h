/**
 * @file s_matriceVote.h
 * @author Marco, Anthony
 * @brief Structure de donnée correspondant à la matrice des votes issue d'un fichier CSV.
 * @version finale
 * @date 2021-11-23
 */

#ifndef __MATRICE_STRING_DYN_H__
#define __MATRICE_STRING_DYN_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

/**
 * @struct s_matriceVote
 * @brief Structure pour allocation matrice dynamique.
 */
typedef struct s_matriceVote{
    int nbLignes; // Nombre de lignes de la matrice
    int nbColonnes; // Nombre de colonnes de la matrice
    char ***tab; // Tableau de pointeurs de pointeurs de caractères
}t_mat_char_star_dyn;

/**
 * @fn t_mat_char_star_dyn *creerMatrice()
 * @brief Fonction pour initialiser la matrice.
 * @return Pointeur vers la matrice créée.
 */
t_mat_char_star_dyn *creerMatrice();

/**
 * @fn int trouverElem(t_mat_char_star_dyn *matrice, char *elem, int *ligne, int *colonne)
 * @brief Fonction qui trouve la ligne et la colonne d'un element dans un fichier CSV.
 * @param matrice Pointeur vers la matrice à afficher.
 * @param elem Chaine de caractère à trouver.
 * @param ligne Ligne où se trouve l'element.
 * @param colonne Colonne où se trouve l'element.
 * @return 1 si element trouvé, 0 sinon.
*/
int trouverElem(t_mat_char_star_dyn *matrice, char *elem, int *ligne, int *colonne);

/**
 * @fn void libererMatrice(t_mat_char_star_dyn *matrice)
 * @brief Fonction pour libérer la matrice.
 * @param matrice Pointeur vers la matrice à libérer.
 */
void libererMatrice(t_mat_char_star_dyn *matrice);


/******************* UTILITAIRE *********************/

/**
 * @fn void afficherMatrice(t_mat_char_star_dyn *matrice)
 * @brief Fonction qui affiche la matrice.
 * @param matrice Pointeur vers la matrice à afficher.
 */
void afficherMatrice(t_mat_char_star_dyn *matrice);

/**
 * @fn void afficherLigne(t_mat_char_star_dyn *matrice,int ligne)
 * @brief Fonction qui affiche une ligne du fichier CSV.
 * @param matrice Pointeur vers la matrice à afficher.
 * @param ligne Ligne à afficher.
 */
void afficherLigne(t_mat_char_star_dyn *matrice, int ligne);

#endif // __MATRICE_STRING_DYN_H__
