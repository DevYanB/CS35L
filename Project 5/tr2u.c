#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv){
  if(argc != 3){ //reason for 3 is that the file for input is to be taken as an arguement
    fprintf(stderr, "Error, incorrect number of arguements passed to function");
    exit(1);
  }

  char* from = argv[1];
  char* to = argv[2];

  if(strlen(from) != strlen(to)){
    fprintf(stderr, "Error, lengths of strigns to transform/result in transform are of mism\
atched length");
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
  // int currChar = getchar();
  char currChar[1]; //makes one char character buff for temporary staging of stdinput char
  int check = read(0, currChar, 1);
  while(check > 0){
    for(int z = 0; z < strlen(from); z++){
      if(currChar[0] == from[z]){
        currChar[0] = to[z];
        break;
      }
    }
    //putchar(currChar);
    write(1,currChar,1);
    //currChar = getchar();
    check = read(0,currChar,1);
  }
  return 0;
}
