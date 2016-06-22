#include <stdio.h>
#include <stdlib.h>

#include "typedefs.h" // very important: keep on top

#include "random.h"

// Respawn
#define INITIAL_RESPAWN_CHANCE 80
#define RESPAWN_CHANCE_DECREMENT 18

#define BALANCE // comment out to test vanilla Pkunk code

BOOLEAN respawning (STARSHIP *StarShipPtr)
{
	if (
#ifdef BALANCE
		(signed)((TFB_Random () >> 10) % 100) < (INITIAL_RESPAWN_CHANCE - 1)
			- (StarShipPtr->static_counter * RESPAWN_CHANCE_DECREMENT)
#else
	   TFB_Random () & 1
#endif
	)
	{
		StarShipPtr->static_counter++;
		return TRUE;
	} else
	{
		return FALSE;
	}
}

int main (void)
{
	// hey look, you'll need to link with libbsd on linux
	TFB_SeedRandom ((DWORD)arc4random ());
	int index;
	
	/*
	 * Will be used as an array, where the index is some number of respawns,
	 * and the value at the index is the number of virtual Pkunks that
	 * attained that number of respawns. We dynamically allocate it because,
	 * although there *should* only be some finite number of possible
	 * respawns (believed to be five), we are only running this program
	 * because we think there may be more...
	 * 
	 * Use of very large data types is simple paranoia and future proofing;
	 * what if some lucky virtual Pkunk respawns 27 billion times, or we
	 * want to simulate a few trillion virtual Pkunks?
	 */
	unsigned long long *respawns;
	unsigned long long count = 6; // Pre-reserve six slots, 0-5

	/*
	 * reallocarray is an OpenBSD interface designed to prevent any
	 * possibility of integer overflow in common but dangerous idioms like
	 * malloc (sizeof(foo) * num); ask and I'll copypaste the implementation
	 */
	if ((respawns = reallocarray (NULL, count, sizeof (unsigned long long))) == NULL)
	{
		printf ("could not allocate memory\n");
		return 1;
	}

	for (index = 0; index < count; index++)
	{
		respawns[index] = 0;
	}

	for (index = 0; index < 1000000000; index++)
	{
		STARSHIP guinea_pig;
		guinea_pig.static_counter = 0;

		while (respawning (&guinea_pig)); // Run respawns until it dies

		if (guinea_pig.static_counter >= count) // We need a bigger array!
		{
			unsigned long long newcount = guinea_pig.static_counter + 1;
			unsigned long long *newrespawns = reallocarray (
			    respawns, newcount, sizeof (unsigned long long)
			);

			if (newrespawns == NULL)
			{
				printf ("could not allocate memory\n");
				free (respawns);
				free (newrespawns);
				return 1;
			}

			respawns = newrespawns;
			count = newcount;
		}

		respawns[guinea_pig.static_counter]++;
	}

	for (index = 0; index < count; index++)
	{
		printf ("%d respawns:\t%d Pkunks\n", index, respawns[index]);
	}

	free (respawns);
	return index;
}
