#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#include "./utils/lecture_csv.h"
#include "./verify/verify_my_vote.h"

char errorMsg[] = "\tErreur : Chaîne non valide\n";

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
 * Vérifie l'existence d'un fichier en utilisant un chemin complet.
 *
 * @param nomFichier Le nom du fichier que l'on souhaite vérifier.
 * @param repertoire Le répertoire dans lequel le fichier est censé se trouver.
 * @param extension L'extension du fichier à chercher
 * @return 1 si le fichier existe, 0 s'il n'existe pas ou en cas d'erreur d'ouverture.
 */
int fichierExiste(const char *nomFichier, const char *repertoire, const char *extension) {
    // Créez un tableau pour le chemin complet (suffisamment grand pour le résultat)
    char cheminComplet[1024];

    // Copiez le répertoire dans le chemin complet
    strcpy(cheminComplet, repertoire);

    // Concaténez le nom du fichier au chemin complet
    strcat(cheminComplet, "/");
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
 * Vérifie si la chaîne de caractères 'cle' est constituée uniquement de caractères alphanumériques.
 * Si la chaîne contient d'autres caractères, affiche un message d'erreur et renvoie 1.
 *
 * @param cle La chaîne de caractères à vérifier.
 * @return 0 si 'cle' est valide, 1 en cas d'erreur.
 */
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


/**
 * Vérifie la validité d'une chaîne de caractères représentant un nom ou un prénom.
 * La fonction contrôle que la chaîne passée en paramètre est valide
 *
 * @param chaine La chaîne de caractères à vérifier.
 * @param prenom 1 si la chaine saisie est un prénom. 0 si c'est un nom de famille
 * @return 0 si 'chaine' est valide, 1 en cas d'erreur.
 */

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
                if (!isalnum(chaine[i-1]))
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
                fprintf(stderr, "Usage : %s -i fichier_csv -d fichier_csv -o fichier_log_txt -m methode\n"
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
    // Vérification de l'existance des fichiers
    char const *fichierCSV = argv[2];
    char const repertoire[] = "tests/";
    char const extension_csv[] = ".csv";
    if (!fichierExiste(fichierCSV,repertoire,extension_csv))
    {
        fprintf(stderr, "Le fichier CSV spécifié n'existe pas.\n");
        exit(EXIT_FAILURE);
    }
    char const *fichierTXT = argv[4];
    char const extension_txt[] = ".txt";
    if (!fichierExiste(fichierTXT,repertoire,extension_txt))
    {
        fprintf(stderr, "Le fichier TXT spécifié n'existe pas.\n");
        exit(EXIT_FAILURE);
    }
    
    // Lancement du menu contextuel
    presentationMenu(fichier, output, methode);

    return 0;
}
