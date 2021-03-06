/**
	Logger provisto por la catedra 72.07 - Protocolos de Comunicacion
*/
#ifndef __LOGGER_H_
#define __LOGGER_H_

#include <stdlib.h>

#define RESET_COLOR "\033[0m"

typedef enum {DEBUG=0, INFO, ERROR, FATAL} LOG_LEVEL;

extern LOG_LEVEL current_level;

/**
*  Minimo nivel de log a registrar. Cualquier llamada a log con un nivel mayor a new_level sera ignorada
**/
void set_log_level(LOG_LEVEL newLevel);

char * level_description(LOG_LEVEL level);

// Debe ser una macro para poder obtener nombre y linea de archivo. 
// fprintf (stderr, "%s%s: %s:%d, ", level_description(level), RESET_COLOR, __FILE__, __LINE__);
// fprintf (stderr, "%s%s: ", level_description(level), RESET_COLOR);
#define log(level, fmt, ...)   {if(level >= current_level) {\
	fprintf (stderr, "%s%s: ", level_description(level), RESET_COLOR); \
	fprintf(stderr, fmt, ##__VA_ARGS__); \
	fprintf(stderr,"\n"); }\
	if ( level==FATAL) exit(1);}
#endif
	