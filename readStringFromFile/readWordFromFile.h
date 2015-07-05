#ifndef READWORDFROMFILE_H_   /* Include guard */
#define READWORDFROMFILE_H_

#include <stdio.h>
#include <stdlib.h>

int getLength(char *str);
char *readWordFromFile(FILE *in, int *checker);

#endif
