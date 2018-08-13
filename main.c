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
#include "parse.c"
#include "eval.c"

int main(int argc, char** argv) {

  mpc_parser_t* parser = generate_parser();  

  /* Print Version and Exit Information */
  puts("lispy Version 0.0.1");
  puts("Press Ctrl+c to Exit\n");

  /* In a never ending loop */
  while (1) {

    /* Output our prompt and get input */
    char* input = readline("lispy> ");

    /* Add input to history */
    add_history(input);

    /* Parsse expressions */
    parse_result_t ast = parse_input(input, parser);

    /* Eval ast */
    if (ast.error) {
      mpc_err_print(ast.r.error);
      mpc_err_delete(ast.r.error);
    } else {
      double result = eval(ast.r.output);
      printf("%f\n", result);
      mpc_ast_delete(ast.r.output);
    }

    /* Free retrieved input */
    free(input);
  }

  free(parser);
  return 0;
}
