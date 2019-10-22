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

#include <cctype>
#include <cstring>

#include <limits>
#include <algorithm>

#include "src/common/string.hpp"
#include "src/common/error.hpp"
#include "src/common/util.hpp"

namespace Common {

bool String::isValidUTF8(const std::string &str) {
	return ::utf8::is_valid(str.begin(), str.end());
}

void String::enforceValidUTF8(const std::string &str) {
	if (!isValidUTF8(str))
		throw Exception("Invalid UTF-8 data");
}

void String::trimLeft(std::string &str) {
	str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](char c) { return c > ' '; } ));
}

void String::trimRight(std::string &str) {
	str.erase(std::find_if(str.rbegin(), str.rend(), [](char c) { return c > ' '; }).base(), str.end());
}

void String::trim(std::string &str) {
	trimLeft(str);
	trimRight(str);
}

std::string String::trimmedLeft(std::string str) {
	trimLeft(str);
	return str;
}

std::string String::trimmedRight(std::string str) {
	trimRight(str);
	return str;
}

std::string String::trimmed(std::string str) {
	trim(str);
	return str;
}

void String::makeLower(std::string &str) {
	for_each(str.begin(), str.end(), [&](char &c) { c = std::tolower(c); } );
}

void String::makeUpper(std::string &str) {
	for_each(str.begin(), str.end(), [&](char &c) { c = std::toupper(c); } );
}

std::string String::toLower(std::string str) {
	makeLower(str);
	return str;
}

std::string String::toUpper(std::string str) {
	makeUpper(str);
	return str;
}

void String::replaceAll(std::string &str, const std::string &from, const std::string &to) {
	size_t startPos = 0;

	while((startPos = str.find(from, startPos)) != std::string::npos) {
		str.replace(startPos, from.length(), to);
		startPos += to.length();
	}
}

std::string String::replacedAll(const std::string &str, const std::string &from, const std::string &to) {
	std::string modified = str;

	replaceAll(modified, from, to);
	return modified;
}

int String::compareIgnoreCase(const std::string &str1, const std::string &str2) {
	return std::strcmp(toLower(str1).c_str(), toLower(str2).c_str());
}

bool String::equalsIgnoreCase(const std::string &str1, const std::string &str2) {
	return compareIgnoreCase(str1, str2) == 0;
}

bool String::lessIgnoreCase(const std::string &str1, const std::string &str2) {
	return compareIgnoreCase(str1, str2) < 0;
}

size_t String::split(const std::string &str, char delim, std::vector<std::string> &parts) {
	parts.clear();
	if (str.empty())
		return 0;

	size_t length = 0;
	parts.emplace_back();

	for (auto &&c : str) {
		if (c == delim) {
			length = std::max<size_t>(length, parts.back().size());
			parts.emplace_back();
			continue;
		}

		parts.back() += c;
	}

	return std::max<size_t>(length, parts.back().size());
}

bool String::isASCII(char c) {
	return (((uint8_t) c) & 0x80) == 0;
}

// Helper functions for String::parse()

static inline void parse(const char *nptr, char **endptr, signed long long &value) {
	value = strtoll(nptr, endptr, 0);
}

static inline void parse(const char *nptr, char **endptr, unsigned long long &value) {
	value = strtoull(nptr, endptr, 0);
}

static inline void parse(const char *nptr, char **endptr, signed long &value) {
	value = strtol(nptr, endptr, 0);
}

static inline void parse(const char *nptr, char **endptr, unsigned long &value) {
	value = strtoul(nptr, endptr, 0);
}

static inline void parse(const char *nptr, char **endptr, signed int &value) {
	signed long tmp = strtol(nptr, endptr, 0);
	if ((tmp < std::numeric_limits<signed int>::lowest()) || (tmp > std::numeric_limits<signed int>::max()))
		errno = ERANGE;

	value = (signed int) tmp;
}

static inline void parse(const char *nptr, char **endptr, unsigned int &value) {
	unsigned long tmp = strtoul(nptr, endptr, 0);
	if (tmp > std::numeric_limits<unsigned int>::max())
		errno = ERANGE;

	value = (unsigned int) tmp;
}

