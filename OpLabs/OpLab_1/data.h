#ifndef DATA_H
#define DATA_H

#include "errors.h"

const int MAX_KEY_VALUE = 100;
const int MAX_KEY_LENGTH = 100;
const int MAX_VARIABLES = 1024;

struct KeyValue {
    char key[MAX_KEY_LENGTH + 1];
    char value[MAX_KEY_VALUE + 1];
};

struct DataStorage {
    KeyValue variables[MAX_VARIABLES];
    int count;
};

ErrorCode FileToData(const char* filename, DataStorage& storage);
const char* findValue(const DataStorage& storage, const char* key);
void printData(const DataStorage& storage);
bool isValidChars(const char* str);


#endif