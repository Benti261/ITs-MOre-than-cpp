#ifndef ERRORS_H
#define ERRORS_H

enum ErrorCode {
    SUCCESS = 0,
    MISSING_KEY = 1,
    ARGUMENT_ERROR = 2,
    IO_ERROR = 3,
    TEMPLATE_SYNTAX_ERROR = 4,
    OTHER_ERROR = 5
};

const char* getErrorMessage(ErrorCode code);
void printError(ErrorCode code);
void resetErrorsHeader();

#endif