#include <stdio.h>

#ifndef MESSAGE  // Preprocessor directive. Asks "Is the macro MESSAGE defined? If not, include the following code.""
#define MESSAGE "... --- ...;" // Preprocessor macro. Will automatically substitite for the string "MESSAGE"
                               // everywhere that it occurs in the code. Works like a case-sensitive search and replace!
                               // We can also define this macro on the gcc command line, which will override this
                               // definition because of the #ifndef.
#endif

char message[] = MESSAGE; // Uses the macro definition to initialize the message character array


int main() {
  
  printf("1,1\n");
  printf("0,1\n");
  printf("1,1\n");
  printf("0,1\n");
  printf("1,1\n");
  printf("0,3\n");
  printf("1,3\n");
  printf("0,1\n");
  printf("1,3\n");
  printf("0,1\n");
  printf("1,3\n");
  printf("0,3\n");
  printf("1,1\n");
  printf("0,1\n");
  printf("1,1\n");
  printf("0,1\n");
  printf("1,1\n");
  printf("0,7\n");

  return 0;
}
