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
 *  Platform-dependant functions.
 */

#ifndef COMMON_PLATFORM_HPP
#define COMMON_PLATFORM_HPP

#include <cstdio>

#include <vector>
#include <string>

namespace Common {

class Platform {
public:
	/** Read the command line parameters into UTF-8 strings. */
	static std::vector<std::string> getParameters(int argc, char **argv);
};

} // End of namespace Common

#endif // COMMON_PLATFORM_HPP
