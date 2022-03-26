#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LINES_LENGTH 1024
#define VARIABLES 50

char variables[VARIABLES];
long long valeur_variable[VARIABLES];
char commande[LINES_LENGTH];

static int cherche_index_variable(char variable) {
    int index = -1;
    for(int i=0; i<VARIABLES; i++) {
        if(variables[i] == variable) {
            index = i;
            break;
        }
    }
    return index;
}

static void print(char c) {
    int index = cherche_index_variable(c);
    if(index == -1) {
        printf("Cette variable n'existe pas !");
        exit(1);
    }
    else {
        printf("%c = %lld\n", c, valeur_variable[index]);
    }
}

static void addition(char variable, char a, char b) {
    int index_variable = cherche_index_variable(variable);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if(index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !");
        exit(1);
    }
    else
        valeur_variable[index_variable] = valeur_variable[index_a] + valeur_variable[index_b];
}

static void soustration(char variable, char a, char b) {
    int index_variable = cherche_index_variable(variable);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if(index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !");
        exit(1);
    }
    else
        valeur_variable[index_variable] = valeur_variable[index_a] - valeur_variable[index_b];
}

static void multiplication(char variable, char a, char b) {
    int index_variable = cherche_index_variable(variable);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if(index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !");
        exit(1);
    }
    else
        valeur_variable[index_variable] = valeur_variable[index_a] * valeur_variable[index_b];
}

void interpreteur() {
    FILE *instruc = fopen("source.txt", "r");
    if(instruc == NULL) {
		printf("Le fichier n'a pas pu être ouvert.\n");
        exit(1);
    }

    char var = 0;
    long long entier = 0;
    char op = 0;

    int i = 0;

    char *commande_ligne = malloc(1024*sizeof(char));
    assert(commande_ligne != NULL);

    while(fgets(commande_ligne, 1023, instruc) != NULL) {
        char *prt = strstr(commande_ligne, "print");
        if(prt != NULL) {
            var = commande_ligne[strlen(commande_ligne)-2];
            print(var);
        }
        else {
            if(sscanf(commande_ligne, "%c = %lld", &var, &entier) == 2) {
                int index = cherche_index_variable(var);
                if(index == -1) {
                    variables[i] = var;
                    valeur_variable[i] = entier;
                    i++;
                }
                else {
                    valeur_variable[index] = entier; 
                }
            }
            else {
                char var1 = 0;
                char var2 = 0;
                sscanf(commande_ligne, "%c = %c %c %c", &var, &var1, &op, &var2);
                if(cherche_index_variable(var) == -1) {
                    variables[i] = var;
                    valeur_variable[i] = entier;
                    i++;
                }
                if(op == '+')
                    addition(var, var1, var2);
                else if(op == '-')
                    soustration(var, var1, var2);
                else if(op == '*')
                    multiplication(var, var1, var2);
                else {
                    printf("Cette operation n'existe pas !");
                    exit(1);
                }
            }
        }
    }

    fclose(instruc);
}

int main(int argc, char *argv[]) {
    /*char *source = malloc(10*sizeof(char));
    assert(source != NULL);*/

    //source = argv[2];
    
    interpreteur();

    return EXIT_SUCCESS;
}
