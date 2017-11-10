#ifndef logging_h
#define logging_h 1

#include "driver/eposcan.h"
#include "gonzales.h"
#include <stdio.h>
#include <string>

#include <Configuration.h>
#include <SystemConfig.h>

extern gonzales_state gonz_state;

void
logging_init();
void
logData();

#endif
