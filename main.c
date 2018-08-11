#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32

static char buffer[2048];

char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

void add_history(char* unused) {}

#else
#include <editline/readline.h>
#endif

#include "mpc/mpc.h"


mpc_result_t parse_input(char* input, mpc_parser_t* parser) {
    /* Attempt to parse the user input */
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, parser, &r)) {
      /* On success print and delete the AST */
      mpc_ast_print(r.output);
      mpc_ast_delete(r.output);
    } else {
      /* Otherwise print and delete the Error */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

    return r;
}

int main(int argc, char** argv) {

  /* Create Some Parsers */
  mpc_parser_t* number_parser   = mpc_new("number");
  mpc_parser_t* operator_parser = mpc_new("operator");
  mpc_parser_t* expresion_parser = mpc_new("expr");
  mpc_parser_t* lispy_parser    = mpc_new("lispy");
  
  /* Define them with the following Language */
  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                     \
      number   : /-?[0-9]+(\\.[0-9]+)?/ ;                 \
      operator : '+' | '-' | '*' | '/' ;                  \
      expr     : <number> | '(' <operator> <expr>+ ')' ;  \
      lispy    : /^/ <operator> <expr>+ /$/ ;             \
    ",
    number_parser, operator_parser, expresion_parser, lispy_parser);

  /* Print Version and Exit Information */
  puts("lispy Version 0.0.1");
  puts("press Ctrl+c to Exit\n");

  /* In a never ending loop */
  while (1) {

    /* Output our prompt and get input */
    char* input = readline("lispy> ");

    /* Add input to history */
    add_history(input);

    parse_input(input, lispy_parser);

    /* Free retrieved input */
    free(input);
  }

  return 0;
}
