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
 *  Basic Decemvirate version information.
 */

#include "src/version/version.hpp"

#if defined(HAVE_CONFIG_H)
	#include "config.h"
#endif

// Define default values if the real ones can't be determined

#ifndef PACKAGE_NAME
	#define PACKAGE_NAME "Decemvirate"
#endif

#ifndef PACKAGE_VERSION
	#define PACKAGE_VERSION "0.0.0"
#endif

#ifndef DECEMVIRATE_REVDESC
	#define DECEMVIRATE_REVDESC "unknown"
#endif

#ifndef DECEMVIRATE_REV
	#define DECEMVIRATE_REV "unk"
#endif

#ifndef DECEMVIRATE_BUILDDATE
	#define DECEMVIRATE_BUILDDATE __DATE__ " " __TIME__
#endif

// If we're in full release mode, the revision is ignored
#ifdef DECEMVIRATE_RELEASE
	#undef DECEMVIRATE_REV
	#define DECEMVIRATE_REV ""
	#define DECEMVIRATE_REVSEP ""
#else
	#define DECEMVIRATE_REVSEP "+"
#endif

// Distributions may append an extra version string
#ifdef DECEMVIRATE_DISTRO
	#undef DECEMVIRATE_REV
	#define DECEMVIRATE_REV DECEMVIRATE_DISTRO
#endif

namespace Version {

static const char *kProjectName            = PACKAGE_NAME;
static const char *kProjectVersion         = PACKAGE_VERSION;
static const char *kProjectNameVersion     = PACKAGE_NAME " " PACKAGE_VERSION DECEMVIRATE_REVSEP DECEMVIRATE_REV;
static const char *kProjectNameVersionFull = PACKAGE_NAME " " PACKAGE_VERSION DECEMVIRATE_REVSEP DECEMVIRATE_REV " [" DECEMVIRATE_REVDESC "] (" DECEMVIRATE_BUILDDATE ")";

static const char *kProjectAuthors =
	"Copyright (c) 2019-2021 by Sven Hesse.\n"
	"Please see the AUTHORS file for details.\n"
	"\n"
	"This is free software; see the source for copying conditions.  There is NO\n"
	"warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n"
	"\n"
	"This program displays data under the terms of the Open Game License and\n"
	"Paizo's Community Use Policy.  Please see the AUTHORS file for details.";

const char *getProjectName() {
	return kProjectName;
}

const char *getProjectVersion() {
	return kProjectVersion;
}

const char *getProjectNameVersion() {
	return kProjectNameVersion;
}

const char *getProjectNameVersionFull() {
	return kProjectNameVersionFull;
}

const char *getProjectAuthors() {
	return kProjectAuthors;
}

} // End of namespace Version
