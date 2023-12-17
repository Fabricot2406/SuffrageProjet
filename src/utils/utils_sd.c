/**
 * @file utils_sd.c
 * @authors Anthony, Marco et Fabio
 * @date 2023-11-28
 */
#include "utils_sd.h"

void retourner_vainqueur(char * methode, int nbCandidats, int nbVotants,char * nomVainqueur, double score, FILE *output) {
    // On affiche le vainqueur en fonction de la méthode de scrutin
    // Cas particulier pour le scrutin uninominal à deux tours
    if (strcmp(methode, "uninominal à un tour") == 0 || strcmp(methode, "uninominal à deux tours, tour 1") == 0 || 
    strcmp(methode, "uninominal à deux tours, tour 2") == 0){
        fprintf(output, "Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s, score = %.2f%%\n",
        methode, nbCandidats, nbVotants, nomVainqueur, score);
        printf("Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s, score = %.2f%%\n",
        methode, nbCandidats, nbVotants, nomVainqueur, score);
    }else {
        fprintf(output, "Mode de scrutin : %s, %d candidats, %d votants, vainqueur = %s\n",
        methode, nbCandidats, nbVotants, nomVainqueur);
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

double calculer_score(int nb_votants, int nb_votes) {
    return ((double) nb_votes / nb_votants) * 100;
}

void afficher_int_ptr(void* elem){
    //On cast elem au type int et on l'affiche
    int *value = elem;
    printf("%d  ",*value);
}

bool cmp_inferieur_egal(void *i, void *j){
    //On cast i et j au type int et on les compare
    int *elem1 = i;
    int *elem2 = j;
    return *elem1<=*elem2;
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

/**
 * @brief Fonction permettant de déterminer si un candidat est vainqueur.
 * Processus à suivre : 1) On parcourt la liste d'arc.
 *                          - Si le candidat est impliqué dans un arc où il est perdant, alors il n'est pas vainqueur.
 *                          - Si le candidat n'est impliqué dans aucun arc où il est perdant, alors il est vainqueur.
 * 
 * @param list_arc Liste d'arc trié par ordre décroissant de différence de voix (score).
 * @param candidat Candidat dont on veut savoir si il est vainqueur.
 * @return true Si le candidat est vainqueur.
 * @return false Si le candidat n'est pas vainqueur.
 */
bool est_vainqueur(List *list_arc, int candidat){
    int count_winner = 0;
    Iterator *it_larc = iterator_create(list_arc);
    // On parcourt la liste d'arc
    while (iterator_has_next(it_larc)){
        arc *arc_courant = iterator_current(it_larc);
        // Si le candidat est impliqué dans un arc où il est perdant
        if (arc_courant->candidat_perdant == candidat){
            // Il n'est pas vainqueur
            iterator_delete(it_larc);
            return false;
        }
        if (arc_courant->candidat_gagnant == candidat) count_winner++;
        
        iterator_next(it_larc);
    }
    iterator_delete(it_larc);
    if (!count_winner) return false;
    // Sinon il est vainqueur
    return true;
}

bool vainqueur_condorcet(larc *list_arc, int *vainqueur){
    List *list = list_arc->larc;
    int nb_candidats = list_arc->nb_candidats;
    statut_candidat *cand_winner = malloc(sizeof(statut_candidat));
    for (int candidat = 0; candidat < nb_candidats; candidat++)
    {
        cand_winner->candidat = candidat;
        cand_winner->est_gagant = true;

        Iterator * it = iterator_create(list);
        while (iterator_has_next(it)){
            arc *a = (arc *)iterator_current(it);
            if(uni_perdant(a, cand_winner)){
                break;
            }
            iterator_next(it);
        }
        iterator_delete(it);

        if (cand_winner->est_gagant){
            *vainqueur = candidat;
            free(cand_winner);
            return true;
        }
    }
    free(cand_winner);
    return false;
}


void afficher_position(void *elem, void *data){
    char *candidat = (char *)elem;
    int *position = (int *)data;
    printf("%d. %s\n",*position,candidat);
    (*position)++;
}

void afficher_classement(List *classement){
    printf("Classement :\n\n");
    int position = 1;
    list_reduce(classement,afficher_position,(void *)&position);
    printf("\n");
}