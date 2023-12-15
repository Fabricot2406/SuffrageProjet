/** \\file */
/**
 * @file main.c
 * @authors Fabio, Anthony et Marco
 * @brief
 * @date 2023-11-28
 * 
 * @copyright Copyright (c) 2023
 */
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#include "./utils/global.h"

// Structure pour représenter une méthode et sa fonction associée.
typedef struct {
    char *nom;
    void (*fonction)();
} Methode;

Methode liste_methodes[] = {
    {"uni1", calculer_uninominale_un_tour},
    {"uni2", calculer_uninominale_deux_tours},
    {"cm", condorcet_minimax},
    {"cp", condorcet_paires},
    {"cs", condorcet_schulze},
    {"jm", determinerVainqueurJugement},
};

void appliquer_methode(char *methode, t_mat_char_star_dyn *matrice_csv, ballot *matrice_ballot, t_mat_int_dyn *matrice_duel, char **candidats_nom, int i) {
    // Jugement majoritaire
    if (strcmp(methode, "jm") == 0) {
        liste_methodes[i].fonction(matrice_csv);
    }
    // Classement par les pairs
    else if (strcmp(methode, "cp") == 0  || strcmp(methode, "cs") == 0 || strcmp(methode, "cm") == 0) {
        liste_methodes[i].fonction(matrice_duel,candidats_nom);
    }
    // Autres méthodes
    else {
        liste_methodes[i].fonction(matrice_ballot); // Appelle la fonction associée à la méthode trouvée
    }
}

/**
 * Lance le calcul du vote en utilisant la méthode spécifiée par l'utilisateur.
 * 
 * @param fichier Le nom du fichier de données de vote.
 * @param output Le nom du fichier de sortie pour les résultats.
 * @param methode La méthode de calcul des résultats choisie par l'utilisateur.
 * @param duel Le type de fichier (duel ou non). Si le fichier est un duel, alors type_fichier = true.
 */
