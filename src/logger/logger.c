#include <stdio.h>
#include <stdlib.h>

#include "logger.h"

LOG_LEVEL current_level = DEBUG;


void set_log_level(LOG_LEVEL new_level) {
	if ( new_level >= DEBUG && new_level <= FATAL )
	   current_level = new_level;
}

char * level_description(LOG_LEVEL level) {
    static char * description[] = {"DEBUG", "INFO", "ERROR", "FATAL"};
    if (level < DEBUG || level > FATAL)
        return "";
    return description[level];
}