#include "stdio.h"
#include "string.h"

int main() {
  string* s = string_create("");
  for (int i = 0; i < 10; ++i) {
    if (string_insertchar(s, 'a', 0)) {
      printf("insertchar failed\n"); return 1;
    }
    string_print(s); printf("\n");
  }
//  string_print(s); printf("\n");
  string_destroy(s);
}
