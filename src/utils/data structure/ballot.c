/*
    Fichier contenant les fonctions permettant de gérer les bulletins de vote
*/




/*
Structure list_char définie en amont

Struct ballot {
    list_char *candidats_nom 
        liste des noms des candidats : char* -> nom de chaque candidat
    t_mat_int_dyn *classement : contient tous les classement des candidats
        nb_ligne = nb de candidats
        nb_col = nb de votants
}

Permet d'accèder directement au candidat préféré d'un votant
    exemple : 
        "2 5 1 3 4 0" : entiers correspondants aux indices des candidat dans la liste *candidats_nom
        si candidats_nom = ["A", "B", "C", "D", "E", "F"]
        alors classement = C > F > B > D > E > A
        alors classement[0] = 2 -> C
        alors classement[1] = 5 -> F
        alors classement[2] = 1 -> B
        alors classement[3] = 3 -> D
        alors classement[4] = 4 -> E
        alors classement[5] = 0 -> A

*/