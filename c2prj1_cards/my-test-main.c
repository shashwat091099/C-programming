#include <stdio.h>
#include <assert.h>
#include "cards.h"

int main(void) {
  card_t c = card_from_num(0);
  for (int i=2; i<15; i++) {
    c.value = i;
    printf("%d: %c\n", i, value_letter(c));
  }
  return 0;
}
