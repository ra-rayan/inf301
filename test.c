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
    size_t len;
    char *new_str;

    if (str == NULL || str[0] == '\0' || n <= 0) {
        return;
    }
    len = strlen(str);
    n=n%len;
    char new[n+1];
    memmove(new, str, n);
    for (int i=0;i<n;i++){
    remove_first_char(str);}
    strcat(str,new);
    printf("%s\n",str);

}
    

int main(){  
        char s[] = "abcdef";
        move_n_first_char_to_end(s, 4);
    }