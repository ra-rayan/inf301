#include "client.h"

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

void remove_first_char(char *str) {
    if (str == NULL || str[0] == '\0') {
        return;
    }
    memmove(str, str + 1, strlen(str));
}

int find_char_index(char *str, char c){
    int i = 0;
    while (str[i] != '\0'){
        if (str[i] == c) return i;
        i++;
    }
    return -1;
}

void move_nth_char_to_end(char *str, int n){
    if (str == NULL || n < 0)
        return;
    int len = strlen(str);
    if (n >= len)
        return;
    char c = str[n];
    int i = n;
    while (i < len - 1){
        str[i] = str[i + 1];
        i++;
    }
    str[len - 1] = c;
}

void crypteSeq(char *reponse){
    char seq[MAXREP] = "";
    char enc[MAXREP] = "";
    while (reponse[0] != '\0'){
        char c = reponse[0];
        int x = find_char_index(seq, c);
        if (x == -1){
            seq[strlen(seq)] = c;
            seq[strlen(seq)] = '\0';
            enc[strlen(enc)] = c;
            enc[strlen(enc)] = '\0';
        } else {
            if (x == 0){
                char d = seq[strlen(seq) - 1];
                enc[strlen(enc)] = d;
                enc[strlen(enc)] = '\0';
                move_nth_char_to_end(seq, x);
            } else {
                char d = seq[x - 1];
                enc[strlen(enc)] = d;
                enc[strlen(enc)] = '\0';
                move_nth_char_to_end(seq, x);
            }
        }
        remove_first_char(reponse);
    }
    strcpy(reponse, enc);
}

void decrypteseq(char *message) {
    char seq[MAXREP] = "";
    char dec[MAXREP] = "";
    while (message[0] != '\0') {
        char o = message[0];
        int pos = find_char_index(seq, o);
        char c;
        if (pos == -1) {
            c = o;
            seq[strlen(seq)] = c;
            seq[strlen(seq)] = '\0';
        } else {
            int x = (pos + 1) % strlen(seq);
            c = seq[x];
            move_nth_char_to_end(seq, x);
        }
        dec[strlen(dec)] = c;
        dec[strlen(dec)] = '\0';
        remove_first_char(message);
    }
    strcpy(message, dec);
}

void extraire_mdp(char *message, char *mdp) {
    char *debut = strstr(message, "actuel est");
    int i = find_char_index(debut, '\'');
    i = i + 1;
    int j = 0;
    while (debut[i] != '\'') {
        mdp[j] = debut[i];
        i++;
        j++;
    }
    mdp[j] = '\0';
}

int main() {
    char reponse[MAXREP];
    char mdp[MAXREP];

    show_messages(true);
    connexion("im2ag-appolab.u-ga.fr");
    envoyer("login 12513439 JALLOULI");
    envoyer("load Northwoods");
    envoyer("depart");
    envoyer_recevoir("hasta la victoria siempre", reponse);

    decrypteseq(reponse);
    extraire_mdp(reponse, mdp);
    envoyer_recevoir(mdp, reponse);
    decrypteseq(reponse);

    char rep[MAXREP];
    strcpy(rep, "There will be no Nineteen Eighty-Four");
    crypteSeq(rep);
    envoyer_recevoir(rep, reponse);
    printf("Reponse du serveur : %s\n", reponse);

    printf ("Fin d'envoi des messages.\n");
    deconnexion();
    printf ("Fin de la connection au serveur\n");
    return 0;
}
