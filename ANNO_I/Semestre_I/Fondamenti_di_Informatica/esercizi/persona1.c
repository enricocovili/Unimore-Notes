#define _CRT_SECURE_NO_WARNINGS
#include "persona.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char* trimwhitespace(char* str){
	char* end;
	while (isspace((unsigned char)*str)) str++;
	if (*str == 0)  // All spaces?
		return str;
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) end--;
	end[1] = '\0';
	return str;
}

struct persona* leggi_persone(const char* filename, size_t* size)
{
	if (filename == NULL || size == NULL) return NULL;
	FILE* f = fopen(filename, "r");
	if (f == NULL) return NULL;
	*size = 0;
	
	int num_people;
	fscanf(f, "%d\n", &num_people);
	struct persona* people = malloc(num_people * sizeof(struct persona));
	
	char* trim_str, temp[50];
	for (size_t i = 0; i < num_people; i++) {
		short num_read = fscanf(f, "%d , ", &people[i].anni);
		num_read += fscanf(f, "%[^\n]", people[i].nome);
		trim_str = NULL;
		memset(temp, 0, 50);
		memcpy(temp, people[i].nome, 50);
		trim_str = trimwhitespace(temp);
		size_t j = 0;
		memset(people[i].nome, 0, 50);
		while (trim_str[j]) {
			people[i].nome[j] = trim_str[j];
			j++;
		}
		if (num_read != 2) { *size = 0; free(people); fclose(f); return NULL; }
		(*size)++;
	}

	fclose(f);
	return people;
}

//int main() {
//	size_t size = 0;
//	struct persona* p = leggi_persone("file3.txt", &size);
//	return 0;
//}