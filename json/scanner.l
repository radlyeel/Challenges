/* 
 * Jason Scanner: 
 * Originally from http://alumni.cs.ucr.edu/~lgao/teaching/flex.html
 * Reference: 
 * https://codingchallenges.fyi/challenges/challenge-json-parser/ 
 */

%{
// Here are C #includes and global definitions
// This logic for handling empty input seems a littl flaky.
//   Be prepared to revist it later.
    int empty = 1;
%}

%%
\{	{ printf("Open Brace\n");
      empty = 0; }
\}	{ printf("Close Brace\n");
      empty = 0; }
%%

main()
{
  int yyl = 1;
  do {
    yyl = yylex();
  } while (yyl && !feof(stdin));
  return empty;
}


