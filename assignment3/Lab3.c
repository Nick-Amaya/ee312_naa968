#include <stdio.h>

int max[20];

/*
 * return 1 if the ASCII interpretation of
 * c is an upper case letter.
 * return 0 otherwise
 */
int isUpperCase(char c) {
	if (c >= 'A' && c <= 'Z') {
		return 1;
	} else {
		return 0;
	}
}

/*
 * return 1 if the ASCII interpretation of
 * c is a lower case letter.
 * return 0 otherwise
 */
int isLowerCase(char c) {
	if (c >= 'a' && c <= 'z') {
		return 1;
	} else {
		return 0;
	}
}

/*
 * return 1 c is an Alphabet.
 * return 0 otherwise
 */
int isAlphabet(char c){
	return isUpperCase(c) || isLowerCase(c);
}

/*
 * if the ASCII interpretation of c is a letter, then
 * return a number between 0 and 25 indicating which letter of
 * the alphabet c represents.  For example, if c is the ASCII
 * encoding for 'A', then we should return 0.  If c is the
 * ASCII encoding for 'e', then we should return 4.
 * if the ASCII interpretation of c is not a letter, then
 * return -1.
 */
int ASCII2Int(char c) {
	if (isUpperCase(c)) {
		return c - 'A';
	} else if (isLowerCase(c)) {
		return c - 'a';
	} else {
		return -1;
	}
}

/*
* assumes i is between 0 and 25 inclusive
*/
char int2UpperCase(int i){
	char c = 'A'+i;
	return c;
}

/*
* assumes i is between 0 and 25 inclusive
*/
char int2LowerCase(int i){
	char c = 'a'+i;
	return c;
}

/*
 * This function shifts a message shift number of times to the right or the left.
 * shifts left if dir == 1
 * shifts right if dir == 0
*/
void rotate(char message[], int messageLength, int shift, int dir) {

	if(dir > 1 || dir < 0) return;

	int i;
	int ASCIIoffset;

	for(i = 0; i < messageLength; i++) {

		if(isUpperCase(message[i])) {
			ASCIIoffset = 'A';
		} else if(isLowerCase(message[i])) {
			ASCIIoffset = 'a';
		} else {
			//not in the alphabet
			ASCIIoffset = 0;
		}

		if(ASCIIoffset) {
			if(dir) {
				//shift letter to the left "shift" number of times
				message[i] = message[i] - ASCIIoffset - shift;
				if(message[i] < 0) {
					message[i] += 26;
				}

			} else {
				//shifts letter to the right "shift" number of times
				message[i] = ((message[i] - ASCIIoffset + shift) % 26);
			}
			message[i] += ASCIIoffset;
		}
	}
}


/*
* This function takes in a message and computes the frequencies of all the alphabets
*/
void buildHistogram(char message[], int messageLength, int histogram[], int histogramLength) {

	int index = 0;
	int ASCIIoffset = 1;

	//empty histogram
	for(int i = 0; i < 26; i++) {
		histogram[i] = 0;
	}

	//construct histogram
	while(index < messageLength) {
		if(isUpperCase(message[index])) {
			ASCIIoffset = 'A';
		} else if(isLowerCase(message[index])) {
			ASCIIoffset = 'a';
		} else {
			//not in the alphabet
			ASCIIoffset = 0;
		}

		if(ASCIIoffset) {
			histogram[message[index] - ASCIIoffset]++;
		}
		index ++;
	}
}

/*
* This function computes the maximum value in an array and returns the index location
* for which the maximum value occured
*
* selects which occurance of most frequent letter you want
* returns -1 if user is trying to access an occurence > the the total number of occurences
*/

int maxIndex(int myArray[], int arrayLength, int select){

	int i = 0;
	int max_value = myArray[0];

	//empty max array declared at the top of the file
	for(i = 0; i < 20; i++) {
		max[i] = 0;
	}

	//find the magnitude of max_value
	i = 0;
	while(i < arrayLength) {
		if(myArray[i] > myArray[max[0]]) {
			max_value = myArray[i];
			max[0] = i;
		}
		i++;
	}

	//record the indices of where max_value occurs
	//terminate the array with a negative 1
	int j = 0;
	i = 0;
	while(i < arrayLength) {
		if(myArray[i] == max_value) {
			max[j] = i;
			if(j < 20) {
				j++;
			}
		}
		i++;
	}
	max[j] = -1;

	//return -1 if the user is trying to select an occurence > the number of occurences
	if(select >= j) return -1;

	//return which occurence of max_value the user specifies
	return max[select];
}

/*
 * Encrypt the string s using the rotation cypher
 * Each letter in s should be shifted "shift" letters to the
 * right.  For example, if "shift" is 2, then "a zebra" should be
 * changed to "c bgdtc".  Note that when shifting past the end
 * of the alphabet, we wrap around again to a.
 *
 * Only change the letters in s.  Do not change spaces, punctuation
 * or numbers in s.
 * For full credit, you should keep upper case letters as
 * upper case, and leave lower case letters as lower case.  So, if
 * s had been the string "a ZeBra", you should change s to be
 * "c BgDtc".
 */
void encrypt(char message[], int messageLength, int shift) {

	//shifts message to the left "shift" number of times
	rotate(message, messageLength, shift, 0);
}

/*
 * return a number between 0 and 25 indicating which letter
 * of the alphabet is most common in the string s
 */
int mostFrequentLetter(char message[], int messageLength) {
	/*
	* Build the histogram and get the index of most frequent letter
	*/

	int hsgram[26] = {0};
	buildHistogram(message, messageLength, hsgram, 26);

	maxIndex(hsgram, 26, 0);

	int i = 0;
	int j = 0;
	int ASCIIoffset;
	while(i < messageLength) {
		while(max[j] != -1) {
			if(isUpperCase(message[i])) {
				ASCIIoffset = 'A';
			} else if(isLowerCase(message[i])) {
				ASCIIoffset = 'a';
			} else {
				ASCIIoffset = 0;
			}

			if(ASCIIoffset) {
				if(max[j] == message[i] - ASCIIoffset) {
					return max[j];
				}
			}
			j++;
		}
		j = 0;
		i++;
	}
	return -1;
}

void decrypt(char cypher[],int cypherLength, int common) {

	int hsgram[26] = {0};
	int shift;

	// ****************** calculate the shift to rotate cypher by. ***************
	shift = mostFrequentLetter(cypher, cypherLength) - common;
	if(shift < 0) {
		//shift is always to the right, so if the number is negative that means it wrapped around. so add 26.
		shift += 26;
	}

	//********************* shift the cypher to the left the calculated "shift" number of times ******************
	rotate(cypher, cypherLength, shift, 1);

}
