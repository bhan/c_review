#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string {
  char* data;
  size_t len;
  size_t cap; // string capacity not including '\0'
} string;

static inline int string_expand(string* s, size_t new_len) {
  while (s->cap < new_len) {
    size_t new_cap = (s->cap == 0) ? 1 : s->cap * 2;
    char* new_data = realloc(s->data, new_cap+1);
    if (new_data == NULL) goto err_exit;
    s->data = new_data; s->cap = new_cap;
  }
  return 0;
err_exit: return 1;
}

int string_insertchar(string* s, char c, size_t pos) {
  assert(s);
  if (string_expand(s, s->len+1)) goto err_exit;
  // shift chars from pos, inclusive, down one
  memmove(s->data+pos+1, s->data+pos, s->len-pos+1);
  s->data[pos] = c; ++s->len;
  return 0;
err_exit: return 1;
}

void string_print(string* s) {
  assert(s);
  printf("%s", s->data);
}

string* string_create(char* str) {
  string* s = malloc(sizeof(string)); if (s == NULL) goto err_exit;
  s->len = (str == NULL) ? 0 : strlen(str);
  s->cap = s->len;
  s->data = malloc(s->cap+1);
  if (s->data == NULL) goto clean_s;
  if (s->len > 0) memmove(s->data, str, s->len);
  s->data[s->len] = '\0';
  return s;
clean_s: free(s);
err_exit: return NULL;
}

void string_destroy(string* s) {
  free(s->data); free(s);
}
