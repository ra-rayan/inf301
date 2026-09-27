#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
void deca_cesar(char *texte, int n){
    if (n<0){
        n=26+n;
    }
    int i=0;
    while(texte[i]!='\0'){
        char c=texte[i];
        if(c>='a'&&c<='z'){
            texte[i]='a'+(c-'a'+n)%26;
        }
        else if(c>='A'&&c<='Z'){
            texte[i]='A'+(c-'A'+n)%26;
        }
        i++;
    }
}
int main(){
    show_messages(true);
    connexion("im2ag-appolab.u-ga.fr");
    char reponse[MAXREP];
    char mdp[MAXREP];
    envoyer("login 12518371 RAHMANI");
    envoyer("load planB");
    envoyer("depart");
    envoyer_recevoir("aide", reponse);
    int i = reponse[0] - 'C';
    deca_cesar(reponse, -i);
    printf("Réponse du serveur : %s\n", reponse);
    strcpy(mdp, "hasta la revolucion");
    deca_cesar(mdp, -i);
    envoyer(mdp);
    envoyer("5402 2586 9910 4327");

    printf ("Fin d'envoi des messages.\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}