#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "unbounded_int.h"

//Caracteres lues dans le fichier par le programme. 
#define LINES_LENGTH 1024 

//Longueur maximale des noms des variables par défaut.
#define VAR_NAME_LENGTH 10 

//Nombre de variable maximum par défaut.
#define NB_VARIABLES 10 

//Longueur maximale des noms des fichiers src et dest.
#define MAX_LENGTH_FILE_NAME 20 

//Correspond a la une variable ou a une valeur de variable.
#define ATOM "%s"

//Operation sur deux variables, une variable et un entier ou deux entiers.
#define BIN_OP "%s %c %[^\n]%s" 

//Recupere le nom de la variable a affiche.
#define PRINT "print %s" 

// Index des tableaux variables et valeur_variable a partir du quel les variables ne sont pas des variables temporaires.
int i = 2;

//Longueur par défaut des tableaux.
int length = NB_VARIABLES;

// Tableau de chaine de caracteres qui sauvegarde les variables ecrite dans le fichier source.
char** variables;

// Tableau de unbounded_int qui sauvegarde les valeurs de chaque variables donnes dans le fichier source.
unbounded_int *valeur_variable;

// Cherche l'indice de la variable dans le tableau de chaine de caractere donne en argument.
static int cherche_variable(char* var) {
    for (int i = 0; i < length && variables[i] != NULL; i++) {
        if (strcmp(variables[i], var) == 0) {
            return i;
        }
    }
    return -1;
}

// Print de l'interpreteur : affiche le nom de la variable et sa valeur.
static void print_f_out(FILE* f, char* var) {
    int index = cherche_variable(var);
    if (index == -1) {
        printf("print_f_out | La variable %s n'existe pas !\n", var);
        exit(EXIT_FAILURE);
    }
    if (!f) {
        perror("print_f_out | Le fichier n'est pas ouvert !\n");
        exit(EXIT_FAILURE);
    }
    char* s = unbounded_int2string(valeur_variable[index]);
    fprintf(f, "%s = %s\n", var, s);
}

// Calcule la nouvelle valeur de var en faisant la somme des deux variables donnes en arguments.
static void addition(char* var, char* a, char* b) {
    int index_var = cherche_variable(var);
    int index_a = cherche_variable(a);
    int index_b = cherche_variable(b);

    if(index_var == -1)
        printf("addition | La variable %s n'existe pas !\n", var);
    if(index_a == -1)
        printf("addition | La variable %s n'existe pas !\n", a);
    if(index_b == -1)
        printf("addition | La variable %s n'existe pas !\n", b);
    if (index_var == -1 || index_a == -1 || index_b == -1) {
        exit(EXIT_FAILURE);
    }

    valeur_variable[index_var] = unbounded_int_somme(valeur_variable[index_a], valeur_variable[index_b]);
}
// Calcule la nouvelle valeur de var en faisant la soustraction des deux variables donnes en arguments.
static void soustraction(char* var, char* a, char* b) {
    int index_var = cherche_variable(var);
    int index_a = cherche_variable(a);
    int index_b = cherche_variable(b);

    if(index_var == -1)
        printf("soustraction | La variable %s n'existe pas !\n", var);
    if(index_a == -1)
        printf("soustraction | La variable %s n'existe pas !\n", a);
    if(index_b == -1)
        printf("soustraction | La variable %s n'existe pas !\n", b);
    if (index_var == -1 || index_a == -1 || index_b == -1) {
        exit(EXIT_FAILURE);
    }

    valeur_variable[index_var] = unbounded_int_difference(valeur_variable[index_a], valeur_variable[index_b]);
}

// Calcule la nouvelle valeur de var en faisant le produit des deux variables donnes en arguments.
static void multiplication(char* var, char* a, char* b) {
    int index_var = cherche_variable(var);
    int index_a = cherche_variable(a);
    int index_b = cherche_variable(b);

    if(index_var == -1)
        printf("multiplication | La variable %s n'existe pas !\n", var);
    if(index_a == -1)
        printf("multiplication | La variable %s n'existe pas !\n", a);
    if(index_b == -1)
        printf("multiplication | La variable %s n'existe pas !\n", b);
    if (index_var == -1 || index_a == -1 || index_b == -1) {
        exit(EXIT_FAILURE);
    }
    
    if (unbounded_int_cmp_unbounded_int(valeur_variable[index_a], valeur_variable[index_b]) == -1)
        valeur_variable[index_var] = unbounded_int_produit(valeur_variable[index_b], valeur_variable[index_a]);
    else
        valeur_variable[index_var] = unbounded_int_produit(valeur_variable[index_a], valeur_variable[index_b]);
}

