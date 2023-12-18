/**
 * @file jugement_majoritaire.c
 * @author Marco
 * @brief Fichier de la méthode de scrutin du jugement majoritaire
 * @date 2023-11-28
 */
#include "jugement_majoritaire.h"

void recalculer_mention(List *tab_candidat);
void calculer_vainqueur_jugement(List *tab_candidat);

/**
 * @brief Structure représentant un candidat dans le scrutin du jugement majoritaire.
 */
typedef struct s_candidat{
    char *nom;
    List *votes_candidat;
    int *mention;
}Candidat;

/**
 * @brief Calcule l'indice de mention.
 * @param nb_votes : Le nombre de votes.
 * @return int : L'indice de mention calculé.
 */
int calculer_indice_mention(int nb_votes){
    //Si le nombre de votes est impair on l'incrémente afin de pouvoir le diviser par 2
    if (nb_votes%2==1)
        nb_votes++;
    //La mention du candidat correspond à la médiane de la liste (valeur a l'indice (n/2)-1)
    return nb_votes/2-1;
}

/**
 * @brief Attribue une mention.
 * @param mention : La mention à attribuer.
 * @return char* : La mention attribuée sous forme de chaîne de caractères.
 */
char *attribuer_mention(int mention){
    char *mention_candidat = malloc(sizeof(int)*3);
    //On attribue une mention en fonction de la note donnée en paramètre
    //On utilise un tableau de chaînes pour stocker les mentions
    char *mentions[] = {"TB", "B", "B", "AB", "AB", "P", "P", "M", "M", "AF"};
    //On vérifie que la mention est entre 1 et 10
    if(mention >= 1 && mention <= 10){
        //On copie la mention correspondante dans le paramètre mention_char
        strcpy(mention_candidat, mentions[mention - 1]);
    }
    return mention_candidat;
}

/**
 * @brief Recherche la meilleure mention.
 * @param tab_candidat : La liste des candidats.
 * @return char* : La meilleure mention trouvée sous forme de chaîne de caractères.
 */
char *rechercher_meilleure_mention(List *tab_candidat){
    int mention = 10;
    for (int i=0;i<tab_candidat->size && mention!=1;i++){
        Candidat *candidat = list_at(tab_candidat,i);
        if (*candidat->mention<mention)
            mention=*candidat->mention;
    }
    return attribuer_mention(mention);
}

/**
 * @brief Initialise un candidat.
 * @param matrice : La matrice contenant les informations du candidat.
 * @param num_candidat : Le numéro du candidat.
 * @return Candidat* : Structure d'un candidat de l'élection.
 */
Candidat *candidat_init(t_mat_char_star_dyn *matrice, int num_candidat){
    //Initialisation de la structure candidat
    Candidat *candidat;
    if((candidat = malloc(sizeof(Candidat)))==NULL){
        fprintf(stderr,"Erreur lors de l'allocation de la strcture.\n");
        return NULL;
    }
    //L'indice colonne représente l'indice du candidat en prenant en compte l'incrément de colonne de la matrice CSV
    int colonne=INCREMENT_COLONNE+num_candidat;
    //On trouve le nom du candidat pour le donner à la structure
    candidat->nom=malloc(sizeof(char)*strlen(matrice->tab[0][colonne])+1);
    strcpy(candidat->nom,matrice->tab[0][colonne]);
    //On crée la liste doublement chainée correspondant à la structure du candidat
    candidat->votes_candidat=list_create();
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
        list_push_back(candidat->votes_candidat,valeur);
    }
    //On trie la liste par ordre croissant afin de trouver la médiane
    candidat->votes_candidat=list_sort(candidat->votes_candidat,cmp_inferieur_egal);
    //Le nombre de votes est égal à la taille de la liste de votes
    int indice_mention = calculer_indice_mention(candidat->votes_candidat->size);
    candidat->mention = list_at(candidat->votes_candidat,indice_mention);
    return candidat;
}

/**
 * @brief Initialise un tableau de candidats.
 * @param matrice : La matrice contenant les informations des candidats.
 * @return List* :  Liste des candidats de l'élection.
 */
List *init_tableau_candidat(t_mat_char_star_dyn *matrice){
    //Si la matrice est nulle on renvoit un message d'erreur et on quitte la fonction
    if (matrice==NULL){
        fprintf(stderr,"Erreur initialisation matrice.\n");
        return NULL;
    }
    //Le nombre de candidat est égal au nombre total de colonnes sans les premieres colonnes informatives
    int nb_candidat = matrice->nbColonnes-INCREMENT_COLONNE;
    //Initialisation de la liste de candidats
    List *tab_candidat=list_create();
    //Pour chaque element du tableau on crée une structure correspondant au candidats de l'élection et on la pousse dans la liste
    for (int i=0;i<nb_candidat;i++){
        list_push_back(tab_candidat,candidat_init(matrice,i));
    }
    return tab_candidat;
}

