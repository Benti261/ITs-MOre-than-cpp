#include "errors.h"
#include <iostream>

static bool errorHeaderPrinted = false;

const char* getErrorMessage(ErrorCode code) {
    switch (code) {
        case SUCCESS: return "Success";
        case MISSING_KEY: return "Missing key in template";
        case ARGUMENT_ERROR: return "Command line argument error";
        case IO_ERROR: return "Input/Output Error";
        case TEMPLATE_SYNTAX_ERROR: return "Template Syntax Error";
        case OTHER_ERROR: return "Other Error";
        default: return "Unknown Error";
    }
}

void printError(ErrorCode code) {
    if (code == SUCCESS) {
        return;
    }

    if (!errorHeaderPrinted) {
        std::cerr << "Errors:" << std::endl;
        errorHeaderPrinted = true;
    }

    std::cerr << getErrorMessage(code) << std::endl;
}

void resetErrorsHeader() {
    errorHeaderPrinted = false;
}