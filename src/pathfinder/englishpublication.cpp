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
 *  English Pathfinder publications.
 */

#include "src/pathfinder/englishpublication.hpp"

namespace Pathfinder {

EnglishPublication::EnglishPublication(const SQLite3::MapStatement::Row &row) :
		_productCode(SQLite3::MapStatement::getCell<std::string>(row, "ProductCode")),
		_date(SQLite3::MapStatement::getCell<std::string>(row, "Date")),
		_title(SQLite3::MapStatement::getCell<std::string>(row, "Title")),
		_category(SQLite3::MapStatement::getCell<std::string>(row, "Category")),
		_abbreviation(SQLite3::MapStatement::getCell<std::string>(row, "Abbreviation")),
		_url(SQLite3::MapStatement::getCell<std::string>(row, "URL")),
		_isbns(SQLite3::MapStatement::getCellArray(row, "ISBN")) {

}


FindEnglishPublicationByProductCode::FindEnglishPublicationByProductCode(SQLite3::DB &db) :
		SQLite3::FindExactMatch(db, "EnglishPublications", "ProductCode") {
}

std::optional<EnglishPublication> FindEnglishPublicationByProductCode::run(const std::string &productCode) {
	execute(productCode);

	std::optional<EnglishPublication> publication = std::nullopt;
	if (!_rows.empty())
		publication = EnglishPublication(_rows[0]);

	reset();
	return publication;
}


FindEnglishPublicationByAbbreviation::FindEnglishPublicationByAbbreviation(SQLite3::DB &db) :
		SQLite3::FindExactMatch(db, "EnglishPublications", "Abbreviation") {
}

std::optional<EnglishPublication> FindEnglishPublicationByAbbreviation::run(const std::string &abbreviation) {
	execute(abbreviation);

	std::optional<EnglishPublication> publication = std::nullopt;
	if (!_rows.empty())
		publication = EnglishPublication(_rows[0]);

	reset();
	return publication;
}


FindEnglishPublicationsByTitle::FindEnglishPublicationsByTitle(SQLite3::DB &db, size_t limit) :
		SQLite3::FindLikeMatch(db, "EnglishPublications", "Title", limit) {
}

std::vector<EnglishPublication> FindEnglishPublicationsByTitle::run(const std::string &title, size_t &count) {
	count = execute(title);

	std::vector<EnglishPublication> publications;

	publications.reserve(_rows.size());
	for (const auto &row: _rows)
		publications.emplace_back(row);

	reset();
	return publications;
}

std::vector<EnglishPublication> FindEnglishPublicationsByTitle::run(const std::string &title) {
	size_t count;
	return run(title, count);
}

} // End of namespace Pathfinder
