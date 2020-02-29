# include <detpic32.h>
# include "../../Utils/utils.h"

int main(void) {
  setPWM_OC1(10, 10);
  while (1);
  return 0;
}