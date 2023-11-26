#include "utils_sd.h"
#include "./dataStructure/ballot.h"

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

uni_data *creer_uni_data(int *vainqueurUn, int *vainqueurDeux, int *votes){
    uni_data *data = malloc(sizeof(uni_data));
    data -> vainqueurUn = vainqueurUn;
    data -> vainqueurDeux = vainqueurDeux;
    data -> votes = votes;
    return data;
}

int uni_reduce(void *elem, void *data){
    uni_data *d = (uni_data *)data;
    Pref *pref = (Pref *)elem;
    int candidat = pref->values;
    if (candidat == *(d->vainqueurUn)) {
        d->votes[*(d->vainqueurUn)] ++;
        return 1;
    } else if (candidat == *(d->vainqueurDeux)) {
        d->votes[*(d->vainqueurDeux)] ++;
        return 1;
    }
    return 0;
}

double calculerScore(int nbVotants, int nbVotes) {
    return ((double) nbVotes / nbVotants) * 100;
}