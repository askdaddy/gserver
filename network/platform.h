//
// Created by Seven on 20/7/22.
//

#ifndef G_PLATFORM_H
#define G_PLATFORM_H


#if defined(WIN32) || defined(WIN64)
#define OS_PLATFORM_WINDOWS
#elif defined(LINUX32) || defined(LINUX64)
#define OS_PLATFORM_LINUX
#endif



#ifdef OS_PLATFORM_WINDOWS


#else

#define FALSE               0
#define TRUE                1

typedef int16_t				INT16;
typedef uint16_t    		UINT16;
typedef int32_t				INT32;
typedef uint32_t    		UINT32;
typedef bool				BOOL;
typedef float				FLOAT;
typedef double				DOUBLE;
typedef int64_t 			INT64;
typedef uint64_t        	UINT64;
typedef void                VOID;
typedef char                CHAR;

typedef int32_t        		SOCKET;


#endif

#endif