/**
 * @brief Libère un candidat.
 * @param elem : Le candidat à libérer.
 */
void liberer_candidat(void *elem){
    //On cast elem au type Candidat et on libère chaque champ de la structure
    Candidat *candidat = elem;
    free(candidat->nom);
    list_delete(candidat->votes_candidat,free);
    free(candidat);
}

/**
 * @brief Recalcule la mention des candidats à égalité en supprimant le vote correspondant à leur mention et en recalculant leur mention avec la liste résultante.
 * @param tab_candidat_reduit : La liste réduite des candidats.
 */
void recalculer_mention(List *tab_candidat){
    //Pour chaque candidat à égalité, on supprime de leur liste de vote le vote correspondant à leur mention et 
    //on recalcule leur mention avec la liste résultante.
    for (int i=0;i<tab_candidat->size;i++){
        Candidat *candidat = list_at(tab_candidat,i);
        int indice_mention = calculer_indice_mention(candidat->votes_candidat->size);
        list_remove_at(candidat->votes_candidat,indice_mention,free);
        indice_mention = calculer_indice_mention(candidat->votes_candidat->size);
        candidat->mention = list_at(candidat->votes_candidat,indice_mention);
    }
    calculer_vainqueur_jugement(tab_candidat);
}

/**
 * @brief Calcule le vainqueur du jugement majoritaire en parcourant la liste des candidats et en supprimant les candidats qui n'ont pas la meilleure mention.
 * si le tableau contient plusieurs gagnants, on recalcule la mention de chaque candidat.
 * @param tab_candidat : La liste des candidats.
 */
void calculer_vainqueur_jugement(List *tab_candidat){
    //On obtient la mention du premier candidat de la liste qui représente la meilleure mention
    char *meilleure_mention = rechercher_meilleure_mention(tab_candidat);
    //On compare la mention de tous les autres candidats avec la meilleure mention
    for (int i=0;i<tab_candidat->size;i++){
        Candidat *candidat = list_at(tab_candidat,i);
        char *mention_candidat = attribuer_mention(*candidat->mention);
        if (strcmp(meilleure_mention,mention_candidat)){
            list_remove_at(tab_candidat,i,liberer_candidat);
            i--;
        }
        free(mention_candidat);
    }

    free(meilleure_mention);
    //Si le tableau contient plusieurs gagnants, on recalcule la mention de chaque candidat
    if (tab_candidat->size>1){
        recalculer_mention(tab_candidat);
    }
}


/**
 * @brief Teste l'affichage du tableau de structure candidat.
 * @param tab_candidat : La liste des candidats.
 */
void test_affichage(List *tab_candidat){
    printf("Candidat List Size = %d\n\n",tab_candidat->size);
    for (int i=0;i<tab_candidat->size;i++){
        Candidat *candidat = list_at(tab_candidat,i);
        printf("Candidat Name = %s\n",candidat->nom);
        list_map(candidat->votes_candidat,afficher_int_ptr);
        char *mention_char=attribuer_mention(*candidat->mention);
        printf("\nNumber of votes = %d\tCandidat Mediane = %d\tCandidat Mention = %s\n",candidat->votes_candidat->size,*candidat->mention,mention_char);
        free(mention_char);
        printf("\n");
    }
    printf("--------------------------------------------------------\n");
}

/**
 * @brief Libère une liste de candidats.
 * @param tab_candidat : La liste des candidats à libérer.
 */
void liberer_liste_candidat(List *tab_candidat){
    list_delete(tab_candidat,liberer_candidat);
}

void determiner_vainqueur_jugement(t_mat_char_star_dyn *matrice, FILE *output){
    List *tab_candidat = init_tableau_candidat(matrice);
    //test_affichage(tab_candidat);
    calculer_vainqueur_jugement(tab_candidat);
    Candidat *vainqueur = list_at(tab_candidat,0);
    int nb_candidat = matrice->nbColonnes-INCREMENT_COLONNE;
    int nb_votant = matrice->nbLignes-INCREMENT_LIGNE;
    retourner_vainqueur("Jugement majoritaire",nb_candidat,nb_votant,vainqueur->nom,0,output);
    liberer_liste_candidat(tab_candidat);
}