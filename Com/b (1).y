%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern int yylex();
extern FILE *yyin;
int yyparse();

struct Variable {
    char identifier[3];
    int value;
};

struct Variable listaIdentificadores[100];

int numIdentificadores = 0;

void agregarIdentificador(char *id, int val) {
    if (numIdentificadores < 100) {
        strcpy(listaIdentificadores[numIdentificadores].identifier, id);
        listaIdentificadores[numIdentificadores].value = val;
        numIdentificadores++;
    } else {
        fprintf(stderr, "Error: Se ha alcanzado el límite de identificadores.\n");
        exit(EXIT_FAILURE);
    }
}

int obtenerValorIdentificador(char *id) {
    for (int i = 0; i < numIdentificadores; i++) {
        if (strcmp(listaIdentificadores[i].identifier, id) == 0) {
            return listaIdentificadores[i].value;
        }
    }

    fprintf(stderr, "Error: Identificador '%s' no encontrado.\n", id);
    exit(EXIT_FAILURE);
}
void yyerror(const char *s, ...);
%}

%token INICIO FIN LEER ESCRIBIR SI ENTONCES IDENTIFICADOR ENTERO IGUAL SUMA RESTA POR DIVIDIDO MENOR MAYOR IGUAL_COMP PAR_DER PAR_IZQ id  cost



%type <entero> ENTERO
%type <carac> PAR_IZQ
%type <carac> PAR_DER
%type <string_val> IDENTIFICADOR
%type <entero> id cost


%token <string_val> texto

%union
{
	char carac;
	int entero;
    char* string_val;
}

%%
programa: INICIO inst FIN
        ;

inst: inst inst
        |inst_leer
        |inst_escribir
        |inst_si
        |inst_asig
        ;

inst_leer: LEER PAR_IZQ IDENTIFICADOR PAR_DER {
    char id[20]; 
    scanf("%d", &listaIdentificadores[numIdentificadores].value);
    strcpy(id, $3); 
    agregarIdentificador(id, listaIdentificadores[numIdentificadores].value);
}
;
// imprimir, enviar a bastain
inst_escribir: ESCRIBIR PAR_IZQ texto PAR_DER {
    printf("%s", $3); 
}
| ESCRIBIR PAR_IZQ IDENTIFICADOR PAR_DER {
    printf("%d", obtenerValorIdentificador($3));
};

inst_si: SI cond ENTONCES inst

        ;

inst_asig: id IGUAL exp 
        ;

exp:    cost
        |id
        |exp SUMA exp
        |exp RESTA exp
        |exp POR exp
        |exp DIVIDIDO exp
        ;

cond:   exp MENOR exp
        |exp MAYOR exp
        |exp IGUAL_COMP exp
        ;
%%

int main() {
	yyin = stdin;
    printf("Bienvenido al traductor AZ2023\n");
    printf("Para iniciar el programa debe escribir la palabra 'INICIO' \n");

    yyparse();
    return 0;
}

void yyerror(const char *s, ...) {
    va_list args;
    va_start(args, s);

    fprintf(stderr, "Error: ");
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");

    va_end(args);
}
/*
exp:    cost                  { printf("Expresión constante: %d\n", $1); }
        |id                   { printf("Identificador: %s\n", $1); }
        |exp MAS exp          { printf("Suma: %s + %s\n", $1, $3); }
        |exp MENOS exp        { printf("Resta: %s - %s\n", $1, $3); }
        |exp POR exp          { printf("Multiplicación: %s * %s\n", $1, $3); }
        |exp DIVIDIDO exp     { printf("División: %s / %s\n", $1, $3); }
        ;

cond:   exp MENOR exp        { printf("Condición Menor: %s < %s\n", $1, $3); }
        |exp MAYOR exp        { printf("Condición Mayor: %s > %s\n", $1, $3); }
        |exp IGUAL_COMP exp   { printf("Condición Igual: %s == %s\n", $1, $3); }
        ;
%%
*/