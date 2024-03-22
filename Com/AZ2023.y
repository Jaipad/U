%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>

extern int yylex();
extern FILE *yyin;
int yyparse();

struct Variable {
    char identifier[20]; // Ajusta el tamaño según tus necesidades
    int value;
};

struct Variable listaIdentificadores[100];
int numIdentificadores = 0;

void agregarIdentificador(char *id, int val) {
    if (numIdentificadores < 100) {
        strncpy(listaIdentificadores[numIdentificadores].identifier, id, sizeof(listaIdentificadores[numIdentificadores].identifier) - 1);
        listaIdentificadores[numIdentificadores].value = val;
        numIdentificadores++;
    } 
    }

int obtenerValorIdentificador(char *id) {
    for (int i = 0; i < numIdentificadores; i++) {
        if (strcmp(listaIdentificadores[i].identifier, id) == 0) {
            return listaIdentificadores[i].value;
        }
    }
}

void yyerror(const char *s, ...);
%}

%token INICIO FIN LEER ESCRIBIR SI ENTONCES IDENTIFICADOR ENTERO IGUAL SUMA RESTA POR DIVIDIDO MENOR MAYOR IGUAL_COMP PAR_DER PAR_IZQ id cost texto 

%union
{
    char carac;
    int entero;
    char* string_val;
    char *text;
    int tipo_inst;
    bool if_statement;
}
%code requires {
    typedef int bool;
    #define true 1
    #define false 0
}

%type <entero> ENTERO cond
%type <entero> exp
%type <string_val> IDENTIFICADOR texto
%type <tipo_inst> inst inst_leer inst_escribir inst_si inst_asig


%%

programa: INICIO inst FIN;

inst: inst inst
        |inst_leer
        |inst_escribir
        |inst_si
        |inst_asig
        ;


inst_leer: LEER PAR_IZQ IDENTIFICADOR PAR_DER {
    char id[20];
    scanf("%d", &listaIdentificadores[numIdentificadores].value);
    strncpy(id, $3, sizeof(id) - 1);
    id[sizeof(id) - 1] = '\0';  
    agregarIdentificador(id, listaIdentificadores[numIdentificadores].value);
}
;

inst_escribir: ESCRIBIR PAR_IZQ texto PAR_DER {
        printf("%s", $3);
        }
        | ESCRIBIR PAR_IZQ IDENTIFICADOR PAR_DER {
        printf("%d", obtenerValorIdentificador($3));
        }
        ;

inst_si: SI cond ENTONCES inst
        {
            if ($2) {
                // Ejecutar la instrucción correspondiente solo si if_statement es verdadero
                if (if_statement) {
                    $$.val = $4.val;
                } else {
                    $$.val = NULL; // Si if_statement es falso, no hay salida
                }
            } else {
                // No hacer nada
                $$.val = NULL;
            }

            // Restaurar if_statement a true después de evaluar la condición
            if_statement = true;
        }
        ;

inst_asig: IDENTIFICADOR IGUAL exp {
    char id[20];
    strncpy(id, $1, sizeof(id) - 1);
    agregarIdentificador(id, $3);
    }
    ;

exp: ENTERO{
        $$ = $1;
    }
    | IDENTIFICADOR {
        $$ = obtenerValorIdentificador($1);
    }
    | exp SUMA exp {
        $$ = $1 + $3;
    }
    | exp RESTA exp {
        $$ = $1 - $3;
    }
    | exp POR exp {
        $$ = $1 * $3;
    }
    | exp DIVIDIDO exp {
        $$ = $1 / $3;
    }
    ;



cond: exp MENOR exp {
        $$ = $1 < $3;
    }
    | exp MAYOR exp {
        $$ = $1 > $3;
    }
    | exp IGUAL_COMP exp {
        $$ = $1 == $3;
    }
    ;
%%

int main() {
    yyin = stdin;
    printf("Bienvenido al traductor AZ2023\n");
    printf("Para iniciar el programa debe escribir la palabra 'INICIO'\n");

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
