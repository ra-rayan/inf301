#include "client.h"
#include <stdio.h>
#include <string.h>

void decrypte_move(const char *enc, char *dest) {
    dest[0] = '\0';
    int len_enc = strlen(enc);

    for (int i = len_enc - 1; i >= 0; i--) {
        char c = enc[i];
        int x = (unsigned char)c % 8;
        int len = strlen(dest);

        
        if (x > 0 && len >= x) {
            char temp[MAXREP];
            memcpy(temp, dest + len - x, x);
            memcpy(temp + x, dest, len - x);
            temp[len] = '\0';
            strcpy(dest, temp);
        }

      
        memmove(dest + 1, dest, len + 1);
        dest[0] = c;
    }
}

int main(void) {
    show_messages(true);
    connexion("im2ag-appolab.u-ga.fr");

    char enc[MAXREP];
    char clair[MAXREP];

    envoyer("login 12513439 JALLOULI");
    envoyer("load BayOfPigs");

    
    envoyer_recevoir("depart", enc);

    
    decrypte_move(enc, clair);

    printf("\nMessage dechiffre :\n%s\n\n", clair);

    deconnexion();
    return 0;
}