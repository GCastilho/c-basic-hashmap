#include <stdio.h>

int hash_char_array(char key[]) {
	int sum = 0;
	while (key != NULL && *key != '\0') {
		sum += *key;
		key++;
	}
	return sum;
}

int main(int argc, char const *argv[]) {
	char str[] = "Hello, world!";
	int hash = hash_char_array(str);

	printf("Hello, World!\nHash is %i\n", hash);
	return 0;
}
