%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

extern int yylex();
extern FILE *yyin;
int yyparse();

void yyerror(const char *s, ...);
%}

%token INICIO FIN LEER ESCRIBIR SI ENTONCES IDENTIFICADOR NUMERO IGUAL MAS MENOS POR DIVIDIDO MENOR MAYOR IGUAL_COMP PAR_DER PAR_IZQ id texto cost

%%
programa: INICIO inst FIN
        ;

inst: inst inst
        |inst_leer
        |inst_escribir
        |inst_si
        |inst_asig
        ;

inst_leer: LEER PAR_IZQ texto PAR_DER
            {
                printf("Instrucción Leer: %s\n",$3);
            }
        ;


inst_escribir: ESCRIBIR PAR_IZQ texto PAR_DER
            {
                printf("Instrucción Escribir texto:\n");
                printf("Texto: %s\n", $3);
            }
        | ESCRIBIR PAR_IZQ id PAR_DER
            {
                printf("Instrucción Escribir id:\n");
                printf("Id: %s\n",$3);
            }
        ;

inst_si: SI cond ENTONCES inst
            {
                printf("Instrucción Si:\n");
                printf("Condición: %s\n", $2);
            }
        ;

inst_asig: id IGUAL exp 
            {
                printf("Instrucción Asignación:\n");
                printf("Id: %s\n", $1);
                printf("Exp: %s\n", $3);
            }
        ;

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

int main() {
	yyin = stdin;
    printf("Bienvenido al traductor AZ2023\n");
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
