typedef struct string string;

int string_insertchar(string* s, char c, size_t pos);
void string_print(string* s);

string* string_create(char* str);
void string_destroy(string* s);
