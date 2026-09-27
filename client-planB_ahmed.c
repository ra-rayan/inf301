#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

void cesar(char *texte, int N){
    N=((N%26)+26)%26;
    int i=0;
    while(texte[i]!='\0'){
        char c=texte[i];
        if(c>='a'&&c<='z'){
            texte[i]='a'+(c-'a'+N)%26;
        }
        else if(c>='A'&&c<='Z'){
            texte[i]='A'+(c-'A'+N)%26;
        }
        i++;
    }
}
int main(){
    show_messages(true);
    connexion("im2ag-appolab.u-ga.fr");
    char reponse[MAXREP];
    char phrase[MAXREP];

    envoyer("login 12513439 JALLOULI");
    envoyer("load planB");
    envoyer("depart");
    envoyer_recevoir("aide", reponse);
    int D = reponse[0] - 'C';
    strcpy(phrase, "hasta la revolucion");
    cesar(phrase, -D);
    envoyer(phrase);

    printf ("Fin d'envoi des messages.\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}
