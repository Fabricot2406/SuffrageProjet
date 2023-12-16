/**
 * @file jugement_majoritaire.c
 * @author Marco
 * @date 2023-11-28
 */
#include "jugement_majoritaire.h"

typedef struct s_candidat{
    char *nom;
    List *votesCandidat;
    int *mention;
}Candidat;

int calculerIndiceMention(int nbVotes){
    //Si le nombre de votes est impair on l'incrémente afin de pouvoir le diviser par 2
    if (nbVotes%2==1)
        nbVotes++;
    //La mention du candidat correspond à la médiane de la liste (valeur a l'indice (n/2)-1)
    return nbVotes/2-1;
}

char *attribuerMention(int mention){
    char *mentionCandidat = malloc(sizeof(int)*3);
    //On attribue une mention en fonction de la note donnée en paramètre
    //On utilise un tableau de chaînes pour stocker les mentions
    char *mentions[] = {"TB", "B", "B", "AB", "AB", "P", "P", "M", "M", "AF"};
    //On vérifie que la mention est entre 1 et 10
    if(mention >= 1 && mention <= 10){
        //On copie la mention correspondante dans le paramètre mentionChar
        strcpy(mentionCandidat, mentions[mention - 1]);
    }
    return mentionCandidat;
}

char *rechercherMeilleureMention(List *tabCandidat){
    int mention = 10;
    for (int i=0;i<tabCandidat->size && mention!=1;i++){
        Candidat *candidat = list_at(tabCandidat,i);
        if (*candidat->mention<mention)
            mention=*candidat->mention;
    }
    return attribuerMention(mention);
}


Candidat *initCandidat(t_mat_char_star_dyn *matrice, int numCandidat){
    //Initialisation de la structure candidat
    Candidat *candidat;
    if((candidat = malloc(sizeof(Candidat)))==NULL){
        fprintf(stderr,"Erreur lors de l'allocation de la strcture.\n");
        return NULL;
    }
    //L'indice colonne représente l'indice du candidat en prenant en compte l'incrément de colonne de la matrice CSV
    int colonne=INCREMENT_COLONNE+numCandidat;
    //On trouve le nom du candidat pour le donner à la structure
    candidat->nom=malloc(sizeof(char)*strlen(matrice->tab[0][colonne])+1);
    strcpy(candidat->nom,matrice->tab[0][colonne]);
    //On crée la liste doublement chainée correspondant à la structure du candidat
    candidat->votesCandidat=list_create();
    //On remplit la liste doublement chainée en négligeant la premiere ligne de la matrice CSV
    for (int i=1;i<matrice->nbLignes;i++){
        //Le TAD liste prend en valeurs des (void *) on caste donc (en int *) la valeur que l'on veut attribuer au candidat
        int *valeur;
        if ((valeur= malloc(sizeof(int)))==NULL){
            fprintf(stderr,"Erreur allocation mémoire int\n");
            exit(-1);
        } 
        *valeur = atoi(matrice->tab[i][colonne]);
        //Si un vote est égal à -1 on le considère comme étant le pire vote il prendra donc la valeur 10
        if (*valeur==-1)
            *valeur=10;
        list_push_back(candidat->votesCandidat,valeur);
    }
    //On trie la liste par ordre croissant afin de trouver la médiane
    candidat->votesCandidat=list_sort(candidat->votesCandidat,cmp_inferieur_egal);
    //Le nombre de votes est égal à la taille de la liste de votes
    int indiceMention = calculerIndiceMention(candidat->votesCandidat->size);
    candidat->mention = list_at(candidat->votesCandidat,indiceMention);
    return candidat;
}

List *initTableauCandidat(t_mat_char_star_dyn *matrice){
    //Si la matrice est nulle on renvoit un message d'erreur et on quitte la fonction
    if (matrice==NULL){
        fprintf(stderr,"Erreur initialisation matrice.\n");
        return NULL;
    }
    //Le nombre de candidat est égal au nombre total de colonnes sans les premieres colonnes informatives
    int nbCandidat = matrice->nbColonnes-INCREMENT_COLONNE;
    //Initialisation de la liste de candidats
    List *tabCandidat=list_create();
    //Pour chaque element du tableau on crée une structure correspondant au candidats de l'élection et on la pousse dans la liste
    for (int i=0;i<nbCandidat;i++){
        list_push_back(tabCandidat,initCandidat(matrice,i));
    }
    return tabCandidat;
}

void libererCandidat(void *elem){
    //On cast elem au type Candidat et on libère chaque champ de la structure
    Candidat *candidat = elem;
    free(candidat->nom);
    list_delete(candidat->votesCandidat,free);
    free(candidat);
}

void calculerVainqueurJugement(List *tabCandidat){
    //On obtient la mention du premier candidat de la liste qui représente la meilleure mention
    char *meilleureMention = rechercherMeilleureMention(tabCandidat);
    //On compare la mention de tous les autres candidats avec la meilleure mention
    for (int i=0;i<tabCandidat->size;i++){
        Candidat *candidat = list_at(tabCandidat,i);
        char *mentionCandidat = attribuerMention(*candidat->mention);
        if (strcmp(meilleureMention,mentionCandidat)){
            list_remove_at(tabCandidat,i,libererCandidat);
            i--;
        }
        free(mentionCandidat);
    }

    free(meilleureMention);
    //Si le tableau contient plusieurs gagnants, on recalcule la mention de chaque candidat
    if (tabCandidat->size>1){
        recalculerMention(tabCandidat);
    }
}

void recalculerMention (List *tabCandidat){
    //Pour chaque candidat à égalité, on supprime de leur liste de vote le vote correspondant à leur mention et 
    //on recalcule leur mention avec la liste résultante.
    for (int i=0;i<tabCandidat->size;i++){
        Candidat *candidat = list_at(tabCandidat,i);
        int indiceMention = calculerIndiceMention(candidat->votesCandidat->size);
        list_remove_at(candidat->votesCandidat,indiceMention,free);
        indiceMention = calculerIndiceMention(candidat->votesCandidat->size);
        candidat->mention = list_at(candidat->votesCandidat,indiceMention);
    }
    calculerVainqueurJugement(tabCandidat);
}

void testAffichage(List *tabCandidat){
    printf("Candidat List Size = %d\n\n",tabCandidat->size);
    for (int i=0;i<tabCandidat->size;i++){
        Candidat *candidat = list_at(tabCandidat,i);
        printf("Candidat Name = %s\tNumber of Votes = %d\n",candidat->nom,candidat->votesCandidat->size);
        list_map(candidat->votesCandidat,afficher_int_ptr);
        char *mentionChar=attribuerMention(*candidat->mention);
        printf("\nCandidat Mediane = %d\tCandidat Mention = %s\n",*candidat->mention,mentionChar);
        free(mentionChar);
        printf("\n");
    }
    printf("--------------------------------------------------------\n");
}

void libererListeCandidat(List *tabCandidat){
    list_delete(tabCandidat,libererCandidat);
}

void determinerVainqueurJugement(t_mat_char_star_dyn *matrice, FILE *output){
    List *tabCandidat = initTableauCandidat(matrice);
    calculerVainqueurJugement(tabCandidat);
    Candidat *vainqueur = list_at(tabCandidat,0);
    int nb_candidat = matrice->nbColonnes-INCREMENT_COLONNE;
    int nb_votant = matrice->nbLignes-INCREMENT_LIGNE;
    retourner_vainqueur("Jugement majoritaire",nb_candidat,nb_votant,vainqueur->nom,0,output);
    libererListeCandidat(tabCandidat);
}