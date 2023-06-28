# FORMAL LOGICLANG GRAMMAR.
This is a G4 style grammar.
```
program: 
	circuit*;
circuit:
	'circuit' ID block;
block:
	'{' (expression';')* '}'
expression:
	connection 
	| in
	| out
	| circuit_usage
	| binary;
connection:
	'connect' ID expression 'to' expression;
out:
	'out' expression (',' expression)*?;
in:
	'in' ID (',' ID)*;
circuit_usage:
	ID '(' expression *',' expression)*? ')'  PIN?;
binary:
	'0' | '1';
// skip all whitespace.
PIN:
	'.' NUMBER

```
