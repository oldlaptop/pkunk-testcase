#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include "compiler.h" // includes types.h

/*
 * Obviously not the full STARSHIP from UQM races.h, but cut down to, uh, the
 * barest minimum needed by the one expression we are interested in.
 */

struct STARSHIP
{
	BYTE static_counter;
};

typedef struct STARSHIP STARSHIP;

#endif // TYPEDEFS_H