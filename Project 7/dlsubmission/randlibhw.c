#include "randlib.h"
#include <immintrin.h>

/*Removed all of the static void functions because it
  has no relevance in the refactoring steps
...also it didnt say to have them*/
/* Return a random value, using hardware operations.  */
static unsigned long long
hardware_rand64 (void)
{
  unsigned long long int x;
  while (! _rdrand64_step (&x))
    continue;
  return x;
}

extern unsigned long long rand64(void){
  return hardware_rand64(); //Have this b/c this is the syntax used in randlib.h lol
}
