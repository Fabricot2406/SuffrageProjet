#include "utils_main.h"

char errorMsg[] = "\tErreur : Chaîne non valide\n";

int fichierExiste(const char *nomFichier, const char *repertoire, const char *extension, char *cheminComplet) {
    // Copiez le répertoire dans le chemin complet
    strcpy(cheminComplet, repertoire);

    // Concaténez le nom du fichier au chemin complet
    strcat(cheminComplet, nomFichier);
    strcat(cheminComplet, extension);

    FILE *fichier = fopen(cheminComplet, "r");

    if (fichier != NULL) {
        fclose(fichier);
        return 1; // Le fichier existe
    } else {
        return 0; // Le fichier n'existe pas
    }
}

int controlCle(char *cle){
    for (int i = 0; cle[i] != '\0'; i++) {
        if (!isalnum(cle[i]))
        {
            fprintf(stderr, "%s",errorMsg);
            return 1;
        }
    }
    return 0;
}

int controlNomPrenom(char *chaine, int prenom){
    int nbSeparateurConsecutif = 0;

    // Le premier caractère doit être une lettre.
    if (!isalpha(chaine[0])) {
        fprintf(stderr, "%s",errorMsg);
        return 1;
    }

    for (int i = 0; chaine[i] != '\0'; i++) {
        char caractCourant = chaine[i];
        int isAlpha = isalpha(caractCourant);
        chaine[0] = toupper(chaine[0]);
        if (caractCourant == ' ' || caractCourant == '-')
        {
            nbSeparateurConsecutif++;
            // Il ne peut pas y avoir plus d'un espace ou d'un tiret consécutif
            // Il ne peut pas y avoir un ' ' ou '-' à la fin de la chaîne
            if (nbSeparateurConsecutif>1 || chaine[i+1]=='\0')
            {
                fprintf(stderr, "%s",errorMsg);
                return 1;
            }
            
        }else if (isAlpha)
        {   
            // Si la chaîne saisie est un prénom, la première lettre de chaque mot est convertie en majuscules.
            // Si la chaîne est un nom, toutes les lettres sont converties en majuscules.
            if (prenom)
            {   
                if (i>0 && isalpha(chaine[i-1])){
                    chaine[i] = tolower(chaine[i]); 
                }
                
                if (i!=0 && !isalnum(chaine[i-1]))
                    chaine[i] = toupper(chaine[i]);
            }else   chaine[i] = toupper(chaine[i]);
            nbSeparateurConsecutif = 0;
        // Si la chaîne contient un caractère incorret : Erreur
        }else
        {
            fprintf(stderr, "%s",errorMsg);
            return 1;
        }
    }
    return 0;
}

void construire_afficher_TAD(char *fichier) {
    t_mat_char_star_dyn *matrice = remplirMatrice(fichier);
    ballot *b = creer_ballot(matrice->nbColonnes - 4, matrice->nbLignes - 1);
    remplir_ballot(b, matrice);
    afficher_ballot(b);
    t_mat_int_dyn *matrice_duel = creer_matrice_duel(b);
    afficher_matrice_duels(matrice_duel);
    larc *list_arc = larc_init(matrice_duel);
    afficher_larc(list_arc);
    int vainqueur = 0;
    if (vainqueur_condorcet(list_arc, &vainqueur)){
        printf("Le vainqueur de Condorcet est le candidat %d\n\n", vainqueur);
    }else{
        printf("Il n'y a pas de vainqueur de Condorcet dans cette election.\n\n");
    }
    
    detruire_larc(list_arc);
    detruire_matrice(matrice_duel);
    libererMatrice(matrice);
    detruire_ballot(b);
}