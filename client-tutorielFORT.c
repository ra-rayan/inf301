#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

int main() {
    char reponse[MAXREP];
    // Affiche les échanges avec le serveur (false pour désactiver)
    show_messages(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr");

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer_recevoir("login 12518371 RAHMANI",reponse);
    printf("Réponse du serveur: %s", reponse);
    envoyer("load tutorielFORT");
    envoyer("depart");
    envoyer("OK");
    envoyer_recevoir("OUI",reponse);
    envoyer_recevoir(toupper(reponse),reponse);
    
    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}
