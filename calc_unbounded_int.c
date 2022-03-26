#include <stdio.h>
#include <stdlib.h>

void interpreteur() {
    FILE *instruc = fopen("source.txt", "r");
    if(instruc == NULL) {
        exit(1);
    }

    //char variables[50];
    //char commande[1024];

    char var = 0;
    char egal = 0;
    long long entier = 0;

    while(fscanf(instruc, "%c %c %lld", &var, &egal, &entier) != EOF){
        printf("varible : %c\n", var);
        printf("egal : %c\n", egal);
        printf("entier : %lld\n", entier);

        printf("\n");
    }
    

    fclose(instruc);
}

int main() {
    interpreteur();

    return EXIT_SUCCESS;
}