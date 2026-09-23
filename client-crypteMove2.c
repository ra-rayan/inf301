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
    if (len < (size_t)n) {
        return;
    }

    char new[n + 1];
    memcpy(new, str, n);
    new[n] = '\0';
    memmove(str, str + n, len - n + 1);
    strcat(str, new);
}

int main(void) {
    show_messages(true);

    connexion("im2ag-appolab.u-ga.fr");

    char reponse[MAXREP];
    char enc[MAXREP] = "";

    envoyer("login 12513439 JALLOULI");
    envoyer("load crypteMove");

    envoyer_recevoir("aide", reponse);

    int idx_enc = 0;
    while (strlen(reponse) > 0) {
        char c = reponse[0];
        enc[idx_enc++] = c;
        enc[idx_enc] = '\0';

        remove_first_char(reponse);

        int x = (unsigned char)c % 8;
        move_n_first_char_to_end(reponse, x);
    }

    
    envoyer("depart");
    envoyer(enc);

    deconnexion();
    return 0;
}