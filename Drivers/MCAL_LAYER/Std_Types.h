/*
 *  STD_TYPES.h
 *  LinkedIn : https://www.linkedin.com/in/ahmed-basem-988529272/
 *  Created on: 30/1/2024
 *  Author: AHMED BASEM
 */

#ifndef STD_TYPES_H
#define STD_TYPES_H
/* Section : Includes */
#include "std_libraries.h"
#include "compiler.h"

/* Section: Data Type Declarations */
typedef unsigned char 	    uint8;
typedef unsigned short 	    uint16;
typedef unsigned long	    uint32;
typedef unsigned long long  uint64;
typedef signed char	    sint8;
typedef signed short 	    sint16;
typedef signed long 	    sint32;
typedef signed long long    sint64;
typedef float  f32;
typedef double f64;

typedef uint8 Std_ReturnType;

/* Section: Macro Declarations */
#define STD_HIGH       0x01
#define STD_LOW        0x00
#define NULL 0LL

/* Section: Macro Declarations */
#define STD_HIGH       0x01
#define STD_LOW        0x00

#define STD_ON         0x01
#define STD_OFF        0x00

#define STD_ACTIVE     0x01
#define STD_IDLE       0x00

#define E_OK         (Std_ReturnType)0x01
#define E_NOT_OK     (Std_ReturnType)0x00

#define ZERO_INIT 0

/* Section: Macro Functions Declarations */

/* Section: Function Declarations */

#endif