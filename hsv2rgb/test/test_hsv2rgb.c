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
#include <time.h>

#include "hsv2rgb.h"

int main( int argc, char **argv ) {
	uint16_t	f, h, s, v;
	uint8_t		r, g, b;
	int16_t		rv;
	uint32_t	line;

	/*	check parameters	*/
	if ( argc != 2 ) {
		(void) fprintf( stderr, "usage: %s CMD\n", argv[0] );
		return EXIT_FAILURE;
	}

	/*	init	*/
	srand( time( NULL ) );
	init_hsv2rgb();

	/*	dispatch	*/
	if ( !strcmp( argv[1], "f" ) ) {
		for ( h = 0; h < 256; h++ ) {
			rv = f8( h );
			line = __LINE__ - 1;
			if ( (rv < 0) || (rv > 255)
					|| (h == 0 && rv != 0)
					|| (h == 42 && rv != 255)
					|| (h == 43 && rv != 0)
					|| (h == 85 && rv != 255)
					|| (h == 86 && rv != 0)
					|| (h == 127 && rv != 255)
					|| (h == 128 && rv != 0)
					|| (h == 170 && rv != 255)
					|| (h == 171 && rv != 0)
					|| (h == 213 && rv != 255)
					|| (h == 214 && rv != 0)
					|| (h == 255 && rv != 255) )
			{
				(void) fprintf( stderr,
						"f( %u ) failed with %i on line %u!\n",
						h, rv, line );
				return EXIT_FAILURE;
			}
		}

		return EXIT_SUCCESS;
	} else if ( !strcmp( argv[1], "hi8" ) ) {
		for ( h = 0; h < 256; h++ ) {
			rv = hi8( h );
			line = __LINE__ - 1;
			if ( (rv < 0) || (rv > 5)
					|| (h == 0 && rv != 0)
					|| (h == 42 && rv != 0)
					|| (h == 43 && rv != 1)
					|| (h == 85 && rv != 1)
					|| (h == 86 && rv != 2)
					|| (h == 127 && rv != 2)
					|| (h == 128 && rv != 3)
					|| (h == 170 && rv != 3)
					|| (h == 171 && rv != 4)
					|| (h == 213 && rv != 4)
					|| (h == 214 && rv != 5)
					|| (h == 255 && rv != 5) )
			{
				(void) fprintf( stderr,
						"hi( %u ) failed with %i on line %u!\n",
						h, rv, line );
				return EXIT_FAILURE;
			}
		}

		return EXIT_SUCCESS;
	} else if ( !strcmp( argv[1], "p8" ) ) {
		for ( s = 0; s < 256; s++ ) {
			/*	V = 0	*/
			if ( (rv = p8( 0, s )) != 0 ) {
				(void) fprintf( stderr,
						"p( V = 0, S = %u ) failed  with %i on line %u!\n",
						s, rv, __LINE__ - 3 );
				return EXIT_FAILURE;
			}

			/*	V = 255	*/
			if ( (rv = p8( 0xFF, s )) != 0xFF - s ) {
				(void) fprintf( stderr,
						"p( V = 255, S = %u ) failed with %i on line %u!\n",
						s, rv, __LINE__ - 3 );
				return EXIT_FAILURE;
			}

			/*	range issues	*/
			for ( v = 0; v < 256; v++ ) {
				rv = p8( s, v );
				if ( rv < 0 || rv > 255 ) {
					(void) fprintf( stderr,
							"p( V = %u, S = %u ) failed with %i on line %u!\n",
							v, s, rv, __LINE__ - 4 );
					return EXIT_FAILURE;
				}
			}
		}

		for ( v = 0; v < 256; v++ ) {
			/*	S = 0	*/
			if ( (rv = p8( v, 0 )) != v ) {
				(void) fprintf( stderr,
						"p( V = %u, S = 0 ) failed with %i on line %u!\n",
						v, rv, __LINE__ - 3 );
				return EXIT_FAILURE;
			}

			/*	S = 255	*/
			if ( (rv = p8( v, 255 )) != 0 ) {
				(void) fprintf( stderr,
						"p( V = %u, S = 255 ) failed with %i on line %u!\n",
						v, rv, __LINE__ - 3 );
				return EXIT_FAILURE;
			}
		}

		return EXIT_SUCCESS;
	} else if ( !strcmp( argv[1], "q8" ) ) {
		for ( v = 0; v < 256; v++ ) {
			for ( s = 0; s < 256; s++ ) {
				for ( f = 0; f < 256; f++ ) {
					rv = q8( v, s, f );
					if ( rv < 0 || rv > 255 ) {
						(void) fprintf( stderr,
								"q( V = %u, S = %u, f = %u ) failed with %i on line %u!\n",
								v, s, f, rv, __LINE__ - 4 );
						return EXIT_FAILURE;
					}
				}
			}
		}
		return EXIT_SUCCESS;
	} else if ( !strcmp( argv[1], "t8" ) ) {
		for ( v = 0; v < 256; v++ ) {
			for ( s = 0; s < 256; s++ ) {
				for ( f = 0; f < 256; f++ ) {
					rv = t8( v, s, f );
					if ( rv < 0 || rv > 255 ) {
						(void) fprintf( stderr,
								"t( V = %u, S = %u, f = %u ) failed with %i on line %u!\n",
								v, s, f, rv, __LINE__ - 4 );
						return EXIT_FAILURE;
					}
				}
			}
		}
		return EXIT_SUCCESS;
	} else if ( !strcmp( argv[1], "rgb" ) ) {
		for ( h = 0; h < 256; h++ ) {
			for ( s = 0; s < 256; s++ ) {
				for ( v = 0; v < 256; v++ ) {
					rgb( h, s, v, &r, &g, &b );

					if ( v == 0 && ( r != 0 || g != 0 || b != 0 ) ) {
						line = __LINE__ - 1;
						goto fail_rgb;
					}

					if ( s == 0 && ( r != g || r != b || g != b ) ) {
						line = __LINE__ - 1;
						goto fail_rgb;
					}

					continue;
fail_rgb:
					(void) fprintf( stderr,
							"rgb( H = %u, S = %u, V = %u ) failed "
							"with R = %u, G = %u, B = %u on line %u!\n",
							h, s, v, r, g, b, line );
					return EXIT_FAILURE;
				}
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
