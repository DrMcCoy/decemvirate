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

enum Result : int {
	kResultSuccess           = 0,
	kResultNotFound          = 1,
	kResultError             = 2,
	kResultMissingParameter  = 3,
	kResultInvalidCommand    = 4,
	kResultInvalidParameters = 5
};

static void showHelp(const cxxopts::Options &options) {
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
	fmt::print("  - finddefeat <name>\n");
	fmt::print("    Search German feats by name\n");
	fmt::print("  - findenfeat <name>\n");
	fmt::print("    Search English feats by name\n");
	fmt::print("\n");
}

static void printPub(const Pathfinder::GermanPublication &pub) {
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

static void printPub(const Pathfinder::EnglishPublication &pub) {
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

static void printGermanSpell(const Pathfinder::GermanSpell &spell) {
	fmt::print("German Name: {}\n", spell.getGermanName());
	fmt::print("English Name: {}\n", spell.getEnglishName());
	fmt::print("\n");
}

static void printGermanFeat(const Pathfinder::GermanFeat &feat) {
	std::string types;
	for (const auto &type : feat.getTypes())
		types += (types.empty() ? "" : ", ") + type;

	fmt::print("German Name: {}\n", feat.getGermanName());
	fmt::print("English Name: {}\n", feat.getEnglishName());
	fmt::print("Book: {}, Page: {}\n", feat.getBook(), feat.getPage());
	fmt::print("Description: {}\n", feat.getDescription());
	fmt::print("Types: {}\n", types);
	fmt::print("\n");
}

static Result findDEPub(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2)
		return kResultInvalidParameters;

	std::vector<Pathfinder::GermanPublication> pubs;

	if (std::optional<Pathfinder::GermanPublication> pub = db.findGermanPublicationByAbbreviation(command[1]); pub)
		pubs.push_back(*pub);

	size_t count = pubs.size();
	if (pubs.empty())
		pubs = db.findGermanPublicationsByTitle(command[1], count);

	if (pubs.empty())
		return kResultNotFound;

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

	return kResultSuccess;
}

static Result findENPub(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2)
		return kResultInvalidParameters;

	std::vector<Pathfinder::EnglishPublication> pubs;

	if (std::optional<Pathfinder::EnglishPublication> pub = db.findEnglishPublicationByProductCode(command[1]); pub)
		pubs.push_back(*pub);
	if (pubs.empty())
		if (std::optional<Pathfinder::EnglishPublication> pub = db.findEnglishPublicationByAbbreviation(command[1]); pub)
			pubs.push_back(*pub);

	size_t count = pubs.size();
	if (pubs.empty())
		pubs = db.findEnglishPublicationsByTitle(command[1], count);

	if (pubs.empty())
		return kResultNotFound;

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

	return kResultSuccess;
}

static Result findDESpell(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2)
		return kResultInvalidParameters;

	std::vector<Pathfinder::GermanSpell> spells = db.findGermanSpellsByGermanName(command[1]);
	if (spells.empty())
		return kResultNotFound;

	for (const auto &spell : spells) {
		printGermanSpell(spell);
	}

	return kResultSuccess;
}

static Result findENSpell(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2)
		return kResultInvalidParameters;

	std::vector<Pathfinder::GermanSpell> spells = db.findGermanSpellsByEnglishName(command[1]);
	if (spells.empty())
		return kResultNotFound;

	for (const auto &spell : spells) {
		printGermanSpell(spell);
	}

	return kResultSuccess;
}

static Result findDEFeat(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2)
		return kResultInvalidParameters;

	std::vector<Pathfinder::GermanFeat> feats = db.findGermanFeatsByGermanName(command[1]);
	if (feats.empty())
		return kResultNotFound;

	for (const auto &feat : feats) {
		printGermanFeat(feat);
	}

	return kResultSuccess;
}

static Result findENFeat(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2)
		return kResultInvalidParameters;

	std::vector<Pathfinder::GermanFeat> feats = db.findGermanFeatsByEnglishName(command[1]);
	if (feats.empty())
		return kResultNotFound;

	for (const auto &feat : feats) {
		printGermanFeat(feat);
	}

	return kResultSuccess;
}

static Result execute(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.empty())
		return kResultInvalidCommand;

	if (Common::String::equalsIgnoreCase(command[0], "finddepub")) {
		return findDEPub(command, db);
	} else if (Common::String::equalsIgnoreCase(command[0], "findenpub")) {
		return findENPub(command, db);
	} else if (Common::String::equalsIgnoreCase(command[0], "finddespell")) {
		return findDESpell(command, db);
	} else if (Common::String::equalsIgnoreCase(command[0], "findenspell")) {
		return findENSpell(command, db);
	} else if (Common::String::equalsIgnoreCase(command[0], "finddefeat")) {
		return findDEFeat(command, db);
	} else if (Common::String::equalsIgnoreCase(command[0], "findenfeat")) {
		return findENFeat(command, db);
	}

	return kResultInvalidCommand;
}

int main(int argc, char **argv) {
	Result result = kResultError;

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

		cxxopts::ParseResult parseResult = options.parse(params);

		if (parseResult.count("help") > 0) {
			showHelp(options);
			return static_cast<int>(kResultSuccess);
		}

		const std::string databaseFile = (parseResult.count("database") > 0) ? parseResult["database"].as<std::string>() : "";
		if (databaseFile.empty() || parseResult.count("command") == 0) {
			showHelp(options);
			return static_cast<int>(kResultMissingParameter);
		}

		Pathfinder::DB db(databaseFile, 0, 3);

		info("Openend Pathfinder database \"{}\": Version {}\n", db.getFile(), db.getVersionString());

		const std::vector<std::string> command = parseResult["command"].as<std::vector<std::string>>();
		result = execute(command, db);
		if (result != kResultSuccess && result != kResultNotFound) {
			showHelp(options);
		}

	} catch (...) {
		Common::exceptionDispatcherError();
		return static_cast<int>(kResultError);
	}

	return static_cast<int>(result);
}
