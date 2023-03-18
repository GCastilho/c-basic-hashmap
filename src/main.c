#include <stdio.h>
#include "hashmap.c"

void add_and_print(HashMap *hash_map, char key[], char *value) {
	int idx = set_hashmap(hash_map, key, value);
	printf(
		"Added to index %d: key %s value: %s\nFilled: %d/%d\n",
		idx, key, value, hash_map->length, hash_map->capacity
	);
}

int main(int argc, char const *argv[]) {
	int capacity = 10;
	HashMap hash_map = new_hash_map(capacity);

	int idx = set_hashmap(&hash_map, "this-is-the-key", "this-is-the-value");
	printf(
		"Idx: %i | Key: %s | Value: %s\n",
		idx,
		hash_map.items[idx]->value->key,
		hash_map.items[idx]->value->value
	);

	idx = set_hashmap(&hash_map, "this-is-key-the", "this-is-the-value");
	printf(
		"Idx: %i | Key: %s | Value: %s\n",
		idx,
		hash_map.items[idx]->next->value->key,
		hash_map.items[idx]->next->value->value
	);

	idx = set_hashmap(&hash_map, "key-the-this-is", "this-value-is-the");
	printf(
		"Idx: %i | Key: %s | Value: %s\n",
		idx,
		hash_map.items[idx]->next->next->value->key,
		hash_map.items[idx]->next->next->value->value
	);

	char *value = get_hashmap(&hash_map, "key-the-this-is");
	printf("found: %s\n", value);

	value = get_hashmap(&hash_map, "not-stored");
	printf("found (do not exist): %s\n", value);

	int del = del_hashmap(&hash_map, "key-the-this-is");
	printf("del is %d\n", del);
	value = get_hashmap(&hash_map, "key-the-this-is");
	printf("found (deleted): %s\n", value);

	printf("HashMap size: %i | length: %i\n", hash_map.capacity, hash_map.length);

	for (size_t i = 0; i < 25; i++) {
		char str[3];
		sprintf(str, "%d", i);
		add_and_print(&hash_map, str, str);
	}

	return 0;
}
