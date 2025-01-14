/****************************************************************/
/******* Author     : Ola Saadeh                *****************/
/******* Created on : 23 Dec 2024               *****************/
/******* File Name  : STD_Types.h               *****************/
/****************************************************************/
#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/**< Unsigned integer types */
typedef unsigned char      u8;   /**< 8-bit unsigned integer type */
typedef unsigned short int u16;  /**< 16-bit unsigned integer type */
typedef unsigned long int  u32;  /**< 32-bit unsigned integer type */

/**< Signed integer types */
typedef signed char        s8;   /**< 8-bit signed integer type */
typedef signed short int   s16;  /**< 16-bit signed integer type */
typedef signed long int    s32;  /**< 32-bit signed integer type */

/**< Floating-point types */
typedef float              f32;  /**< Single-precision floating-point type */
typedef double             f64;  /**< Double-precision floating-point type */
typedef long double        f128; /**< Extended-precision floating-point type */

/**< Null pointer definition */
#define NULL 0
#define NULL_PTR ((void *)0)

/**< Standard return type for functions */
typedef u8 Std_ReturnType;

/**< Marker for invalid or uninitialized data */
typedef s8 INVALID_VALUE;

/**< Function execution status codes */
#define E_OK            ((Std_ReturnType)1)       /**< Function execution successful */
#define E_NOT_OK        ((Std_ReturnType)0)       /**< Function execution failed */
#define E_INVALID_PARAMETER  ((INVALID_VALUE)-1)  /**< Invalid parameter marker */

#endif /* STD_TYPES_H_ */
