#ifndef INPUT_H
#define INPUT_H

#include "errors.h"

struct Config {
    char templatePath[256];
    char dataPath[256];
    char outputPath[256];
    bool outputToFile;
};

ErrorCode parseArguments(int argc, char* argv[], Config& config);

#endif