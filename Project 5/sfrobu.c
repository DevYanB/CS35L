#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <ctype.h>
#include <unistd.h>
#include <getopt.h>

int fFlag = 0;

int frobcmp(char const* a , char const* b){
  int a_I = 0; int b_I = 0; 
  while((a[a_I] != ' ') && (b[b_I] != ' ')){
    if ((a[a_I] ^ 0x2A) > (b[b_I] ^ 0x2A)){
      return 1;
    }
    else if ((a[a_I] ^ 0x2A) < (b[b_I] ^ 0x2A)){
      return -1;
    }
    a_I++; 
    b_I++;
  }
  if(a[a_I] != ' ')
    return 1; 
  else if(b[b_I] != ' ')
    return -1;
  else
    return 0; 
}

int frobcmpUpper(char const* a , char const* b){
  int a_I = 0; int b_I = 0;
  while((a[a_I] != ' ') && (b[b_I] != ' ')){
    if ((a[a_I] ^ 0x2A) > (b[b_I] ^ 0x2A)){
      return 1;
    }
    else if ((a[a_I] ^ 0x2A) < (b[b_I] ^ 0x2A)){
      return -1;
    }
    a_I++;
    b_I++;
  }
  if(a[a_I] != ' ')
    return 1;
  else if(b[b_I] != ' ')
    return -1;
  else
    return 0;
}

int frobHelper(const void* input1, const void* input2){
  const char* s = *(const char**)input1;
  const char* t = *(const char**)input2;
  return frobcmp(s,t);
}

int frobHelperUpper(const void* input1, const void* input2){
  const char* s = *(const char**)input1;
  const char* t = *(const char**)input2;
  return frobcmpUpper(s,t);
}

int main(int argc, char** argv){
  if(argc > 2){
    fprintf(stderr , "Error, number of arguements incorrect, only allow -f");
  }
  if((argc == 2) && (strcmp(argv[0], "-f") == 0)){
    fFlag = 1;
  }

struct stat file;
    
if(fstat(0, &file) < 0){
  fprintf(stderr, "Error, can't read file");
  exit(1);
 }

char* word = (char*)malloc(sizeof(char));
int wordIndex = 0;

char** allWords = (char**)malloc(sizeof(char*));
int allWordsIndex = 0;

char currChar = ' ';
char nextChar = ' ';
char* temp;
if(S_ISREG(file.st_mode)){
    temp = (char*)malloc(sizeof(char)*file.st_size+1);
    read(0, temp, file.st_size);
    //Looking at two at once, thats why +1 abv
    currChar = temp[0];
    nextChar = temp[1];
    int i = 2;
    for(; i < file.st_size+2; i++){ //to account for going +1
	word[wordIndex] = currChar;
	char* strAlloc = realloc(word, sizeof(char)*(wordIndex+2));
	if(strAlloc == NULL) {
	  fprintf(stderr, "Error, can't reallocate memory for chars");
	  exit(1);
	}
    else{
	  word = strAlloc;
    }

	if(currChar == ' '){
	    allWords[allWordsIndex] = word;
	    char** toAlloc = realloc(allWords, (allWordsIndex + 2) * sizeof(char*));

	    if(toAlloc == NULL) {
	      fprintf(stderr, "Error, can't reallocate memory for pointers");
	      exit(1);
	    }
	    else {
	      allWords = toAlloc;
        }
        
	    allWordsIndex++;
	    word = NULL; 
	    word = (char*)malloc(sizeof(char));

	    if(word == NULL) {
	      fprintf(stderr, "Error, null");
	      exit(1);
	    }
	    wordIndex = -1;
	  }

    if((currChar == ' ') && (i >= file.st_size)){
	  break;
    }
	else if((currChar != ' ') && (i >= file.st_size)){
	  currChar = ' ';
      wordIndex++;
      continue;
    }
	currChar = temp[i];
	nextChar = temp[i+1];
    wordIndex++;
    }
  }

word = NULL;
word = (char*)malloc(sizeof(char));

int inpFst = read(0, &currChar, 1);
int inpSnd = read(0, &nextChar, 1);

wordIndex = 0;

while(1){
      
  word[wordIndex] = currChar;
  char* tempVar = realloc(word, (wordIndex +2)* sizeof(char));

  if(tempVar == NULL) {
    fprintf(stderr, "Error, can't reallocate memory for chars");
    exit(1);
  }
  else{
    word = tempVar;
  }

  if(currChar == ' ') {

    allWords[allWordsIndex] = word;
    char** toAlloc  = realloc(allWords, (allWordsIndex + 2)* sizeof(char*));
    if(toAlloc == NULL) {
      fprintf(stderr, "Error, can't reallocate memory for chars");
      exit(1);
    }
    else{
      allWords = toAlloc;
    }
      
    allWordsIndex++;
     word = NULL;
    word = (char*)malloc(sizeof(char));

    if(word == NULL){
      fprintf(stderr, "Error, null"); exit(1);
    }
    wordIndex = -1;
  }


  if(currChar == ' ' && inpSnd < 1){
      break;
    }
  else if (currChar != ' ' && inpSnd < 1) {
    currChar = ' '; wordIndex++; continue;
  }
  currChar = nextChar;
  inpSnd = read(0, &nextChar, 1);
  wordIndex++;
 }

if(fFlag == 1) {
  qsort(allWords, allWordsIndex, sizeof(char*), frobHelperUpper);
}
else{
   qsort(allWords, allWordsIndex, sizeof(char*), frobHelper);
}


int tC = 0;
while (tC < allWordsIndex){
    int j = -1;
    while (allWords[tC][j] != ' '){
	j++;
	write(1,&allWords[tC][j],1);
    }
    tC++;
  }
int count = 0;
for(; count < allWordsIndex; count++) {
    free(allWords[count]); 
}
free(allWords);
free(temp);
exit(0); 
}
