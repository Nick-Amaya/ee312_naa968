/*
 * Nicholas Amaya
 * naa968
 * 16300
 * assignment5.c
 * SpellCheck
 * Oct. 19, 2016
 */

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types
#include <stdlib.h>

#define MAX_WORDLEN     30
#define MAX_DICTLEN     200000
#define MAX_WORDSINART  10000

/* All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)
 *
 * Many students find it helpful to declare global variables (often arrays). You are welcome to use
 * globals if you find them helfpul. Global variables are by no means necessary for this project.
 */

 /*typedef struct node {
	 char word[MAX_WORDLEN];
	 struct node * next;
 } Node; */

/* You must write this function (spellCheck). Do not change the way the function is declared (i.e., it has
 * exactly two parameters, each parameter is a standard (mundane) C string (see SpellCheck.pdf).
 * You are expected to use reasonable programming style. I strongly encourage you to avoid big functions
 * (while there are always exceptions, a good rule of thumb is about 15 lines in a function).
 * So, plan on implementing spellCheck by writing two or three other "support functions" that
 * help make the actual spell checking easier for you.
 * There are no explicit restictions on using functions from the C standard library. However,
 * for this project you should avoid using functionality from the C++ standard libary. You will
 * almost certainly find it easiest to just write everything you need from scratch!
 */


 //*******************************************

 /*void appendChar(char * ptr, size_t * ptr_size, char data) {
	 realloc(ptr, *ptr_size + 1);
	 ptr[*ptr_size] = data;
	 (*ptr_size)++;
 }

 void deallocChar(char * ptr, size_t * ptr_size) {

	 if(*ptr_size == 1) {
		 *ptr = '\0';
		 (*ptr_size)--;
	 }
	 if(*ptr_size > 1) {
		 realloc(ptr, *ptr_size - 1);
		 (*ptr_size)--;
	 }
 } */

char toLowerCase(char character) {
	 if(character >= 65 && character <= 90) {
		 return character + 32;
	 }

	 if(character >= 97 && character <= 122) {
 		return character;
 	 }

	return -1;
 }

int isLetter(char character) {
	if(character >= 65 && character <= 90) {
		return 1;
	}

	if(character >= 97 && character <= 122) {
		return 1;
	}

	return 0;
}


/* Identify words in the article given.
 * Word defined as :
 *
 * Output: dynamically allocated string of words delimited by the null character.
 * Returns the size of the array
 */
size_t identifyWords(char output[][MAX_WORDLEN], char article[]) {
	int wordflg, count, temp_index;
  unsigned int art_index;
  size_t output_index;
	wordflg = count = art_index = output_index = temp_index = 0;

	char character = article[art_index];
	while(character != '\0') {

		if(isLetter(character)) {
			character = toLowerCase(character);
			if(!wordflg) {
				wordflg = 1;
			}
      output[output_index][temp_index++] = character;
			count++;

		} else {
			if(wordflg) {
				wordflg = 0;
				if(count > 1) {
                    output[output_index++][temp_index] = '\0';
				}
                temp_index = 0;
				count = 0;
			}
		}

		character = article[++art_index];
	}


  if(wordflg) {
    if(count > 1) {
      output[output_index++][temp_index] = '\0';
    }
  }

  output[output_index][0] = '\0';
  return output_index;
}

size_t strtoArr(char array[][MAX_WORDLEN], char * str) {
  unsigned int str_index, temp_index;
  size_t arr_index;
	str_index = temp_index = arr_index = 0;

	char character = str[str_index];
	while(character != '\0') {

		switch(character) {
			case '\n':
        array[arr_index][temp_index] = '\0';
				temp_index = 0;
        arr_index++;
				break;

			default:
        character = toLowerCase(character);
				array[arr_index][temp_index++] = character;
				break;
		}

		character = str[++str_index];
	}
  array[arr_index][0] = '\0';

  return arr_index;
}

void printDict(char dict[][MAX_WORDLEN]) {
  int dict_index = 0;
  int word_index = 0;
  while(dict[dict_index][0] != '\0') {
    while(dict[dict_index][word_index] != '\0') {
      printf("%c", dict[dict_index][word_index]);
      word_index++;
    }
    printf("\n");
    dict_index++;
    word_index = 0;
  }
}

void strCPY(char * dest, char * src) {

  int index = 0;
  while(dest[index] != '\0') {
    dest[index++] = '\0';
  }

  index = 0;
  do {
    dest[index] = src[index];
    index++;
  } while(src[index] != '\0');

  dest[index] = '\0';
}

int strCMP(char * str1, char * str2) {
  int str_index;

  for(str_index = 0; str1[str_index] != '\0'; str_index++) {
    if(str1[str_index] < str2[str_index]) {
      return -1;
    }
    if(str1[str_index] > str2[str_index]) {
      return 1;
    }
  }
  if(str2[str_index] != str1[str_index]) {
    return -1;
  }
  return 0;
}

int binarySearch(int lower_bound, int upper_bound, char sorted_list[][MAX_WORDLEN], char target[]) {
  int mid, cmp;
  if(upper_bound < lower_bound) {
    return -1;
  }

  mid = (upper_bound + lower_bound) / 2;
  cmp = strCMP(target, sorted_list[mid]);

  if(cmp == 0) {
    return mid;
  } else if(cmp < 0) {
    return binarySearch(lower_bound, mid - 1, sorted_list, target);
  } else if (cmp > 0) {
    return binarySearch(mid + 1, upper_bound, sorted_list, target);
  }

  return -2;
}

int linearSearch(char list[][MAX_WORDLEN], size_t list_size, char target[]) {
  for(int i = 0; i < list_size; i++) {
    if(strCMP(target, list[i]) == 0)
      return i;
  }
  return -1;
}

void findMsWords(char MSwords[][MAX_WORDLEN], char words[][MAX_WORDLEN], size_t words_size, char dictionary[][MAX_WORDLEN], size_t dict_size) {
  int isMS, isNOTDup, MSwords_index;
  isMS = isNOTDup = MSwords_index = 0;

  int words_index;
  for(words_index = 0; words_index < words_size; words_index++) {
    isMS = binarySearch(0, dict_size - 1, dictionary, words[words_index]);
    if(isMS == -1) {
      isNOTDup = linearSearch(MSwords, MSwords_index, words[words_index]);
      if(isNOTDup == -1) {
        strCPY(MSwords[MSwords_index++], words[words_index]);
      }
    }
  }
  MSwords[MSwords_index][0] = '\0';
}



//TODO:
void spellCheck(char article[], char dictionary[]) {

    char words[MAX_WORDSINART][MAX_WORDLEN];
  char MSwords[MAX_WORDSINART][MAX_WORDLEN];
  char dictionaryArr[MAX_DICTLEN][MAX_WORDLEN];

	size_t words_size = identifyWords(words, article);
  size_t dict_size = strtoArr(dictionaryArr, dictionary);

  findMsWords(MSwords, words, words_size, dictionaryArr, dict_size);
  printDict(MSwords);

}
