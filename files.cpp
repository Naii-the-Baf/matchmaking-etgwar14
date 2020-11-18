#include <stdio.h>
#include <stdlib.h>

void readTerminal(FILE** file){
    *file = stdin;
    return;
}

void writeTerminal(FILE** file){
    *file = stdout;
    return;
}

void readFile(FILE** file, const char* filename){
    *file = fopen(filename, "r");
    if(*file == NULL){
        FILE *err = fopen("err.txt", "w");
        fprintf(err, "ERROR READING FILE");
        fflush(err);
        fclose(err);
        exit(EXIT_FAILURE);
    }
    return;
}

void writeFile(FILE** file, const char* filename){
    *file = fopen(filename, "w");
    return;
}

void writeToFile(FILE** file, const char* filename){
    *file = fopen(filename, "a");
    return;
}

void readBinaryFile(FILE** file, const char* filename){
    *file = fopen(filename, "rb");
    if(*file == NULL){
        FILE *err = fopen("err.txt", "w");
        fprintf(err, "ERROR READING FILE");
        fflush(err);
        fclose(err);
        exit(EXIT_FAILURE);
    }
    return;
}

void writeBinaryFile(FILE** file, const char* filename){
    *file = fopen(filename, "wb");
    return;
}

void closeReadFile(FILE* file){
    if(file != stdin){
        fclose(file);
    }
    return;
}

void closeWriteFile(FILE* file){
    if(file != stdout){
        fflush(file);
        fclose(file);
    }
    return;
}
