#include <stdio.h>
#include <stdlib.h>

#include "logger.h"

LOG_LEVEL current_level = DEBUG;


void set_log_level(LOG_LEVEL new_level) {
	if ( new_level >= DEBUG && new_level <= FATAL )
	   current_level = new_level;
}

char * level_description(LOG_LEVEL level) {
    static char * description[] = {"DEBUG", "\033[0;36mINFO", "\033[0;33mERROR", "\033[0;31mFATAL"};
    if (level < DEBUG || level > FATAL)
        return "";
    return description[level];
}
