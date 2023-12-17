/**
 * @file lecture_csv.c
 * @author Marco
 * @date 2023-11-28
 */
#include "lecture_csv.h"

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

int estMauvaiseExtension(char *fichier){
    //pointe sur la derniere occurence du "." dans le nom de fichier
    char *extension = strrchr(fichier,'.');
    //retourne 0 si l'extension est ".csv"
    return extension!=NULL && strcmp(extension,".csv");
}