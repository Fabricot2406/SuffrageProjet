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
    List *liste_candidat = pref->list;
    int candidat = *(int *)list_at(liste_candidat, 0);
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

/**
 * @brief Structure de données pour la méthode Condorcet
 * @details Cette structure permet de déterminer si un candidat est le perdant ou le gagnant d'un duel
 */
typedef struct s_statut_candidat{
    int candidat;
    bool est_gagant;
} statut_candidat;

/**
 * @brief Fonction de réduction pour déterminer si le candidat passé en paramètre est le perdant d'un duel
 * @param elem Un élément de la liste, dans le cadre de cette fonction, un arc
 * @param data La structure de données gagnant
 * @return int 1 si le candidat est le perdant d'un duel, 0 sinon
 */
int uni_perdant(void *elem, void *data){
    statut_candidat *g = (statut_candidat *)data;
    arc *a = (arc *)elem;
    if (a->candidat_perdant == g->candidat)
    {
        g->est_gagant = false;
        return 1;
    }
    return 0;
}

bool vainqueur_condorcet(larc *list_arc, int *vainqueur){
    List *list = list_arc->larc;
    int nb_candidats = list_arc->nb_candidats;
    statut_candidat *cand_winner = malloc(sizeof(statut_candidat));
    for (int candidat = 0; candidat < nb_candidats; candidat++)
    {
        cand_winner->candidat = candidat;
        cand_winner->est_gagant = true;
        list_reduce(list,uni_perdant,cand_winner);
        if (cand_winner->est_gagant){
            *vainqueur = candidat;
            free(cand_winner);
            return true;
        }
    }
    free(cand_winner);
    return false;
}