void calculerVote(char *fichier, char *output, char *methode, bool duel) {
    int methode_trouvee = 0;

    t_mat_int_dyn *matrice_duel = NULL;
    ballot *matrice_ballot = NULL;
    char **candidats_nom = NULL;

    // Remplissage de la matrice de vote.
    t_mat_char_star_dyn *matrice_csv = remplirMatrice(fichier);

    if (!duel){
        // Création et remplissage du ballot.
        matrice_ballot = creer_ballot(matrice_csv -> nbColonnes, matrice_csv -> nbLignes);
        remplir_ballot(matrice_ballot, matrice_csv);
        candidats_nom = matrice_ballot->candidats_nom;

        // Création de la matrice de duel à partir du ballot.
        matrice_duel = creer_matrice_duel(matrice_ballot);

    }else{
        // Création de la matrice de duel directement à partir de la matrice de chaines de caractères.
        matrice_duel = creer_matrice_duel_f_char(matrice_csv);
        candidats_nom = matrice_csv->tab[0];
    }
    
    if (strcmp(methode, "all") == 0) {
        for (size_t i = 0; i < sizeof(liste_methodes) / sizeof(Methode); i++) {
            appliquer_methode(liste_methodes[i].nom, matrice_csv, matrice_ballot, matrice_duel, candidats_nom, i);
            methode_trouvee = 1;
        }
    } else {
        // Cherche la méthode choisie.
        for (size_t i = 0; i < sizeof(liste_methodes) / sizeof(Methode); i++) {
            if (strcmp(methode, liste_methodes[i].nom) == 0) {
                appliquer_methode(methode, matrice_csv, matrice_ballot, matrice_duel, candidats_nom, i);
                methode_trouvee = 1;
                break;
            }
        }
    }


    if (!methode_trouvee) {
        fprintf(stderr, "Liste des paramètres de l'option m : uni1, uni2, cm, cp, cs, jm, all.\n");
        exit(EXIT_FAILURE);
    }
    detruire_matrice(matrice_duel);
    libererMatrice(matrice_csv);
    if (!duel){
        detruire_ballot(matrice_ballot);
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
 * @brief Affiche un menu d'actions pour l'utilisateur et effectue l'action choisie.
 *
 * @param fichier Le nom du fichier de données de vote.
 * @param output Le nom du fichier de sortie pour les résultats.
 * @param methode La méthode de calcul des résultats.
 * @param duel Le type de fichier (duel ou non). Si le fichier est un duel, alors type_fichier = true.
 */
void presentationMenu(char *fichier, char *output, char *methode, bool duel) {
    int choix;

    do {
        printf("Choisissez une action à effectuer :\n");
        printf("1. Calculer les résultats de vote.\n");
        printf("2. Consulter ses votes.\n");
        printf("3. Construire et afficher le ballot.\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        // On vide le tampon d'entrée (buffer) après la saisie.
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choix) {
            case 1:
                calculerVote(fichier, output, methode, duel);
                break;
            case 2:
                verifierVote(fichier);
                break;
            case 3:
                construire_afficher_TAD(fichier);
                break;
            default:
                printf("Veuillez choisir une action valide (1 ou 2) !\n");
                break;
        }
    } while (choix != 1 && choix != 2 && choix != 3);
}

/**
 * Affiche le tutoriel d'utilisation du programme.
 *
 * @param nom_executable Le nom de l'exécutable du programme.
 */
void afficher_tutoriel(char *nom_executable){

    char *tuto =    "\n\t-i et -d sont incompatibles."
                    "\n\t-i signifie que le fichier est un fichier d'entrée."
                    "\n\t-d signifie que le fichier est un fichier de duel (à utiliser pour condorcet)."
                    "\n\t-m est la méthode de calcul des résultats. Mettre uninominal."
                    "\n\tFacultatif : -o est le fichier de sortie des résultats. Pas encore implémenté"
                    "\n\nExemple : ./Suffrage -i voteCondorcet test tes -m uninominal"
                    "\n\nPour plus d'informations, veuillez consulter la documentation.\n";
                
    fprintf(stderr, "\n<USAGE> : %s (-i fichier) ou (-d fichier) -o fichier_log -m methode\n%s", nom_executable,tuto);           
}

/*------------------------ PROGRAMME PRINCIPAL ------------------------*/

/**
 * Fonction principale du programme.
 *
 * @param argc Le nombre d'arguments de la ligne de commande.
 * @param argv Un tableau d'arguments de la ligne de commande.
 * @return 0 en cas de succès, d'autres valeurs en cas d'erreur.
 */
int main(int argc, char* argv[]) {
    char *input = NULL, *duel = NULL, *output = NULL, *methode = NULL;
    int option;

    // Vérification du nombre d'options (au minimum 5).
    if (argc < 5) {
        afficher_tutoriel(argv[0]);
        exit(EXIT_FAILURE);
    }

    // Récupération des paramètres des options.
    while ((option = getopt(argc, argv, "i:d:o:m:")) != -1) {
        switch (option) {
            case 'i':
                input = optarg;
                break;
            case 'd':
                duel = optarg;
                break;
            case 'o': // Fichier de sortie pas encore implémenté
                output = optarg;
                // Ici on vérifiera si le fichier txt existe déjà, ou si il faut le créer.
                break;
            case 'm':
                methode = optarg;
                break;
            default:
                afficher_tutoriel(argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    // Vérification de la présence des options nécessaires.
    if (methode == NULL || (input == NULL && duel == NULL)) {
        fprintf(stderr, "Les options -i ou -d (au choix), ainsi que l'option -m sont obligatoires.\n");
        exit(EXIT_FAILURE);
    }

    // Vérification de l'incompatibilité des options -i et -d.
    if (!((input == NULL || duel == NULL) && !(input == NULL && duel == NULL))) {
        fprintf(stderr, "Les options -i et -d sont incompatibles.\n");
        exit(EXIT_FAILURE);
    }

    // Vérification de l'incompatibilité entre l'option -d et les méthodes uni1 et uni2.
    if (duel != NULL && (strcmp(methode, "uni1") == 0 || strcmp(methode, "uni2") == 0 || strcmp(methode, "jm") == 0 || strcmp(methode, "all") == 0)) {
        fprintf(stderr, "Il est impossible d'utiliser les méthodes uni1, uni2, jm et all avec l'option -d.\n");
        exit(EXIT_FAILURE);
    }
    // Vérification de l'existance des fichiers
    char const *fichierCSV = argv[2];
    char const repertoire[] = "./tests/";
    char const extension_csv[] = ".csv";
    char cheminComplet[1024];
    if (!fichierExiste(fichierCSV,repertoire,extension_csv,cheminComplet))
    {
        fprintf(stderr, "Le fichier CSV spécifié n'existe pas.\n"
                    "Veuillez entrer le nom du fichier uniquement (sans son extension ni son chemin).\n"
                    "Celui-ci doit se trouver dans le répertoire tests.\n\n"
                    "Exemple : ./Suffrage -i voteCondorcet -m uni1\n");
        exit(EXIT_FAILURE);
    }
    // Lancement du menu contextuel
    presentationMenu(cheminComplet, output, methode, duel != NULL);

    return 0;
}