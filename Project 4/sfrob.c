#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const* a , char const* b){
  int a_I = 0; int b_I = 0; 
  while( (a[a_I] != ' ') && (b[b_I] != ' ')){
    if ((a[a_I] ^ 0x2A) > (b[b_I] ^ 0x2A))
      return 1; 
    else if ((a[a_I] ^ 0x2A) < (b[b_I] ^ 0x2A))
      return -1;
    a_I++; b_I++;
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


int main(void) {
  char* word = (char*)malloc(0);
  int wordIndex = 0;

  char** allwords = (char**)malloc(0);
  int allwordsIndex = 0;

  char currentchar = ' ';
  while (!ferror(stdin))
{
      //Getting each char value from input and seeing if it is valid                                                          

      currentchar = getchar();
      
      if(ferror(stdin)){
	fprintf(stderr,"Error while parsing");
	exit(1);
      }

      //ferror checks for errors from (), which represents input location
      if(currentchar == EOF)
        break;
      if((currentchar == ' ') && (wordIndex == 0))
        continue;

      //allocating space after new addition  
      word = realloc(word, (wordIndex + 1)* sizeof(char));
      word[wordIndex] = currentchar;
      if(word == NULL) {
        free(word);
        fprintf(stderr, "Cannot reallocate memory for chars");
        exit(1);
      }
      wordIndex++;


      //REallocate new space when at the end of a current word for new word

      if(currentchar == ' ')
        {
          allwords = realloc(allwords, (allwordsIndex + 1) * sizeof(char*));
          allwords[allwordsIndex] = word;
          if(allwords == NULL) {
            free(allwords);
            fprintf(stderr, "Cannot reallocate memory for pointers");
            exit(1);
          }
          allwordsIndex++;
          word = (char*)malloc(0);
          wordIndex = 0;
        }
    }
                                                                                                        
  if(wordIndex != 0) {
    word = realloc(word, (wordIndex +1)* sizeof(char));
    word[wordIndex] = ' ';
    if(word == NULL) {
      free(word);
      fprintf(stderr, "Cannot reallocate memory for chars");
      exit(1);
    }
    wordIndex++;
    allwords = realloc(allwords, (allwordsIndex +1)* sizeof(char*));
    allwords[allwordsIndex] = word;
    if(allwords == NULL) {
      free(allwords);
      fprintf(stderr, "Cannot reallocate memory for chars");
      exit(1);
    }
    allwordsIndex++;
    word = (char*)malloc(0);
    wordIndex = 0;
  }

  qsort(allwords, allwordsIndex, sizeof(char*), frobHelper);

    
  int i = 0;
  for (; i < allwordsIndex; i++) //goes per word
    {
      int j = 0;
      for (; allwords[i][j] != ' '; j++)
        {
            putchar(allwords[i][j]);//prints chars in a word; like in 33, i + j + charSize
        }
      putchar(' ');
    }

  free(allwords);
}
