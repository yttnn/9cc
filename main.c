#include "9cc.h"

char *user_input;
Token *token;
// ;区切りでstmtを保管
Node *code[100];
LVar *locals;

int count_number_of_local_variables() {
  int counter = 0;
  for (LVar *var = locals; var; var = var->next)
    counter++;
  return counter;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Invalid number of arguments\n");
    return 1;
  }

  // tokenize and parse
  user_input = argv[1];
  token = tokenize(user_input);
  program();

  printf(".intel_syntax noprefix\n");
  printf(".global main\n");
  printf("main:\n");

  // prologue
  printf("  push rbp\n");
  printf("  mov rbp, rsp\n");
  printf("  sub rsp, %d\n", count_number_of_local_variables() * 8);

  for (int i = 0; code[i]; i++) {
    gen(code[i]);
    printf("  pop rax\n");
  }

  // epilogue
  printf("  mov rsp, rbp\n");
  printf("  pop rbp\n");
  printf("  ret\n");
  return 0;
}