// Calcule la nouvelle valeur de var egale au quotient de la division des deux variables donnes en arguments.
static void quotient(char* var, char* a, char* b) {
    int index_var = cherche_variable(var);
    int index_a = cherche_variable(a);
    int index_b = cherche_variable(b);

    if(index_var == -1)
        printf("quotient | La variable %s n'existe pas !\n", var);
    if(index_a == -1)
        printf("quotient | La variable %s n'existe pas !\n", a);
    if(index_b == -1)
        printf("quotient | La variable %s n'existe pas !\n", b);
    if (index_var == -1 || index_a == -1 || index_b == -1) {
        exit(EXIT_FAILURE);
    }
    
    valeur_variable[index_var] = unbounded_int_quotient(valeur_variable[index_a], valeur_variable[index_b]);
}

// Calcule la nouvelle valeur de var egale au reste de la division des deux variables donnes en arguments.
static void modulo(char* var, char* a, char* b) {
    int index_var = cherche_variable(var);
    int index_a = cherche_variable(a);
    int index_b = cherche_variable(b);

    if(index_var == -1)
        printf("modulo | La variable %s n'existe pas !\n", var);
    if(index_a == -1)
        printf("modulo | La variable %s n'existe pas !\n", a);
    if(index_b == -1)
        printf("modulo | La variable %s n'existe pas !\n", b);
    if (index_var == -1 || index_a == -1 || index_b == -1) {
        exit(EXIT_FAILURE);
    }

    valeur_variable[index_var] = unbounded_int_modulo(valeur_variable[index_a], valeur_variable[index_b]);
}

// Calcule la nouvelle valeur de var egale a la variable a puissance b.
static void puissance(char* var, char* a, char* b) {
    int index_var = cherche_variable(var);
    int index_a = cherche_variable(a);
    int index_b = cherche_variable(b);

    if(index_var == -1)
        printf("puissance | La variable %s n'existe pas !\n", var);
    if(index_a == -1)
        printf("puissance | La variable %s n'existe pas !\n", a);
    if(index_b == -1)
        printf("puissance | La variable %s n'existe pas !\n", b);
    if (index_var == -1 || index_a == -1 || index_b == -1) {
        exit(EXIT_FAILURE);
    }
    
    valeur_variable[index_var] = unbounded_int_puissance(valeur_variable[index_a], valeur_variable[index_b]);
}

// Identifie quel type d'operation doit etre effectue.
static void cond_ope(char op, char* var, char* var1, char* var2) {
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
    case '/':
        if (isdigit(var1[0]) && isdigit(var2[0]))
            quotient(var, variables[0], variables[1]);
        else if (isdigit(var1[0]) && !isdigit(var2[0]))
            quotient(var, variables[0], var2);
        else if (!isdigit(var1[0]) && isdigit(var2[0]))
            quotient(var, var1, variables[1]);
        else
            quotient(var, var1, var2);
        break;
    case '%':
        if (isdigit(var1[0]) && isdigit(var2[0]))
            modulo(var, variables[0], variables[1]);
        else if (isdigit(var1[0]) && !isdigit(var2[0]))
            modulo(var, variables[0], var2);
        else if (!isdigit(var1[0]) && isdigit(var2[0]))
            modulo(var, var1, variables[1]);
        else
            modulo(var, var1, var2);
        break;
    case '^':
        if (isdigit(var1[0]) && isdigit(var2[0]))
            puissance(var, variables[0], variables[1]);
        else if (isdigit(var1[0]) && !isdigit(var2[0]))
            puissance(var, variables[0], var2);
        else if (!isdigit(var1[0]) && isdigit(var2[0]))
            puissance(var, var1, variables[1]);
        else
            puissance(var, var1, var2);
        break;
    default:
        perror("cond_ope | L'operation n'existe pas !\n");
        exit(EXIT_FAILURE);
        break;
    }
}

