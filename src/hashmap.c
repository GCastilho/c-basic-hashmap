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
	size_t length;
	Node* *items;
} HashMap;

HashMap new_hash_map(int capacity) {
	HashMap hash_map;
	hash_map.capacity = capacity;
	hash_map.length = 0;
	hash_map.items = malloc(sizeof(Node*) * capacity);
	return hash_map;
}

void double_hashmap(HashMap *hash_map) {
	HashMap doubled_hash_map = new_hash_map(hash_map->capacity * 2);
	for (size_t i = 0; i < hash_map->capacity; i++) {
		Node *head = hash_map->items[i];
		while (head != NULL) {
			set_hashmap(&doubled_hash_map, head->value->key, head->value->value);
			head = head->next;
		}
	}
	free(hash_map->items);
	hash_map->capacity = doubled_hash_map.capacity;
	hash_map->items = doubled_hash_map.items;
}

int set_hashmap(HashMap *hash_map, char key[], char value[]) {
	Item *item = malloc(sizeof(Item));
	item->key = key;
	item->value = value;
	Node *node = malloc(sizeof(Node));
	node->value = item;

	float filled = (float)hash_map->length / (float)hash_map->capacity;
	if (filled > 0.7) {
		double_hashmap(hash_map);
	}

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
	hash_map->length++;

	return idx;
}

char* get_hashmap(HashMap *hash_map, char key[]) {
	int idx = hash_char_array(key) % hash_map->capacity;
	Node *node = hash_map->items[idx];
	while (node != NULL) {
		if (strcmp(key, node->value->key) == 0) {
			return node->value->value;
		}
		node = node->next;
	}
	return NULL;
}

int del_hashmap(HashMap *hash_map, char key[]) {
	int idx = hash_char_array(key) % hash_map->capacity;
	Node *head = hash_map->items[idx];
	Node *previous;
	while (head != NULL) {
		if (strcmp(key, head->value->key) == 0) {
			previous->next = head->next;
			// Maybe there is a leak here bc key&val are not freed
			free(head);
			hash_map->length--;
			return 1;
		}
		previous = head;
		head = head->next;
	}
	return 0;
}
