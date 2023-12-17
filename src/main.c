/**
 * @file main.c
 * @authors Fabio, Anthony et Marco
 * @brief Fichier principal du programme.
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
    {"jm", determiner_vainqueur_jugement},
};

/**
 * @brief Fonction permettant d'appliquer la méthode de scrutin spécifiée en paramètre.
 * 
 * @param methode Nom de la méthode à appliquer.
 * @param structures Structure contenant les données nécessaires à l'application de la méthode.
 * @param index Indice de la méthode dans le tableau liste_methodes.
 * @param output Fichier de sortie pour les résultats.
 */
void appliquer_methode(char *methode, Data structures, int index, FILE *output) {
    // Jugement majoritaire
    if (strcmp(methode, "jm") == 0) {
        liste_methodes[index].fonction(structures.matrice_csv,output);
    }
    // Classement par les pairs
    else if (strcmp(methode, "cp") == 0  || strcmp(methode, "cs") == 0 || strcmp(methode, "cm") == 0) {
        liste_methodes[index].fonction(structures.matrice_duel,structures.candidats_nom,output);
    }
    // Autres méthodes
    else liste_methodes[index].fonction(structures.matrice_ballot,output);
}

/**
 * Lance le calcul du vote en utilisant la méthode spécifiée par l'utilisateur.
 * 
 * @param fichier Le nom du fichier de données de vote.
 * @param log_file Le fichier de log.
 * @param output_file Le fichier de sortie pour les résultats.
 * @param methode La méthode de calcul des résultats choisie par l'utilisateur.
 * @param duel Le type de fichier (duel ou non). Si le fichier est un duel, alors type_fichier = true.
 */
void calculerVote(char *fichier, FILE *log_file, FILE *output_file, char *methode, bool duel) {
    int methode_trouvee = false;
    // Structures de données 
    t_mat_int_dyn *matrice_duel = NULL;
    ballot *matrice_ballot = NULL;
    char **candidats_nom = NULL;

    /*------------------------ Traitement des données ------------------------*/
    
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

    // Structures de données à passer aux méthodes.
    Data donnees = {candidats_nom, matrice_csv, matrice_duel, matrice_ballot};

    // Remplissage du fichier de log.
    if(log_file != NULL) remplir_log(log_file, donnees);
    
    /*------------------------ Execution des méthodes ------------------------*/

    // Si l'utilisateur a choisi la méthode "all", on applique toutes les méthodes.
    if (!strcmp(methode, "all")) {
        for (size_t i = 0; i < sizeof(liste_methodes) / sizeof(Methode); i++) {
            appliquer_methode(liste_methodes[i].nom, donnees, i, output_file);
            methode_trouvee = true;
        }
    } else { // Sinon, on applique la méthode choisie.
        // Cherche la méthode choisie.
        for (size_t i = 0; i < sizeof(liste_methodes) / sizeof(Methode); i++) {
            if (!strcmp(methode, liste_methodes[i].nom)) {
                appliquer_methode(methode, donnees, i, output_file);
                methode_trouvee = true;
                break;
            }
        }
    }

    // Si la méthode n'a pas été trouvée, on affiche un message d'erreur.
    if (!methode_trouvee) {
        fprintf(stderr, "Liste des paramètres de l'option m : uni1, uni2, cm, cp, cs, jm, all.\n");
        exit(EXIT_FAILURE);
    }

    /*------------------------ Libération de la mémoire ------------------------*/

    detruire_matrice(matrice_duel);
    libererMatrice(matrice_csv);
    if (!duel) detruire_ballot(matrice_ballot);
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
    } while (control_nom_prenom(nom,0));
    printf("\tNom de famille saisie : %s\n",nom);

    // 2 - Prénom
    do
    {
        printf("Veuillez entrer votre prénom: ");
        scanf("%99[^\n]", prenom);
        // On vide le tampon d'entrée (buffer) après la saisie.
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    } while (control_nom_prenom(prenom,1));
    printf("\tPrénom saisie : %s\n",prenom);

    // 3 - Cle
    do
    {
        printf("Veuillez entrer votre cle: ");
        scanf("%99[^\n]", cle);
        // On vide le tampon d'entrée (buffer) après la saisie.
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    } while (control_cle(cle));
    
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
    char nom[TAILLE_NOM_MAX] = "";
    char prenom[TAILLE_NOM_MAX] = "";
    char cle[TAILLE_CLE_MAX] = "";

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
 * @param log_file Le fichier de log.
 * @param output_file Le fichier de sortie pour les résultats.
 * @param methode La méthode de calcul des résultats.
 * @param duel Le type de fichier (duel ou non). Si le fichier est un duel, alors type_fichier = true.
 */
