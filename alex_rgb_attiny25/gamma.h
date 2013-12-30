/*  save this to gamma.h
 *  gamma was 2.2
 *  tablesize was 32
 *  pwmres was 256
 *  x was 7.48954692248057 */

#ifndef _GAMMA_H_
#define _GAMMA_H_

#include <stdint.h>

const uint8_t gammatbl[32] = {
    0, 0, 0, 1, 2, 4, 6, 9, 12, 16, 
    21, 26, 31, 37, 44, 51, 59, 68, 77, 86, 
    97, 108, 119, 132, 145, 158, 173, 188, 203, 220, 
    237, 255
};

#endif /* _GAMMA_H_ */
