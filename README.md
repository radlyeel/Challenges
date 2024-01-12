# Challenges 
Coding Challenges on https://codingchallenges.fyi/challenges/intro .  

## wc

The first challenge is to write my own version of the classic Unix utility
'wc'.The reference will be wc's man page.  I'll use the getopt function to
process the command line options. In the spirit of "classic Unix utility"
I'll use C (with Vim, make, and gcc).

I'll be obsessive about error checking, but lazy about recovery--most of the time a simple exit(n) will satisfy me.  Ibid. for end-of-program resource cleanup ( free-ing memory, closing files, etc. ).

option --lbxo is not implemented, for lack of documentation.

Instead of parsing the comand line by brute force, I'll use the getopt() function.


### References
man wc

man 3 getopt

## Environment
Unless specified otherwise, I'm using a M2 2022 Macbook Air, Vim 9.1.0 (I won't mention updates), GNU Make 3.81, clang 15.0.0 (invoked with gcc/g++) 
