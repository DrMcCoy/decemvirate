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
 *  German Pathfinder spells.
 */

#ifndef PATHFINDER_GERMANSPELL_HPP
#define PATHFINDER_GERMANSPELL_HPP

#include <string>
#include <vector>
#include <optional>

#include "src/sqlite3/findlikematch.hpp"
#include "src/sqlite3/findregexpmatch.hpp"

namespace Pathfinder {

/** A German Pathfinder spell. */
class GermanSpell {
public:
	struct Class {
		std::string name;
		uint8_t level;

		Class(const std::string n, uint8_t l) : name(n), level(l) { }
	};


	/** Read a German English Pathfinder spell from a database query result. */
	GermanSpell(const SQLite3::MapStatement::Row &row);

	/** Return the German name of the spell. */
	std::string getGermanName() const { return _germanName; }

	/** Return the English name of the spell. */
	std::string getEnglishName() const { return _englishName; }

	/** Return the German book abbreviation the spell is found in. */
	std::string getBook() const { return _book; }

	/** Return the page of the book the spell is found in. */
	std::string getPage() const { return _page; }

	/** Return the German name of the arcane school this spell belings to. */
	std::string getSchool() const { return _school; }

	/** Return the German name of the race this spell is limited to. */
	std::string getRace() const { return _race; }

	/** Return the German short description of the spell. */
	std::string getDescription() const { return _description; }

	/** Return the German short meta string of the spell's properties. */
	std::string getMeta() const { return _meta; }

	/** Return information about which classes have access to the spell. */
	std::vector<Class> getClasses() const { return _classes; }

	/** Return the spell level for a certain class, or 255 if the class has no access to the spell. */
	uint8_t getClassLevel(const std::string &className) const;


private:
	std::string _germanName;
	std::string _englishName;
	std::string _book;
	std::string _page;
	std::string _school;
	std::string _race;
	std::string _description;
	std::string _meta;

	std::vector<std::string> _classStrings;
	std::vector<Class> _classes;

	void parseClasses();
};


/** Find German spell by German name. */
class FindGermanSpellsByGermanName : public SQLite3::FindLikeMatch {
public:
	FindGermanSpellsByGermanName(SQLite3::DB &db, size_t limit = SQLite3::FindLikeMatch::kNoLimit);
	FindGermanSpellsByGermanName(const FindGermanSpellsByGermanName &) = delete;
	FindGermanSpellsByGermanName(FindGermanSpellsByGermanName &&) = default;
	~FindGermanSpellsByGermanName() override = default;

	FindGermanSpellsByGermanName &operator=(const FindGermanSpellsByGermanName &) = delete;
	FindGermanSpellsByGermanName &operator=(FindGermanSpellsByGermanName &&) = default;

	std::vector<GermanSpell> run(const std::string &name);
	std::vector<GermanSpell> run(const std::string &name, size_t &count);
};


/** Find German spell by English name. */
class FindGermanSpellsByEnglishName : public SQLite3::FindLikeMatch {
public:
	FindGermanSpellsByEnglishName(SQLite3::DB &db, size_t limit = SQLite3::FindLikeMatch::kNoLimit);
	FindGermanSpellsByEnglishName(const FindGermanSpellsByEnglishName &) = delete;
	FindGermanSpellsByEnglishName(FindGermanSpellsByEnglishName &&) = default;
	~FindGermanSpellsByEnglishName() override = default;

	FindGermanSpellsByEnglishName &operator=(const FindGermanSpellsByEnglishName &) = delete;
	FindGermanSpellsByEnglishName &operator=(FindGermanSpellsByEnglishName &&) = default;

	std::vector<GermanSpell> run(const std::string &name);
	std::vector<GermanSpell> run(const std::string &name, size_t &count);
};


/** Find German spell by class. */
class FindGermanSpellsByClass : public SQLite3::FindRegexpMatch {
public:
	FindGermanSpellsByClass(SQLite3::DB &db, size_t limit = SQLite3::FindRegexpMatch::kNoLimit);
	FindGermanSpellsByClass(const FindGermanSpellsByClass &) = delete;
	FindGermanSpellsByClass(FindGermanSpellsByClass &&) = default;
	~FindGermanSpellsByClass() override = default;

	FindGermanSpellsByClass &operator=(const FindGermanSpellsByClass &) = delete;
	FindGermanSpellsByClass &operator=(FindGermanSpellsByClass &&) = default;

	std::vector<GermanSpell> run(const std::string &name, int level);
	std::vector<GermanSpell> run(const std::string &name, int level, size_t &count);

private:
	std::string formatArgument(const std::string &name, int level);
};

} // End of namespace Pathfinder

#endif // PATHFINDER_GERMANSPELL_HPP
