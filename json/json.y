%{
/* stripped-down jq */

#include <stdio.h>
int yylex();
void yyerror(char *s);

/* Note on tokens and grammar symbols

Any symbols not declared as tokens have to appear on the left side of at least
one rule in the program. (If a symbol neither is a token nor appears on the
left side of a rule, it’s like an unreferenced variable in a C program. It
doesn’t hurt anything, but it probably means the programmer made a mistake.)

*/
%}

/* declare tokens
 * None needed, since JSON punctuation suffices
 */

%token digit1_9
%token DOT 
%%
%%
int main(int argc, char **argv)
{
  yyparse();
}

void yyerror(char *s)
{
  fprintf(stderr, "error: %s\n", s);
  
}
