#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

#include "unbounded_int.h"

#define LINES_LENGTH 1024
#define VARIABLES 50
#define ATOM "%s"
#define BIN_OP "%s %c %s"
#define PRINT "print %s"

int i = 2;
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

static void print_f_out(FILE* d, char c) {
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

static void division_quotient(char variable, char a, char b) {
    int index_variable = cherche_index_variable(variable);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if (index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !\n");
        exit(1);
    }
    else {
        valeur_variable[index_variable] = unbounded_int_quotient(valeur_variable[index_a], valeur_variable[index_b]);
    }
}

static void division_modulo(char variable, char a, char b) {
    int index_variable = cherche_index_variable(variable);
    int index_a = cherche_index_variable(a);
    int index_b = cherche_index_variable(b);

    if (index_variable == -1 || index_a == -1 || index_b == -1) {
        printf("Une des variables n'existe pas !\n");
        exit(1);
    }
    else {
        valeur_variable[index_variable] = unbounded_int_modulo(valeur_variable[index_a], valeur_variable[index_b]);
    }
}

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
    case '/':
        if (isdigit(var1[0]) && isdigit(var2[0]))
            division_quotient(var, variables[0], variables[1]);
        else if (isdigit(var1[0]) && !isdigit(var2[0]))
            division_quotient(var, variables[0], var2[0]);
        else if (!isdigit(var1[0]) && isdigit(var2[0]))
            division_quotient(var, var1[0], variables[1]);
        else
            division_quotient(var, var1[0], var2[0]);
        break;
    case '%':
        if (isdigit(var1[0]) && isdigit(var2[0]))
            division_modulo(var, variables[0], variables[1]);
        else if (isdigit(var1[0]) && !isdigit(var2[0]))
            division_modulo(var, variables[0], var2[0]);
        else if (!isdigit(var1[0]) && isdigit(var2[0]))
            division_modulo(var, var1[0], variables[1]);
        else
            division_modulo(var, var1[0], var2[0]);
        break;
    default:
        printf("Cette operation n'existe pas !");
        break;
    }
}

static void process_print(FILE* f, char var) {
    print_f_out(f, var);
}

static void process_atom(char v, char *var) {
    int index = cherche_index_variable(v);

    if (index == -1) {
        variables[i] = v;
        valeur_variable[i] = string2unbounded_int(var);
        i++;
    }
    else {
        valeur_variable[index] = string2unbounded_int(var);
    }
}

static void process_expression(char v, char* exp) {
    char* lhs = malloc(30 * sizeof(char));
    assert(lhs != NULL);
    char* rhs = malloc(30 * sizeof(char));
    assert(rhs != NULL);

    char* a = malloc(30 * sizeof(char));
    assert(a != NULL);
    char op = '0';

    if (sscanf(exp, BIN_OP, lhs, &op, rhs) == 3) {
        if (cherche_index_variable(v) == -1) {
            variables[i] = v;
            valeur_variable[i] = string2unbounded_int("0");
            i++;
        }

        if (isdigit(lhs[0]) || ((lhs[0] == '-' || lhs[0] == '+') && isdigit(lhs[1])))
            valeur_variable[0] = string2unbounded_int(lhs);
        if (isdigit(rhs[0]) || ((rhs[0] == '-' || rhs[0] == '+') && isdigit(rhs[1])))
            valeur_variable[1] = string2unbounded_int(rhs);

        if (lhs[0] == '-' || lhs[0] == '+')
            condition_operation(op, v, lhs + 1, rhs);
        else if (lhs[0] == '-' || rhs[0] == '+')
            condition_operation(op, v, lhs, rhs + 1);
        else if ((lhs[0] == '-' || lhs[0] == '+') && (rhs[0] == '-' || rhs[0] == '+'))
            condition_operation(op, v, lhs + 1, rhs + 1);
        else
            condition_operation(op, v, lhs, rhs);
    }
    else if (sscanf(exp, ATOM, a) == 1) {
        process_atom(v, a);
    }
    else {
        printf("ERROR : p_e");
        exit(EXIT_FAILURE);
    }
}

void interpreteur(char *source, char *dest) {
    FILE *fic_in = NULL;
    FILE* fic_out = NULL;

    if(strcmp(source, "vide") != 0) {
        fic_in = fopen(source, "r");
        if(fic_in == NULL) {
		    printf("Le fichier n'a pas pu etre ouvert.\n");
            exit(EXIT_FAILURE);
        }
    }
    else
        fic_in = stdin;

    if (strcmp(dest, "vide") != 0) {
        fic_out = fopen(dest, "w+");
        if (fic_out == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
    }
    else
        fic_out = stdout;

    /*char var = 0;
    char op = 0;*/

    variables[0] = 'z'; //valeur temp 1
    valeur_variable[0] = string2unbounded_int("0");
    variables[1] = 'x'; //valeur temp 2
    valeur_variable[1] = string2unbounded_int("0");

    //SOLUTION PROF TD
    char op = '0';
    char var[128];

    char buffer[LINES_LENGTH];

    while (fgets(buffer, LINES_LENGTH, fic_in)) {
        char* lhs = malloc(30 * sizeof(char));
        assert(lhs != NULL);
        char* rhs = malloc(30 * sizeof(char));
        assert(rhs != NULL);
        
        if (sscanf(buffer, BIN_OP, lhs, &op, rhs) == 3) {
            if (op == '=')
                process_expression(lhs[0], rhs);
            else {
                printf("ERROR : 1 if");
                exit(EXIT_FAILURE);
            }
        }
        else if (sscanf(buffer, PRINT, var) == 1) {
            process_print(fic_out, var);
        }
        else {
            printf("ERROR : else");
            exit(EXIT_FAILURE);
        }
    }

    /*char* commande_ligne = malloc(LINES_LENGTH * sizeof(char));
    assert(commande_ligne != NULL);*/

    /*while(fgets(commande_ligne, LINES_LENGTH, fic_in) != NULL) {
        char* prt = strstr(commande_ligne, "print");
        if(prt != NULL) {
            var = commande_ligne[strlen(commande_ligne)-3]; //2 ou 3
            print(fic_out, var);
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
    }*/
    
    fclose(fic_in);
    fclose(fic_out);
}

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
    
    interpreteur("source.txt", dest);

    return EXIT_SUCCESS;
}
