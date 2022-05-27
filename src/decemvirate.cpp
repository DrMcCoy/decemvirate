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

#include <functional>
#include <vector>
#include <string>

#include "external/fmt/core.hpp"

#include "external/scn/scan/scan.hpp"

#include "external/tao/json.hpp"

#include "external/cxxopts/cxxopts.hpp"

#include "src/version/version.hpp"

#include "src/common/util.hpp"
#include "src/common/string.hpp"
#include "src/common/error.hpp"
#include "src/common/platform.hpp"

#include "src/pathfinder/db.hpp"
#include "src/pathfinder/collection.hpp"

enum Result : int {
	kResultSuccess               = 0,
	kResultNotFound              = 1,
	kResultError                 = 2,
	kResultMissingParameter      = 3,
	kResultInvalidCommand        = 4,
	kResultInvalidParameters     = 5,
	kResultInvalidParameterCount = 6
};

namespace tao::json {
	template<>
	struct traits<Result> {
		template<template<typename...> class Traits>
		static void assign(tao::json::basic_value<Traits> &v, const Result &t) {
			v = static_cast<int>(t);
		}

		template<template< typename...> class Traits>
		[[nodiscard]] static Result as(const basic_value<Traits> &v) {
			return static_cast<Result>(v.template as<int>());
		}
	};
}

static const std::vector<std::string> kResultText = {
	"Success",
	"No results found",
	"Fatal error",
	"Mandatory parameter missing",
	"Invalid command",
	"Wrong parameters for command",
	"Wrong number of parameters for command"
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
	fmt::print("  - findspellbyclass <class> [<level>]\n");
	fmt::print("    Search spells by class (and level)\n");
	fmt::print("  - finddefeat <name>\n");
	fmt::print("    Search German feats by name\n");
	fmt::print("  - findenfeat <name>\n");
	fmt::print("    Search English feats by name\n");
	fmt::print("\n");
}

static void printError(const tao::json::value &error) {
	fmt::print(stderr, "{}\n", error.as<std::string>("text"));

	if (const tao::json::value *stack = error.find("stack"); stack) {
		bool first = true;

		for (const auto &s : stack->get_array()) {
			status("{}: {}", first ? "\nERROR" : "    Because", s.as<std::string>());
			first = false;
		}
	}
}

static void printVersion(const tao::json::value &version) {
	fmt::print("{}\n", version.as<std::string>("name_version_full"));
	fmt::print("{}\n", version.as<std::string>("url"));
	fmt::print("\n");
	fmt::print("{}\n", version.as<std::string>("authors"));

	if (const tao::json::value *db = version.find("database"); db) {
		fmt::print("\n");
		fmt::print("Pathfinder database \"{}\": Version {}\n", db->as<std::string>("path"), db->as<std::string>("version"));
	}
}

static void printFeat(const tao::json::value &feat) {
	std::string types;
	for (const auto &type : feat.at("types").get_array())
		types += (types.empty() ? "" : ", ") + type.as<std::string>();

	fmt::print("German Name: {}\n", feat.as<std::string>("german_name"));
	fmt::print("English Name: {}\n", feat.as<std::string>("english_name"));
	fmt::print("Book: {}, Page: {}\n", feat.as<std::string>("book"), feat.as<std::string>("page"));
	fmt::print("Description: {}\n", feat.as<std::string>("description"));
	fmt::print("Types: {}\n", types);
	fmt::print("\n");
}

static void printFeats(const tao::json::value &feats) {
	for (const auto &feat : feats.get_array())
		printFeat(feat);
}

static void printSpell(const tao::json::value &spell) {
	std::string classes;
	for (const auto &c : spell.at("classes").get_array())
		classes += (classes.empty() ? "" : ", ") + fmt::format("{} {}", c.as<std::string>("name"), c.as<int>("level"));

	fmt::print("German Name: {}\n", spell.as<std::string>("german_name"));
	fmt::print("English Name: {}\n", spell.as<std::string>("english_name"));
	fmt::print("Book: {}, Page: {}\n", spell.as<std::string>("book"), spell.as<std::string>("page"));
	fmt::print("Class: {}\n", classes);
	if (!spell.as<std::string>("race").empty())
		fmt::print("School: {}, Race: {}\n", spell.as<std::string>("school"), spell.as<std::string>("race"));
	else
		fmt::print("School: {}\n", spell.as<std::string>("school"));
	fmt::print("Meta: {}\n", spell.as<std::string>("meta"));
	fmt::print("Description: {}\n", spell.as<std::string>("description"));
	fmt::print("\n");
}

