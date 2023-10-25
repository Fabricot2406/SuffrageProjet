#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lecture_csv.h"

//contiendra infos fichier CSV
struct s_matriceVote{
    int nbLignes;
    int nbColonnes;
    char ***tab;
};

t_mat_char_star_dyn *creerMatrice (){
    //initialisation de la structure
    t_mat_char_star_dyn *matrice;
    if ((matrice=malloc(sizeof(t_mat_char_star_dyn)))==NULL){
        fprintf(stderr,"Erreur lors de l'allocation de la strcture.\n");
        return NULL;
    }
    matrice->nbLignes=0;
    matrice->nbColonnes=0;
    //initialisation de la matrice
    if ((matrice->tab=malloc(sizeof(char**)))==NULL){
        fprintf(stderr,"Erreur lors de l'allocation du tableau de lignes.\n");
        return NULL;
    }
    if ((matrice->tab[0]=malloc(sizeof(char*)))==NULL){
        fprintf(stderr,"Erreur lors de l'allocation du tableau de colonnes.\n");
        return NULL;
    }
    if ((matrice->tab[0][0]=malloc(TAILLE_MAX*sizeof(char)))==NULL){
        fprintf(stderr,"Erreur lors de l'allocation des cellules.\n");
        return NULL;
    }
    return matrice;   
}

int estMauvaiseExtension(char *fichier){
    //pointe sur la derniere occurence du "." dans le nom de fichier
    char *extension = strrchr(fichier,'.');
    //retourne 0 si l'extension est ".csv"
    return extension!=NULL && strcmp(extension,".csv");
}

t_mat_char_star_dyn *remplirMatrice(char *fichier){
    //si mauvaise extension on retourne matrice vide
    if (estMauvaiseExtension(fichier)){
        fprintf(stderr,"Erreur mauvaise extension de fichier.\n");
        return NULL;
    }
    FILE *f = fopen(fichier,"r");
    //si probleme d'ouverture on retourne matrice vide
    if (f==NULL){
        fprintf(stderr,"Erreur lors de l'ouverture du fichier, verifiez le chemin ou le nom du fichier.\n");
        return NULL;
    }
    t_mat_char_star_dyn *matrice = creerMatrice();


    int ligne=0,colonne=0,cellule=0;

    //lecture du fichier caractère par caractère
    char c=fgetc(f);
    
    while (c!=EOF){
        if (c==','){
            //Si virgule rencontrée : 
            //On termine le mot correspondant la la cellule
            matrice->tab[ligne][colonne][cellule]='\0';
            //On incrémente l'indice de colonne
            colonne++;
        }
        if (c=='\n'){
            //Si saut de ligne rencontré : 
            //On termine le mot correspondant à la dernière cellule de la ligne
            matrice->tab[ligne][colonne][cellule]='\0';
            //On rajoute le nombre de colonnes total a la structure
            matrice->nbColonnes=colonne+1;
            //On incrémente l'indice de ligne
            ligne++;
            //On alloue de l'espace pour une ligne supplémentaire
            if ((matrice->tab=realloc(matrice->tab,(ligne+1)*sizeof(char**)))==NULL){
                fprintf(stderr,"Erreur lors de la reallocation du tableau de lignes.\n");
                return NULL;
            }
            //On initialise la nouvelle ligne a NULL
            matrice->tab[ligne]=NULL;
            //On rétablit l'indice de colonne à 0
            colonne=0;

        }
        if (c==',' || c=='\n'){
            //Si virgule ou saut de ligne rencontré :
            //On alloue de l'espace pour une colonne supplémentaire dans la nouvelle ligne
            if ((matrice->tab[ligne]=realloc(matrice->tab[ligne],(colonne+1)*(sizeof(char*))))==NULL){
                fprintf(stderr,"Erreur lors de la reallocation du tableau de colonnes.\n");
                return NULL;
            }
            //On alloue de l'espace pour un mot supplémentaire dans la premiere colonne de la nouvelle ligne
            if ((matrice->tab[ligne][colonne]=malloc(TAILLE_MAX*sizeof(char)))==NULL){
                fprintf(stderr,"Erreur lors de l'allocation des cellules.\n");
                return NULL;
            }
            //On rétablit l'indice de cellule à 0
            cellule=0;
        }
        else{
            //Si autre caractère, on construit la cellule avec
            matrice->tab[ligne][colonne][cellule]=c;
            cellule++;
        }
        c=fgetc(f);
    }
    //On libere la derniere cellule et la deniere ligne qui resprésentent l'espace vide du fichier CSV
    free(matrice->tab[ligne][colonne]);
    free(matrice->tab[ligne]);
    fclose(f);
    //On determine le nombre total de lignes a la fin après avoir enlevé l'espace de tableau en trop dans la matrice avant de là retourner
    matrice->nbLignes=ligne;
    return matrice;
}

void afficherMatrice(t_mat_char_star_dyn *matrice){
    //Si la matrice est nulle on renvoie une erreur
    if (matrice==NULL){
        fprintf(stderr,"Matice non valide.\n");
        return;
    }
    for (int i=0;i<matrice->nbLignes;i++){
        for (int j=0;j<matrice->nbColonnes;j++){
            //On affiche chaque cellule de la matrice
            printf("%s\t",matrice->tab[i][j]);
        }
        //On passe à la ligne suivante
        printf("\n");
    }
}

void afficherLigne(t_mat_char_star_dyn *matrice, int ligne){
    //Si la matrice est nulle on renvoie une erreur
    if (matrice==NULL){
        fprintf(stderr,"Matice non valide.\n");
        return;
    }
    //On affiche chaque cellule de la ligne
    for (int j=0;j<matrice->nbColonnes;j++){
        printf("%s:\t %s\n",matrice->tab[0][j],matrice->tab[ligne][j]);
    }
}

int trouverElem(t_mat_char_star_dyn *matrice, char *elem, int *ligne, int *colonne){
    //Si la matrice est nulle on renvoie une erreur
    if (matrice==NULL){
        fprintf(stderr,"Matrice non valide.\n");
        return 0;
    }
    //On initialise les indices de ligne et de colonne à -1
    *ligne=-1;
    *colonne=-1;
    //On parcourt la matrice
    for (int i=0;i<matrice->nbLignes;i++){
        for (int j=0;j<matrice->nbColonnes;j++){
            //On compare chaque cellule à l'element recherché
            if (!strcmp(elem,matrice->tab[i][j])){
                //Si on trouve l'element on met à jour les indices de ligne et de colonne
                *ligne=i;
                *colonne=j;
            }
        }
        //On passe à la ligne suivante
    }
    return *ligne!=1 && *colonne!=-1;
}

void libererMatrice(t_mat_char_star_dyn *matrice){
    //Si la matrice est nulle on renvoie une erreur
    if (matrice==NULL){
        return;
    }
    for (int i=0;i<matrice->nbLignes;i++){
        for (int j=0;j<matrice->nbColonnes;j++){
            //On libère chaque cellule de la matrice
            free(matrice->tab[i][j]);
        }
        //On libère chaque ligne de la matrice
        free(matrice->tab[i]);
    }
    //On libère la matrice
    free(matrice->tab);
    //On réinitialise la structure
    matrice->nbLignes=0;
    matrice->nbColonnes=0;
    //On libère la structure
    free(matrice);
    return ; 
}

/*int main(int argc, char **argv){
    t_mat_char_star_dyn *matrice = remplirMatrice("/root/ProjetA/SuffrageProjet/FichiersTestLinux/voteCondorcet.csv");
    afficherMatrice(matrice);
    libererMatrice(matrice);
    return 0;
}*/

