%{
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
FILE *yyin;
%}

%option noyywrap

%option yylineno

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
{INICIO}            {printf("\n Palabra reservada INICIO: (%s)", yytext);}
{LEER}              {printf("\nPalabra reservada LEER: (%s)", yytext);}
{ENTONCES}          {printf("\nPalabra reservada ENTONCES: (%s)", yytext);}
{DIGITO}              {printf("\nOperador digito: (%s)", yytext);}
{CHAR_PUNTOYCOMA}   {printf("\nSimbolo punto y coma: (%s)", yytext);}
{SUMA}              {printf("\nOperador suma: (%s)", yytext);}
{RESTA}              {printf("\nOperador resta: (%s)", yytext);}
{IGUAL}              {printf("\nOperador igual: (%s)", yytext);}


{IDENTIFICADOR}     {printf("\nIdentificador (%s)",yytext);}

%%
/*Codigo de usuario*/
int main(int arc,char *argv[]){
yyin = fopen("Prueba1.txt", "r");
yylex();
return 0;
/*    if ((yyin = fopen(argv[1],"rt")) == NULL){
        printf("\nNo se puede abrir el archivo: %x\n,argv[1]");
        return 1;
    }
    else{
        printf("\nEl archivo %s se abrio correctamente\n",argv[1]);
        yylex();
}
printf("\nFLEX Finalizo la lectura del archivo %s \n", argv[1]);
fclose(yyin);
return 0;*/
}

int yyerror(void){
    printf("\nErrorlexico: caracter invalido: %s\n", yytext);
    exit(1);
}