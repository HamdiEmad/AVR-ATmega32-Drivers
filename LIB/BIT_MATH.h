/*
 * BIT_MATH.h
 *
 *  Created on: Sep 16, 2026
 *      Author: Hamdi
 */

#ifndef LIB_BIT_MATH_H_
#define LIB_BIT_MATH_H_

#define SET_BIT(REG, BIT) ((REG) |= (1 << (BIT)))
#define CLR_BIT(REG, BIT) ((REG) &= (~(1 << (BIT))))
#define TOG_BIT(REG, BIT) ((REG) ^= (1 << (BIT)))
#define READ_BIT(REG, BIT) (((REG) & (1 << (BIT))) >> (BIT))

#endif /* LIB_BIT_MATH_H_ */
