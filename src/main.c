#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#include "./utils/lecture_csv.h"
#include "./verify/verify_my_vote.h"
#include "./utils/utils_main.h"
#include "./utils/dataStructure/arc.h"
//#include "./utils/dataStructure/ballot.h"
#include "./utils/dataStructure/matrice_int_dyn.h"
#include "./utils/dataStructure/matrice_string_dyn.h"
#include "./utils/dataStructure/listegen.h"
#include "./utils/dataStructure/ballotgen.h"

// Structure pour représenter une méthode et sa fonction associée.
typedef struct {
    const char *nom;
    void (*fonction)();
} Methode;

// Définition des fonctions correspondant à chaque méthode.
void methode_uni1() {
    printf("Méthode uni1 sélectionnée.\n");
}

void methode_uni2() {
    printf("Méthode uni2 sélectionnée.\n");
}

void methode_cm() {
    printf("Méthode cm sélectionnée.\n");
}

void methode_cp() {
    printf("Méthode cp sélectionnée.\n");
}

void methode_cs() {
    printf("Méthode cs sélectionnée.\n");
}

void methode_jm() {
    printf("Méthode jm sélectionnée.\n");
}

void methode_all() {
    printf("Méthode all sélectionnée.\n");
}

Methode liste_methodes[] = {
    {"uni1", methode_uni1},
    {"uni2", methode_uni2},
    {"cm", methode_cm},
    {"cp", methode_cp},
    {"cs", methode_cs},
    {"jm", methode_jm},
    {"all", methode_all},
};


/**
 * Lance le calcul du vote en utilisant la méthode spécifiée par l'utilisateur.
 * 
 * @param fichier Le nom du fichier de données de vote.
 * @param output Le nom du fichier de sortie pour les résultats.
 * @param methode La méthode de calcul des résultats choisie par l'utilisateur.
 */
void calculerVote(char *fichier, char *output, char *methode) {
    int methode_trouvee = 0;

    // Cherche la méthode choisie.
    for (size_t i = 0; i < sizeof(liste_methodes) / sizeof(Methode); i++) {
        if (strcmp(methode, liste_methodes[i].nom) == 0) {
            liste_methodes[i].fonction(); // Appelle la fonction associée à la méthode trouvée
            methode_trouvee = 1;
            break;
        }
    }

    if (!methode_trouvee) {
        fprintf(stderr, "Liste des paramètres de l'option m : uni1, uni2, cm, cp, cs, jm, all.\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * Demande à l'utilisateur d'entrer son nom de famille, prénom et clé, puis vérifie leur validité.
 * La fonction affiche également le nom complet (nom et prénom concaténés) et la clé à la fin.
 *
 * @param nom Pointeur vers le tableau où le nom de famille sera stocké.
 * @param prenom Pointeur vers le tableau où le prénom sera stocké.
 * @param cle Pointeur vers le tableau où la clé sera stockée.
 */
void presentationIdentifiant(char *nom,char *prenom,char *cle){
    // 1 - Nom de famille
    do
    {
        printf("Veuillez entrer votre nom de famille: ");
        scanf("%99[^\n]", nom);
        // On vide le tampon d'entrée (buffer) après la saisie.
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    } while (controlNomPrenom(nom,0));
    printf("\tNom de famille saisie : %s\n",nom);

    // 2 - Prénom
    do
    {
        printf("Veuillez entrer votre prénom: ");
        scanf("%99[^\n]", prenom);
        // On vide le tampon d'entrée (buffer) après la saisie.
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    } while (controlNomPrenom(prenom,1));
    printf("\tPrénom saisie : %s\n",prenom);

    // 3 - Cle
    do
    {
        printf("Veuillez entrer votre cle: ");
        scanf("%99[^\n]", cle);
        // On vide le tampon d'entrée (buffer) après la saisie.
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    } while (controlCle(cle));
    
    // On concatène le nom et prénom
    strcat(nom," ");
    strcat(nom,prenom);

    printf("\n\tNom complet : %s\n",nom);
    printf("\tCle : %s\n\n",cle);
}


/**
 * Vérifie la validité du vote en demandant à l'utilisateur d'entrer ses informations d'identification,
 * de les hasher, puis de rechercher le hash correspondant dans un fichier CSV.
 * La fonction effectue les étapes suivantes :
 * 1. Demande à l'utilisateur d'entrer son nom, prénom et clé d'identification.
 * 2. Hash les informations d'identification.
 * 3. Recherche le hash dans un fichier CSV contenant les informations de vote.
 *
 * @param fichier Le nom du fichier CSV contenant les informations de vote.
 */
void verifierVote(char * fichier) {
    char nom[TAILLE_NOM_MAX]; // Contient NOM et prénom
    char prenom[TAILLE_NOM_MAX];
    char cle[TAILLE_CLE_MAX];

    //on demande à l'utilisateur d'entrer ses informations
    presentationIdentifiant(nom,prenom,cle);
    
    //on hash le nom et la cle
    char *hash=hasherChaines(nom,cle);
    //on cherche le hash dans le fichier csv
    trouverHashDansCsv(hash,fichier);
    //on libere le hash
    free(hash);
}

/**
 * Affiche un menu d'actions pour l'utilisateur et effectue l'action choisie.
 *
 * @param fichier Le nom du fichier de données de vote.
 * @param output Le nom du fichier de sortie pour les résultats.
 * @param methode La méthode de calcul des résultats.
 */
void presentationMenu(char *fichier, char *output, char *methode) {
    int choix;

    do {
        printf("Choisissez une action à effectuer :\n");
        printf("1. Calculer les résultats de vote.\n");
        printf("2. Consulter ses votes.\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        // On vide le tampon d'entrée (buffer) après la saisie.
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choix) {
            case 1:
                calculerVote(fichier, output, methode);
                break;
            case 2:
                verifierVote(fichier);
                break;
            default:
                printf("Veuillez choisir une action valide (1 ou 2) !\n");
                break;
        }
    } while (choix != 1 && choix != 2);
}

// Main de test
int main(void) {
    char *fichier = "./tests/vote10.csv";
    t_mat_char_star_dyn *matrice = remplirMatrice(fichier);
    ballot *b = creer_ballot(matrice->nbColonnes - 4, matrice->nbLignes - 1);
    remplir_ballot(b, matrice);
    afficher_ballot(b);
    t_mat_int_dyn *matrice_duel = creer_matrice_duel(b);
    afficher_matrice(matrice_duel, 0);
    detruire_matrice(matrice_duel);
    detruire_ballot(b);
    return 0;
}
