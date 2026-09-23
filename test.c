#include "client.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
void move_last_n_char_to_first(char *str,int n){
    if (n<0 || (unsigned long)n>strlen(str)) return;
    unsigned long i=strlen(str)-n;
    unsigned long j=0;
    char temp[MAXREP];
    while (i<strlen(str)){
        temp[j]=str[i];
        j++;
        i++;
    }
    i=0;
    while (j<strlen(str)){
        temp[j]=str[i];
        j++;
        i++;
    }
    temp[j]='\0';
    strcpy(str,temp);
}
void add_first_char_to_beginning(char *str,char c){
    int len=strlen(str);
    for (int i=len;i>0;i--){
        str[i]=str[i-1];
    }
    str[0]=c;
    str[len+1]='\0';
}
void decrypter(char *enc){
    int i = strlen(enc)-1;
    char rep[MAXREP];
    while (i>=0){ 
        char c = enc[i];
        int x=c%8;
        move_last_n_char_to_first(rep,x);
        add_first_char_to_beginning(rep,c);
        enc[i]='\0';
        i--;
    }
    strcpy(enc,rep);
}
int main(){
char enc[MAXREP]="Pee ct mosusriae.ttg";
decrypter(enc);
printf("%s\n",enc);
}