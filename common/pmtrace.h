/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/

#ifndef PM_TRACE_H
#define PM_TRACE_H

typedef struct
{
	vec3_t	normal;
	float	dist;
} pmplane_t;

typedef struct pmtrace_s pmtrace_t;

#ifdef __cplusplus
// workaround layout difference between Vector and float[3]
// when aggregate-returing pmtrace_s, it comes with float[3], not Vector class
// which differs in calling conversion on E2K

typedef struct
{
	float	normal[3];
	float	dist;
} pmplane_c;

typedef struct pmtrace_c_s
{
	qboolean	allsolid;		// if true, plane is not valid
	qboolean	startsolid;	// if true, the initial point was in a solid area
	qboolean	inopen, inwater;  // End point is in empty space or in water
	float	fraction;		// time completed, 1.0 = didn't hit anything
	float	endpos[3];		// final position
	pmplane_c	plane;		// surface normal at impact
	int	ent;		// entity at impact
	float	deltavelocity[3];	// Change in player's velocity caused by impact.  
				// Only run on server.
	int	hitgroup;
} pmtrace_c;
#include <string.h>
#else
#define pmtrace_c pmtrace_t
#endif

struct pmtrace_s
{
	qboolean	allsolid;		// if true, plane is not valid
	qboolean	startsolid;	// if true, the initial point was in a solid area
	qboolean	inopen, inwater;  // End point is in empty space or in water
	float	fraction;		// time completed, 1.0 = didn't hit anything
	vec3_t	endpos;		// final position
	pmplane_t	plane;		// surface normal at impact
	int	ent;		// entity at impact
	vec3_t	deltavelocity;	// Change in player's velocity caused by impact.  
				// Only run on server.
	int	hitgroup;
#ifdef __cplusplus
	pmtrace_s & operator = (const pmtrace_c_s &other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
#endif
};

#endif//PM_TRACE_H
