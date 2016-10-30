#include <stdlib.h>
#include <stdio.h>

#define HEAP_SIZE 100

int64_t * jumpUp_Knuth(int64_t *);
int64_t * jumpDown_Knuth(int64_t *);
char * alloc_Knuth(char *,int64_t *, int);

//Initialize the starting point of the array
void init_heap(char heap[]){
  int64_t * metadata = (int64_t *) heap;
  *metadata = (HEAP_SIZE/4) - 4;

  metadata = (int64_t *) (heap + HEAP_SIZE - sizeof(int64_t));
  *metadata = (HEAP_SIZE/4) - 4;
}

//Allocate requested memory
char *my_malloc(char heap[], int numbytes) {
  printf("My malloc called\n");

  int64_t * metadata_ptr = (int64_t *) (heap + HEAP_SIZE);
  metadata_ptr--;

  int32_t numWords = numbytes / 4;
  if(numbytes % 4 > 0) {
    numWords++;
  }

  while((char *) metadata_ptr > heap) {
    if(*metadata_ptr > 0) {
      if(*metadata_ptr >= numWords) {
        return alloc_Knuth(heap, metadata_ptr, numWords);
      }
    }

    metadata_ptr = jumpUp_Knuth(metadata_ptr);
  }


  printf("Sorry nothing is available!\n");
  return NULL;
}

//Deallocate requested memory
void my_free(char slab[], char *p) {

  //make sure I'm within the boundaries when I jumpDown or jumpUp
  int64_t * lower_bound = (int64_t *) (slab + HEAP_SIZE);
  int64_t * upper_bound = (int64_t *) slab;

  int64_t * metadata_ptr;
  int32_t * word_ptr;
  int64_t sizeKnuth;

  metadata_ptr = (int64_t *) p;
  metadata_ptr--;

  sizeKnuth = (-1 * (*metadata_ptr)) + 2;

  metadata_ptr--;

  if(metadata_ptr > upper_bound && *metadata_ptr > 0) {
    sizeKnuth = sizeKnuth + *metadata_ptr + 4;
  }

  metadata_ptr++;
  metadata_ptr = jumpDown_Knuth(metadata_ptr);

  if(metadata_ptr < lower_bound && *metadata_ptr > 0) {
    sizeKnuth = sizeKnuth + *metadata_ptr + 4;
    metadata_ptr = jumpDown_Knuth(metadata_ptr);
  }

  metadata_ptr--;

  *metadata_ptr = sizeKnuth - 2;
  word_ptr = (int32_t *) metadata_ptr;
  word_ptr -= sizeKnuth;
  metadata_ptr = (int64_t *) word_ptr;
  *metadata_ptr = sizeKnuth - 2;

}

int64_t * jumpUp_Knuth(int64_t * MD_ptr) {

  int32_t * word_ptr;
  int64_t * return_ptr;
  int64_t temp = *MD_ptr;

  if(temp < 0) {
    temp ^= -1;
    temp++;
  }

  word_ptr = (int32_t *) MD_ptr;
  word_ptr -= temp;

  return_ptr = (int64_t *) word_ptr;

  return return_ptr - 2;

}

int64_t * jumpDown_Knuth(int64_t * MD_ptr) {

  int32_t * word_ptr;
  int64_t * return_ptr;
  int64_t temp = *MD_ptr;

  if(temp < 0) {
    temp ^= -1;
    temp++;
  }

  word_ptr = (int32_t *) (MD_ptr + 1);
  word_ptr += temp;

  return_ptr = (int64_t *) word_ptr;

  return return_ptr + 1;

}

char * alloc_Knuth(char * heap, int64_t * MD_ptr, int numWords) {

  int32_t * word_ptr;
  char * return_ptr;
  int64_t temp;

  temp = *MD_ptr;
  *MD_ptr = numWords * -1;                        //initialize the bottom metadata of the allocated block

  word_ptr = (int32_t *) MD_ptr;
  word_ptr -= numWords;
  return_ptr = (char *) word_ptr;                 //allocate space for the block and save the pointer of the block

  MD_ptr = (int64_t *) word_ptr;
  MD_ptr--;
  *MD_ptr = numWords * -1;                        //initialize the top metadata of the allocated block
  MD_ptr--;

  if((char *) MD_ptr < heap) return return_ptr;   //the heap is full so you don't need to rescale prev block.
  if(*MD_ptr < 0) return return_ptr;              //the knuth block does not need rescaling bc it fit perfectly.

  temp = temp - numWords - 4;                     //****** REDEFINING TEMP ******
  *MD_ptr = temp;

  word_ptr = (int32_t *) MD_ptr;
  word_ptr -= temp;
  MD_ptr = (int64_t *) word_ptr;
  MD_ptr--;
  *MD_ptr = temp;                                 //rescale the prev allocated block

  return return_ptr;
}
