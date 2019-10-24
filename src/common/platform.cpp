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

#include "src/common/system.hpp"

#if defined(WIN32)
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <shellapi.h>
	#include <wchar.h>
#endif

#if defined(UNIX)
	#include <pwd.h>
	#include <unistd.h>
#endif

#include "src/common/platform.hpp"

namespace Common {

// .--- getParameters() ---.
#if defined(WIN32)

// Convert a wide Unicode string to an UTF-8 string
std::string utf8Encode(const std::wstring &wstr) {
	if (wstr.empty())
		return std::string();

	const int length = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], static_cast<int>(wstr.size()),
	                                       nullptr, 0, nullptr, nullptr);

	std::string str(length, 0);

	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], static_cast<int>((int)wstr.size()),
	                    &str[0], length, nullptr, nullptr);

	return str;
}

/* On Windows, we're not going to use the passed-in argc and argv, since those are
 * usually in a local 8-bit encoding. Instead, we're calling Windows functions to
 * get the parameters in UTF-16, and convert them. */
std::vector<std::string> Platform::getParameters(int UNUSED(argc), char **UNUSED(argv)) {
	int argc;
	wchar_t **argv = CommandLineToArgvW(GetCommandLineW(), &argc);

	std::vector<std::string> args(argc);
	for (int i = 0; i < argc; i++)
		args[i] = utf8Encode(argv[i]);

	return args;
}

#else

/* On non-Windows system, we assume the parameters are already in UTF-8. */
std::vector<std::string> Platform::getParameters(int argc, char **argv) {
	std::vector<std::string> args(argc);
	for (int i = 0; i < argc; i++)
		args[i] = argv[i];

	return args;
}

#endif
// '--- getParameters() ---'

} // End of namespace Common
