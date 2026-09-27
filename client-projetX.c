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
    char decoded[MAXREP];
    int i=0;
    while (reponse[i]!='\0'){
        char c=reponse[i];
        if (c>='a' && c<='z'){
            decoded[i]='a'+(c-'a'-5+26)%26;
        } else if (c>='A' && c<='Z'){
            decoded[i]='A'+(c-'A'-5+26)%26;
        } else {
            decoded[i]=c;
        }
        i++;
    }
    decoded[i]='\0';
    printf("Message décodé : %s\n", decoded);
    envoyer("depart");
    envoyer("veni vidi vici");
    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}