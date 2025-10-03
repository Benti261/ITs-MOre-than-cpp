#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "data.h"
#include "errors.h"

ErrorCode processTemplate(const char* templatePath, const DataStorage& data, char* output, int outputSize);

#endif