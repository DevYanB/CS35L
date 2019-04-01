#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char** argv){
  if(argc != 3){ //reason for 3 is that the file for input is to be taken as an arguement
    fprintf(stderr, "Error, incorrect number of arguements passed to function");
    exit(1);
  }
  
  char* from = argv[1];
  char* to = argv[2];

  if(strlen(from) != strlen(to)){
    fprintf(stderr, "Error, lengths of strigns to transform/result in transform are of mismatched length");
    exit(1);
  }
  
  for(int i = 0; i < strlen(from); i++){
    for(int j = i + 1; j < strlen(from); j++){
      if(from[i] == from[j]){
	fprintf(stderr, "Error, duplicate character in from string");
	exit(1);
      }
    }
  }
  int currChar = getchar();
  while(currChar != EOF){
    for(int z = 0; z < strlen(from); z++){
      if(currChar == from[z]){
	currChar = to[z];
	break;
      }
    }
      putchar(currChar);
      currChar = getchar();
  }
  return 0;
}
