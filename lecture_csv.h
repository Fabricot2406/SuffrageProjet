#ifndef LECTURE_CSV_H
#define LECTURE_CSV_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX 65

//structure pour allocation matrice dynamique
typedef struct s_matriceVote t_mat_char_star_dyn; 

//fonction qui confirme si le fichier est un ".csv"
int bonneExtension(char *fichier);

//fonction pour initialiser la matrice 
t_mat_char_star_dyn *creerMatrice(char *fichier);

//fonction qui print la matrice
void afficherMatrice(t_mat_char_star_dyn *matrice);

//fonction pour liberer la matrice
void libererMatrice(t_mat_char_star_dyn *matrice);

#endif
