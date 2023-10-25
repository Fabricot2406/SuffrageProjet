#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sha256.h"
#include "sha256_utils.h"
#include "../utils/lecture_csv.h"
#include "verify_my_vote.h"

//fonctione demandée dans le fichier verification.pdf mais je vois pas encore l'utilité
unsigned char *hexaToByte (char *chaine){
    //on multiplie par 4 car 1 caractere hexa = 4 caracteres binaires
    int longueurChaineByte = strlen(chaine)*4+1;
    //on alloue la memoire pour la chaine de caractere binaire
    unsigned char *chaineByte=malloc(longueurChaineByte*sizeof(unsigned char));
    //on met le caractere de fin de chaine
    chaineByte[longueurChaineByte-1]='\0';
    //on convertit la chaine hexa en long
    long valeurHex = strtol(chaine,NULL,16);
    for (int i=longueurChaineByte-2;i>=0;i--){
        //on recupere le bit de poids faible
        chaineByte[i]=valeurHex%2+'0';
        //on divise par 2 pour passer au bit suivant
        valeurHex/=2;
    }
    return chaineByte;
}

char *hasherChaines(char *nom,char *cle){
    //on alloue la memoire pour la chaine de caractere qui contiendra le nom et la cle
    char *nomCle = malloc((strlen(nom)+strlen(cle)+1)*sizeof(unsigned char));
    //on concatene le nom et la cle
    strcpy(nomCle,nom);
    strcat(nomCle,cle);
    /*unsigned char *nomCleByte = hexaToByte(nomCle);
    printf("%s\t %s\n",nomCle,nomCleByte);*/
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
    t_mat_char_star_dyn *matrice = remplirMatrice(fichier);
    int ligne,colonne;
    //on cherche le hash dans la matrice
    if (trouverElem(matrice,hash,&ligne,&colonne)==0){
        //si on ne le trouve pas on affiche un message d'erreur
        printf("Impossible de trouver votre vote veuillez verifier vos donnees.\n");
        libererMatrice(matrice);
        return;
    }
    //on affiche la ligne correspondante au hash
    afficherLigne(matrice,ligne);
    //on libere la matrice
    libererMatrice(matrice);
}

/*int main(){
    //on demande à l'utilisateur d'entrer ses informations
    char nomComplet[TAILLE_NOM_MAX];
    char cle[TAILLE_CLE_MAX];
    char nomFichier[TAILLE_NOM_FICHIER_MAX];
    printf("Veuillez entrer votre nom complet (NOM DE FAMILLE Prenom) : ");
    scanf("%49[^\n]",nomComplet);
    printf("Veuillez entrer le chemin du fichier de vote (avec extension) : ");
    scanf("%99s",nomFichier);
    printf("Veuillez entrer la cle : ");
    scanf("%16s",cle);
    //on hash le nom et la cle
    char *hash=hasherChaines(nomComplet,cle);
    //on cherche le hash dans le fichier csv
    trouverHashDansCsv(hash,nomFichier);
    //on libere le hash
    free(hash);

}*/