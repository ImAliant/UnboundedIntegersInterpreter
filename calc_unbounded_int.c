#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

#include "unbounded_int.h"

#define LINES_LENGTH 1024
#define VARIABLES 50

char variables[VARIABLES];
unbounded_int valeur_variable[VARIABLES];

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
        printf("%c = %s\n", c, unbounded_int2string(valeur_variable[index]));
    }
}

static void addition(char variable, char a, char b) {
    int index_variable = cherche_index_variable(variable);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if(index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !\n");
        exit(1);
    }
    else {
        valeur_variable[index_variable] = unbounded_int_somme(valeur_variable[index_a], valeur_variable[index_b]);
    }
}

static void soustration(char variable, char a, char b) {
    int index_variable = cherche_index_variable(variable);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if(index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !\n");
        exit(1);
    }
    else
        valeur_variable[index_variable] = unbounded_int_difference(valeur_variable[index_a], valeur_variable[index_b]);
}

static void multiplication(char variable, char a, char b) {
    int index_variable = cherche_index_variable(variable);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if(index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !\n");
        exit(1);
    }
    else{
        if(unbounded_int_cmp_unbounded_int(valeur_variable[index_a], valeur_variable[index_b]) == -1)
            valeur_variable[index_variable] = unbounded_int_produit(valeur_variable[index_b], valeur_variable[index_a]);
        else
            valeur_variable[index_variable] = unbounded_int_produit(valeur_variable[index_a], valeur_variable[index_b]);
    }
        
}

static void condition_operation(char op, char var, char *var1, char *var2) {
    switch (op)
    {
    case '+':
        if(isdigit(var1[0]) && isdigit(var2[0]))
            addition(var, variables[0], variables[1]);
        else if(isdigit(var1[0]) && !isdigit(var2[0]))
            addition(var, variables[0], var2[0]);
        else if(!isdigit(var1[0]) && isdigit(var2[0]))
            addition(var, var1[0], variables[1]);
        else
            addition(var, var1[0], var2[0]);

        /*if((isdigit(var1[0]) || ((var1[0] == '-' || var1[0] == '+') && isdigit(var1[1]))) && (isdigit(var2[0]) || ((var2[0] == '-' || var2[0] == '+') && isdigit(var2[1])))) 
            addition(var, variables[0], variables[1]);
        else if((isdigit(var1[0]) || ((var1[0] == '-' || var1[0] == '+') && isdigit(var1[1])) && (!isdigit(var2[0]) && var2[0] != '-' || var2[0] != '+')))
            addition(var, variables[0], var2[0]);
        else if((!isdigit(var1[0]) && var1[0] != '-' || var1[0] != '+') && (isdigit(var2[0]) || ((var2[0] == '-' || var2[0] == '+') && isdigit(var2[1]))))
            addition(var, var1[0], variables[1]);
        else
            addition(var, var1[0], var2[0]);*/
        break;
    case '-':
        if(isdigit(var1[0]) && isdigit(var2[0]))
            soustration(var, variables[0], variables[1]);
        else if(isdigit(var1[0]) && !isdigit(var2[0]))
            soustration(var, variables[0], var2[0]);
        else if(!isdigit(var1[0]) && isdigit(var2[0]))
            soustration(var, var1[0], variables[1]);
        else
            soustration(var, var1[0], var2[0]);
        break;
    case '*':
        if(isdigit(var1[0]) && isdigit(var2[0]))
            multiplication(var, variables[0], variables[1]);
        else if(isdigit(var1[0]) && !isdigit(var2[0]))
            multiplication(var, variables[0], var2[0]);
        else if(!isdigit(var1[0]) && isdigit(var2[0]))
            multiplication(var, var1[0], variables[1]);
        else
            multiplication(var, var1[0], var2[0]);
        break;
    default:
        printf("Cette operation n'existe pas !");
        break;
    }
}

void interpreteur(/*char *source, char *dest*/) {
    FILE *instruc = fopen("source.txt", "r");
    if(instruc == NULL) {
		printf("Le fichier n'a pas pu être ouvert.\n");
        exit(1);
    }

    char var = 0;
    char * entier = malloc(20*sizeof(char));
    assert(entier != NULL);
    char op = 0;

    variables[0] = 'z'; //valeur temp 1
    valeur_variable[0] = string2unbounded_int("0");
    variables[1] = 'x'; //valeur temp 2
    valeur_variable[1] = string2unbounded_int("0");
    int i = 2;

    char *commande_ligne = malloc(1024*sizeof(char));
    assert(commande_ligne != NULL);

    while(fgets(commande_ligne, 1023, instruc) != NULL) {
        char *prt = strstr(commande_ligne, "print");
        if(prt != NULL) {
            var = commande_ligne[strlen(commande_ligne)-3];
            print(var);
        }
        else {
            long long e = 0;
            if(sscanf(commande_ligne, "%c = %lld", &var, &e) == 2) {
                int index = cherche_index_variable(var);
                if(index == -1) {
                    variables[i] = var;
                    valeur_variable[i] = ll2unbounded_int(e);
                    i++;
                }
                else {
                    valeur_variable[index] = ll2unbounded_int(e);
                }
            }
            else {
                char * var1 = malloc(20*sizeof(char));
                assert(var1 != NULL);
                char * var2 = malloc(20*sizeof(char));
                assert(var2 != NULL);
                if(sscanf(commande_ligne, "%c = %s %c %s", &var, var1, &op, var2) == 4) {
                    if(cherche_index_variable(var) == -1) {
                        variables[i] = var;
                        valeur_variable[i] = string2unbounded_int("0");
                        i++;
                    }
                    
                    char *eptr;
                    long long result;
                    if(isdigit(var1[0]) || ((var1[0] == '-' || var1[0] == '+') && isdigit(var1[1])))
                        valeur_variable[0] = string2unbounded_int(var1);
                    if(isdigit(var2[0]) || ((var2[0] == '-' || var2[0] == '+') && isdigit(var2[1])))
                        valeur_variable[1] = string2unbounded_int(var2);

                    condition_operation(op, var, var1, var2);
                }
            }
        }
    }
    fclose(instruc);
}

int main(int argc, char *argv[]) {
    /*char *source = malloc(10*sizeof(char));
    assert(source != NULL);

    if(strcmp(argv[1], "-i") == 0)
        source = argv[2];
    else
        source = "vide";

    char *dest = malloc(10*sizeof(char));
    assert(dest != NULL);
    
    if(strcmp(source, "vide") == 0) {
        if(strcmp(argv[1], "-o") == 0)
            dest = argv[2];
        else
            dest = "vide";
    }
    else {
        if(strcmp(argv[3], "-o") == 0)
            dest = argv[4];
        else
            dest = "vide";
    }*/
    interpreteur(/*source, dest*/);

    return EXIT_SUCCESS;
}
