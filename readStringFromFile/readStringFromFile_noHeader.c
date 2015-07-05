
#include <stdio.h>
#include <stdlib.h>

int getLength(char *str);
char *readWordFromFile(FILE *in, int *checker);


int main (int argc, char **argv) {
	
	
	FILE *in = fopen("input.txt", "r");
	int L = -1;
	int checker = 0;
	int numWords = 0;
	fscanf(in, "%d", &L); // there was an number in the file so i just read over it
	
	while (checker != EOF) {
		char *word = readWordFromFile(in, &checker);
		
		printf("(word): %s\n", word);
		if (word != NULL) numWords++;
	}
	
	printf("Total Number Of Words: %d\n", numWords);
	

	
	fclose(in);
	
	return 0;
}


int getLength(char *str) {
	// this will get the length of string 
	// until '\0'
	int i = 0;
	
	while (str[i] != '\0') i++;
	
	return i; // this is the length of the ACTUAL WORD (without non-whitespace characters ie '\0')
}

char *readWordFromFile(FILE *in, int *checker) {
	
	// create Local Vars
	char *tmpWord = NULL;
	int tmpWordSize = 0;
	int sizeOfWord = 0; // len of word we are reading IN
	int len = 0; // array subscript id
	
	// used for checking special events ie. EOF
	char ch, tmpChar;
	
	// reads over whitespace characters
	while ((ch = fscanf(in, "%c", &tmpChar)) != EOF && (!isalpha(tmpChar)));
	
	// now since we are using checker to 'return' the EOF int
	// we just check to see if EOF has been reached then 
	// return NULL with checker = EOF;
	
	if (ch == EOF) {
		*checker = EOF;
		return NULL;
	}
	
	
	// now remember tmpChar actually has an alpha Character so we 
	// need to save it before going forward;
	
	// this is a whitespace character
	sizeOfWord++;
	tmpWordSize = sizeOfWord;

	// tmpWord is null, create the initall array
				
	tmpWord = (char*)malloc(sizeof(char)*(tmpWordSize)); // allocates the init array
				
	// error checking
	if (tmpWord == NULL) {
		printf("Unable To allocate memory for inital tmpWord Array Store.");
		exit(1);
	}
	
	// now we need to store the current alpha key
	tmpWord[len++] = tmpChar;
	
	
	// basically while is alpha
	while ((ch = fscanf(in, "%c", &tmpChar)) != EOF) {
		
		// we're reading in whitespace characters
		if (isalpha(tmpChar)) {
				
			if (len >= tmpWordSize) {
					
				tmpWordSize = tmpWordSize * 2; // doubles the current temp Store
					
				tmpWord = (char*)realloc(tmpWord, sizeof(char)*(tmpWordSize)); // reallocates the memory
					
				// error checking
				if (tmpWord == NULL) {
					printf("Unable to Allocate Addition Memory for wordArray Reallocation.\n");
					exit(1);
					
				}
					
			}
				
			// Time to store the character found
			tmpWord[len++] = tmpChar;
			
		} else {
			
			// non-whitespace character
			// break while loop
			break;
			
		}
		
	}
	
	// we have an array of characters but it isn't terminated so we do that
	// but we need to do some error checking just to make sure we don't try to
	// access a subscript that doesn't exist;
	if (len < tmpWordSize) // we have space in the array allocated
		tmpWord[len] = '\0';
	else { // we need to allocate some more memory;
		// we will double the memory space and reallocate
		// as we will spend some extra processing to break it down to its specific length;
		
		tmpWordSize = tmpWordSize * 2;
		
		tmpWord = (char*)realloc(tmpWord, sizeof(char)*(tmpWordSize));
		
		if (tmpWord == NULL) {
			printf("Unable to realloc memory to place the string terminator.\n");
			exit(1);
		}
		
		tmpWord[len] = '\0';
	}
	
	// debug
	// printf("String (tmpWord): %s\n", tmpWord);
	
	// now we have the whitespace characters until a non-whitespace character
	// but its store in a really large array, which isn't good. Remember we 
	// did that to reduce the chance of malloc and realloc crashing
	// so now we will create a specific length character array
	// and free the temp string memory
	
	char *newWord = NULL; // our new word Variable
	int lenOfNewWord = getLength(tmpWord); // now remember that we need to add one for the string terminator
	
	// debug
	// printf("Length Of Temporary Word: %d\n", lenOfNewWord);
	
	
	// allocate new array
	newWord = (char*)malloc(sizeof(char)*(lenOfNewWord+1)); // remember to add one for string terminator
	
	// error checking
	if (newWord == NULL) {
		printf("Unable to allocate memory for the new array.\n");
		exit(1);
	}
	
	// okay time to copy data from one array to another;
	int i = 0; // needed to iterate through the array
	
	// transfer
	while (tmpWord[i] != '\0') {
		newWord[i] = tmpWord[i];
		i++;
	}
	
	// i is at the end of the string, but without the string terminator
	// add it back
	newWord[i] = '\0';
	
	// now free the tmpWord ptr memory;
	free(tmpWord);
	
	// also we stored return value for the fscanf inside ch to check
	// for EOF, we can check for it here instead of running the 
	// loop again.
	if (ch == EOF) {
		*checker = EOF;
	}
	
	// return the pointer to the fixed string;
	return newWord;
}
