/*******************************************************************//**
 *	@file	test_hsv2rgb.c
 *
 *	@author	Alexander Dahl <post@lespocky.de>
 *
 *	@copyright	2013 Alexander Dahl
 *
 *	This file is part of hsv2rgb.
 *
 *	_hsv2rgb_ is free software: you can redistribute it and/or modify it
 *	under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	_hsv2rgb_ is distributed in the hope that it will be useful, but
 *	WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *	General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with _hsv2rgb_. If not, see <http://www.gnu.org/licenses/>.
 **********************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hsv2rgb.h"

int main( int argc, char **argv ) {
	uint8_t	bsize_8[6], s, v;
	int16_t	rv;
	int		lpc;

	/*	init	*/
	for ( lpc = 0; lpc < 5; lpc++ ) {
		bsize_8[lpc] = buckets_8[lpc+1] - buckets_8[lpc];
	}
	bsize_8[5] = 256 - buckets_8[5];
#ifndef NDEBUG
	(void) printf( "bsize_8:" );
	for ( lpc = 0; lpc < 6; lpc++ ) {
		(void) printf( " %u", bsize_8[lpc] );
	}
	(void) printf( "\n" );
#endif

	if ( argc != 2 ) {
		(void) fprintf( stderr, "usage: %s CMD\n", argv[0] );
		return EXIT_FAILURE;
	}

	if ( !strcmp( argv[1], "hi8" ) ) {
		if ( (rv = hi8( 0 )) != 0 ) {
			(void) fprintf( stderr,
					"hi( 0 ) failed with %i on line %u!\n",
					rv, __LINE__);
		}
	} else if ( !strcmp( argv[1], "p8" ) ) {
		for ( s = 0xFF; s; s-- ) {
			/*	V = 0	*/
			if ( p8( 0, s ) != 0 ) {
				(void) fprintf( stderr,
						"p( V = 0, S = %u ) failed on line %u!\n",
						s, __LINE__ - 3 );
				return EXIT_FAILURE;
			}

			/*	V = 255	*/
			if ( p8( 0xFF, s ) != 0xFF - s ) {
				(void) fprintf( stderr,
						"p( V = 255, S = %u ) failed on line %u!\n",
						s, __LINE__ - 3 );
				return EXIT_FAILURE;
			}

			/*	range issues	*/
			for ( v = 0xFF; v; v-- ) {
				rv = p8( s, v );
				if ( rv < 0 || rv > 255 ) {
					(void) fprintf( stderr,
							"p( V = %u, S = %u ) failed with %i on line %u!\n",
							v, s, rv, __LINE__ - 4 );
					return EXIT_FAILURE;
				}
			}
		}

		for ( v = 0xFF; v; v-- ) {
			/*	S = 0	*/
			if ( p8( v, 0 ) != v ) {
				(void) fprintf( stderr,
						"p( V = %u, S = 0 ) failed on line %u!\n",
						v, __LINE__ - 3 );
				return EXIT_FAILURE;
			}

			/*	S = 255	*/
			if ( p8( v, 255 ) != 0 ) {
				(void) fprintf( stderr,
						"p( V = %u, S = 255 ) failed on line %u!\n",
						v, __LINE__ - 3 );
				return EXIT_FAILURE;
			}
		}

		return EXIT_SUCCESS;
	} else {
		(void) fprintf( stderr, "command not recognized!\n" );
		return EXIT_FAILURE;
	}

	return EXIT_FAILURE;
}

/* vim: set noet sts=0 ts=4 sw=4 sr: */
