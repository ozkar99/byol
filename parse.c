/* This file includes the grammar and parsing utilities for lispy */

#include "mpc/mpc.h"

char* GRAMMAR =  
  "                                                               \
    number   : /-?[0-9]+(\\.[0-9]+)?/ ;                           \
    symbol   : \"list\" | \"head\" | \"tail\"                     \
             | \"join\" | \"eval\"                                \
             | '+' | '-' | '*' | '/' | '%' | '^' ;                \
    sexpr    : '(' <expr>* ')' ;                                  \
    qexpr  : '{' <expr>* '}' ;                                    \
    expr     : <number> | <symbol> | <sexpr> | <qexpr> ;          \
    lispy    : /^/ <expr>* /$/ ;                                  \
  ";

typedef struct {
  int error;
  mpc_result_t r;
} parse_result_t;

parse_result_t parse_input(char* input, mpc_parser_t* parser) {
    /* Attempt to parse the user input */
    parse_result_t result;
    mpc_result_t r;

    if(mpc_parse("<stdin>", input, parser, &r)) {
      result.error = 0;
    } else {
      result.error = 1;
    }

    result.r = r;
    return result;
}

mpc_parser_t* generate_parser() {

  /* Create Some Parsers */
  mpc_parser_t* number_parser   = mpc_new("number");
  mpc_parser_t* symbol_parser = mpc_new("symbol");
  mpc_parser_t* sexpr_parser = mpc_new("sexpr");
  mpc_parser_t* qexpr_parser = mpc_new("qexpr");
  mpc_parser_t* expresion_parser = mpc_new("expr");
  mpc_parser_t* lispy_parser    = mpc_new("lispy");
  
  /* Define them with the "GRAMMAR" variable */
  mpca_lang(MPCA_LANG_DEFAULT, GRAMMAR,
    number_parser, symbol_parser, 
    sexpr_parser, expresion_parser,
    qexpr_parser, lispy_parser);

  return lispy_parser;
}