// freq.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "freq.h"

#define BUFFSIZE 40
#define NUMENTRIES 100
FILE *fp;
char buffer[BUFFSIZE];
dict_type my_dict;

char *get_word() {
  if (fscanf(fp, "%s",buffer) == 1) { // if word was read
    // make lowercase and remove punctuation
       int i = 0;
    while (buffer[i] != '\0') {
      buffer[i] = tolower(buffer[i]);
      if (ispunct(buffer[i]) && buffer[i+1] == '\0')
	buffer[i] = '\0';
      i++;
    }
  return buffer;
  }
 else 
    return NULL;
}

void dict_initialize(dict_type *d) {
  dict_entry_type *entries = (dict_entry_type *) calloc(NUMENTRIES,sizeof(dict_entry_type));
  if (entries == NULL) {
    printf("Not enough memory");
    return;
  }
  d->entries = entries;
  d->size = NUMENTRIES;
  d->num_entries = 0;
}

void dict_increment(dict_type *d, char *word) {
  int done = 1; // not done, 0 means word has been added
  int i = 0;
  while (done == 1 && i < d->num_entries) {
    if (strcmp(d->entries[i].word,word) == 0) {
      d->entries[i].count++;
      done = 0;
    }
    i++;
  }
  if (done == 1) {
    if (d->num_entries < d->size) {
      char *new_word = (char *) calloc(30,sizeof(char));
      strcpy(new_word,word);
      d->entries[d->num_entries].word = new_word;
      d->entries[d->num_entries].count = 1;
      d->num_entries++;
      done = 0;
    }
    else { //more room must be made
      dict_entry_type *new_entries = (dict_entry_type *) calloc(d->size + NUMENTRIES,sizeof(dict_entry_type));
      int i;
      for (i = 0; i < d->num_entries; i++)
	new_entries[i] = d->entries[i];
      char *new_word = (char *) calloc(30,sizeof(char));
      strcpy(new_word,word);
      new_entries[d->num_entries].word = new_word;
      new_entries[d->num_entries].count = 1;
      d->entries = new_entries;
      d->size = d->size + NUMENTRIES;
      done = 0;
    }
    return;
  }
}

dict_entry_type **dict_get_entries(dict_type *d) {
  return &d->entries;
}

int main(int argc, char **argv) {
  fp = fopen(argv[1],"r");
  dict_initialize(&my_dict);
  char *word = get_word();
  while (word != NULL) {
    dict_increment(&my_dict,word);
    word = get_word();
  }
  int i;
  qsort(my_dict.entries,my_dict.num_entries,sizeof(dict_entry_type),compare);
  for (i = 0; i < my_dict.num_entries; i++)
    printf("%s\t\t%i\n",my_dict.entries[i].word,my_dict.entries[i].count);
  return 0;
}

int compare(const void * a, const void * b) {
  int count1 = ((dict_entry_type*)a)->count;
  int count2 = ((dict_entry_type*)b)->count;
  if (count2 - count1 == 0) {
    char *word1 = ((dict_entry_type*)a)->word;
    char *word2 = ((dict_entry_type*)b)->word;
    return strcmp(word1,word2);
  }
  else 
    return count2 - count1;
}
    
