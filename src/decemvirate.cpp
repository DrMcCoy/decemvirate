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
 *  The project's main entry point.
 */

#include <vector>
#include <string>

#include "external/fmt/core.hpp"

#include "external/cxxopts/cxxopts.hpp"

#include "src/version/version.hpp"

#include "src/common/util.hpp"
#include "src/common/string.hpp"
#include "src/common/error.hpp"
#include "src/common/platform.hpp"

#include "src/pathfinder/db.hpp"

void showHelp(const cxxopts::Options &options) {
	fmt::print("{}", options.help());
	fmt::print("\n");
	fmt::print("Supported commands:\n");
	fmt::print("  - finddepub <abbreviation/title>\n");
	fmt::print("    Search German publication by abbreviation or title\n");
	fmt::print("  - findenpub <code/abbreviation/title>\n");
	fmt::print("    Search English publication by product code, abbreviation or title\n");
	fmt::print("  - finddespell <name>\n");
	fmt::print("    Search German spells by name\n");
	fmt::print("  - findenspell <name>\n");
	fmt::print("    Search English spells by name\n");
	fmt::print("\n");
}

void printPub(const Pathfinder::GermanPublication &pub) {
	std::string isbns;
	for (const auto &isbn : pub.getISBNs())
		isbns += (isbns.empty() ? "" : ", ") + isbn;

	fmt::print("Title: {}\n", pub.getTitle());
	fmt::print("Product Code: {}\n", pub.getProductCode());
	fmt::print("Abbreviation: {}\n", pub.getAbbreviation());
	fmt::print("StatBlock: {}\n", pub.getStatBlock());
	fmt::print("Category: {}\n", pub.getCategory());
	fmt::print("Date: {}\n", pub.getDate());
	fmt::print("Commentary: {}\n", pub.getCommentary());
	fmt::print("URL: {}\n", pub.getURL());
	fmt::print("ISBNs: {}\n", isbns);
	fmt::print("\n");
}

void printPub(const Pathfinder::EnglishPublication &pub) {
	std::string isbns;
	for (const auto &isbn : pub.getISBNs())
		isbns += (isbns.empty() ? "" : ", ") + isbn;

	fmt::print("Title: {}\n", pub.getTitle());
	fmt::print("Product Code: {}\n", pub.getProductCode());
	fmt::print("Abbreviation: {}\n", pub.getAbbreviation());
	fmt::print("Category: {}\n", pub.getCategory());
	fmt::print("Date: {}\n", pub.getDate());
	fmt::print("URL: {}\n", pub.getURL());
	fmt::print("ISBNs: {}\n", isbns);
	fmt::print("\n");
}

void printGermanSpell(const Pathfinder::GermanSpell &spell) {
	fmt::print("German Name: {}\n", spell.getGermanName());
	fmt::print("English Name: {}\n", spell.getEnglishName());
	fmt::print("\n");
}

bool findDEPub(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2)
		return false;

	std::vector<Pathfinder::GermanPublication> pubs;

	if (std::optional<Pathfinder::GermanPublication> pub = db.findGermanPublicationByAbbreviation(command[1]); pub)
		pubs.push_back(*pub);

	size_t count = pubs.size();
	if (pubs.empty())
		pubs = db.findGermanPublicationsByTitle(command[1], count);

	if (pubs.empty())
		return true;

	for (const auto &pub : pubs) {
		printPub(pub);
	}

	if (count != pubs.size())
		fmt::print("Showing {} of {} results\n", pubs.size(), count);

	if (pubs.size() == 1) {
		const std::vector<Pathfinder::EnglishPublication> originals = db.findOriginals(pubs[0]);
		if (!originals.empty()) {
			fmt::print("This publication translates the following originals:\n\n");
			for (const auto &pub : originals) {
				printPub(pub);
			}
		}
	}

	return true;
}

bool findENPub(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2)
		return false;

	std::vector<Pathfinder::EnglishPublication> pubs;

	if (std::optional<Pathfinder::EnglishPublication> pub = db.findEnglishPublicationByProductCode(command[1]); pub)
		pubs.push_back(*pub);
	if (pubs.empty())
		if (std::optional<Pathfinder::EnglishPublication> pub = db.findEnglishPublicationByAbbreviation(command[1]); pub)
			pubs.push_back(*pub);

	size_t count = pubs.size();
	if (pubs.empty())
		pubs = db.findEnglishPublicationsByTitle(command[1], count);

	for (const auto &pub : pubs) {
		printPub(pub);
	}

	if (count != pubs.size())
		fmt::print("Showing {} of {} results\n", pubs.size(), count);

	if (pubs.size() == 1) {
		const std::vector<Pathfinder::GermanPublication> translations = db.findTranslations(pubs[0]);
		if (!translations.empty()) {
			fmt::print("This publication is translated in the following publications:\n\n");
			for (const auto &pub : translations) {
				printPub(pub);
			}
		}
	}

	return true;
}

bool findDESpell(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2)
		return false;

	std::vector<Pathfinder::GermanSpell> spells = db.findGermanSpellsByGermanName(command[1]);
	for (const auto &spell : spells) {
		printGermanSpell(spell);
	}

	return true;
}

bool findENSpell(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2)
		return false;

	std::vector<Pathfinder::GermanSpell> spells = db.findGermanSpellsByEnglishName(command[1]);
	for (const auto &spell : spells) {
		printGermanSpell(spell);
	}

	return true;
}

bool execute(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.empty())
		return false;

	if (Common::String::equalsIgnoreCase(command[0], "finddepub")) {
		return findDEPub(command, db);
	} else if (Common::String::equalsIgnoreCase(command[0], "findenpub")) {
		return findENPub(command, db);
	} else if (Common::String::equalsIgnoreCase(command[0], "finddespell")) {
		return findDESpell(command, db);
	} else if (Common::String::equalsIgnoreCase(command[0], "findenspell")) {
		return findENSpell(command, db);
	}

	return false;
}

int main(int argc, char **argv) {
	try {
		const std::vector<std::string> params = Common::Platform::getParameters(argc, argv);

		cxxopts::Options options(params[0], std::string(Version::getProjectNameVersion()) + " - A FLOSS Pathfinder TTRPG helper");
		options.add_options()
				( "h,help", "Show this text and exit" )
				( "d,database", "SQLite database to use (required)", cxxopts::value<std::string>() )
				( "command", "", cxxopts::value<std::vector<std::string>>())
			;

		options.parse_positional("command");
		options.positional_help("<command> [<parameters>]");

		cxxopts::ParseResult result = options.parse(params);

		if (result.count("help") > 0) {
			showHelp(options);
			return 0;
		}

		const std::string databaseFile = (result.count("database") > 0) ? result["database"].as<std::string>() : "";
		if (databaseFile.empty() || result.count("command") == 0) {
			showHelp(options);
			return 1;
		}

		Pathfinder::DB db(databaseFile, 0, 2);

		info("Openend Pathfinder database \"{}\": Version {}\n", db.getFile(), db.getVersionString());

		const std::vector<std::string> command = result["command"].as<std::vector<std::string>>();
		if (!execute(command, db)) {
			showHelp(options);
			return 1;
		}

	} catch (...) {
		Common::exceptionDispatcherError();
	}

	return 0;
}
