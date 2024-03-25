#include <stdlib.h>
#include <stdio.h>

/**
 * Prints metadata of bitmap file (Task 1).
 * input: Pointer to a bitmap file opened for reading.
 */
void print_metadata(FILE *input){
  // TODO: Implement function.
}

/**
 * Inverts image of a bitmap file and saves the inverted image to a new bitmap
 * file named "output.bmp" (Task 2).
 * input: Pointer to a bitmap file opened for reading
 */
void invert_bitmap(FILE *input){
  // TODO: Implement function.
}

int main(int argc, char **argv) {
  // open input file for binary reading
  FILE *input;
  input = fopen(argv[1],"rb");
  
  // call function to print metadata (Task 1).
  print_metadata(input);
  
  // call function to invert image (Task 2).
  invert_bitmap(input);

  // close input file
  fclose(input);
    
  return 0;
}