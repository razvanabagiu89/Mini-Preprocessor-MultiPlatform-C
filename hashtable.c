
#include "hashtable.h"

Hashtable *hashtable_create(Hashtable *h_inst, int capacity)
{
	unsigned int i;
	h_inst = calloc(1, sizeof(Hashtable));
	h_inst->capacity = capacity;
	h_inst->size = 0;
	h_inst->entries = (struct hashtable_entry **) calloc(capacity,
	sizeof(struct hashtable_entry *));

	// set entries to NULL to differentiate them
	for (i = 0; i < h_inst->capacity; i++)
		h_inst->entries[i] = NULL;
	return h_inst;
}

Hashtable *hashtable_destroy(Hashtable *hashtable)
{

	unsigned int i;

	for (i = 0; i < hashtable->capacity; i++) {
		if (hashtable->entries[i] != NULL) {
			free(hashtable->entries[i]->key);
			free(hashtable->entries[i]->value);
			free(hashtable->entries[i]);
		} else {
			free(hashtable->entries[i]);
		}
	}
	free(hashtable->entries);
	return hashtable;
}

// random compute func
unsigned int hash_compute(Hashtable *hashtable, char *key)
{

	unsigned long value = 0;
	size_t i;

	for (i = 0; i < strlen(key); i++)
		value = ((((int) key[i] + i) * MULTIPLIER) << 2) %
		(hashtable->capacity);

	return value;
}

void hashtable_put(Hashtable *hashtable, char *key, char *value)
{

	unsigned int index = hash_compute(hashtable, key);
	struct hashtable_entry *entry = hashtable->entries[index];

	// key does not exist yet
	if (entry == NULL) {
		// test if hashtable is not full
		if (hashtable->size == hashtable->capacity) {
			exit(-1);
		} else { // set entry
			entry = calloc(1, sizeof(struct hashtable_entry));
			entry->key = malloc((strlen(key) + 1) * sizeof(char));
			strcpy(entry->key, key);
			entry->value = malloc((strlen(value) + 1)
			* sizeof(char));
			strcpy(entry->value, value);
			hashtable->entries[index] = entry;
			hashtable->size++;
		}
	} else { // key exists so we need either to update or linear probing
		if (strcmp(key, entry->key) == 0) {
			strcpy(hashtable->entries[index]->value,
			value); // update value
		} else { // collision so we are doing a linear probing
		// to find the next available slot -> entry doesnt exist
			while (hashtable->entries[index]->key != NULL) {
				index++;
				if (index >= hashtable->capacity)
					index = 0;
			}
			// found an empty spot
			entry = malloc(sizeof(struct hashtable_entry));
			entry->key = malloc((strlen(key) + 1) * sizeof(char));
			strcpy(entry->key, key);
			entry->value = malloc(strlen(value) + 1);
			strcpy(entry->value, value);
			hashtable->entries[index] = entry;
			hashtable->size++;
		}
	}
}

char *hashtable_get(Hashtable *hashtable, char *key)
{

	int index = hash_compute(hashtable, key);
	struct hashtable_entry *entry = hashtable->entries[index];

	if (entry != NULL) {
		// make sure it is the same key
		if (strcmp(entry->key, key) == 0)
			return entry->value;
	}
	return NULL;
}

void hashtable_delete(Hashtable *hashtable, char *key)
{
	int index = hash_compute(hashtable, key);
	struct hashtable_entry *entry = hashtable->entries[index];

	if (entry != NULL) {
		// make sure it is the same key
		if (strcmp(entry->key, key) == 0) {
			free(hashtable->entries[index]->key);
			free(hashtable->entries[index]->value);
			free(hashtable->entries[index]);
			hashtable->entries[index] = NULL;
		}
	}
}
