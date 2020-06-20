/*
*
*    Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*    This product contains software technology licensed from Id
*    Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*    All Rights Reserved.
*
*    Use, distribution, and modification of this source code and/or resulting
*    object code is restricted to non-commercial enhancements to products from
*    Valve LLC.  All other use, distribution, or modification is prohibited
*    without written permission from Valve LLC.
*
*/

#pragma once

#ifdef _MSC_VER
#pragma warning(disable:4244)		// int or float down-conversion
#pragma warning(disable:4305)		// int or float data truncation
#pragma warning(disable:4201)		// nameless struct/union
#pragma warning(disable:4514)		// unreferenced inline function removed
#pragma warning(disable:4100)		// unreferenced formal parameter
#endif

#include "maintypes.h"
#include "tier0/basetypes.h"

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#define NOWINRES
	#define NOSERVICE
	#define NOMCX
	#define NOIME
	#include "winsani_in.h"
	#include "windows.h"
	#include "winsani_out.h"
	#undef PlaySound
#else
	#include <limits.h>
	#include <stdarg.h>
	#include <string.h>
#endif // _WIN32

// Misc C-runtime library headers
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// Header file containing definition of globalvars_t and entvars_t
typedef int EOFFSET;					// More explicit than "int"
typedef unsigned int func_t;
typedef unsigned int string_t;			// from engine's pr_comp.h;
typedef float vec_t;					// needed before including progdefs.h

// Vector class
#include "mathlib/vector.h"

// Defining it as a (bogus) struct helps enforce type-checking
#define vec3_t Vector
// Shared engine/DLL constants

#include "const.h"
#include "edict.h"

// Shared header describing protocol between engine and DLLs
#include "eiface.h"
// Shared header between the client DLL and the game DLLs
#include "cdll_dll.h"
#include "extdef.h"
