/*******************************************************************//**
 *	@file	hsv2rgb.c
 *
 *	@brief	HSV to RGB implementation(s) …
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

#include "hsv2rgb.h"

#include <stdint.h>

const uint8_t buckets_8[6] = { 0, 43, 86, 128, 171, 214 };
const uint16_t buckets_10[6] = { 0, 171, 342, 512, 683, 854 };

int16_t hi8( uint8_t h ) {
	if ( h < buckets_8[3] ) {
		if ( h < buckets_8[1] ) {
			return 0;
		} else if ( h < buckets_8[2] ) {
			return 1;
		} else {
			return 2;
		}
	} else {
		if ( h < buckets_8[4] ) {
			return 3;
		} else if ( h < buckets_8[5] ) {
			return 4;
		} else {
			return 5;
		}
	}
}

int16_t hi10( uint16_t h ) {
	return -1;
}

int16_t p8( uint8_t v, uint8_t s ) {
	uint16_t _v = v, _s = s;

//	return (int16_t) ( _v * ( (uint16_t) 255 - _s ) / 255 );
	return (int16_t) ( _v * ( 255 - _s ) / 255 );
}

/* vim: set noet sts=0 ts=4 sw=4 sr: */
