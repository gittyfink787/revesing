#include <stdio.h>
#include <stdint.h> 
extern FILE* __acrt_iob_func(int);

int stage2() {
	printf("You know what? That was too easy. *Now* tell me the second passwo\n");
	char user_input[1024];
	int len;
	char* str = "into the rabbit hole\0";
	int i;

	do {
		memset(user_input, 0, sizeof(user_input));
		FILE* stream = __acrt_iob_func(0);
		fgets(user_input, sizeof(user_input), stream);
		user_input[strcspn(user_input, "\n")] = '\0';
		len = strlen(user_input);

		for (int i = 0; i + 3 < len; i += 4) {
			*(int*)(user_input + i) ^= 0x41524241;
		}

		if (strcmp(user_input, str) != 0)	
			printf("Wrong password!\r\n");

	} while (strcmp(user_input, str) != 0);
	printf("Correct! you may enter..\r\n");
	return 0;
}


int main() {
	stage2();
	return 0;
}