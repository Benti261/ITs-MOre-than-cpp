#include "data.h"
#include "errors.h"
#include "input.h"
#include "template.h"

#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    Config config;
    DataStorage data;
    char output[10000];

    ErrorCode result = parseArguments(argc, argv, config);
    if (result != SUCCESS) {
        printError(result);
        return result;
    }

    result = FileToData(config.dataPath, data);
    if (result != SUCCESS) {
        printError(result);
        return result;
    }

    result = processTemplate(config.templatePath, data, output, sizeof(output));
    if (result != SUCCESS) {
        printError(result);
        return result;
    }

    if (config.outputToFile) {
        std::ofstream outFile(config.outputPath);
        outFile << output;
    } else {
        std::cout << output;
    }

    return 0;
}