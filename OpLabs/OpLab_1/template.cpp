#include "template.h"
#include "data.h"
#include "errors.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>

ErrorCode processTemplate(const char* templatePath, const DataStorage& data, char* output, int outputSize) {
    std::ifstream file(templatePath);
    if (!file.is_open()) {
        return IO_ERROR;
    }

    char templateText[10000];
    file.read(templateText, sizeof(templateText));
    templateText[file.gcount()] = '\0';

    const char* current = templateText;
    char* out_ptr = output;

    while (*current != '\0') {
        const char* start_brace = strstr(current, "{{");

        if (start_brace == NULL) {
            strcpy(out_ptr, current);
            break;
        }

        int copy_len = start_brace - current;
        strncpy(out_ptr, current, copy_len);
        out_ptr += copy_len;

        const char* end_brace = strstr(start_brace + 2, "}}");
        if (end_brace == NULL) {
            return TEMPLATE_SYNTAX_ERROR;
        }

        char varName[100];
        int varLen = end_brace - (start_brace + 2);
        strncpy(varName, start_brace + 2, varLen);
        varName[varLen] = '\0';

        char* start = varName;
        while (*start && isspace(*start)) start++;
        char* end_ptr = start + strlen(start) - 1;
        while (end_ptr > start && isspace(*end_ptr)) end_ptr--;
        int cleanLen = end_ptr - start + 1;
        memmove(varName, start, cleanLen);
        varName[cleanLen] = '\0';

        const char* value = findValue(data, varName);
        if (!value) return MISSING_KEY;

        strcpy(out_ptr, value);
        out_ptr += strlen(value);

        current = end_brace + 2;
    }

    strcat(output, "\n");

    return SUCCESS;
}