static void realloc_variables(int length) {
    char** t1 = realloc(variables, 2 * length * sizeof(char*));
    if(t1 == NULL) {
        perror("realloc_variables | Réallocation tableau variables : ECHOUE\n");
        exit(EXIT_FAILURE);
    }
    variables = t1;
    unbounded_int *t2 = realloc(valeur_variable, 2 * length * sizeof(unbounded_int));
    if(t2 == NULL) {
        perror("realloc_variables | Réallocation tableau valeur variables : ECHOUE\n");
        exit(EXIT_FAILURE);
    }
    valeur_variable = t2;
    for(int i = length; i<length*2; i++) {
        variables[i] = malloc(VAR_NAME_LENGTH * sizeof(char) + 1);
        if(variables[i] == NULL) {
            printf("realloc_variables | Allocation de la case %d du tableau variables: ECHOUE\n", i);
            exit(EXIT_FAILURE);
        }
    }
}

// Appelle le print de l'interpreteur.
static void process_print(FILE* f, char* var) {
    print_f_out(f, var);
}

// Attribue a la variable var la valeur val.
static void process_atom(char* var, char* val) {
    int index = cherche_variable(var);

    if (index == -1) {
        if(i+1 > length) {
            realloc_variables(length);
            length *= 2;
        }
        if(strlen(var) > VAR_NAME_LENGTH) {
            char *t = realloc(variables[i], strlen(var) * sizeof(char) + 1);
            if(variables[i] == NULL) {
                printf("process_atom | Réallocation de la case %d du tableau variables: ECHOUE\n", i);
                exit(EXIT_FAILURE);
            }
            variables[i] = t;
        }
        strcpy(variables[i], var);

        valeur_variable[i] = string2unbounded_int(val);
        i++;
    }
    else
        valeur_variable[index] = string2unbounded_int(val);
}

// Verifie si l'expression donne en argument est une attribution de valeur ou un calcule.
static void process_expression(char* var, char* exp) {
    char* lhs = malloc(128 * sizeof(char) + 1);
    if(lhs == NULL) {
        perror("process_expression | Allocation lhs : ECHOUE\n");
        exit(EXIT_FAILURE);
    }
    char* rhs = malloc(128 * sizeof(char) + 1);
    if(rhs == NULL) {
        perror("process_expression | Allocation rhs : ECHOUE\n");
        exit(EXIT_FAILURE);
    }

    char* nom_entier = malloc(128 * sizeof(char) + 1);
    if(nom_entier == NULL) {
        perror("process_expression | Allocation nom_entier : ECHOUE\n");
        exit(EXIT_FAILURE);
    }
    char op = '0';

    if (sscanf(exp, BIN_OP, lhs, &op, rhs) == 3) {
        if (cherche_variable(var) == -1) {
            if(i+1 > length) {
                realloc_variables(length);
                length *= 2;
            }
            if(strlen(var) > VAR_NAME_LENGTH) {
                char *t = realloc(variables[i], strlen(var) * sizeof(char) + 1);
                if(t == NULL) {
                    printf("process_expression | Réallocation de la case %d du tableau variables: ECHOUE\n", i);
                    exit(EXIT_FAILURE);
                }
                variables[i] = t;
            }
            strcpy(variables[i], var);

            valeur_variable[i] = string2unbounded_int("0");
            i++;
        }

        if (isdigit(lhs[0]) || ((lhs[0] == '-' || lhs[0] == '+') && isdigit(lhs[1])))
            valeur_variable[0] = string2unbounded_int(lhs);
        if (isdigit(rhs[0]) || ((rhs[0] == '-' || rhs[0] == '+') && isdigit(rhs[1])))
            valeur_variable[1] = string2unbounded_int(rhs);

        if ((lhs[0] == '-' || lhs[0] == '+') && (rhs[0] == '-' || rhs[0] == '+'))
            cond_ope(op, var, lhs + 1, rhs + 1);
        else if (lhs[0] == '-' || lhs[0] == '+')
            cond_ope(op, var, lhs + 1, rhs);
        else if (rhs[0] == '-' || rhs[0] == '+')
            cond_ope(op, var, lhs, rhs + 1);
        else
            cond_ope(op, var, lhs, rhs);
    }
    else if (sscanf(exp, ATOM, nom_entier) == 1) {
        process_atom(var, nom_entier);
    }
    else {
        perror("process_expression | ERROR\n");
        exit(EXIT_FAILURE);
    }
}

