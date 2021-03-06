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

#ifndef VERSION_VERSION_HPP
#define VERSION_VERSION_HPP

namespace Version {

// "Decemvirate"
const char *getProjectName();

// "0.0.1+2197.g19f9c1b"
const char *getProjectVersion();

// "Decemvirate 0.0.1+2197.g19f9c1b"
const char *getProjectNameVersion();

// "Decemvirate 0.0.1+2197.g19f9c1b [0.0.1+2197.g19f9c1b] (2013-07-28T13:32:04)"
const char *getProjectNameVersionFull();

// Very shortened authors/copyright message
const char *getProjectAuthors();

} // End of namespace Version

#endif // VERSION_VERSION_HPP
