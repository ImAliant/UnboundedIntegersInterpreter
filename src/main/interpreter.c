#include "unbounded_int.h"

#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_INPUT_SIZE 1024
#define DEFAULT_VARIABLES_SIZE 10
#define MAX_VARIABLE_NAME_SIZE 64

#define ATOM "%s"
#define BIN_OP "%s %c %[^\n]"
#define PRINT "print %s"
#define EXIT "exit"

#define EQUALS '='
#define SUM '+'
#define DIFFERENCE '-'
#define PRODUCT '*'
#define QUOTIENT '/'
#define MODULO '%'
#define POWER '^'
#define OP_ERROR -1

typedef struct {
    char *var_a;
    char *var_b;
    char operation;
} operation;

typedef struct {
    char *name;
    unbounded_int value;
} variables;

static variables *vars;
static size_t capacity;
static size_t vars_size;

static void scan_input(char *input);
static int process_print(char *var_name);
static int process_expression(const char *var_name, char *expr);
static int process_atomic_expr(size_t pos_var, char *atom);
static int process_operation(size_t pos_var, operation op);
static size_t find_variable_position(const char *var_name);
static unbounded_int find_variable_value(const char *var_name);
static void create_variable(const char *var_name);
static void create_variable_at_pos(const char *var_name, size_t pos);
static int is_operation(char op, int expected);
static int is_expr_atomic(char *expr);
static int is_expr_operation(const char *expr);
static void variables_init(size_t size);
static operation create_operation(const char *expr);
static void free_operation(operation op);

void init_readline() {
    rl_initialize();

    using_history();
}

int main(int argc, char **argv) {
    variables_init(DEFAULT_VARIABLES_SIZE);
    init_readline();

    char input[MAX_INPUT_SIZE];

    while (1) {
        sprintf(input, "%s", readline("> "));
        if (strlen(input) == 0) {
            continue;
        }
        add_history(input);

        scan_input(input);
    }

    free(vars);

    return EXIT_SUCCESS;
}

static void scan_input(char *input) {
    if (strcmp(input, EXIT) == 0) {
        exit(EXIT_SUCCESS);
    }

    char var_name[MAX_VARIABLE_NAME_SIZE];
    char op;
    char expr[MAX_INPUT_SIZE];

    if (sscanf(input, PRINT, input) == 1) {
        if(!process_print(input)) {
            fprintf(stderr, "Erreur: \"%s\" variable non trouvée\n", input);
        }
    } else if (sscanf(input, BIN_OP, var_name, &op, expr) == 3) {
        if (!is_operation(op, EQUALS)) {
            fprintf(stderr, "Erreur: opération non reconnue\n");
            return;
        }

        if (!process_expression(var_name, expr)) {
            fprintf(stderr, "Erreur: expression non reconnue\n");
        }
    } else {
        fprintf(stderr, "Erreur: opération non reconnue\n");
    }
}

static int process_print(char *var_name) {
    unbounded_int res = find_variable_value(var_name);

    if (res.signe == ERROR) return 0;
    
    char *res_str = unbounded_int2string(res);
    printf("%s = %s\n", var_name, res_str);
    free(res_str);

    return 1;
}

static int process_expression(const char *var_name, char *expr) {
    if (find_variable_position(var_name) == -1) {
        create_variable(var_name);
    }

    size_t pos = find_variable_position(var_name);

    if (is_expr_operation(expr)) {
        operation op = create_operation(expr);
        if (op.operation == OP_ERROR) {
            free_operation(op);
            return 0;
        }

        if (!process_operation(pos, op)) {
            free_operation(op);
            return 0;
        }

        free_operation(op);
    } else if (is_expr_atomic(expr)) {
        if (!process_atomic_expr(pos, expr)) {
            return 0;
        }
    } else {
        return 0;
    }

    return 1;
}

static void create_variable(const char *var_name) {
    if (find_variable_position(var_name) != -1) {
        fprintf(stderr, "Erreur: la variable \"%s\" existe déjà\n", var_name);
        return;
    }

    size_t len = vars_size;

    if (len + 1 > capacity) {
        capacity *= 2;
        variables *new_vars = realloc(vars, capacity * sizeof(variables));
        if (new_vars == NULL) {
            fprintf(stderr, "Erreur: problème d'allocation mémoire (create_variable)\n");
            free(vars);
            exit(EXIT_FAILURE);
        }
        vars = new_vars;
    }

    if (len == 0) {
        create_variable_at_pos(var_name, 0);
        return;
    }

    for (size_t i = 0; i < len+1; i++) {
        if (vars[i].name == NULL) {
            create_variable_at_pos(var_name, i);
            return;
        }
    }
}

