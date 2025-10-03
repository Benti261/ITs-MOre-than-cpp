#include "data.h"
#include "errors.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

void printData(const DataStorage& storage) {
    for (int i = 0; i < storage.count; ++i) {
        std::cout << storage.variables[i].key << "=" << storage.variables[i].value << std::endl;
    }
}

bool isValidChars(const char *str) {
    while (*str != '\0') {
        if (!isalnum(*str) && *str != '_') {
            return false;
        }
        ++str;
    }
    return true;
}

const char* findValue(const DataStorage& storage, const char* key) {
    for (int i = 0; i < storage.count; ++i) {
        if (strcmp(storage.variables[i].key, key) == 0) {
            return storage.variables[i].value;
        }
    }
    return nullptr;
}

ErrorCode FileToData(const char* filename, DataStorage& storage) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return IO_ERROR;
    }

    char line[256];
    storage.count = 0;

    while (file.getline(line, sizeof(line)) && storage.count < MAX_VARIABLES) {
        if (line[0] == '#' || line[0] == '\0' || (line[0] == '/' && line[1] == '/')) {
            continue;
        }

        char* equal_pos = strchr(line, '=');
        if (!equal_pos) {
            continue;
        }

        *equal_pos = '\0';
        strcpy(storage.variables[storage.count].key, line);
        strcpy(storage.variables[storage.count].value, equal_pos + 1);
        *equal_pos = '=';

        char* start = storage.variables[storage.count].key;
        while (*start && isspace(*start)) {
            start++;
        }
        char* end = start + strlen(start) - 1;
        while (end > start && isspace(*end)) {
            --end;
        }
        memmove(storage.variables[storage.count].key, start, end - start + 1);
        storage.variables[storage.count].key[end - start + 1] = '\0';

        start = storage.variables[storage.count].value;
        while (*start && isspace(*start)) {
            start++;
        }
        end = start + strlen(start) - 1;
        while (end > start && isspace(*end)) {
            --end;
        }
        memmove(storage.variables[storage.count].value, start, end - start + 1);
        storage.variables[storage.count].value[end - start + 1] = '\0';

        if (!(isValidChars(storage.variables[storage.count].key) || isValidChars(storage.variables[storage.count].value))) {
            continue;
        }

        if ((strlen(storage.variables[storage.count].key) > MAX_KEY_LENGTH) || (strlen(storage.variables[storage.count].value) > MAX_KEY_VALUE)) {
            continue;
        }

        bool duplicate = false;
        for (int i = 0; i < storage.count; ++i) {
            if (strcmp(storage.variables[i].key, storage.variables[storage.count].key) == 0) {
                strcpy(storage.variables[i].value, storage.variables[storage.count].value);
                duplicate = true;
                break;
            }
        }
        if (duplicate) {
            continue;
        }

        storage.count++;
    }

    file.close();
    return SUCCESS;
}