static void printSpells(const tao::json::value &spells) {
	for (const auto &spell : spells.get_array())
		printSpell(spell);
}

static void printGermanPub(const tao::json::value &pub) {
	std::string isbns;
	for (const auto &isbn : pub.at("isbns").get_array())
		isbns += (isbns.empty() ? "" : ", ") + isbn.as<std::string>();

	fmt::print("Title: {}\n", pub.as<std::string>("title"));
	fmt::print("Product Code: {}\n", pub.as<std::string>("product_code"));
	fmt::print("Abbreviation: {}\n", pub.as<std::string>("abbreviation"));
	fmt::print("StatBlock: {}\n", pub.as<std::string>("stat_block"));
	fmt::print("Category: {}\n", pub.as<std::string>("category"));
	fmt::print("Date: {}\n", pub.as<std::string>("date"));
	fmt::print("Commentary: {}\n", pub.as<std::string>("commentary"));
	fmt::print("URL: {}\n", pub.as<std::string>("url"));
	fmt::print("ISBNs: {}\n", isbns);
	fmt::print("\n");
}

static void printEnglishPub(const tao::json::value &pub) {
	std::string isbns;
	for (const auto &isbn : pub.at("isbns").get_array())
		isbns += (isbns.empty() ? "" : ", ") + isbn.as<std::string>();

	fmt::print("Title: {}\n", pub.as<std::string>("title"));
	fmt::print("Product Code: {}\n", pub.as<std::string>("product_code"));
	fmt::print("Abbreviation: {}\n", pub.as<std::string>("abbreviation"));
	fmt::print("Category: {}\n", pub.as<std::string>("category"));
	fmt::print("Date: {}\n", pub.as<std::string>("date"));
	fmt::print("URL: {}\n", pub.as<std::string>("url"));
	fmt::print("ISBNs: {}\n", isbns);
	fmt::print("\n");
}

static void printGermanPubs(const tao::json::value &pubs) {
	for (const auto &pub : pubs.get_array())
		printGermanPub(pub);

	if (pubs.get_array().size() == 1) {
		if (const tao::json::value *originals = pubs.at(0).find("originals"); originals && !originals->get_array().empty()) {
			fmt::print("This publication translates the following originals:\n\n");
			for (const auto &pub : originals->get_array())
				printEnglishPub(pub);
		}
	}
}

static void printEnglishPubs(const tao::json::value &pubs) {
	for (const auto &pub : pubs.get_array())
		printEnglishPub(pub);

	if (pubs.get_array().size() == 1) {
		if (const tao::json::value *translations = pubs.at(0).find("translations"); translations && !translations->get_array().empty()) {
			fmt::print("This publication is translated in the following publications:\n\n");
			for (const auto &pub : translations->get_array())
				printGermanPub(pub);
		}
	}
}

struct PrettyPrinter {
	const std::string type;
	const std::function<void(const tao::json::value &)> printer;
};

static const std::vector<PrettyPrinter> kPrettyPrinters = {
	{ "error"              , &printError       },
	{ "version"            , &printVersion     },
	{ "feat"               , &printFeats       },
	{ "spell"              , &printSpells      },
	{ "german_publication" , &printGermanPubs  },
	{ "english_publication", &printEnglishPubs }
};

static void print(const tao::json::value &json, bool asJSON) {
	if (asJSON) {
		fmt::print("{}\n", tao::json::to_string(json));
		return;
	}

	if (const tao::json::value *db = json.find("database"); db)
		info("Openend Pathfinder database \"{}\": Version {}\n", db->as<std::string>("path"), db->as<std::string>("version"));

	for (const auto &p : kPrettyPrinters)
		if (p.type == json.as<std::string>("type"))
			p.printer(json.at("data"));

	if (const tao::json::value *count = json.find("count"); count && count->as<size_t>() != json.at("data").get_array().size())
		fmt::print("Showing {} of {} results\n", json.at("data").get_array().size(), json.as<size_t>("count"));
}

