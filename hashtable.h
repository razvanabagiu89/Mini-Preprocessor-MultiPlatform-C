
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MULTIPLIER 57
#define DEFAULT_CAPACITY 64
#define Hashtable struct hashtable

struct hashtable_entry {
	char *key;
	char *value;
};

struct hashtable {
	struct hashtable_entry **entries;
	unsigned int capacity;
	unsigned int size;
};

Hashtable *hashtable_create(Hashtable *hashtable, int capacity);

Hashtable *hashtable_destroy(Hashtable *hashtable);

unsigned int hash_compute(Hashtable *hashtable, char *key);

void hashtable_put(Hashtable *hashtable, char *key, char *value);

char *hashtable_get(Hashtable *hashtable, char *key);

void hashtable_delete(Hashtable *hashtable, char *key);
