#ifndef AUX__H
#define AUX__H

#ifdef DEBUG
# define DPRINTF(arg) printf arg
#else
# define DPRINTF(arg)
#endif

#include <string.h>
#include <stdlib.h>

#define err_abort(code,text) do { \
	fprintf(stderr, "%s at \"%s\":%d: %s\n", \
		text, __FILE__, __LINE__, strerror(code)); \
	abort(); \
	} while(0)
	
#define errno_abort(text) do { \
	fprintf(stderr, "%s at \"%s\":%d: %s\n", \
		text, __FILE__, __LINE__, strerror(errno)); \
	abort(); \
	} while (0)

char* concat(char *str1, char *str2) {
	char* result = (char*) malloc(sizeof(char)*(strlen(str1)+strlen(str2)));
	char* s1 = strcat(result, str1);
	char* s2 = strcat(result, str2);
	return result;
}

#endif