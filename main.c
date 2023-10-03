#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

int main(int argc, char* argv[]) {
    char *input = NULL, *duel = NULL, *output = NULL, *methode = NULL;
    int option;

    if (argc < 2) {
        fprintf(stderr, "Usage : %s -i fichier_csv -d fichier_csv -o fichier_txt_log -m methode\n"
                        "Pour plus d'informations quant à l'usage des options, référez-vous à la documentation.\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    while ((option = getopt(argc, argv, "i:d:o:m:")) != -1) {
        switch (option) {
            case 'i':
                input = optarg;
                // Ici on ajoutera la vérification que le fichier est un fichier csv.
                break;
            case 'd':
                duel = optarg;
                // Ici on ajoutera la vérification que le fichier est un fichier csv.
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

    if (methode == NULL || (input == NULL && duel == NULL)) {
        fprintf(stderr, "Les options -i ou -d (au choix), ainsi que l'option -m sont obligatoires.\n");
        exit(EXIT_FAILURE);
    }

    if (!((input == NULL || duel == NULL) && !(input == NULL && duel == NULL))) {
        fprintf(stderr, "Les options -i et -d sont incompatibles.\n");
        exit(EXIT_FAILURE);
    }

    if (duel != NULL && (strcmp(methode, "uni1") == 0 || strcmp(methode, "uni2") == 0)) {
        fprintf(stderr, "Il est impossible d'utiliser les méthodes uni1 et uni2 avec l'option -d.\n");
        exit(EXIT_FAILURE);
    }

    if (input != NULL) {
        printf("Option -i : %s\n", input);
    }
    if (duel != NULL) {
        printf("Option -d : %s\n", duel);
    }
    if (output != NULL) {
        printf("Option -o : %s\n", output);
    }
    printf("Option -m : %s\n", methode);

    if (strcmp(methode, "uni1") == 0) {
        // Cas où methode est égal à "uni1"
        printf("Méthode uni1 sélectionnée.\n");
    } else if (strcmp(methode, "uni2") == 0) {
        // Cas où methode est égal à "uni2"
        printf("Méthode uni2 sélectionnée.\n");
    } else if (strcmp(methode, "cm") == 0) {
        // Cas où methode est égal à "cm"
        printf("Méthode cm sélectionnée.\n");
    } else if (strcmp(methode, "cp") == 0) {
        // Cas où methode est égal à "cp"
        printf("Méthode cp sélectionnée.\n");
    } else if (strcmp(methode, "cs") == 0) {
        // Cas où methode est égal à "cs"
        printf("Méthode cs sélectionnée.\n");
    } else if (strcmp(methode, "jm") == 0) {
        // Cas où methode est égal à "jm"
        printf("Méthode jm sélectionnée.\n");
    } else if (strcmp(methode, "all") == 0) {
        // Cas où methode est égal à "all"
        printf("Méthode all sélectionnée.\n");
    } else {
        fprintf(stderr, "Liste des paramètres de l'option m : uni1, uni2, cm, cp, cs, jm, all.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}