#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>


typedef enum {
  ND_ADD,
  ND_SUB,
  ND_MUL,
  ND_DIV,
  ND_EQ,
  ND_NE,
  ND_LT,
  ND_LE,
  ND_NUM,
  ND_ASSIGN,
  ND_LVAR,
} NodeKind;

typedef enum {
  TK_RESERVED,
  TK_IDENT,
  TK_NUM,
  TK_EOF,
} TokenKind;

typedef struct Token Token;

struct Token {
  TokenKind kind;
  Token *next;
  int val;
  char *str;
  int len;
};

typedef struct Node Node;

struct Node {
  NodeKind kind;
  Node *lhs; // left-hand-side
  Node *rhs; // right-hand-side
  int val;
  int offset; // offset from base-pointer of local variable
};

typedef struct LVar LVar; // Local Variable

struct LVar {
  LVar *next;
  char *name;
  int len;
  int offset;
};

/*
noreturn void error(char *fmt, ...) __attribute__((format(printf, 1, 2)));
noreturn void error_at(char *loc, char *fmt, ...) __attribute__((format(printf, 2, 3)));
noreturn void error_tok(Token *tok, char *fmt, ...) __attribute__((format(printf, 2, 3)));
*/


// parse.c
Token *tokenize(char *p);
void program();
Node *stmt();
Node *expr();
Node *assign();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();

// codegen.c
void gen(Node *node);

// error.c
void error(char *fmt, ...);
void error_at(char *loc, char *fmt, ...);

// global
extern Token *token;
extern char *user_input;
extern Node *code[100];
extern LVar *locals;