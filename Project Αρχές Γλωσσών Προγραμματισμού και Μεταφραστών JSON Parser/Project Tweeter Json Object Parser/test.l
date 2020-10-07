%{
#include "y.tab.h" 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
extern YYSTYPE yylval;
%}
%option noyywrap
%option yylineno

boolean_true	true
boolean_false	false
null_string	null
letter	[a-zA-Z]
string	\"([^\\\"]|\\.)*\" 
digit	[0-9]
sign	[+|-]{digit}+	
unsign  {digit}+
real	({sign}|{unsign})"."{digit}+	
%%

"+"	{ return '+'; }
"!"	{ return '!'; }
":"	{ return ':'; }
","	{ return ','; }
"{"	{ return '{'; }
"}"	{ return '}'; }
"["	{ return '['; }
"]"	{ return ']'; }
"-"	{ return '-'; }
"e"	{ return 'e'; }
"&"	{ return '&'; }
[ \t\n] //ignore whitespace, tab, newline
{string}	{ yylval.string = strdup(yytext); return STRING;}
{sign}	{ yylval.number = atoi(yytext); return SIGN; }
{real}	{	yylval.real = atof(yytext); return REAL;}
{boolean_true}	{	return true;}
{boolean_false}	{	return false;}
{unsign}	{ yylval.number = atoi(yytext); return UNSIGN; }
{null_string}	{ return null; }
.	{ printf("Illegal Sequence at Line: %d\n", yylineno); exit(1); } 
%%

