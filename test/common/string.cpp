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
 *  Unit tests for our String utility functions.
 */

#include <string>

#include "gtest/gtest.hpp"

#include "src/common/string.hpp"
#include "src/common/error.hpp"

static const std::string validUTF8("F""\xC3""\xB6""\xC3""\xB6""b""\xC3""\xA4""r");
static const std::string invalidUTF8("F""\xC3");

static const std::string kTestString("Foobar Barfoo");

static const std::string kTestStringLower("foobar barfoo");
static const std::string kTestStringUpper("FOOBAR BARFOO");


GTEST_TEST(String, isValidUTF8) {
	EXPECT_TRUE(Common::String::isValidUTF8(validUTF8));

	EXPECT_FALSE(Common::String::isValidUTF8(invalidUTF8));
}

GTEST_TEST(String, enforceValidUTF8) {
	Common::String::enforceValidUTF8(validUTF8);

	EXPECT_THROW(Common::String::enforceValidUTF8(invalidUTF8), Common::Exception);
}

GTEST_TEST(String, trim) {
	std::string str1("  Foobar  ");
	std::string str2("  Foobar  ");
	std::string str3("  Foobar  ");

	EXPECT_STREQ(Common::String::trimmedLeft (str1).c_str(), "Foobar  ");
	EXPECT_STREQ(Common::String::trimmedRight(str2).c_str(), "  Foobar");
	EXPECT_STREQ(Common::String::trimmed     (str3).c_str(), "Foobar");

	EXPECT_STREQ(str1.c_str(), "  Foobar  ");
	EXPECT_STREQ(str2.c_str(), "  Foobar  ");
	EXPECT_STREQ(str3.c_str(), "  Foobar  ");

	Common::String::trimLeft(str1);
	Common::String::trimRight(str2);
	Common::String::trim(str3);

	EXPECT_STREQ(str1.c_str(), "Foobar  ");
	EXPECT_STREQ(str2.c_str(), "  Foobar");
	EXPECT_STREQ(str3.c_str(), "Foobar");
}

GTEST_TEST(String, upper) {
	std::string str(kTestString);

	EXPECT_STREQ(Common::String::toUpper(str).c_str(), kTestStringUpper.c_str());
	EXPECT_STREQ(str.c_str(), kTestString.c_str());

	Common::String::makeUpper(str);

	EXPECT_STREQ(str.c_str(), kTestStringUpper.c_str());
}

GTEST_TEST(String, lower) {
	std::string str(kTestString);

	EXPECT_STREQ(Common::String::toLower(str).c_str(), kTestStringLower.c_str());
	EXPECT_STREQ(str.c_str(), kTestString.c_str());

	Common::String::makeLower(str);

	EXPECT_STREQ(str.c_str(), kTestStringLower.c_str());
}

GTEST_TEST(String, replaceAll) {
	static const char *kTestString1   = "abababa";
	static const char *kResultString1 = "bbbbbbb";
	static const char *kTestString2   = "abababa";
	static const char *kResultString2 = "aaaa";
	static const char *kTestString3   = "abababa";
	static const char *kResultString3 = "bbbbbbbbbbb";
	static const char *kTestString4   = "aaaaaaa";
	static const char *kResultString4 = "aaaaaaaaaaaaaa";
	static const char *kTestString5   = "abababa";
	static const char *kResultString5 = "abababa";

	std::string str1 = kTestString1;
	EXPECT_STREQ(Common::String::replacedAll(str1, "a", "b").c_str(), kResultString1);
	EXPECT_STREQ(str1.c_str(), kTestString1);

	Common::String::replaceAll(str1, "a", "b");
	EXPECT_STREQ(str1.c_str(), kResultString1);

	std::string str2 = kTestString2;
	EXPECT_STREQ(Common::String::replacedAll(str2, "ab", "a").c_str(), kResultString2);
	EXPECT_STREQ(str2.c_str(), kTestString2);

	Common::String::replaceAll(str2, "ab", "a");
	EXPECT_STREQ(str2.c_str(), kResultString2);

	std::string str3 = kTestString3;
	EXPECT_STREQ(Common::String::replacedAll(str3, "a", "bb").c_str(), kResultString3);
	EXPECT_STREQ(str3.c_str(), kTestString3);

	Common::String::replaceAll(str3, "a", "bb");
	EXPECT_STREQ(str3.c_str(), kResultString3);

	std::string str4 = kTestString4;
	EXPECT_STREQ(Common::String::replacedAll(str4, "a", "aa").c_str(), kResultString4);
	EXPECT_STREQ(str4.c_str(), kTestString4);

	Common::String::replaceAll(str4, "a", "aa");
	EXPECT_STREQ(str4.c_str(), kResultString4);

	std::string str5 = kTestString5;
	EXPECT_STREQ(Common::String::replacedAll(str5, "c", "b").c_str(), kResultString5);
	EXPECT_STREQ(str5.c_str(), kTestString5);

	Common::String::replaceAll(str5, "c", "b");
	EXPECT_STREQ(str5.c_str(), kResultString5);
}

GTEST_TEST(String, split) {
	const std::string str("Foobar Barfoo Quux");

	std::vector<std::string> parts;
	const size_t maxLength = Common::String::split(str, ' ', parts);

	EXPECT_EQ(maxLength, 6);
	ASSERT_EQ(parts.size(), 3);

	EXPECT_STREQ(parts[0].c_str(), "Foobar");
	EXPECT_STREQ(parts[1].c_str(), "Barfoo");
	EXPECT_STREQ(parts[2].c_str(), "Quux");
}

GTEST_TEST(String, isASCII) {
	EXPECT_TRUE (Common::String::isASCII('F'));
	EXPECT_FALSE(Common::String::isASCII(0xF6));
}

