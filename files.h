#ifndef FILES_H
#define FILES_H

#include <stdio.h>

void readTerminal(FILE** file);
void writeTerminal(FILE** file);
void readFile(FILE** file, const char* filename);
void writeFile(FILE** file, const char* filename);
void writeToFile(FILE** file, const char* filename);
void readBinaryFile(FILE** file, const char* filename);
void writeBinaryFile(FILE** file, const char* filename);
void closeReadFile(FILE* file);
void closeWriteFile(FILE* file);

#endif
