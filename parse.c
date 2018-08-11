/* This file includes the grammar and parsing utilities for lispy */

#include "mpc/mpc.h"

char* GRAMMAR =  
  "                                                     \
    number   : /-?[0-9]+(\\.[0-9]+)?/ ;                 \
    operator : '+' | '-' | '*' | '/' ;                  \
    expr     : <number> | '(' <operator> <expr>+ ')' ;  \
    lispy    : /^/ <expr>+ /$/ ;                        \
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
  mpc_parser_t* operator_parser = mpc_new("operator");
  mpc_parser_t* expresion_parser = mpc_new("expr");
  mpc_parser_t* lispy_parser    = mpc_new("lispy");
  
  /* Define them with the "GRAMMAR" variable */
  mpca_lang(MPCA_LANG_DEFAULT, GRAMMAR,
    number_parser, operator_parser, expresion_parser, lispy_parser);

  return lispy_parser;
}