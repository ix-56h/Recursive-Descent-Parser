# Recursive-Descent-Parser
A recursive descent parser for arithmetic language implementation in C.

# Usage

`./rdp "expression" [-debug=all] [-ast=draw]`

`ast=draw` draw the AST

`debug=all` print all debug messages

# BNF
``expr	: term ((PLUS | MINUS) term)*

term	: factor ((MUL | DIV) factor)*

factor	: INTEGER | LPAREN expr RPAREN``
