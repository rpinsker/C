// pow.c
// Algorithm from: http://mitpress.mit.edu/sicp/chapter1/node15.html

#include <stdio.h>

long int power(long int a, long int x);

// main function that reads in values for a and x to solve a to the x. prints out solution as found by power function.
int main(int argc, char **argv) {
  long int a = atoi(argv[1]);
  long int x = atoi(argv[2]);
  long int answer = power(a,x);
  printf("%ld\n",answer);
  return 0;
}

// finds the solution of a to the x using the following recursive algorithm: if the power is 0, return 1. if the power is 1, return 1. if the power is even, recursively find the base to that power over two and square that. if the power is odd, return the base times the base to one less power (which will now be even).
long int power(long int a, long int x) {
  if (x == 0)
    return 1;
  else if (x == 1)
    return a;
  else if (x % 2 == 0) {
    //use temp to only solve for this once
    int temp = power(a,x/2);
    return temp*temp;
  }
  else
    return a * power(a,x-1);
}
