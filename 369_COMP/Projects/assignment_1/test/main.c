#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define N 10

int main(void) {

	FILE *ptr_file;
	char *buf = (char*)malloc(200 * sizeof(char));
	char myString[200];

	ptr_file = fopen("../questions/chapter1.txt", "r");
	if(!ptr_file){
		return 1;
	}

	int i;
	for(i = 0; i < 6; i++){
		if(fgets(buf, 200, ptr_file) != NULL) {
			strcpy(myString, buf);
			printf("%s", myString);
		}
	}
	fclose(ptr_file);
	return 0;
}