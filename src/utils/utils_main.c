/**
 * @file utils_main.c
 * @brief Fichier de fonctions utilitaires nécessaires au main.
 * @authors Anthony, Marco et Fabio
 * @date 2023-12-17
 */
#include "utils_main.h"

char error_msg[] = "\tErreur : Chaîne non valide\n";

void creer_chemin_complet(char *chemin_complet, const char *nomFichier, const char *repertoire,const char *extension) {
    strcpy(chemin_complet, repertoire);
    strcat(chemin_complet, nomFichier);
    strcat(chemin_complet, extension);
}

int fichier_existe(const char *nomFichier, const char *repertoire, const char *extension, char *cheminComplet) {
    creer_chemin_complet(cheminComplet, nomFichier, repertoire, extension);
    FILE *fichier = fopen(cheminComplet, "r");
    if (fichier != NULL) {
        fclose(fichier);
        return 1;
    } else return 0;
}

int control_cle(char *cle){
    for (int i = 0; cle[i] != '\0'; i++) {
        if (!isalnum(cle[i])){
            fprintf(stderr, "%s",error_msg);
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Fonction qui vérifie si la chaine est valide
 * Processus pour chaque caractère de la chaine:
 *    CAS 1 : Lettre
 *         Prénom : La première lettre de chaque mot est en majuscule.
 *         nom : toutes les lettres sont converties en majuscules.
 *    CAS 2 : Espace ou tiret
 *         - Il ne peut pas y avoir plus d'un espace ou d'un tiret consécutif
 *         - Il ne peut pas y avoir un ' ' ou '-' à la fin de la chaîne
 *    CAS 3 : Autre caractère
 *         - Erreur
 * @param chaine la chaine à vérifier
 * @param prenom 1 si c'est un prénom, 0 si c'est un nom
 * @return int 1 si la chaine est invalide, 0 sinon
 */
int verif_chaine(char *chaine, int prenom){
    int alpha = 0;
    int nb_separateur_consecutif = 0;
    char caract_courant;

    for (int i = 0; chaine[i] != '\0'; i++) {
        caract_courant = chaine[i];
        alpha = isalpha(caract_courant);
        chaine[0] = toupper(chaine[0]);
        if (caract_courant == ' ' || caract_courant == '-'){
            nb_separateur_consecutif++;
            // Il ne peut pas y avoir plus d'un espace ou d'un tiret consécutif
            // Il ne peut pas y avoir un ' ' ou '-' à la fin de la chaîne
            if (nb_separateur_consecutif>1 || chaine[i+1]=='\0'){
                fprintf(stderr, "%s",error_msg);
                return 1;
            }
        }else if (alpha){ // CAS : Lettre
            // a - CAS Prénom
            if (prenom){   
                // La première lettre de chaque mot est en majuscule.
                if (i>0 && isalpha(chaine[i-1])) chaine[i] = tolower(chaine[i]);
                if (i!=0 && !isalnum(chaine[i-1])) chaine[i] = toupper(chaine[i]);
            // b - CAS nom : toutes les lettres sont converties en majuscules.
            }else chaine[i] = toupper(chaine[i]);
            nb_separateur_consecutif = 0;
        }else{ // CAS : Autre caractère
            fprintf(stderr, "%s",error_msg);
            return 1;
        }
    }
    return 0;
}

int control_nom_prenom(char *chaine, int prenom){
    // Verifier si la chaine est vide
    if (sizeof(chaine) == 0) {
        fprintf(stderr, "%s",error_msg);
        return 1;
    }

    // Le premier caractère doit être une lettre.
    if (!isalpha(chaine[0])) {
        fprintf(stderr, "%s",error_msg);
        return 1;
    }
    
    // Verifier si la chaine est valide
    return verif_chaine(chaine, prenom);
}

void remplir_log(FILE *log_file, Data data) {
    char **candidats_nom = data.candidats_nom;
    ballot *ballot = data.matrice_ballot;
    t_mat_int_dyn *matrice_duel = data.matrice_duel;
    larc *list_arc = larc_init(matrice_duel);
    
    if(ballot != NULL) ballot_log(ballot, log_file);
    else{
        int nb_votants = matrice_duel->mat[0][1] + matrice_duel->mat[1][0];
        int nb_candidats = matrice_duel->cols;
        fprintf(log_file,
            "Nombre de candidats : %d\n"
            "Nombre de votants : %d\n"
            "Liste des candidats : \n", 
        nb_candidats, nb_votants);
        for (int i = 0; i < nb_candidats; i++) {
            fprintf(log_file,"[%d] : %s\n",i,candidats_nom[i]);
        }
        fprintf(log_file,"\n");
    }
    mat_duel_log(matrice_duel, log_file);
    larc_log(list_arc, log_file);

    larc_delete(list_arc);
}