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
    for(int i=0; i<VARIABLES; i++) {
        if(variables[i] == variable) {
            return i;
        }
    }
    return -1;
}
/*static int cherche_index_variable(char* variable) {
    int index = -1;
    for (int i = 0; i < VARIABLES && variables[i] != NULL; i++) {
        if (strcmp(variables[i], variable) == 0) {
            index = i;
            break;
        }
    }
    return index;
}*/

static void print(FILE* d, char c) {
    int index = cherche_index_variable(c);
    if(index == -1) {
        printf("Cette variable n'existe pas !");
        exit(1);
    }
    else {
        char* s = unbounded_int2string(valeur_variable[index]);
        if (!d) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        fprintf(d, "%c = %s\n", c, s);
    }
}
/*static void print(FILE* d, char* c) {
    int index = cherche_index_variable(c);
    if (index == -1) {
        printf("Cette variables n'existe pas !");
        exit(EXIT_FAILURE);
    }
    else {
        char* s = unbounded_int2string(valeur_variable[index]);
        if (!d) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        fprintf(d, "%s = %s\n", c, s);
    }
}*/

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
/*static void addition(char* var, char* a, char* b) {
    int index_variable = cherche_index_variable(var);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if (index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !\n");
        exit(EXIT_FAILURE);
    }
    
    valeur_variable[index_variable] = unbounded_int_somme(valeur_variable[index_a], valeur_variable[index_b]);
}*/

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
/*static void soustraction(char* var, char* a, char* b) {
    int index_variable = cherche_index_variable(var);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if (index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !\n");
        exit(1);
    }
    
    valeur_variable[index_variable] = unbounded_int_difference(valeur_variable[index_a], valeur_variable[index_b]);
}*/

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
/*static void multiplication(char* var, char* a, char* b) {
    int index_variable = cherche_index_variable(var);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if (index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !\n");
        exit(1);
    }
    
    if (unbounded_int_cmp_unbounded_int(valeur_variable[index_a], valeur_variable[index_b]) == -1)
        valeur_variable[index_variable] = unbounded_int_produit(valeur_variable[index_b], valeur_variable[index_a]);
    else
        valeur_variable[index_variable] = unbounded_int_produit(valeur_variable[index_a], valeur_variable[index_b]);
}*/


