/*******************************************************************//**
 *	@file	hsv2rgb.h
 *
 *	@brief	declarations for a HSV to RGB
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

#ifndef _HSV2RGB_H_
#define _HSV2RGB_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *	@see	https://de.wikipedia.org/wiki/HSV-Farbraum
 */
int16_t f8( uint8_t h );

/**
 *	@note	Do not return 6 for full H, but 0 instead.
 *
 *	@return	0 to 5
 */
int16_t hi8( uint8_t h );

/**
 *	@note	Do not return 6 for full H, but 0 instead.
 *
 *	@return	0 to 5
 */
int16_t hi10( uint16_t h );

/**
 *	precalculates bucket sizes
 */
void init_hsv2rgb( void );

/**
 *	@see	https://de.wikipedia.org/wiki/HSV-Farbraum
 */
int16_t p8( uint8_t v, uint8_t s );

/**
 *	@see	https://de.wikipedia.org/wiki/HSV-Farbraum
 */
int16_t q8( uint8_t v, uint8_t s, uint8_t f );

void rgb( uint8_t h, uint8_t s, uint8_t v,
		uint8_t *r, uint8_t *g, uint8_t *b );

/**
 *	@see	https://de.wikipedia.org/wiki/HSV-Farbraum
 */
int16_t t8( uint8_t v, uint8_t s, uint8_t f );

#ifdef __cplusplus
}
#endif

#endif /* _HSV2RGB_H_ */

/* vim: set noet sts=0 ts=4 sw=4 sr: */
