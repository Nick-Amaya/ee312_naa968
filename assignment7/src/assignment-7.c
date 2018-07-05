
/*	Amaya Nicholas
 *	naa968
 *  16300
 *	EE 312-Assignment 7
*/

#include <stdio.h>
#include <string.h>

#define STRLEN 50
#define NUMSTR 50

void _generateAllMatchedParens(int, int, int, char *);
int _generateAllPalindromicDecompositions(char[], char[][STRLEN], int);
int isSymmetric(char[]);

void generateAllMatchedParens(int n){
	//Function needs to generate all matched parens as described in the assignment
	if(n >= 0) {
		char paren_str[20];
		_generateAllMatchedParens(n, 0, 0, paren_str);

	} else {
		printf("Please enter a valid number.\n");
	}
}

void generateAllPalindromicDecompositions(char str[]){
	char output[NUMSTR][STRLEN];
	_generateAllPalindromicDecompositions(str, output, 0);
}



void _generateAllMatchedParens(int NL, int NR, int pos, char * str) {

	if(NL == 0 && NR == 0) {
		for(int k = 0; k < pos; k++) {
			printf("%c", str[k]);
		}
		printf("\n");
	}

	if(NL > 0) {
		str[pos] = '(';
		_generateAllMatchedParens(NL - 1, NR + 1, pos + 1, str);
	}
	if(NR > 0) {
		str[pos] = ')';
		_generateAllMatchedParens(NL, NR - 1, pos + 1, str);
	}
}

int _generateAllPalindromicDecompositions(char str[], char output[][STRLEN], int output_index) {

	if(str[0] == '\0') {
		return 1;
	}

	char temp[STRLEN];
	int i, j, k;
	int pos = 1;
	int len = strlen(str);

	for(k = 0; k < len; k++) {

		for(i = 0; i < pos; i++) {
			temp[i] = str[i];
		}
		temp[i] = '\0';

		if(isSymmetric(temp)) {

			strcpy(output[output_index], temp);

			j = 0;
			for(i = pos; i < len; i++){
				temp[j] = str[i];
				j++;
			}
			temp[j] = '\0';

			if(_generateAllPalindromicDecompositions(temp, output, output_index + 1)) {
				for(int l = 0; l <= output_index; l++) {
					printf("%s ", output[l]);
				}
				printf("\n");
			}
		}

		pos++;
	}
	return 0;
}

int isSymmetric(char str[]) {
	char rev_str[STRLEN];
	int i = 0;
	for(int k = strlen(str) - 1; k >= 0; k--) {
		rev_str[i] = str[k];
		i++;
	}
	rev_str[i] = '\0';

	if(!strcmp(rev_str, str)) {
		return 1;
	}

	return 0;
}