static inline void parse(const char *nptr, char **endptr, signed short &value) {
	signed long tmp = strtol(nptr, endptr, 0);
	if ((tmp < std::numeric_limits<signed short>::lowest()) || (tmp > std::numeric_limits<signed short>::max()))
		errno = ERANGE;

	value = (signed short) tmp;
}

static inline void parse(const char *nptr, char **endptr, unsigned short &value) {
	unsigned long tmp = strtoul(nptr, endptr, 0);
	if (tmp > std::numeric_limits<unsigned short>::max())
		errno = ERANGE;

	value = (unsigned short) tmp;
}

static inline void parse(const char *nptr, char **endptr, signed char &value) {
	signed long tmp = strtol(nptr, endptr, 0);
	if ((tmp < std::numeric_limits<signed char>::lowest()) || (tmp > std::numeric_limits<signed char>::max()))
		errno = ERANGE;

	value = (signed char) tmp;
}

static inline void parse(const char *nptr, char **endptr, unsigned char &value) {
	unsigned long tmp = strtoul(nptr, endptr, 0);
	if (tmp > std::numeric_limits<unsigned char>::max())
		errno = ERANGE;

	value = (unsigned char) tmp;
}

static inline void parse(const char *nptr, char **endptr, float &value) {
	value = strtof(nptr, endptr);
}

static inline void parse(const char *nptr, char **endptr, double &value) {
	value = strtod(nptr, endptr);
}


template<typename T> void String::parse(const std::string &str, T &value, bool allowEmpty) {
	if (str.empty()) {
		if (allowEmpty)
			return;

		throw Exception("Trying to parse an empty string");
	}

	const char *nptr = str.c_str();
	char *endptr = 0;

	T oldValue = value;

	errno = 0;
	::Common::parse(nptr, &endptr, value);

	while (endptr && std::isspace(*endptr))
		endptr++;

	try {
		if (endptr && (*endptr != '\0'))
			throw Exception("Can't convert \"{}\" to type of size {}", str, sizeof(T));
		if (errno == ERANGE)
			throw Exception("\"{}\" out of range for type of size {}", str, sizeof(T));
	} catch (...) {
		value = oldValue;
		throw;
	}
}

template<> void String::parse(const std::string &str, bool &value, bool allowEmpty) {
	if (str.empty()) {
		if (allowEmpty)
			return;

		throw Exception("Trying to parse an empty string");
	}

	// Valid true values are "true", "yes", "y", "on" and "1"

	bool oldValue = value;

	try {
		value = (equalsIgnoreCase(str, "true") ||
		         equalsIgnoreCase(str, "yes")  ||
		         equalsIgnoreCase(str, "y")    ||
		         equalsIgnoreCase(str, "on")   ||
		         str == "1") ?
			true : false;
	} catch (...) {
		value = oldValue;
		throw;
	}
}

template<> void String::parse(const std::string &str, std::string &value, bool UNUSED(allowEmpty)) {
	value = str;
}

template void String::parse<  signed char     >(const std::string &str,   signed char      &value, bool allowEmpty);
template void String::parse<unsigned char     >(const std::string &str, unsigned char      &value, bool allowEmpty);
template void String::parse<  signed short    >(const std::string &str,   signed short     &value, bool allowEmpty);
template void String::parse<unsigned short    >(const std::string &str, unsigned short     &value, bool allowEmpty);
template void String::parse<  signed int      >(const std::string &str,   signed int       &value, bool allowEmpty);
template void String::parse<unsigned int      >(const std::string &str, unsigned int       &value, bool allowEmpty);
template void String::parse<  signed long     >(const std::string &str,   signed long      &value, bool allowEmpty);
template void String::parse<unsigned long     >(const std::string &str, unsigned long      &value, bool allowEmpty);
template void String::parse<  signed long long>(const std::string &str,   signed long long &value, bool allowEmpty);
template void String::parse<unsigned long long>(const std::string &str, unsigned long long &value, bool allowEmpty);

template void String::parse<float             >(const std::string &str, float              &value, bool allowEmpty);
template void String::parse<double            >(const std::string &str, double             &value, bool allowEmpty);

} // End of namespace Common
