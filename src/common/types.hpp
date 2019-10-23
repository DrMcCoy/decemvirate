/* Decemvirate - A FLOSS Pathfinder TTRPG helper
 *
 * Decemvirate is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * Decemvirate is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Decemvirate is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with Decemvirate. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file
 *  Low-level type definitions to handle fixed width types portably.
 */

#ifndef COMMON_TYPES_HPP
#define COMMON_TYPES_HPP

#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif

#include <cstddef>
#include <climits>

#ifdef HAVE_INTTYPES_H
	#include <inttypes.h>
#endif // HAVE_INTTYPES_H
#ifdef HAVE_STDINT_H
	#include <stdint.h>
#endif // HAVE_STDINT_H
#ifdef HAVE_SYS_TYPES_H
	#include <sys/types.h>
#endif // HAVE_SYS_TYPES_H

#if defined(HAVE_INTTYPES_H) || defined(HAVE_STDINT_H)
	/* If either of these is available, the C99 integer types are
	   available. Furthermore <inttypes.h> should even already
	   include <stdint.h>. */
#elif defined(HAVE_SYS_TYPES_H)
	/* <sys/types.h> should define signed integer types just like
	   C99. However, the unsigned ones are usually named a bit
	   differently.

	   TODO: This might be different on some platforms!
	*/

	using uint8_t  = u_int8_t;
	using uint16_t = u_int16_t;
	using uint32_t = u_int32_t;
	using uint64_t = u_int64_t;
#elif defined(SIZEOF_CHAR) && \
      defined(SIZEOF_SHORT) && \
      defined(SIZEOF_INT) && \
      defined(SIZEOF_LONG) && \
      defined(SIZEOF_LONG_LONG)

	/* Otherwise, look for candidates among the usual integer
	   types, if we know about their sizes. */

	#if SIZEOF_CHAR == 1
		using  int8_t = signed   char;
		using uint8_t = unsigned char;
	#else
		#error Cannot find an 8-bit integer type
	#endif

	#if SIZEOF_SHORT == 2
		using  int16_t =          short;
		using uint16_t = unsigned short;
	#elif SIZEOF_INT == 2
		using  int16_t =          int;
		using uint16_t = unsigned int;
	#else
		#error Cannot find a 16-bit integer type
	#endif

	#if SIZEOF_INT == 4
		using  int32_t =          int;
		using uint32_t = unsigned int;
	#elif SIZEOF_LONG == 4
		using  int32_t =          long;
		using uint32_t = unsigned long;
	#else
		#error Cannot find a 32-bit integer type
	#endif

	#if SIZEOF_LONG == 8
		using  int64_t =          long;
		using uint64_t = unsigned long;
	#elif SIZEOF_LONG_LONG == 8
		using  int64_t =          long long;
		using uint64_t = unsigned long long;
	#else
		#error Cannot find a 64-bit integer type
	#endif
#else
	#error Cannot find a way to derive fixed-width integer types
#endif

// intptr_t
#ifndef HAVE_INTPTR_T
	#undef intptr_t

	#if defined(SIZEOF_VOID_P) && \
	    defined(SIZEOF_SHORT) && \
	    defined(SIZEOF_INT) && \
	    defined(SIZEOF_LONG) && \
	    defined(SIZEOF_LONG_LONG)

		#if SIZEOF_VOID_P == SIZEOF_SHORT
			using intptr_t = short;
			#define HAVE_INTPTR_T
		#elif SIZEOF_VOID_P = SIZEOF_INT
			using intptr_t = int;
			#define HAVE_INTPTR_T
		#elif SIZEOF_VOID_P = SIZEOF_LONG
			using intptr_t = long;
			#define HAVE_INTPTR_T
		#elif SIZEOF_VOID_P = SIZEOF_LONG_LONG
			using intptr_t = long long;
			#define HAVE_INTPTR_T
		#endif
	#endif

	#ifndef HAVE_INTPTR_T
		#error Cannot find a way to derive a signed integer type to fit a pointer
	#endif
#endif

// uintptr_t
#ifndef HAVE_UINTPTR_T
	#undef uintptr_t

	#if defined(SIZEOF_VOID_P) && \
	    defined(SIZEOF_SHORT) && \
	    defined(SIZEOF_INT) && \
	    defined(SIZEOF_LONG) && \
	    defined(SIZEOF_LONG_LONG)

		#if SIZEOF_VOID_P == SIZEOF_SHORT
			using uintptr_t = unsigned short;
			#define HAVE_UINTPTR_T
		#elif SIZEOF_VOID_P = SIZEOF_INT
			using uintptr_t = unsigned int;
			#define HAVE_UINTPTR_T
		#elif SIZEOF_VOID_P = SIZEOF_LONG
			using uintptr_t = unsigned long;
			#define HAVE_UINTPTR_T
		#elif SIZEOF_VOID_P = SIZEOF_LONG_LONG
			using uintptr_t = unsigned long long;
			#define HAVE_UINTPTR_T
		#endif
	#endif

	#ifndef HAVE_UINTPTR_T
		#error Cannot find a way to derive an unsigned integer type to fit a pointer
	#endif
#endif

// The maximum value a size_t can describe
#ifndef SIZE_MAX
	#define SIZE_MAX ((size_t) -1)
#endif

// Fallback macro to printf an int64. A bit wonky; usage discouraged.
#ifndef PRId64
	#define PRId64   "lld"
	#define Cd64(x)  ((signed long long) (x))
#else
	#define Cd64(x)  ((int64) (x))
#endif

// Fallback macro to printf an uint64. A bit wonky; usage discouraged.
#ifndef PRIu64
	#define PRIu64   "llu"
	#define Cu64(x)  ((unsigned long long) (x))
#else
	#define Cu64(x)  ((uint64) (x))
#endif

// Type to indicate that this is a raw byte (or an array of raw bytes, ...).
using byte = std::byte;
// Convenience type definition for a simple unsigned int.
using uint = unsigned int;

// Fallback macro to create an int64 constant.
#ifndef INT64_C
	#define INT64_C(c) (c ## LL)
#endif

// Fallback macro to create an uint64 constant.
#ifndef UINT64_C
	#define UINT64_C(c) (c ## ULL)
#endif

// Fallback macros for type limits.
#ifndef UINT8_MAX
	#define UINT8_MAX 0xFF
#endif
#ifndef UINT16_MAX
	#define UINT16_MAX 0xFFFF
#endif
#ifndef UINT32_MAX
	#define UINT32_MAX 0xFFFFFFFF
#endif
#ifndef UINT64_MAX
	#define UINT64_MAX UINT64_C(0xFFFFFFFFFFFFFFFF)
#endif

#ifndef INT8_MAX
	#define INT8_MAX 0x7F
#endif
#ifndef INT16_MAX
	#define INT16_MAX 0x7FFF
#endif
#ifndef INT32_MAX
	#define INT32_MAX 0x7FFFFFFF
#endif
#ifndef INT64_MAX
	#define INT64_MAX INT64_C(0x7FFFFFFFFFFFFFFF)
#endif

#ifndef INT8_MIN
	#define INT8_MIN (-INT8_MAX - 1)
#endif
#ifndef INT16_MIN
	#define INT16_MIN (-INT16_MAX - 1)
#endif
#ifndef INT32_MIN
	#define INT32_MIN (-INT32_MAX - 1)
#endif
#ifndef INT64_MIN
	#define INT64_MIN (-INT64_MAX - INT64_C(1))
#endif

#endif // COMMON_TYPES_HPP
