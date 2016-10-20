
#define _CRT_SECURE_NO_WARNINGS 1 // this #define is for VS2012, which doesn't like the standard C library

#include <stdio.h> // declaraations of standard input/output functions
#include <stdint.h> // declarations of standard integer types (e.g., int32_t)
#include <stdlib.h> // declarations of general functions in the standard library (e.g., abort, exit)


#define ONE_MB (1 << 20)
#define BUFFER_SIZE ONE_MB

char dictionary[BUFFER_SIZE]; // a large buffer to hold a dictionary (1MB)
char article[BUFFER_SIZE]; // a large buffer to hold an article (1MB)

void spellCheck(char[], char[]); // this is the function you write (put your function in Project1.cpp

/*
 * Read a .txt file into one of the two buffers
 * this function does NOT confirm that the file is correctly formatted
 */
void readFile(const char file_name[], char buffer[]) {
	FILE* file = fopen(file_name, "r");
	if (file == 0) {
		printf("unable to open file \"%s\"\n", file_name);
		abort();
	}

	/* clear (set to zeros) the buffer */
	for (uint32_t k = 0; k < BUFFER_SIZE; k += 1) {
		buffer[k] = 0;
	}

	/* read the file (this is a binary read, which is OK) */
	uint32_t bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
	buffer[bytes_read] = 0;
}

void fruityTest(void) {
	printf("\n\n******* Starting Base Test #1 (fruity) *******\n");
	char dictionary[] = "apple\nbanana\norange\npear\n";
	char article[] = "I ate an apple and a pear\n";
	spellCheck(article, dictionary); // should print: ate, an, and
	printf("****DONE****\n");
}

void dogTest(void) {
	printf("\n\n******* Starting Base Test #2 (dogs) *******\n");
	char dictionary[] = "Beagle\nBulldog\nCollie\nPoodle\nretriever\n";
	char article[] = "bulldog dalmation beagle Retriever poodles";
	spellCheck(article, dictionary); // should print: dalmation poodles
	printf("****DONE****\n");
}

void punctuationTests(void) {
	printf("\n\n******* Starting Base Test #3 (punctuation) *******\n");
	char dictionary[] = "but\ncan\ncan't\ndo\ndon't\nthink\nOh'fire\n"; // the dictionary can contain punctuation
	char article[] = "I think I can fire , but I can't. I think I do, but I don't";
	spellCheck(article, dictionary); // should print: fire don
	printf("****DONE****\n");
}

void generalTest1(void) {
	printf("\n\n******* Starting General Test #1 *******\n");
	readFile("greek-finances.txt", article);
	readFile("american-english.txt", dictionary);
	spellCheck(article, dictionary);
	printf("****DONE****\n");
}

void generalTest2(void) {
	printf("\n\n******* Starting General Test #2 *******\n");
	readFile("bobsledding.txt", article);
	readFile("american-english.txt", dictionary);
	spellCheck(article, dictionary);
	printf("****DONE****\n");
}
void generalTest3(void) {
	printf("\n\n******* Starting General Test #3 *******\n");
	readFile("greek-finances.txt", article);
	readFile("american-english.txt", dictionary);
	spellCheck(article, dictionary);
	printf("****DONE****\n");
}

void crazyTest1(void){
	printf("\n\n******* Starting Crazy Test #1 (Stuff) *******\n");
	readFile("american-english.txt", dictionary);
	char article[] = " 10 hellsing 100years ago, I knew how 2 spell #ss# and A-Z!";
	spellCheck(article, dictionary); // should print: hellsing ss
	printf("****DONE****\n");

}
void crazyTest2(void){
	printf("\n\n******* Starting Crazy Test #2 (Numbers) *******\n");
	readFile("american-english.txt", dictionary);
	char article[] = "817847327184hello3918948184world4819347817abcd";
	spellCheck(article, dictionary); // should print: abcd
	printf("****DONE****\n");

}
void crazyTest3(void){
	printf("\n\n******* Starting Crazy Test #3 (Punctuations) *******\n");
	char dictionary[] = "live\nOh'fire\nfirefly";
	char article[] = "live fire";
	spellCheck(article, dictionary); // should print: fire
	printf("****DONE****\n");

}

void customTest1(void) {
	printf("\n\n******* Starting Custom Test #1 (Extra Credit) *******\n");
	char dictionary[] = "live\nOh'fire\nfirefly";
	char article[] = "fire live fire fire live";
	spellCheck(article, dictionary); // should print: fire
	printf("****DONE****\n");
}


/* you should also make your own tests! */
int main(void) {
    /* for starters, uncomment the following tests, one at a time */

  fruityTest();
  dogTest();
  punctuationTests();
  generalTest1();
  generalTest2();
	generalTest3();
	crazyTest1();
	crazyTest2();
	crazyTest3();
	customTest1();
}