static tao::json::value getDBInfo(Pathfinder::DB &db) {
	return tao::json::value({
		{ "version", db.getVersionString() },
		{ "path", db.getFile() }
	});
}

static tao::json::value getVersion(const std::string &databaseFile) {
	tao::json::value version = {
		{ "name", Version::getName() },
		{ "description", Version::getDescription() },
		{ "version", Version::getVersion() },
		{ "revision", Version::getRevision() },
		{ "revision_description", Version::getRevisionDescription() },
		{ "build_date", Version::getBuildDate() },
		{ "name_version", Version::getNameVersion() },
		{ "name_version_full", Version::getNameVersionFull() },
		{ "url", Version::getURL() },
		{ "authors", Version::getAuthors() },
		{ "copyright_date", Version::getCopyrightDate() },
		{ "copyright_holder", Version::getCopyrightHolder() }
	};

	if (!databaseFile.empty()) {
		try {
			Pathfinder::DB db(databaseFile, 0, 0);

			version.insert({ { "database", getDBInfo(db) } });

		} catch (...) {
		}
	}

	return tao::json::value({
		{ "type", "version" },
		{ "data", version }
	});
}

static tao::json::value createError(Result result) {
	return tao::json::value({
		{ "type", "error" },
		{ "data", {
			{ "code", result},
			{ "text", kResultText[result] }
		} }
	});
}

static Result extractError(const tao::json::value &json) {
	if (json.as<std::string>("type") == "error")
		return json.at("data").as<Result>("code");

	if (json.as<std::string>("type") == "version")
		return kResultSuccess;

	if (json.at("data").get_array().empty())
		return kResultNotFound;

	return kResultSuccess;
}

static tao::json::value findDEFeat(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2)
		return createError(kResultInvalidParameterCount);

	std::vector<Pathfinder::GermanFeat> feats = db.findGermanFeatsByGermanName(command[1]);
	Pathfinder::Collection::sortByGermanName(feats);

	return tao::json::value({
		{ "type", "feat" },
		{ "count", feats.size() },
		{ "data", feats }
	});
}

static tao::json::value findENFeat(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2)
		return createError(kResultInvalidParameterCount);

	std::vector<Pathfinder::GermanFeat> feats = db.findGermanFeatsByEnglishName(command[1]);
	Pathfinder::Collection::sortByEnglishName(feats);

	return tao::json::value({
		{ "type", "feat" },
		{ "count", feats.size() },
		{ "data", feats }
	});
}

static tao::json::value findDESpell(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2)
		return createError(kResultInvalidParameterCount);

	std::vector<Pathfinder::GermanSpell> spells = db.findGermanSpellsByGermanName(command[1]);
	Pathfinder::Collection::sortByGermanName(spells);

	return tao::json::value({
		{ "type", "spell" },
		{ "count", spells.size() },
		{ "data", spells }
	});
}

static tao::json::value findENSpell(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2)
		return createError(kResultInvalidParameterCount);

	std::vector<Pathfinder::GermanSpell> spells = db.findGermanSpellsByEnglishName(command[1]);
	Pathfinder::Collection::sortByEnglishName(spells);

	return tao::json::value({
		{ "type", "spell" },
		{ "count", spells.size() },
		{ "data", spells }
	});
}

static tao::json::value findSpellByClass(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2 && command.size() != 3)
		return createError(kResultInvalidParameterCount);

	int level = -1;
	if (command.size() > 2)
		if (!scn::scan(command[2], "{}", level))
			return createError(kResultInvalidParameters);

	std::vector<Pathfinder::GermanSpell> spells = db.findGermanSpellsByClass(command[1], level);

	Pathfinder::Collection::sortByGermanName(spells);
	Pathfinder::Collection::sortByClassLevel(spells, command[1]);

	return tao::json::value({
		{ "type", "spell" },
		{ "count", spells.size() },
		{ "data", spells }
	});
}