static void create_variable_at_pos(const char *var_name, size_t pos) {
    vars[pos].name = malloc(strlen(var_name) + 1);
    if (vars[pos].name == NULL) {
        fprintf(stderr, "Erreur: problème d'allocation mémoire (create_variable_at_pos)\n");
        exit(EXIT_FAILURE);
    }

    strcpy(vars[pos].name, var_name);
    vars[pos].value = init_unbounded_int();
    vars_size++;
}

static int process_atomic_expr(size_t pos_var, char *atom) {
    if (!is_expr_atomic(atom)) {
        return 0;
    }

    if (check_integer(atom)) {
        vars[pos_var].value = string2unbounded_int(atom);
    } else {
        size_t pos_atom = find_variable_position(atom);
        if (pos_atom == -1) {
            fprintf(stderr, "Erreur: \"%s\" variable non trouvée\n", atom);
            return 0;
        }

        vars[pos_var].value = vars[pos_atom].value;
    }

    return 1;
}

static int process_operation(size_t pos_var, operation op) {
    unbounded_int a_val = check_integer(op.var_a) ? string2unbounded_int(op.var_a) : find_variable_value(op.var_a);
    unbounded_int b_val = check_integer(op.var_b) ? string2unbounded_int(op.var_b) : find_variable_value(op.var_b);

    unbounded_int res;

    switch (op.operation) {
        case SUM:
            res = unbounded_int_somme(a_val, b_val);
            break;
        case DIFFERENCE:
            res = unbounded_int_difference(a_val, b_val);
            break;
        case PRODUCT:
            res = unbounded_int_produit(a_val, b_val);
            break;
        case QUOTIENT:
            res = unbounded_int_quotient(a_val, b_val);
            break;
        case MODULO:
            res = unbounded_int_modulo(a_val, b_val);
            break;
        case POWER:
            res = unbounded_int_puissance(a_val, b_val);
            break;
        default:
            fprintf(stderr, "Erreur: opération non reconnue\n");
            return 0;
    }

    vars[pos_var].value = res;

    return 1;
}

static size_t find_variable_position(const char *var_name) {
    for (size_t i = 0; i < vars_size; i++) {
        if (vars[i].name != NULL && strcmp(vars[i].name, var_name) == 0) {
            return i;
        }
    }

    return -1;
}

static unbounded_int find_variable_value(const char *var_name) {
    size_t pos = find_variable_position(var_name);

    if (pos == -1) {
        return init_unbounded_int();
    }

    return vars[pos].value;
}

static operation create_operation(const char *expr) {
    operation op;

    if (!is_expr_operation(expr)) {
        fprintf(stderr, "Erreur: expression non reconnue (create_operation)\n");
        op.operation = OP_ERROR;
        return op;
    }

    char a[MAX_INPUT_SIZE];
    char b[MAX_INPUT_SIZE];
    char operation;

    sscanf(expr, BIN_OP, a, &operation, b);

    op.var_a = malloc(strlen(a) + 1);
    if (op.var_a == NULL) {
        fprintf(stderr, "Erreur: problème d'allocation mémoire (create_operation)\n");
        exit(EXIT_FAILURE);
    }

    strcpy(op.var_a, a);

    op.var_b = malloc(strlen(b) + 1);
    if (op.var_b == NULL) {
        fprintf(stderr, "Erreur: problème d'allocation mémoire (create_operation)\n");
        exit(EXIT_FAILURE);
    }

    strcpy(op.var_b, b);

    op.operation = operation;

    return op;
}

static void variables_init(size_t size) {
    vars = malloc(size * sizeof(variables));
    if (vars == NULL) {
        fprintf(stderr, "Erreur: problème d'allocation mémoire (variables_init)\n");
        exit(EXIT_FAILURE);
    }

    capacity = size;
    vars_size = 0;
}

static int is_operation(char op, int expected) {
    return op == expected;
}

static int is_expr_atomic(char *expr) {
    return sscanf(expr, ATOM, expr) == 1;
}

static int is_expr_operation(const char *expr) {
    char a[MAX_INPUT_SIZE];
    char b[MAX_INPUT_SIZE];
    char op;

    return sscanf(expr, BIN_OP, a, &op, b) == 3;
}

static void free_operation(operation op) {
    if (op.var_a != NULL) {
        free(op.var_a);
    }
    if (op.var_b != NULL) {
        free(op.var_b);
    }
}