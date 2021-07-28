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
 *  German Pathfinder feats.
 */

#include "src/pathfinder/germanfeat.hpp"

namespace Pathfinder {

GermanFeat::GermanFeat(const SQLite3::MapStatement::Row &row) :
		_germanName(SQLite3::MapStatement::getCell<std::string>(row, "GermanName")),
		_englishName(SQLite3::MapStatement::getCell<std::string>(row, "EnglishName")),
		_book(SQLite3::MapStatement::getCell<std::string>(row, "Book")),
		_page(SQLite3::MapStatement::getCell<std::string>(row, "Page")),
		_description(SQLite3::MapStatement::getCell<std::string>(row, "Description")),
		_types(SQLite3::MapStatement::getCellArray(row, "Type")) {

}


FindGermanFeatsByGermanName::FindGermanFeatsByGermanName(SQLite3::DB &db, size_t limit) :
		SQLite3::FindLikeMatch(db, "GermanFeats", "GermanName", limit) {
}

std::vector<GermanFeat> FindGermanFeatsByGermanName::run(const std::string &name, size_t &count) {
	count = execute(name);

	std::vector<GermanFeat> feats;

	feats.reserve(_rows.size());
	for (const auto &row: _rows)
		feats.emplace_back(row);

	reset();
	return feats;
}

std::vector<GermanFeat> FindGermanFeatsByGermanName::run(const std::string &name) {
	size_t count;
	return run(name, count);
}


FindGermanFeatsByEnglishName::FindGermanFeatsByEnglishName(SQLite3::DB &db, size_t limit) :
		SQLite3::FindLikeMatch(db, "GermanFeats", "EnglishName", limit) {
}

std::vector<GermanFeat> FindGermanFeatsByEnglishName::run(const std::string &name, size_t &count) {
	count = execute(name);

	std::vector<GermanFeat> feats;

	feats.reserve(_rows.size());
	for (const auto &row: _rows)
		feats.emplace_back(row);

	reset();
	return feats;
}

std::vector<GermanFeat> FindGermanFeatsByEnglishName::run(const std::string &name) {
	size_t count;
	return run(name, count);
}

} // End of namespace Pathfinder
