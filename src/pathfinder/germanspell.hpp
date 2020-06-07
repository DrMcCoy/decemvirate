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

namespace Pathfinder {

/** A German Pathfinder spell. */
class GermanSpell {
public:
	/** Read a German English Pathfinder spell from a database query result. */
	GermanSpell(const SQLite3::MapStatement::Row &row);

	/** Return the German name of the spell. */
	std::string getGermanName() const { return _germanName; }

	/** Return the English name of the spell. */
	std::string getEnglishName() const { return _englishName; }


private:
	std::string _germanName;
	std::string _englishName;
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

} // End of namespace Pathfinder

#endif // PATHFINDER_GERMANSPELL_HPP
