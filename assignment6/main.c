#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define MEM_SIZE  10000

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

  char slab[MEM_SIZE]= {0}; // Memory that's being used
  char * a;
  char * b;
  char * c;
  char * d;
  char * e;

  init_heap(slab);

  a = my_malloc(slab, 20);  //2 words
  b = my_malloc(slab, 81);

  *a = 0x01;
  *b = 0x02;
  *(b + 4) = 0x90;

  my_free(slab, a);

  printSlab(slab, MEM_SIZE);
  //Check if ptr is null!
}
