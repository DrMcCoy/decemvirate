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

#include "src/pathfinder/germanspell.hpp"

namespace Pathfinder {

GermanSpell::GermanSpell(const SQLite3::MapStatement::Row &row) :
		_germanName(SQLite3::MapStatement::getCell<std::string>(row, "GermanName")),
		_englishName(SQLite3::MapStatement::getCell<std::string>(row, "EnglishName")) {

}


FindGermanSpellsByGermanName::FindGermanSpellsByGermanName(SQLite3::DB &db, size_t limit) :
		SQLite3::FindLikeMatch(db, "GermanSpells", "GermanName", limit) {
}

std::vector<GermanSpell> FindGermanSpellsByGermanName::run(const std::string &name, size_t &count) {
	count = execute(name);

	std::vector<GermanSpell> spells;

	spells.reserve(_rows.size());
	for (const auto &row: _rows)
		spells.emplace_back(row);

	reset();
	return spells;
}

std::vector<GermanSpell> FindGermanSpellsByGermanName::run(const std::string &name) {
	size_t count;
	return run(name, count);
}


FindGermanSpellsByEnglishName::FindGermanSpellsByEnglishName(SQLite3::DB &db, size_t limit) :
		SQLite3::FindLikeMatch(db, "GermanSpells", "EnglishName", limit) {
}

std::vector<GermanSpell> FindGermanSpellsByEnglishName::run(const std::string &name, size_t &count) {
	count = execute(name);

	std::vector<GermanSpell> spells;

	spells.reserve(_rows.size());
	for (const auto &row: _rows)
		spells.emplace_back(row);

	reset();
	return spells;
}

std::vector<GermanSpell> FindGermanSpellsByEnglishName::run(const std::string &name) {
	size_t count;
	return run(name, count);
}

} // End of namespace Pathfinder
