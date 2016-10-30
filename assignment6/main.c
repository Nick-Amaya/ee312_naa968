#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define MEM_SIZE  100

void init_heap(char slab[]);
char *my_malloc(char slab[], int numbytes);
void my_free(char slab[], char *p);

void printSlab(char slab[], int slab_size) {

  for(int i = 0; i < slab_size; i++) {
    if(i % 4 == 0) {
      printf("---------------- (%d)\n", i / 4);
    }
    printf("0x%.2x\n", (unsigned char) slab[i]);
  }
  printf("----------------\n");

}

int main() {

  //char slab[MEM_SIZE]= {0}; // Memory that's being used
  char test_slab[MEM_SIZE] = {0};
  char * a;
  char * b;
  char * c;
  char * d;
  char * e;

  init_heap(test_slab);

  a = my_malloc(test_slab, 7);  //2 words
  b = my_malloc(test_slab, 3);  //1 word
  c = my_malloc(test_slab, 10); //3 words
  d = my_malloc(test_slab, 12); //3 words
  //e = my_malloc(test_slab, 5);  //2 words

  *a = 0x08;
  *b = 0x12;
  *c = 0x03;
  *d = 0x07;

  //my_free(test_slab, a);
  my_free(test_slab, b);
  //my_free(test_slab, c);
  my_free(test_slab, d);

  b = my_malloc(test_slab, 10);

  *b = -0x02;

  printSlab(test_slab, MEM_SIZE);
  //Check if ptr is null!
}
