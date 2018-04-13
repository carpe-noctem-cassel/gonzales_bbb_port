#ifndef logging_h
#define logging_h 1

#include "driver/eposcan.h"
#include "gonzales.h"
#include <stdio.h>
#include <string>

#include <Configuration.h>
#include <SystemConfig.h>

// logData logs the motion state to the given file
void logData(FILE* file);

#endif
