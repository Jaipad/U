%{#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
file *yylex;
%}

/* Definiciones */
DIGITO              [0-9]
LETRA_MINUSCULA     [a-z]
LETRA_MAYUSCULA     [A-Z]
ESPACIO             [" "]
GUIONES             [-_]
CHAR_COMA           [","]
CHAR_PUNTO          ["."]
CHAR_PUNTOYCOMA     [";"]
CHAR_DOSPUNTOS      [":"]

IDENTIFICADOR       {LETRA_MAYUSCULA}{DIGITO}

/*Operaciones logicas y operadores aritmeticos basicos*/
SUMA                ["+"]
RESTA               ["-"]
MULT                ["*"]
DIV                 ["/"]
IGUAL               ["="]
MAYOR               [">"]
MENOR               ["<"]
MAYORIGUAL          ">="
MENORIGUAL          "<="
IGUALIGUAL          "=="
NEGATION            "!"
DISTINTO            "!="
/*palabras reservadas*/
INICIO              "inicio"|"INICIO"
LEER                "leer"|"LEER" 
ENTONCES            "entonces"|"ENTONCES"

%%

%%
Codigo de usuario