GTEST_TEST(String, parseBool) {
	bool x = false;

	Common::String::parse("true", x);
	EXPECT_EQ(x, true);
	Common::String::parse("false", x);
	EXPECT_EQ(x, false);

	Common::String::parse("yes", x);
	EXPECT_EQ(x, true);
	Common::String::parse("no", x);
	EXPECT_EQ(x, false);

	Common::String::parse("y", x);
	EXPECT_EQ(x, true);
	Common::String::parse("n", x);
	EXPECT_EQ(x, false);

	Common::String::parse("on", x);
	EXPECT_EQ(x, true);
	Common::String::parse("off", x);
	EXPECT_EQ(x, false);

	Common::String::parse("1", x);
	EXPECT_EQ(x, true);
	Common::String::parse("0", x);
	EXPECT_EQ(x, false);

	Common::String::parse("foobar", x);
	EXPECT_EQ(x, false);
}

GTEST_TEST(String, parseInt8) {
	int8_t  x = 0;

	Common::String::parse("-23", x);
	EXPECT_EQ(x, -23);
	Common::String::parse( "23", x);
	EXPECT_EQ(x,  23);

	Common::String::parse("-0", x);
	EXPECT_EQ(x, 0);
	Common::String::parse( "0", x);
	EXPECT_EQ(x, 0);

	Common::String::parse("-128", x);
	EXPECT_EQ(x, INT8_MIN);
	Common::String::parse( "127", x);
	EXPECT_EQ(x, INT8_MAX);
}

GTEST_TEST(String, parseInt16) {
	int16_t x = 0;

	Common::String::parse("-23", x);
	EXPECT_EQ(x, -23);
	Common::String::parse( "23", x);
	EXPECT_EQ(x,  23);

	Common::String::parse("-0", x);
	EXPECT_EQ(x, 0);
	Common::String::parse( "0", x);
	EXPECT_EQ(x, 0);

	Common::String::parse("-32768", x);
	EXPECT_EQ(x, INT16_MIN);
	Common::String::parse( "32767", x);
	EXPECT_EQ(x, INT16_MAX);
}

GTEST_TEST(String, parseInt32) {
	int32_t x = 0;

	Common::String::parse("-23", x);
	EXPECT_EQ(x, -23);
	Common::String::parse( "23", x);
	EXPECT_EQ(x,  23);

	Common::String::parse("-0", x);
	EXPECT_EQ(x, 0);
	Common::String::parse( "0", x);
	EXPECT_EQ(x, 0);

	Common::String::parse("-2147483648", x);
	EXPECT_EQ(x, INT32_MIN);
	Common::String::parse( "2147483647", x);
	EXPECT_EQ(x, INT32_MAX);
}

GTEST_TEST(String, parseInt64) {
	int64_t x = 0;

	Common::String::parse("-23", x);
	EXPECT_EQ(x, -23);
	Common::String::parse( "23", x);
	EXPECT_EQ(x,  23);

	Common::String::parse("-0", x);
	EXPECT_EQ(x, 0);
	Common::String::parse( "0", x);
	EXPECT_EQ(x, 0);

	Common::String::parse("-9223372036854775808", x);
	EXPECT_EQ(x, INT64_MIN);
	Common::String::parse( "9223372036854775807", x);
	EXPECT_EQ(x, INT64_MAX);
}

GTEST_TEST(String, parseUInt8) {
	uint8_t  x = 0;

	Common::String::parse("23", x);
	EXPECT_EQ(x, 23);

	Common::String::parse( "0", x);
	EXPECT_EQ(x, 0);

	Common::String::parse("255", x);
	EXPECT_EQ(x, UINT8_MAX);
}

GTEST_TEST(String, parseUInt16) {
	uint16_t x = 0;

	Common::String::parse("23", x);
	EXPECT_EQ(x, 23);

	Common::String::parse( "0", x);
	EXPECT_EQ(x, 0);

	Common::String::parse("65535", x);
	EXPECT_EQ(x, UINT16_MAX);
}

GTEST_TEST(String, parseUInt32) {
	uint32_t x = 0;

	Common::String::parse("23", x);
	EXPECT_EQ(x, 23);

	Common::String::parse( "0", x);
	EXPECT_EQ(x, 0);

	Common::String::parse("4294967295", x);
	EXPECT_EQ(x, UINT32_MAX);
}

GTEST_TEST(String, parseUInt64) {
	uint64_t x = 0;

	Common::String::parse("23", x);
	EXPECT_EQ(x, 23);

	Common::String::parse( "0", x);
	EXPECT_EQ(x, 0);

	Common::String::parse("18446744073709551615", x);
	EXPECT_EQ(x, UINT64_MAX);
}

GTEST_TEST(String, parseSizeT) {
	size_t x = 0;

	Common::String::parse("23", x);
	EXPECT_EQ(x, 23);

	Common::String::parse( "0", x);
	EXPECT_EQ(x, 0);
}

GTEST_TEST(String, parseFloat) {
	float x = 0.0f;

	Common::String::parse("-1.0", x);
	EXPECT_FLOAT_EQ(x, -1.0f);
	Common::String::parse( "1.0", x);
	EXPECT_FLOAT_EQ(x,  1.0f);

	Common::String::parse( "0.0", x);
	EXPECT_FLOAT_EQ(x, 0.0f);
}

GTEST_TEST(String, parseDouble) {
	double x = 0.0;

	Common::String::parse("-1.0", x);
	EXPECT_DOUBLE_EQ(x, -1.0);
	Common::String::parse( "1.0", x);
	EXPECT_DOUBLE_EQ(x,  1.0);

	Common::String::parse( "0.0", x);
	EXPECT_DOUBLE_EQ(x, 0.0);
}
