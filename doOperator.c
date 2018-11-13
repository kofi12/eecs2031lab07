#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doOperator.h"
#include "tokenStack.h"
#include "lexical.h"

static int op_quit(struct tokenStack *stack);
static int op_print(struct tokenStack *stack);
static int op_dump(struct tokenStack *stack);
static int op_add(struct tokenStack *stack);
static int popInt(struct tokenStack *s);
static void pushInt(struct tokenStack *s, int v);
static int op_diff(struct tokenStack *s);
static int op_product(struct tokenStack *s);
static int op_quotient(struct tokenStack *s);
static int op_gt(struct tokenStack *s);
static int op_lt(struct tokenStack *s);
static int op_ge(struct tokenStack *s);
static int op_le(struct tokenStack *s);
static int op_eq(struct tokenStack *s);
static int op_if(struct tokenStack *s, int v);
static int op_modquot(struct tokenStack *s);

static struct operator_struct {
  char *name;
  int (*fn_ptr)(struct tokenStack *);
} ops[] = {
  {"quit", op_quit},
  {"print", op_print},
  {"dump", op_dump},
  {"+", op_add},
  {"-", op_diff},
  {"*", op_product},
  {"/", op_quotient},
  {"GT", op_gt},
  {"LT", op_lt},
  {"GE", op_ge},
  {"LE", op_le},
  {"EQ", op_eq},
  {"IF", op_if},
  {"MODQUOT", op_modquot},
  {(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};


/* YOU WRITE THIS */
static int popInt(struct tokenStack *s)
{
	int temp = s->e[s->top]->symbol[0];
	s->e[(s->top)--]->symbol[0] = '\0';
  	return temp;
}

/* YOU WRITE THIS */
static void pushInt(struct tokenStack *s, int v)
{
	if(v < '0' || v > '9')
		printf("error");
	s->e[(s->top)++]->symbol[0] = v;
}

int doOperator(struct tokenStack *stack, char *o) 
{
  struct operator_struct *op = ops;
  for(op=ops;op->name != (char *)NULL; op++) {
    if(!strcmp(op->name, o))
      return op->fn_ptr(stack);
  }
  return(-1);
}

/*ARGSUSED*/
static int op_quit(struct tokenStack *stack)
{
  printf("[quit]\n");
  exit(0);
  /*NOTREACHED*/
}

static int op_print(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  printToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_dump(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  dumpToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_add(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1+v2);
  return(0);
}

static int op_diff(struct tokenStack *s)
{
	int n2 = popInt(s);
	int n1 = popInt(s);
	pushInt(s,(n1 - n2));
	return(0);
}

static int op_product(struct tokenStack *s)
{
	int n2 = popInt(s);
        int n1 = popInt(s);
        pushInt(s,(n1 * n2));
	return(0);
}

static int op_quotient(struct tokenStack *s)
{
	int n2 = popInt(s);
        int n1 = popInt(s);
        pushInt(s,(n1 / n2));
	return(0);
}

static int op_gt(struct tokenStack *s)
{
	int n2 = popInt(s);
        int n1 = popInt(s);
        if(n1 > n2)
		pushInt(s,1);
	pushInt(s,0);
	return(0);
}

static int op_lt(struct tokenStack *s)
{
	int n2 = popInt(s);
        int n1 = popInt(s);
        if(n1 < n2)
                pushInt(s,1);
        pushInt(s,0);
	return(0);
}

static int op_ge(struct tokenStack *s)
{
	int n2 = popInt(s);
        int n1 = popInt(s);
        if(n1 >= n2)
                pushInt(s,1);
        pushInt(s,0);
	return(0);
}

static int op_le(struct tokenStack *s)
{
        int n2 = popInt(s);
        int n1 = popInt(s);
        if(n1 <= n2)
                pushInt(s,1);
        pushInt(s,0);
	return(0);
}

static int op_eq(struct tokenStack *s)
{
        int n2 = popInt(s);
        int n1 = popInt(s);
        if(n1 == n2)
                pushInt(s,1);
        pushInt(s,0);
	return(0);
}

static int op_if(struct tokenStack *s, int v)
{
	int n2 = popInt(s);
        int n1 = popInt(s);    
	(v != 0) ? pushInt(s,n1) : pushInt(s,n2);
	return(0); 
}

static int op_modquot(struct tokenStack *s)
{
        int n2 = popInt(s);
        int n1 = popInt(s);
	pushInt(s,n1 % n2);
	pushInt(s,n1 / n2);
	return(0);
}
