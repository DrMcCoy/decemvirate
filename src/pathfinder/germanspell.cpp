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

#include <algorithm>

#include "external/scn/scn.hpp"

#include "src/common/error.hpp"

#include "src/pathfinder/germanspell.hpp"

namespace Pathfinder {

GermanSpell::GermanSpell(const SQLite3::MapStatement::Row &row) :
		_germanName(SQLite3::MapStatement::getCell<std::string>(row, "GermanName")),
		_englishName(SQLite3::MapStatement::getCell<std::string>(row, "EnglishName")),
		_book(SQLite3::MapStatement::getCell<std::string>(row,"Book")),
		_page(SQLite3::MapStatement::getCell<std::string>(row, "Page")),
		_school(SQLite3::MapStatement::getCell<std::string>(row, "School")),
		_race(SQLite3::MapStatement::getCell<std::string>(row, "Race")),
		_description(SQLite3::MapStatement::getCell<std::string>(row, "Description")),
		_meta(SQLite3::MapStatement::getCell<std::string>(row, "Meta")),
		_classStrings(SQLite3::MapStatement::getCellArray(row, "Classes")) {

	parseClasses();
}

void GermanSpell::parseClasses() {
	_classes.reserve(_classStrings.size());

	for (const auto &str : _classStrings) {
		std::string name;
		uint8_t level;

		auto result = scn::scan(str, "{} {}", name, level);
		if (!result)
			throw Common::Exception("Can't parse class information \"{}\": {}", str, result.error().msg());

		_classes.emplace_back(name, level);
	}
}

uint8_t GermanSpell::getClassLevel(const std::string &className) const {
	auto it = std::find_if(_classes.begin(), _classes.end(), [&className](const Class &c) { return c.name == className; });
	if (it == _classes.end())
		return 255;

	return it->level;
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


FindGermanSpellsByClass::FindGermanSpellsByClass(SQLite3::DB &db, size_t limit) :
		SQLite3::FindRegexpMatch(db, "GermanSpells", "Classes", limit) {
}

std::string FindGermanSpellsByClass::formatArgument(const std::string &name, int level) {
	if (level >= 0)
		return fmt::format(".*\\b{}\\b {}.*", name, level);

	return fmt::format(".*\\b{}\\b.*", name);
}

std::vector<GermanSpell> FindGermanSpellsByClass::run(const std::string &name, int level, size_t &count) {
	count = execute(formatArgument(name, level));

	std::vector<GermanSpell> spells;

	spells.reserve(_rows.size());
	for (const auto &row: _rows)
		spells.emplace_back(row);

	reset();
	return spells;
}

std::vector<GermanSpell> FindGermanSpellsByClass::run(const std::string &name, int level) {
	size_t count;
	return run(name, level, count);
}

} // End of namespace Pathfinder
