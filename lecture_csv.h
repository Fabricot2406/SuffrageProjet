#ifndef LECTURE_CSV_H
#define LECTURE_CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 65

/**
 * @struct s_matriceVote
 * @brief Structure pour allocation matrice dynamique.
 */
typedef struct s_matriceVote t_mat_char_star_dyn; 

/**
 * @fn int estMauvaiseExtension(char *fichier)
 * @brief Fonction qui confirme si le fichier est un ".csv".
 * @param fichier Le nom du fichier à vérifier.
 * @return 1 si le fichier n'est pas un ".csv", 0 sinon.
 */
int estMauvaiseExtension(char *fichier);

/**
 * @fn t_mat_char_star_dyn *creerMatrice()
 * @brief Fonction pour initialiser la matrice.
 * @return Pointeur vers la matrice créée.
 */
t_mat_char_star_dyn *creerMatrice();

/**
 * @fn t_mat_char_star_dyn *remplirMatrice(t_mat_char_star_dyn *matrice, char *fichier)
 * @brief Fonction pour remplir la matrice avec les données du fichier CSV.
 * @param matrice Pointeur vers la matrice à remplir.
 * @param fichier Le nom du fichier CSV.
 * @return Pointeur vers la matrice remplie.
 */
t_mat_char_star_dyn *remplirMatrice(t_mat_char_star_dyn *matrice, char *fichier);

/**
 * @fn void afficherMatrice(t_mat_char_star_dyn *matrice)
 * @brief Fonction qui affiche la matrice.
 * @param matrice Pointeur vers la matrice à afficher.
 */
void afficherMatrice(t_mat_char_star_dyn *matrice);

/**
 * @fn void libererMatrice(t_mat_char_star_dyn *matrice)
 * @brief Fonction pour libérer la matrice.
 * @param matrice Pointeur vers la matrice à libérer.
 */
void libererMatrice(t_mat_char_star_dyn *matrice);

#endif