#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

int main() {

    // Affiche les échanges avec le serveur (false pour désactiver)
    show_messages(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr");
    char reponse[MAXREP];

    // Remplacez <identifiant> et <mot de passe> ci dessous.
    envoyer("login 12518371 RAHMANI");
    envoyer_recevoir("load BayOfPigs", reponse);

    for (int i = 0; reponse[i] != '\0'; i++) {
        if (reponse[i] >= 'A' && reponse[i] <= 'Z') {
            reponse[i] = 'A' + (reponse[i] - 'A' - 5 + 26) % 26;
        } else if (reponse[i] >= 'a' && reponse[i] <= 'z') {
            reponse[i] = 'a' + (reponse[i] - 'a' - 5 + 26) % 26;
        }
    }

    printf("Reponse decalee de -5 : %s\n", reponse);
    envoyer_recevoir("help", reponse);
    for (int i = 0; reponse[i] != '\0'; i++) {
        if (reponse[i] >= 'A' && reponse[i] <= 'Z') {
            reponse[i] = 'A' + (reponse[i] - 'A' - 5 + 26) % 26;
        } else if (reponse[i] >= 'a' && reponse[i] <= 'z') {
            reponse[i] = 'a' + (reponse[i] - 'a' - 5 + 26) % 26;
        }
    }
    printf("Reponse decalee de -5 : %s\n", reponse);

    envoyer_recevoir("depart", reponse);
    FILE *file = fopen("bayofpigs.txt", "w");
    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }
    fprintf(file, "%s", reponse);
    fclose(file);

    printf ("Fin d'envoi des messages.\n");
    printf ("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}
