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
 *  String utility functions.
 */

#ifndef COMMON_STRING_HPP
#define COMMON_STRING_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <functional>

#include "external/utf8cpp/utf8.hpp"

namespace Common {

class String {
public:
	/** Does this string contain valid UTF-8 data? */
	static bool isValidUTF8(const std::string &str);

	/** Check this string for valid UTF-8 data and throw an exception if it is not. */
	static void enforceValidUTF8(const std::string &str);

	/** Trim whitespace and control characters from the left of the string, in place. */
	static void trimLeft(std::string &str);
	/** Trim whitespace and control characters from the right of the string, in place. */
	static void trimRight(std::string &str);
	/** Trim whitespace and control characters from the left and right of the string, in place. */
	static void trim(std::string &str);

	/** Trim whitespace and control characters from the left of the string, return a copy. */
	static std::string trimmedLeft(std::string str);
	/** Trim whitespace and control characters from the right of the string, return a copy. */
	static std::string trimmedRight(std::string str);
	/** Trim whitespace and control characters from the left and right of the string, return a copy. */
	static std::string trimmed(std::string str);

	/** Convert the string to lowercase, in place.
	 *  NOTE: Currently, it does *not* work with non-English characters! */
	static void makeLower(std::string &str);
	/** Convert the string to uppercase, in place.
	 *  NOTE: Currently, it does *not* work with non-English characters! */
	static void makeUpper(std::string &str);

	/** Return a lowercased copy of the string.
	 *  NOTE: Currently, it does *not* work with non-English characters! */
	static std::string toLower(std::string str);
	/** Return an uppercased copy of the string.
	 *  NOTE: Currently, it does *not* work with non-English characters! */
	static std::string toUpper(std::string str);

	/** Modify a string, replacing all occurrences of one substring with another string. */
	static void replaceAll(std::string &str, const std::string &from, const std::string &to);

	/** Return a modified string, replacing all occurrences of one substring with another string. */
	static std::string replacedAll(const std::string &str, const std::string &from, const std::string &to);

	/** Parse a string into any POD integer, float/double or bool type.
	 *
	 *  If allowEmpty is false, parse() will throw when encountering an empty string.
	 *  If allowEmpty is true and an empty string is encountered, parse() will
	 *  immediately return without modifying the value parameter.
	 */
	template<typename T> static void parse(const std::string &str, T &value, bool allowEmpty = false);

	/** Split the string into several parts separated by a single character.
	 *
	 *  @param  str The string to split.
	 *  @param  delim The character to split at.
	 *  @param  parts The parts after splitting.
	 *  @return The length (in bytes) of the longest part.
	 */
	static size_t split(const std::string &str, char delim, std::vector<std::string> &parts);

	/** Is this character a plain ASCII character? */
	static bool isASCII(char c);

	/** Compare two strings ignoring the case.
	 *  NOTE: Currently, it does *not* work with non-English characters! */
	static int compareIgnoreCase(const std::string &str1, const std::string &str2);
	/** Compare two strings ignoring the case.
	 *  NOTE: Currently, it does *not* work with non-English characters! */
	static bool equalsIgnoreCase(const std::string &str1, const std::string &str2);
	/** Compare two strings ignoring the case.
	 *  NOTE: Currently, it does *not* work with non-English characters! */
	static bool lessIgnoreCase(const std::string &str1, const std::string &str2);

	/** Case sensitive comparator. */
	struct sless : std::binary_function<std::string, std::string, bool> {
		bool operator() (const std::string &str1, const std::string &str2) const {
			return str1 < str2;
		}
	};
	/** Case insensitive comparator. */
	struct iless : std::binary_function<std::string, std::string, bool> {
		bool operator() (const std::string &str1, const std::string &str2) const {
			return lessIgnoreCase(str1, str2);
		}
	};

	/** Case sensitive hasher. */
	struct shash {
		size_t operator()(const std::string &str) const {
			return std::hash<std::string>{}(str);
		}
	};
	/** Case insensitive hasher. */
	struct ihash {
		size_t operator()(const std::string &str) const {
			return std::hash<std::string>{}(toLower(str));
		}
	};
};

} // End of namespace Common

#endif // COMMON_STRING_HPP
