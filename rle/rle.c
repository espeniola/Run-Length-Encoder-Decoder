#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXCHAR 1000


char* decode(char* src)
{
	int rLen;
	char count[3];
	char chr;
	int len = strlen(src);

	char* dest = (char*)malloc(sizeof(char) * (len * 100 + 1));


	int i, j = 0, k = 0;

	for (i = 0; i < len; i++) {

		chr = src[i];

		while (i + 1 < len && ((int)(src[i + 1])) < 64) {
			count[k] = src[i + 1];
			i++;
			k++;
		}

		sscanf_s(count, "%d", &rLen);

		for (int l = j; l < j + rLen; ++l) {
			dest[l] = chr;
		}

		j += rLen;

		k = 0;

	}
	dest[j] = '\n';
	dest[j + 1] = '\0';
	return dest;
}

char* encode(char* src)
{
	int rLen;
	char count[MAXCHAR];
	int len = strlen(src);

	char* dest = (char*)malloc(sizeof(char) * (len * 5 + 1));

	int i, j = 0, k;

	for (i = 0; i < len; i++) {

		dest[j++] = src[i];

		rLen = 1;

		while (i + 1 < len && src[i] == src[i + 1]) {
			rLen++;
			i++;
		}

		if (src[i] != '\n') {
			sprintf_s(count, MAXCHAR, "%d", rLen);

			for (k = 0; *(count + k); k++, j++) {
				dest[j] = count[k];
			}
		}

	}

	dest[j] = '\0';
	return dest;
}




void fileOperations(char type) {



	FILE* filePointer;

	char* girisFilePtr = "giris.txt";
	char* sikistirilmisFilePtr = "sikistirilmis.txt";
	char* cikisFilePtr = "cikis.txt";

	char* encodeArr[MAXCHAR];
	char* decodeArr[MAXCHAR];
	char str[MAXCHAR];

	int i = 0;
	int line = 0;

	if (type == 'e') {
		fopen_s(&filePointer, girisFilePtr, "r");
		if (filePointer == NULL) {
			printf("Could not open file %s", girisFilePtr);
			printf("\nTry again");
		}
		else {
			while (fgets(str, MAXCHAR, filePointer) != NULL) {
				*(encodeArr + i) = encode(str);
				i++;
				line++;
			}
			fclose(filePointer);
			fopen_s(&filePointer, sikistirilmisFilePtr, "w");
			for (int j = 0; j < line; j++) {
				fputs(*(encodeArr + j), filePointer);
			}
		}
	}
	else
	{
		fopen_s(&filePointer, sikistirilmisFilePtr, "r");
		if (filePointer == NULL) {
			printf("Could not open file %s", sikistirilmisFilePtr);
			printf("\nTry again");
		}
		else
		{
			while (fgets(str, MAXCHAR, filePointer) != NULL) {
				*(decodeArr + i) = decode(str);
				i++;
				line++;
			}
			fclose(filePointer);
			fopen_s(&filePointer, cikisFilePtr, "w");
			for (int j = 0; j < line; j++) {
				fputs(*(decodeArr + j), filePointer);
			}
			fclose(filePointer);
		}
	}



}



int main() {

	char processType;
	printf("Select the process type you want to get \n e for encoding \n d for decoding ...\n");
startAgain:
	scanf_s("%c", &processType);

	if (processType == 'e') {
		fileOperations(processType);
		//encode();
	}
	else if (processType == 'd') {
		fileOperations(processType);
	}
	else {
		printf("Invalid selection. Choose e (encoding) or d (decoding) ... \n");
		goto startAgain;
	}
	return 0;


}