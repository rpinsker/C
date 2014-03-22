// freq.h


typedef struct {
  char *word;
  int count;
} dict_entry_type;

typedef struct {
  dict_entry_type *entries;
  int size;
  int num_entries;
} dict_type;

char *get_word();

void dict_initialize(dict_type *d);
void dict_increment(dict_type *d, char *word);

dict_entry_type **dict_get_entries(dict_type *d);

int compare(const void * a, const void * b);
