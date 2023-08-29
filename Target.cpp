#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 this is an example program written 
 to test hooking, patching and runtime
 injections on android
 */

const char * get_arch() {
  #if defined(__x86_64__) || defined(_M_X64)
  return "x86_64";
  #elif defined(i386) || defined(__i386__)
  return "x86_32";
  #elif defined(__aarch64__) || defined(_M_ARM64)
  return "ARM64";
  #elif defined(__arm__)
  return "ARM32";
  #else
  return "UNKNOWN";
  #endif
}

void breakpoint() {
  #if defined(__aarch64__) || defined(_M_ARM64)
  asm("BRK 0");
  #elif defined(__x86_64__) || defined(__i386__)
  asm("int $3");
  #elif defined(__arm__)
  asm("BKPT 0");
  #else
  printf("Unsupported arch\n");
  #endif
}

void print_args(int num, char * str) {
  printf("Arguments: %d, %s\n", num, str);
}

int get_int() {
  return 5;
}

char * get_str() {
  return "test";
}

void run_loops() {
  for (int i = 0; i < 10; i++)
    printf("%d ", i);
  printf("\n");
  int a = 0;
  while (a < 10) {
    printf("%d ", a);
    a++;
  }
  printf("\n");
}

int intv;
char * strv;

void static_mem() {
	intv = 5;
	strv = "test";
	printf("Static values: %d, %s\n", intv, strv);
}

void dynamic_mem() {
  int * dyn_int  = (int *)malloc(sizeof(int));
  char * dyn_str = (char*) malloc(5);
  *dyn_int = 5;
  strcpy(dyn_str, "test\0");
  printf("Dynamic values: %d, %s\n", *dyn_int, dyn_str);
  free(dyn_int);
  free(dyn_str);
}

int main() {
  printf("A C binary for hexpatching/hooking testing.\nCPU ARCH: (%s)\n", get_arch());
  printf("1. For/While loop test\n");
  printf("2. Method retval/args test\n");
  printf("3. ASM breakpoints test\n");
  printf("4. Static memory access test\n");
  printf("5. Dynamic memory access test\n");
  printf("> ");
  
  // Input the option
  char input[2];
  fgets(input, sizeof(input), stdin);
  switch (atoi(input)) {
  case 1:
    run_loops();
    break;
  case 2:
    printf("Retvals: %d, %s\n", get_int(), get_str());
    print_args(5, "test");
    break;
  case 3:
    breakpoint();
    break;
  case 4:
    static_mem();
    break;
  case 5:
    dynamic_mem();
    break;
  default:
    printf("Unknown option, exiting..");
    return -1;
  }
  return 0;
}