/**
 * @file s_matriceVote.h
 * @author Marco, Anthony
 * @brief Structure de donnée correspondant à la matrice des votes issue d'un fichier CSV.
 * @version 1.0
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
    int nbLignes;
    int nbColonnes;
    char ***tab;
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


/******************* ITERATEUR *********************/

/**
 * @enum TraverseType
 * @brief Enumération pour le type de parcours.
*/
typedef enum {
    ROW,
    COLUMN
} TraverseType;

/**
 * @enum IteratorDirection
 * @brief Enumération pour la direction du parcours.
*/
typedef enum {
    FORWARD,
    BACKWARD
} IteratorDirection;

/**
 * @struct MatrixIterator
 * @brief Structure pour l'itérateur.
 * @param matrix Pointeur vers la matrice.
 * @param current_row Ligne courante.
 * @param current_col Colonne courante.
 * @param traverse_type Type de parcours (ligne ou colonne).
 * @param direction Direction du parcours (avant ou arrière).
*/
typedef struct {
    t_mat_char_star_dyn *matrix;
    int current_row;
    int current_col;
    TraverseType traverse_type;
    IteratorDirection direction;
} MatrixIterator;

/**
 * @struct s_iterateur
 * @brief Structure pour l'itérateur.
 */
typedef struct s_iterateur t_iterateur;

/**
 * @fn MatrixIterator createMatrixIterator(t_mat_char_star_dyn *matrix, TraverseType traverse_type, IteratorDirection direction)
 * @brief Fonction pour créer un itérateur.
 * @param matrix Pointeur vers la matrice.
 * @param traverse_type Type de parcours (ligne ou colonne).
 * @param direction Direction du parcours (avant ou arrière).
 * @return L'itérateur créé.
*/
MatrixIterator createMatrixIterator(t_mat_char_star_dyn *matrix, TraverseType traverse_type, IteratorDirection direction);

/**
 * @fn char *currentValue(const MatrixIterator *iterator)
 * @brief Fonction pour obtenir la valeur courante de l'itérateur.
 * @param iterator Pointeur vers l'itérateur.
 * @return La valeur courante de l'itérateur.
*/
char *currentValue(const MatrixIterator *iterator);

/**
 * @fn bool hasMoreElements(const MatrixIterator *iterator)
 * @brief Fonction pour savoir s'il y a encore des éléments à parcourir.
 * @param iterator Pointeur vers l'itérateur.
 * @return true s'il y a encore des éléments à parcourir, false sinon.
*/
bool hasMoreElements(const MatrixIterator *iterator);

/**
 * @fn void moveToNextElement(MatrixIterator *iterator)
 * @brief Fonction pour passer à l'élément suivant.
 * @param iterator Pointeur vers l'itérateur.
*/
void moveToNextElement(MatrixIterator *iterator);

/**
 * @fn void setPosition(MatrixIterator *iterator, int position, int default_value)
 * @brief Fonction pour se positionner à une position donnée.
 * @param iterator Pointeur vers l'itérateur.
 * @param position Position à laquelle se positionner.
*/
void setPosition(MatrixIterator *iterator, int position);

/**
 * @fn void libererIterateur(MatrixIterator *iterator)
 * @brief Fonction pour libérer l'itérateur.
 * @param iterator Pointeur vers l'itérateur.
*/
void libererIterateur(MatrixIterator *iterator);


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