static tao::json::value findDEPub(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2)
		return createError(kResultInvalidParameterCount);

	std::vector<Pathfinder::GermanPublication> pubs;

	if (std::optional<Pathfinder::GermanPublication> pub = db.findGermanPublicationByAbbreviation(command[1]); pub)
		pubs.push_back(*pub);

	size_t count = pubs.size();
	if (pubs.empty())
		pubs = db.findGermanPublicationsByTitle(command[1], count);

	tao::json::value pubsJSON = tao::json::empty_array;
	for (const auto &pub : pubs) {
		pubsJSON.push_back(tao::json::value(pub).merge({ { "originals", db.findOriginals(pub) } }));
	}

	return tao::json::value({
		{ "type", "german_publication" },
		{ "count", count },
		{ "data", pubsJSON }
	});
}

static tao::json::value findENPub(const std::vector<std::string> &command, Pathfinder::DB &db) {
	if (command.size() != 2)
		return createError(kResultInvalidParameterCount);

	std::vector<Pathfinder::EnglishPublication> pubs;

	if (std::optional<Pathfinder::EnglishPublication> pub = db.findEnglishPublicationByProductCode(command[1]); pub)
		pubs.push_back(*pub);
	if (pubs.empty())
		if (std::optional<Pathfinder::EnglishPublication> pub = db.findEnglishPublicationByAbbreviation(command[1]); pub)
			pubs.push_back(*pub);

	size_t count = pubs.size();
	if (pubs.empty())
		pubs = db.findEnglishPublicationsByTitle(command[1], count);

	tao::json::value pubsJSON = tao::json::empty_array;
	for (const auto &pub : pubs) {
		pubsJSON.push_back(tao::json::value(pub).merge({ { "translations", db.findTranslations(pub) } }));
	}

	return tao::json::value({
		{ "type", "english_publication" },
		{ "count", count },
		{ "data", pubsJSON }
	});
}

struct Command {
	const std::string name;
	const std::function<tao::json::value(const std::vector<std::string> &, Pathfinder::DB &)> func;
};

static const std::vector<Command> kCommands = {
	{ "finddefeat"      , &findDEFeat       },
	{ "findenfeat"      , &findENFeat       },
	{ "finddespell"     , &findDESpell      },
	{ "findenspell"     , &findENSpell      },
	{ "findspellbyclass", &findSpellByClass },
	{ "finddepub"       , &findDEPub        },
	{ "findenpub"       , &findENPub        }
};

static tao::json::value execute(const std::vector<std::string> &command, Pathfinder::DB &db) {
	for (const auto &c : kCommands ) {
		if (!command.empty() && Common::String::equalsIgnoreCase(command[0], c.name)) {
			return c.func(command, db);
		}
	}

	return createError(kResultInvalidCommand);
}

int main(int argc, char **argv) {
	Result result = kResultError;
	bool asJSON = false;

	try {
		const std::vector<std::string> params = Common::Platform::getParameters(argc, argv);

		cxxopts::Options options(params[0], std::string(Version::getNameVersion()) + " - " + Version::getDescription());
		options.add_options()
				( "h,help", "Show this text and exit" )
				( "version", "Display version and exit" )
				( "j,json", "Output information in JSON format instead of plain text" )
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

		asJSON = parseResult.count("json") > 0;
		const std::string databaseFile = (parseResult.count("database") > 0) ? parseResult["database"].as<std::string>() : "";

		if (parseResult.count("version") > 0) {
			print(getVersion(databaseFile), asJSON);
			return static_cast<int>(kResultSuccess);
		}

		if (databaseFile.empty() || parseResult.count("command") == 0) {
			showHelp(options);
			return static_cast<int>(kResultMissingParameter);
		}

		Pathfinder::DB db(databaseFile, 0, 5);

		const std::vector<std::string> command = parseResult["command"].as<std::vector<std::string>>();
		const tao::json::value json = execute(command, db).merge({ {"database", getDBInfo(db) } });

		print(json, asJSON);

		result = extractError(json);

	} catch (...) {
		const tao::json::value stack = Common::exceptionDispatcherJSON();

		tao::json::value error = createError(kResultError);
		error["data"]["stack"] = stack;

		print(error, asJSON);

		return static_cast<int>(extractError(error));
	}

	return static_cast<int>(result);
}
