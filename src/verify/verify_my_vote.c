/**
 * @file verify_my_vote.c
 * @author Marco  
 * @brief Fichier qui contient les fonctions pour vérifier son vote
 * @date 2023-11-26
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"
#include "sha256_utils.h"
#include "../utils/lecture_csv.h"
#include "verify_my_vote.h"

char *hasherChaines(char *nom,char *cle){
    //on alloue la memoire pour la chaine de caractere qui contiendra le nom et la cle
    char *nomCle = malloc((strlen(nom)+strlen(cle)+1)*sizeof(unsigned char));
    //on concatene le nom et la cle
    strcpy(nomCle,nom);
    strcat(nomCle,cle);
    //on alloue la memoire pour le hash
    int bufferSize=SHA256_BLOCK_SIZE;
    char *hash = malloc(bufferSize*2+1*sizeof(char));
    //on hash la chaine de caractere
    sha256ofString((BYTE *)nomCle,hash);
    free(nomCle);
    return hash;
}

void trouverHashDansCsv (char *hash, char *fichier){
    //on lit le fichier csv et on le stocke dans une matrice
    t_mat_char_star_dyn *matrice = mat_char_init_from_file(fichier);
    int ligne,colonne;
    //on cherche le hash dans la matrice
    if (mat_char_search_elem(matrice,hash,&ligne,&colonne)==0){
        //si on ne le trouve pas on affiche un message d'erreur
        printf("Impossible de trouver votre vote veuillez verifier vos donnees.\n");
        mat_char_delete(matrice);
        return;
    }
    //on affiche la ligne correspondante au hash
    mat_char_display_row(matrice,ligne);
    //on libere la matrice
    mat_char_delete(matrice);
}