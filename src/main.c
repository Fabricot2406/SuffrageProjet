#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#include "./utils/lecture_csv.h"
#include "./verify/verify_my_vote.h"

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

// Fonction lançant le calcul du vote selon la méthode choisie.
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

int estAlphabetique(const char *chaine) {
    for (int i = 0; chaine[i] != '\0'; i++) {
        if (!isalpha(chaine[i])) {
            return 0;
        }
    }
    return 1;
}

int controlPrenom(char *prenom){
    char *token = strtok(prenom, "-");

    while (token != NULL) {
        if (islower(token[0])) {
            token[0] = toupper(token[0]);
        }

        if (!estAlphabetique(token)) {
            printf("Le prénom ne doit contenir que des caractères alphabétiques : %s\n", token);
            return -1;
        }

        token = strtok(NULL, "-");  // Passage au token suivant
    }
    return 0;
}

int controlNom(char *nom) {

    char *token = strtok(nom, " ");
    while (token != NULL) {
        if (!estAlphabetique(token)) {
            printf("Le nom de famille ne doit contenir que des caractères alphabétiques.\n");
            printf("Format attendu : 'DUPONT' ou 'DUPONT AIGNAN\n");
            return 1;
        }

        int estEnMajuscules = 1;

        for (int i = 0; token[i] != '\0'; i++) {
            if (!isupper(token[i])) {
                estEnMajuscules = 0;
                break;
            }
        }

        if (!estEnMajuscules) {
            for (int i = 0; token[i] != '\0'; i++) {
                token[i] = toupper(token[i]);
            }
        }

        token = strtok(NULL, " ");
    }
    return 0;
}

void presentationIdentifiant(void){
    char nomComplet[TAILLE_NOM_MAX];
    char cle[TAILLE_CLE_MAX];
    char nom[TAILLE_NOM_MAX];
    do
    {
        printf("Veuillez entrer votre nom de famille: ");
        scanf("%s", nom);
    } while (controlNom(&nom));

    do
    {
        printf("Veuillez entrer votre prénom: ");
        scanf("%s", nom);
    } while (controlPrenom(&nom));
    
    fprintf()
    printf("Veuillez entrer la cle : ");
    while (getchar() != '\n');
    scanf("%16s",cle);
}

// Fonction lançant la vérification du vote.
void verifierVote(char * fichier) {
    char nomComplet[TAILLE_NOM_MAX];
    char cle[TAILLE_CLE_MAX];

    //on demande à l'utilisateur d'entrer ses informations

    printf("Veuillez entrer votre nom complet (NOM Prenom) : ");
    while (getchar() != '\n');
    scanf("%49[^\n]",nomComplet);
    printf("Veuillez entrer la cle : ");
    while (getchar() != '\n');
    scanf("%16s",cle);
    
    //on hash le nom et la cle
    char *hash=hasherChaines(nomComplet,cle);
    //on cherche le hash dans le fichier csv
    trouverHashDansCsv(hash,fichier);
    //on libere le hash
    free(hash);
}

// Fonction s'occupant de la gestion du menu.
void presentationMenu(char *fichier, char *output, char *methode) {
    int choix;

    do {
        printf("Choisissez une action à effectuer :\n");
        printf("1. Calculer les résultats de vote.\n");
        printf("2. Consulter ses votes.\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

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


// Début du programme principal.
int main(int argc, char* argv[]) {
    char *input = NULL, *duel = NULL, *output = NULL, *methode = NULL;
    int option;

    // Vérification du nombre d'options (au minimum 5).
    if (argc < 5) {
        fprintf(stderr, "Usage : %s -i fichier_csv -d fichier_csv -o fichier_txt_log -m methode\n"
                        "Pour plus d'informations quant à l'usage des options, référez-vous à la documentation.\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *fichier;

    // Récupération des paramètres des options.
    while ((option = getopt(argc, argv, "i:d:o:m:")) != -1) {
        switch (option) {
            case 'i':
                input = optarg;
                fichier = optarg;
                break;
            case 'd':
                duel = optarg;
                fichier = optarg;
                break;
            case 'o':
                output = optarg;
                // Ici on vérifiera si le fichier txt existe déjà, ou si il faut le créer.
                break;
            case 'm':
                methode = optarg;
                break;
            default:
                fprintf(stderr, "Usage : %s -i fichier_csv -d fichier_csv -o fichier_txt_log -m methode\n"
                        "Pour plus d'informations quant à l'usage des options, référez-vous à la documentation.\n", argv[0]);
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
    if (duel != NULL && (strcmp(methode, "uni1") == 0 || strcmp(methode, "uni2") == 0)) {
        fprintf(stderr, "Il est impossible d'utiliser les méthodes uni1 et uni2 avec l'option -d.\n");
        exit(EXIT_FAILURE);
    }

    // PROGRAMME PRINCIPAL
    presentationMenu(fichier, output, methode);

    return 0;
}
