#include "client.h"
#include <stdio.h>
#include <string.h>

void remove_first_char(char *str) {
    if (str == NULL || str[0] == '\0') {
        return;
    }

    memmove(str, str + 1, strlen(str));
}

void move_n_first_char_to_end(char *str, int n) {
    if (str == NULL || str[0] == '\0' || n <= 0) {
        return;
    }
    size_t len = strlen(str);
    
    // On sort s'il ne reste pas au moins n caractères
    if (len < (size_t)n) {
        return;
    }

    char new[n + 1];
    memcpy(new, str, n);
    new[n] = '\0'; //  car memcpy n'ajoute pas de '\0'
    memmove(str, str + n, len - n + 1);
    strcat(str, new);
}

int main(void) {
    // Affiche les échanges avec le serveur (false pour désactiver)
    show_messages(true);

    // Connexion au serveur AppoLab
    connexion("im2ag-appolab.u-ga.fr");

    char reponse[MAXREP];
    char enc[MAXREP] = ""; 

    envoyer("login 12513439 JALLOULI");
    envoyer("load crypteMove");
    envoyer_recevoir("help", reponse);

    int idx_enc = 0;
    while (reponse[0] != '\0') {
        // STEP 1
        char c = reponse[0];
        enc[idx_enc++] = c;
        enc[idx_enc] = '\0';

        // STEP 2
        remove_first_char(reponse);        
        int x = (unsigned char)c % 8;
        move_n_first_char_to_end(reponse, x);
    }

    
    envoyer("depart");

    
    envoyer(enc);

    printf("Fin d'envoi des messages.\n");
    deconnexion();
    printf("Fin de la connection au serveur\n");
    return 0;
}