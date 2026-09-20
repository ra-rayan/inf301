#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

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

    int len = strlen(str);
    if (n >= len) {
        return;
    }

    char moved[n + 1];
    memcpy(moved, str, n);
    moved[n] = '\0';
    memmove(str, str + n, len - n + 1);
    strcat(str, moved);
}

int main() {
    show_messages(true);

    connexion("im2ag-appolab.u-ga.fr");
    char reponse[MAXREP];
    char enc[MAXREP] = "";

    envoyer("login 12518371 RAHMANI");
    envoyer("load crypteMove");
    envoyer_recevoir("help", reponse);
    envoyer("depart");

    while (reponse[0] != '\0') {
        char c = reponse[0];
        size_t enc_len = strlen(enc);
        enc[enc_len] = c;
        enc[enc_len + 1] = '\0';

        remove_first_char(reponse);
        int x = (unsigned char)c % 8;
        move_n_first_char_to_end(reponse, x);
    }

    envoyer(enc);

    printf("Fin d'envoi des messages.\n");
    printf("Pour envoyer d'autres lignes, ajouter des appels à la fonction `envoyer`\n");
    deconnexion();
    printf("Fin de la connection au serveur\n");
    return 0;
}
