
#include "hashtable.h"

// find the old_word and replace everywhere with the new_word
void replace_ocurr(char *str, char *old_word, char *new_word)
{
	char temp[256] = {0};
	int index = 0;
	int len_old_word = strlen(old_word);
	char *pos;

	while ((pos = strstr(str, old_word)) != NULL) {
		strcpy(temp, str);
		index = pos - str;
		str[index] = '\0';
		strcat(str, new_word);
		strcat(str, temp + index + len_old_word);
	}
}

int main(int argc, char **argv)
{

	char *input = NULL;
	char *output = NULL;
	// used for branching between stdin, file input or error
	int file_counter = 0;
	int got_input_file = 0;
	int got_output_file = 0;
	int i;
	Hashtable *hashtable = NULL;
	char *buffer = calloc(100, sizeof(char)); // line buffer
	char *content = calloc(5000, sizeof(char)); // file buffer
	static const char delim[30] = "\t []{}<>=-*/%!&|^.,:;()\n";
	char *token;

	hashtable = hashtable_create(hashtable, DEFAULT_CAPACITY);
	for (i = 1; i < argc; i++) {
		if (strncmp(argv[i], "-D", 2) == 0) {
			if (strlen(argv[i]) == 2) {

				char *key = strtok(argv[i + 1], "=");
				char *value = strtok(NULL, "=");

				if (value != NULL)
					hashtable_put(hashtable, key, value);

				i++;
			}
		} else {  // read file or check wrong '-' parameter
			if (strncmp(argv[i], "-", 1) == 0) {
				i++;
				continue;
			}
			// first file is the input file
			if (file_counter == 0) {
				input = calloc(strlen(argv[i]) + 1,
				sizeof(char));
				strcpy(input, argv[i]);
				got_input_file = 1;
				file_counter++;

			} else if (got_output_file == 0) { // read output
				output = calloc(strlen(argv[i]) + 1,
				sizeof(char));
				strcpy(output, argv[i]);
				got_output_file = 1;
				file_counter++;
			} else { // too many files reached -> exit
				return -1;
			}
		}
	}

	// get from stdin
	if (got_input_file == 0) {
		fgets(content, 256, stdin);
	} else { // read from file
		FILE *file;
		int got_multiline_define = 0;
		char *multiline_key, *multiline_val;
		unsigned int i;

		file = fopen(input, "r");
		if (file == NULL)
			return -1;

		while (fgets(buffer, 256, file)) {

			if (got_multiline_define == 1) {
				if (strstr(buffer, "\\") != NULL) {
					strcat(multiline_val, buffer);
					continue;
				}
				strcat(multiline_val, buffer);
				got_multiline_define = 0;
				replace_ocurr(multiline_val, "\\", "");
				replace_ocurr(multiline_val, "\n", "");
				replace_ocurr(multiline_val, "        ", "");
				hashtable_put(hashtable,
				multiline_key, multiline_val);
				free(multiline_key);
				free(multiline_val);
			}

			if (strstr(buffer, "#define") == NULL &&
			strstr(buffer, "#undef") == NULL &&
			strstr(buffer, "        +") == NULL &&
			strstr(buffer, "#if") == NULL &&
			strstr(buffer, "#endif") == NULL)
				strcat(content, buffer);

			token = strtok(buffer, delim);
			while (token != NULL) {
				char *value;

				if (strcmp(token, "#define") == 0) {
					char *key = strtok(NULL, delim);
					char *value = strtok(NULL, delim);
					char *value_again = strtok(NULL, delim);

					if (hashtable_get(hashtable,
					value) != NULL)
						value =
						hashtable_get(hashtable, value);

					if (value_again == NULL) {
						hashtable_put(hashtable,
						key, value);
					} else if (strcmp(
					value_again, "\\") == 0) {
						got_multiline_define = 1;
						multiline_key =
						calloc(strlen(key) + 1,
						sizeof(char));
						strcpy(multiline_key, key);
						multiline_val =
						calloc(strlen(value) + 1,
						sizeof(char));
						strcpy(multiline_val, value);
					} else {
						char aux[100] = {0};

					while (1) {
						strncpy(aux,
						value, strlen(value));
						strcat(aux, value_again);
						value_again =
						strtok(NULL, delim);
					if (value_again == NULL) {
						hashtable_put(
						hashtable, key, aux);
						break;
					}
						}
					}
				} else if (strcmp(token, "#undef") == 0) {
					char *key = strtok(NULL, delim);

					hashtable_delete(hashtable, key);
				}
				value = hashtable_get(hashtable, token);

				if (value != NULL)
					replace_ocurr(content, token, value);

				token = strtok(NULL, delim);
			}
			// empty buffer
		   memset(buffer, 0, strlen(buffer) + 1);
		}
		fclose(file);

		for (i = 0; i < hashtable->capacity; i++) {
			struct hashtable_entry
			*current_entry = hashtable->entries[i];

			if (current_entry != NULL)
				replace_ocurr(
				content,
				current_entry->key, current_entry->value);
		}
	}

	// write to output
	if (got_output_file == 1) {
		FILE *file;

		file = fopen(output, "w");
		if (file == NULL)
			file = fopen(output, "wb");
		fwrite(content, sizeof(char), strlen(content), file);
		fclose(file);
	} else { // or send to stdout
		printf("%s", content);
	}

	free(input); input = NULL;
	free(output); output = NULL;
	free(buffer); buffer = NULL;
	free(content); content = NULL;
	hashtable = hashtable_destroy(hashtable);
	if (hashtable != NULL)
		free(hashtable);
	return 0;
}
