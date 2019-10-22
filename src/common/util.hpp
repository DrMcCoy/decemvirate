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
 *  Utility templates and functions.
 */

/* Based on ScummVM (<http://scummvm.org>) code, which is released
 * under the terms of version 2 or later of the GNU General Public
 * License.
 *
 * The original copyright note in ScummVM reads as follows:
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef COMMON_UTIL_HPP
#define COMMON_UTIL_HPP

#include <string>

#include "external/fmt/core.hpp"

#include "src/common/system.hpp"

/** Print a warning message to stderr.
 *
 *  Automatically prepends the text "WARNING: " and appends
 *  an exclamation mark and a newline.
 */
template<typename... Args> void warning(const std::string &format, const Args & ... args);

/** Print a status message to stderr.
 *
 *  Automatically appends a newline.
 */
template<typename... Args> void status(const std::string &format, const Args & ... args);

/** Print an info message to stdout.
 *
 *  Automatically appends a newline.
 */
template<typename... Args> void info(const std::string &format, const Args & ... args);

/** Print an error message to stderr.
 *
 *  Automatically prepends the text "ERROR: " and appends
 *  an exclamation mark and a newline.
 *
 *  Additionally, the program will immediately quit with
 *  return code 1.
 */
template<typename... Args> void NORETURN_PRE error(const std::string &format, const Args & ... args) NORETURN_POST;

// ---

void vwarning(const std::string &format, fmt::format_args args);
template<typename... Args>
void warning(const std::string &format, const Args & ... args) {
	vwarning(format, fmt::make_format_args(args...));
}

void vstatus(const std::string &format, fmt::format_args args);
template<typename... Args>
void status(const std::string &format, const Args & ... args) {
	vstatus(format, fmt::make_format_args(args...));
}

void vinfo(const std::string &format, fmt::format_args args);
template<typename... Args>
void info(const std::string &format, const Args & ... args) {
	vinfo(format, fmt::make_format_args(args...));
}

void NORETURN_PRE verror(const std::string &format, fmt::format_args args) NORETURN_POST;
template<typename... Args>
void NORETURN_PRE error(const std::string &format, const Args & ... args) {
	verror(format, fmt::make_format_args(args...));
}

#endif // COMMON_UTIL_HPP
