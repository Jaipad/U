%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "y.tab.h"
FILE *yyin;
%}

%option noyywrap
%option yylineno

/* Definicion de tokens */
DIGITO              [0-9]
LETRA_MINUSCULA     [a-z]
LETRA_MAYUSCULA     [A-Z]
ENTERO              {DIGITO}+
ESPACIO             [" "]
GUIONES             [-_]
CHAR_COMA           [","]
CHAR_PUNTO          ["."]
CHAR_PUNTOYCOMA     [";"]
CHAR_DOSPUNTOS      [":"]
IDENTIFICADOR       {LETRA_MAYUSCULA}{DIGITO}

/* Operaciones logicas y operadores aritmeticos básicos */

/* Operaciones de asignación */
ASIG                "=="
/* Operaciones aritméticas */
SUMA                "+"
RESTA               "-"
MULT                "*"
DIV                 "/"
/* Operaciones Relacionales */
IGUAL               "="
MAYOR               ">"
MENOR               "<"
/* Palabras reservadas */
INICIO              "INICIO"
LEER                "LEER" 
ENTONCES            "ENTONCES"
FIN                 "FIN"
texto               "("[^"]+")"

/* Sección de reglas */
%%

{SUMA}              { return SUMA; }
{RESTA}             { return RESTA; }
{IGUAL}             { return IGUAL; }
{IDENTIFICADOR}     { yylval.string_val = strdup(yytext); return IDENTIFICADOR; }
{ENTERO}            { yylval.entero = atoi(yytext); return ENTERO;}
\"[^"]*\"           { yylval.string_val = strdup(yytext); return texto; }

"INICIO"            { return INICIO; }
"FIN"               { return FIN; }
"LEER"              { return LEER; }
"ESCRIBIR"          { return ESCRIBIR; }
"SI"                { return SI; }
"ENTONCES"          { return ENTONCES; }
"("                 { return PAR_IZQ; }
")"                 { return PAR_DER; }
%%
