# FORMAL LOGICLANG GRAMMAR.
This is a G4 style grammar.
```
program: 
	circuit*;
circuit:
	(expression';')*;
expression:
	connection 
	| in
	| out
	| circuit_usage;
connection:
	'connect' ID expression 'to' expression;
out:
	'out' expression (',' expression)*?;
in:
	'in' ID (',' ID)*;
circuit_usage:
	ID '(' expression *',' expression)*? ')';
```