static void condition_operation(char op, char var, char* var1, char* var2) {
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
/*static void condition_operation(char op, char* var, char* var1, char* var2) {
    switch (op)
    {
    case '+':
        if (isdigit(var1[0]) && isdigit(var2[0]))
            addition(var, variables[0], variables[1]);
        else if (isdigit(var1[0]) && !isdigit(var2[0]))
            addition(var, variables[0], var2);
        else if (!isdigit(var1[0]) && isdigit(var2[0]))
            addition(var, var1, variables[1]);
        else
            addition(var, var1, var2);
        break;
    case '-':
        if (isdigit(var1[0]) && isdigit(var2[0]))
            soustraction(var, variables[0], variables[1]);
        else if (isdigit(var1[0]) && !isdigit(var2[0]))
            soustraction(var, variables[0], var2);
        else if (!isdigit(var1[0]) && isdigit(var2[0]))
            soustraction(var, var1, variables[1]);
        else
            soustraction(var, var1, var2);
        break;
    case '*':
        if (isdigit(var1[0]) && isdigit(var2[0]))
            multiplication(var, variables[0], variables[1]);
        else if (isdigit(var1[0]) && !isdigit(var2[0]))
            multiplication(var, variables[0], var2);
        else if (!isdigit(var1[0]) && isdigit(var2[0]))
            multiplication(var, var1, variables[1]);
        else
            multiplication(var, var1, var2);
        break;
    default:
        printf("Cette operation n'existe pas !");
        break;
    }
}*/

void interpreteur(char *source, char *dest) {
    FILE *instruc = NULL;
    FILE* destination = NULL;

    if(strcmp(source, "vide") != 0) {
        instruc = fopen(source, "r");
        if(instruc == NULL) {
		    printf("Le fichier n'a pas pu etre ouvert.\n");
            exit(1);
        }
    }
    else
        instruc = stdin;

    if (strcmp(dest, "vide") != 0) {
        destination = fopen(dest, "w+");
        if (destination == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
    }
    else
        destination = stdout;

    char var = 0;
    char op = 0;

    variables[0] = 'z'; //valeur temp 1
    valeur_variable[0] = string2unbounded_int("0");
    variables[1] = 'x'; //valeur temp 2
    valeur_variable[1] = string2unbounded_int("0");
    int i = 2;

    char *commande_ligne = malloc(LINES_LENGTH*sizeof(char));
    assert(commande_ligne != NULL);

    while(fgets(commande_ligne, LINES_LENGTH, instruc) != NULL) {
        char *prt = strstr(commande_ligne, "print");
        if(prt != NULL) {
            var = commande_ligne[strlen(commande_ligne)-2]; //2 ou 3
            print(destination, var);
        }
        else {
            char * var1 = malloc(30*sizeof(char));
            assert(var1 != NULL);
            char * var2 = malloc(30*sizeof(char));
            assert(var2 != NULL);
            if(sscanf(commande_ligne, "%c = %s %c %s", &var, var1, &op, var2) == 4) {
                if(cherche_index_variable(var) == -1) {
                    variables[i] = var;
                    valeur_variable[i] = string2unbounded_int("0");
                    i++;
                }
                
                if(isdigit(var1[0]) || ((var1[0] == '-' || var1[0] == '+') && isdigit(var1[1])))
                    valeur_variable[0] = string2unbounded_int(var1);
                if(isdigit(var2[0]) || ((var2[0] == '-' || var2[0] == '+') && isdigit(var2[1])))
                    valeur_variable[1] = string2unbounded_int(var2);

                if(var1[0] == '-' || var1[0] == '+')
                    condition_operation(op, var, var1 + 1, var2);
                else if(var2[0] == '-' || var2[0] == '+')
                    condition_operation(op, var, var1, var2 + 1);
                else if((var1[0] == '-' || var1[0] == '+') && (var2[0] == '-' || var2[0] == '+'))
                    condition_operation(op, var, var1 + 1, var2 + 1);
                else
                    condition_operation(op, var, var1, var2);
            }
            else {
                char *ent = malloc(30*sizeof(char));
                assert(ent != NULL);
                if(sscanf(commande_ligne, "%c = %s", &var, ent) == 2) {
                    int index = cherche_index_variable(var);
                    if(index == -1) {
                        variables[i] = var;
                        valeur_variable[i] = string2unbounded_int(ent);
                        i++;
                    }
                    else {
                        valeur_variable[index] = string2unbounded_int(ent);
                    }
                }
            }
        }
    }
    
    fclose(instruc);
    fclose(destination);
}

/*void interpreteur(char* source, char* dest) {
    FILE* instruc = NULL;
    FILE* destination = NULL;

    if (strcmp(source, "vide") != 0) {
        instruc = fopen(source, "r");
        if (instruc == NULL) {
            printf("Le fichier n'a pas pu etre ouvert.\n");
            exit(1);
        }
    }
    else
        instruc = stdin;

    if (strcmp(dest, "vide") != 0) {
        destination = fopen(dest, "w+");
        if (destination == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
    }
    else
        destination = stdout;

    char op = 0;
    char* var = malloc(10*sizeof(char));
    assert(var != NULL);

    variables[0] = "x";
    valeur_variable[0] = string2unbounded_int("0");
    variables[1] = "z";
    valeur_variable[1] = string2unbounded_int("0");
    int i = 2;

    char* commande_ligne = malloc(LINES_LENGTH * sizeof(char));
    assert(commande_ligne != NULL);

    while (fgets(commande_ligne, LINES_LENGTH, instruc) != NULL) {
        char* prt = strstr(commande_ligne, "print");
        if (prt != NULL) {
            sscanf(commande_ligne, "print %s", var);
            print(destination, var);
        }
        else {
            char* var1 = malloc(30 * sizeof(char));
            assert(var1 != NULL);
            char* var2 = malloc(30 * sizeof(char));
            assert(var2 != NULL);
            if (sscanf(commande_ligne, "%s = %s %c %s", var, var1, &op, var2) == 4) {
                if (cherche_index_variable(var) == -1) {
                    variables[i] = var;
                    valeur_variable[i] = string2unbounded_int("0");
                    i++;
                }

                if (isdigit(var1[0]) || ((var1[0] == '-' || var1[0] == '+') && isdigit(var1[1])))
                    valeur_variable[0] = string2unbounded_int(var1);
                if (isdigit(var2[0]) || ((var2[0] == '-' || var2[0] == '+') && isdigit(var2[1])))
                    valeur_variable[1] = string2unbounded_int(var2);

                if (var1[0] == '-' || var1[0] == '+')
                    condition_operation(op, var, var1 + 1, var2);
                else if (var2[0] == '-' || var2[0] == '+')
                    condition_operation(op, var, var1, var2 + 1);
                else if ((var1[0] == '-' || var1[0] == '+') && (var2[0] == '-' || var2[0] == '+'))
                    condition_operation(op, var, var1 + 1, var2 + 1);
                else
                    condition_operation(op, var, var1, var2);
            }
            else {
                char* ent = malloc(30 * sizeof(char));
                assert(ent != NULL);
                if (sscanf(commande_ligne, "%s = %s", var, ent) == 2) {
                    int index = cherche_index_variable(var);
                    if (index == -1) {
                        variables[i] = var;
                        valeur_variable[i] = string2unbounded_int(ent);
                        i++;
                    }
                    else {
                        valeur_variable[index] = string2unbounded_int(ent);
                    }
                }
            }
        }
    }

    fclose(instruc);
    fclose(destination);
}*/

int main(int argc, char *argv[]) {
    char* source = malloc(10 * sizeof(char));
    assert(source != NULL);
    source = "vide";
    char *dest = malloc(10*sizeof(char));
    assert(dest != NULL);
    dest = "vide";

    if(argv[1] != NULL) {
        if(strcmp(argv[1], "-i") == 0)
            source = argv[2];
    
        if(strcmp(source, "vide") == 0) {
            if(strcmp(argv[1], "-o") == 0)
                dest = argv[2];
        }
        else {
            if(argv[3] != NULL) {
                if(strcmp(argv[3], "-o") == 0)
                    dest = argv[4];
            }
        }
    }

    interpreteur(source, dest);

    //TABLEAU BIDIMENSIONNEL DE CHAINE DE CARACTERES
    /*char* variable[10] = {""};
    variable[0] = "Alexandre";
    variable[1] = "Luc";
    variable[2] = "Valerie";

    for (int i = 0; i < 10 && variable[i] != NULL; i++) {
        printf("%s\n", variable[i]);
    }
    printf("\n");
    */

    return EXIT_SUCCESS;
}
