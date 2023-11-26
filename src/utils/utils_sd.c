#include "utils_sd.h"

void afficherVainqueur(char * methode, int nbCandidats, int nbVotants, char * nomVainqueur, double score) {
    if (strcmp(methode, "uninominale à un tour") == 0 || strcmp(methode, "uninominale à deux tours, tour 1") == 0 || 
    strcmp(methode, "uninominale à deux tours, tour 2") == 0) {
        printf("Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s, score = %.2f%%\n",
        methode, nbCandidats, nbVotants, nomVainqueur, score);
    } else {
        printf("Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s\n",
        methode, nbCandidats, nbVotants, nomVainqueur);
    }
};