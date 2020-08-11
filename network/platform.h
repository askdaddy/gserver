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
// *nux OS

#define FALSE               0
#define TRUE                1

typedef char				INT8;
typedef unsigned char		UINT8;
typedef short				INT16;
typedef unsigned short		UINT16;
typedef int					INT32;
typedef unsigned int		UINT32;
typedef int					BOOL;
typedef void				VOID;
typedef float				FLOAT;
typedef double				DOUBLE;
typedef long long			INT64;
typedef unsigned long long	UINT64;
typedef char				BYTE;
typedef char				CHAR;
typedef int					SOCKET;

typedef int SOCKET;


#endif

#endif
