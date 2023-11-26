#include "uninominale.h"

int nbCandidats, nbVotants;
int * votes;

void initialiserTableauVotes(ballot * matrice) {
    nbCandidats = matrice -> nb_candidats;
    nbVotants = matrice -> nb_votants; 

    // Création d'un tableau de votes avec le résultat de chaque candidat
    if ((votes = malloc(nbCandidats * sizeof(int))) == NULL) {
        fprintf(stderr,"Erreur lors de l'allocation de la mémoire.\n");
        exit(-1);
    }

    // Init du tableau de votes
    for (int i = 0; i < nbCandidats; i++) {
        votes[i] = 0;
    }
    /*
    // Entrée des scores de chaque candidats
    for (int i = 0; i < nbVotants; i++) {
        votes[fav_candidat(matrice, i)] ++;
    }
    */
}

void calculerUninominaleUnTour(ballot * matrice) {
    initialiserTableauVotes(matrice);

    // Recherche du vainqueur
    int vainqueur = 0;
    for (int i = 0; i < nbCandidats; i++) {
        if (votes[i] > votes[vainqueur]) {
            vainqueur = i;
        }
    }

    afficherVainqueur("uninominale à un tour", nbCandidats, nbVotants, matrice -> candidats_nom[vainqueur], ((double) votes[vainqueur] / nbVotants) * 100);

    free(votes);
}

void calculerUninominaleDeuxTours(ballot * matrice) {
    initialiserTableauVotes(matrice);

    // Recherche des deux vainqueurs
    int vainqueurUn = 1, vainqueurDeux = 0;
    for (int i = 0; i < nbCandidats; i++) {
        if (votes[i] > votes[vainqueurUn]) {
            vainqueurDeux = vainqueurUn;
            vainqueurUn = i;
        } else if (votes[i] > votes[vainqueurDeux]) {
            vainqueurDeux = i;
        }
    }

    // Vérification de la présence de majorité absolue
    if (votes[vainqueurUn] > (nbVotants) / 2) {
        afficherVainqueur("uninominale à deux tours, tour 1", nbCandidats, nbVotants, matrice -> candidats_nom[vainqueurUn], ((double) votes[vainqueurUn] / nbVotants) * 100);
    } else {
        afficherVainqueur("uninominale à deux tours, tour 1", nbCandidats, nbVotants, matrice -> candidats_nom[vainqueurUn], ((double) votes[vainqueurUn] / nbVotants) * 100);
        afficherVainqueur("uninominale à deux tours, tour 1", nbCandidats, nbVotants, matrice -> candidats_nom[vainqueurDeux], ((double) votes[vainqueurDeux] / nbVotants) * 100);

        votes[vainqueurUn] = 0;
        votes[vainqueurDeux] = 0;

        /*
        // Recherche du vainqueur au second tour
        for (int i = 0; i < nbVotants; i++) {
            for (int j = 0; j < nbCandidats; j++) {
                if (matrice -> classement -> mat[i][j] == vainqueurUn) {
                    votes[vainqueurUn] ++;
                    break;
                } else if (matrice -> classement -> mat[i][j] == vainqueurDeux) {
                    votes[vainqueurDeux] ++;
                    break;
                }
            }
        }*/

        // Affichage du vainqueur au second tour
        if (votes[vainqueurUn] < votes[vainqueurDeux]) {
            afficherVainqueur("uninominale à deux tours, tour 2", nbCandidats, nbVotants, matrice -> candidats_nom[vainqueurDeux], ((double) votes[vainqueurDeux] / nbVotants) * 100);
        } else {
            afficherVainqueur("uninominale à deux tours, tour 2", nbCandidats, nbVotants, matrice -> candidats_nom[vainqueurUn], ((double) votes[vainqueurUn] / nbVotants) * 100);
        }
    }

    free(votes);
}