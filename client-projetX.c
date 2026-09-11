#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

int main() {
    // Affiche les échanges avec le serveur (false pour désactiver)
    show_messages(true);
    char reponse[MAXREP];
    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr");

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer("login 12518371 RAHMANI");
    envoyer("load projetX");
    envoyer_recevoir("help",reponse);
    FILE *fichier = fopen("projetX.txt", "w");
    fprintf(fichier, "%s\n", reponse);
    fclose(fichier);
    envoyer("depart");
    envoyer("veni vidi vici");
    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}