void presentationMenu(char *fichier, FILE *log_file, FILE *output_file, char *methode, bool duel) {
    int choix;
    do {
        printf("Choisissez une action à effectuer :"
               "\n1. Calculer les résultats de vote."
               "\n2. Consulter ses votes."
               "\nVotre choix : ");
        scanf("%d", &choix);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        switch (choix) {
            case 1:
                calculerVote(fichier, log_file, output_file, methode, duel);
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

/**
 * Affiche le tutoriel d'utilisation du programme.
 *
 * @param nom_executable Le nom de l'exécutable du programme.
 */
void afficher_tutoriel(char *nom_executable){
    fprintf(stderr, 
        "\n<USAGE> : %s (-i fichier) ou (-d fichier) -o fichier_log -m methode\n"
        "\n\t-i et -d sont incompatibles."
        "\n\t-i signifie que le fichier est un fichier d'entrée."
        "\n\t-d signifie que le fichier est un fichier de duel (à utiliser pour condorcet)."
        "\n\t-m est la méthode de calcul des résultats. Mettre uninominal."
        "\n\tFacultatif : -o est le fichier de sortie des résultats. Pas encore implémenté"
        "\n\nExemple : ./scrutin -i voteCondorcet test tes -m uninominal"
        "\n\nPour plus d'informations, veuillez consulter la documentation.\n", 
    nom_executable);           
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
    char *input = NULL, *duel = NULL, *methode = NULL;
    int option;
    char const *fichier_csv = NULL;
    char const *fichier_log = NULL;
    char const *fichier_output = NULL;
    char const *repertoire_CSV = NULL;
    char const *repertoire_log = "./tests/output/log/";
    char const *repertoire_output = "./tests/output/result/";
    char const *extension_csv = ".csv";
    char const *extension_txt = ".txt";

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
                fichier_csv = optarg;
                fichier_output = optarg;
                break;
            case 'd': 
                duel = optarg;
                fichier_csv = optarg;
                fichier_output = optarg;
                break;
            case 'o': fichier_log = optarg;
                break;
            case 'm': methode = optarg;
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

    /*------------------------ FICHIER LECTURE CSV ------------------------*/
    char cheminCompletCsv[1024];
    if(duel != NULL) repertoire_CSV = "./tests/input/duel/";
    else repertoire_CSV = "./tests/input/vote/";
    // On concatène le chemin du répertoire avec le nom du fichier et son extension
    if (!fichier_existe(fichier_csv,repertoire_CSV,extension_csv,cheminCompletCsv)){ 
        fprintf(stderr,
            "Le fichier CSV spécifié n'existe pas.\n"
            "Veuillez entrer le nom du fichier uniquement (sans son extension ni son chemin).\n"
            "Celui-ci doit se trouver dans le répertoire tests.\n\n"
            "Exemple : ./scrutin -i voteCondorcet -m uni1\n");
        exit(EXIT_FAILURE);
    }

    /*------------------------ FICHIER OUTPUT ------------------------*/
    char chemin_complet_output[1024];
    FILE *output_file = NULL;

    if(fichier_output != NULL){
        // On concatène le chemin du répertoire avec le nom du fichier et son extension
        creer_chemin_complet(chemin_complet_output, fichier_output, repertoire_output, extension_txt);

        // Creer le fichier txt s'il n'existe pas encore :
        output_file = fopen(chemin_complet_output, "w");
    }


    /*------------------------ FICHIER LOG ------------------------*/
    char chemin_complet_log[1024];
    FILE *log_file = NULL;
    if(fichier_log != NULL){
        // On concatène le chemin du répertoire avec le nom du fichier et son extension
        creer_chemin_complet(chemin_complet_log, fichier_log, repertoire_log, extension_txt);

        // Creer le fichier txt s'il n'existe pas encore :
        log_file = fopen(chemin_complet_log, "w");
    }

    /*------------------------ LANCEMENT DU MENU ------------------------*/

    // Lancement du menu contextuel
    presentationMenu(cheminCompletCsv, log_file, output_file, methode, duel != NULL);

    // Fermeture du fichier log.
    if (fichier_log != NULL) fclose(log_file);

    // Fermeture du fichier output.
    if (fichier_output != NULL) fclose(output_file);

    return 0;
}