// Lit les instructions presente dans le fichier source.
// Ecrit les valeurs des variables demandes dans le fichier dest.
void interpreteur(char* source, char* dest) {
    FILE* fic_in = NULL;
    FILE* fic_out = NULL;

    if (strcmp(source, "vide") != 0) {
        fic_in = fopen(source, "r");
        if (fic_in == NULL) {
            perror("interpreteur | Le fichier source n'a pas pu etre ouvert.\n");
            exit(EXIT_FAILURE);
        }
    }
    else
        fic_in = stdin;

    if (strcmp(dest, "vide") != 0) {
        fic_out = fopen(dest, "w+");
        if (fic_out == NULL) {
            perror("interpreteur | Le fichier dest n'a pas pu etre ouvert.\n");
            exit(EXIT_FAILURE);
        }
    }
    else
        fic_out = stdout;

    variables = malloc(NB_VARIABLES * sizeof(char *));
    if(variables == NULL) {
        perror("interpreteur | Allocation du tableau variables : ECHOUE\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i<NB_VARIABLES; i++) {
        variables[i] = malloc(VAR_NAME_LENGTH * sizeof(char) + 1);
        if(variables[i] == NULL) {
            printf("interpreteur | Allocation de la case %d du tableau variables : ECHOUE\n", i);
            exit(EXIT_FAILURE);
        }
    }

    valeur_variable = malloc(NB_VARIABLES * sizeof(unbounded_int));
    if(valeur_variable == NULL) {
        perror("interpreteur | Allocation du tableau valeur_variable : ECHOUE\n");
        exit(EXIT_FAILURE);
    }
    
    strcpy(variables[0], "tmp1");
    valeur_variable[0] = string2unbounded_int("0");

    strcpy(variables[1], "tmp2");
    valeur_variable[1] = string2unbounded_int("0");

    char op = '0';
    char* var = malloc(256 * sizeof(char) + 1);
    if(var == NULL) {
        perror("interpreteur | Allocation var : ECHOUE\n");
        exit(EXIT_FAILURE);
    }

    char buffer[LINES_LENGTH];

    while (fgets(buffer, LINES_LENGTH, fic_in)) {
        char* lhs = malloc(256 * sizeof(char) + 1);
        if(lhs == NULL) {
            perror("interpreteur | Allocation lhs : ECHOUE\n");
            exit(EXIT_FAILURE);
        }
        char* rhs = malloc(256 * sizeof(char) + 1);
        if(rhs == NULL) {
            perror("interpreteur | Allocation rhs : ECHOUE\n");
            exit(EXIT_FAILURE);
        }

        if (sscanf(buffer, PRINT, var) == 1) {
            process_print(fic_out, var);
        }
        else if (sscanf(buffer, BIN_OP, lhs, &op, rhs) == 3) {
            if (op == '=')
                process_expression(lhs, rhs);
            else {
                perror("interpreteur | ERROR : L'opération n'existe pas !\n");
                exit(EXIT_FAILURE);
            }
        }
        else if (buffer[0] == '\n')
            continue;
        else {
            printf("interpreteur | ERROR : Le format ne correspond pas !\n");
            exit(EXIT_FAILURE);
        }
    }

    fclose(fic_in);
    fclose(fic_out);
}

// Main du fichier calc_unbounded_int.c
int main(int argc, char *argv[]) {
    char* source = malloc(MAX_LENGTH_FILE_NAME * sizeof(char));
    if(source == NULL) {
        perror("main | Allocation nom fichier source: ECHOUE\n");
        exit(EXIT_FAILURE);
    }
    source = "vide";
    char *dest = malloc(MAX_LENGTH_FILE_NAME * sizeof(char));
    if(dest == NULL) {
        perror("main | Allocation nom fichier dest: ECHOUE\n");
        exit(EXIT_FAILURE);
    }
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

    for(int i=0; i<length; i++) {
        free(variables[i]);
    }
    free(variables);

    return EXIT_SUCCESS;
}
