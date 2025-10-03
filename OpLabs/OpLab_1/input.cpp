#include "input.h"
#include "errors.h"
#include <cstring>

ErrorCode parseArguments(int argc, char* argv[], Config& config) {
    config.templatePath[0] = '\0';
    config.dataPath[0] = '\0';
    config.outputPath[0] = '\0';
    config.outputToFile = false;

    if (argc < 5) {
        return ARGUMENT_ERROR;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0) {
            if (i + 1 < argc) {
                strncpy(config.templatePath, argv[i + 1], 255);
                config.templatePath[255] = '\0';
                i++;
            } else {
                return ARGUMENT_ERROR;
            }
        } else if (strncmp(argv[i], "--template=", 11) == 0) {
            strncpy(config.templatePath, argv[i] + 11, 255);
            config.templatePath[255] = '\0';
        } else if (strcmp(argv[i], "-d") == 0) {
            if (i + 1 < argc) {
                strncpy(config.dataPath, argv[i + 1], 255);
                config.dataPath[255] = '\0';
                i++;
            } else {
                return ARGUMENT_ERROR;
            }
        } else if (strncmp(argv[i], "--data=", 7) == 0) {
            strncpy(config.dataPath, argv[i] + 7, 255);
            config.dataPath[255] = '\0';
        } else if (strcmp(argv[i], "-o") == 0) {
            if (i + 1 < argc) {
                strncpy(config.outputPath, argv[i + 1], 255);
                config.outputPath[255] = '\0';
                config.outputToFile = true;
                i++;
            } else {
                return ARGUMENT_ERROR;
            }
        } else if (strncmp(argv[i], "--output=", 9) == 0) {
            strncpy(config.outputPath, argv[i] + 9, 255);
            config.outputPath[255] = '\0';
            config.outputToFile = true;
        } else {
            return ARGUMENT_ERROR;
        }
    }

    if (config.templatePath[0] == '\0' || config.dataPath[0] == '\0') {
        return ARGUMENT_ERROR;
    }

    return SUCCESS;
}