#ifndef __errors_h
#define __errors_h

#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Defines a macro that can be used for disgnostic output examples.
When compiled with -DDEBUG, it results in calling printf with the specified
argument list. When DEBUG is not defined, it expands to nothing */

#ifndef DEBUG
# define DPRINTF(arg) printf arg
#else
# define DPRINTF(arg)
#endif

/* Note: the "do {" ... "}while(0);" braketing  around the macros allows
the err_abort and errno_abort macros to be used as if they were function
calls, even in contexts where a trailing ";" would generatye a null statement.
For example-

	if (status != 0 )
		err_abort(status, "message");
	else
		return status;

will not compile if err_Abort is a macro ending with "}", because C does not 
expect a ";" to follow the "}". Because C does not expect a ";" to following
the ")" in the do....while construct, err_abort and errno_abort can be used as 
if they were function calls.
*/

#define err_abort(code, text) do { \
	fprintf(stderr, "%s at \"%s\":%d: %s\n", \
		text, __FILE__, __LINE__, strerror(code));\
	abort();\
	} while(0)

#define errno_abort(text) do { \
        fprintf(stderr, "%s at \"%s\":%d: %s\n", \
                text, __FILE__, __LINE__, strerror(errno));\
        abort();\
	} while(0)

#endif











