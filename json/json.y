%{
/* simplest version of calculator */
/* corrections from downloaded code & tips from 
   https://stackoverflow.com/questions/20106574/
   simple-yacc-grammars-give-an-error
*/

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

/* declare tokens */
%token NUMBER
%token ADD SUB MUL DIV ABS
%token OP CP
%token EOL

%%

calclist: /* nothing */                      
 | calclist exp EOL { printf("= %d\n", $2); }
 | calclist EOL { printf("> "); } /* blank line or a comment */
 ;

exp: factor      
 | exp ADD factor { $$ = $1 + $3; }
 | exp SUB factor { $$ = $1 - $3; }
 ;

factor: term    
 | factor MUL term { $$ = $1 * $3; }
 | factor DIV term { $$ = $1 / $3; }
 ;

term: NUMBER  
 | ABS term   { $$ = $2 >= 0? $2 : - $2; }
;
%%
int main(int argc, char **argv)
{
  printf("> "); // Prompt user
  yyparse();
}

void yyerror(char *s)
{
  fprintf(stderr, "error: %s\n", s);
  
}
