
#ifndef _LVAL_INCL
#define _LVAL_INCL
// lisp-value struct
typedef struct lval {
  int type;
  double num;
  char* err;
  char* sym;

  //list
  int count;
  struct lval** cell;
} lval;

/* Create Enumeration of Possible lval Types */
enum { LVAL_NUM, LVAL_ERR, LVAL_SYM, LVAL_SEXPR };

// Posible errors
enum { LERR_DIV_ZERO, LERR_BAD_OP, LERR_BAD_NUM };
#endif
