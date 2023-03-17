#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hash_char_array(char key[]) {
	int sum = 0;
	while (key != NULL && *key != '\0') {
		sum += *key;
		key++;
	}
	return sum;
}

typedef struct Item {
	char *key;
	char *value;
} Item;

typedef struct Node {
	struct Node *next;
	Item *value;
} Node;

typedef struct HashMap {
	size_t capacity;
	Node* *items;
} HashMap;

HashMap new_hash_map(int capacity) {
	HashMap hash_map;
	hash_map.capacity = capacity;
	hash_map.items = malloc(sizeof(Node*) * capacity);
	return hash_map;
}

int set_hashmap(HashMap *hash_map, char key[], char value[]) {
	Item *item = malloc(sizeof(Item));
	item->key = key;
	item->value = value;
	Node *node = malloc(sizeof(Node));
	node->value = item;

	int idx = hash_char_array(key) % hash_map->capacity;
	Node *stored_node = hash_map->items[idx];
	if (stored_node == NULL) {
		hash_map->items[idx] = node;
	} else {
		while (stored_node->next != NULL) {
			stored_node = stored_node->next;
		}
		stored_node->next = node;
	}

	return idx;
}

char* get_hashmap(HashMap *hash_map, char key[]) {
	int idx = hash_char_array(key) % hash_map->capacity;
	Node *node = hash_map->items[idx];
	if (node == NULL) {
		return NULL;
	}
	while (node != NULL) {
		if (strcmp(key, node->value->key) == 0) {
			return node->value->value;
		}
		node = node->next;
	}
	return NULL;
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

	return 0;
}
