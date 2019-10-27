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
 *  German Pathfinder publications.
 */

#include <algorithm>

#include "src/pathfinder/germanpublication.hpp"

namespace Pathfinder {

GermanPublication::GermanPublication(const SQLite3::MapStatement::Row &row) :
		_productCode(SQLite3::MapStatement::getCell<std::string>(row, "ProductCode")),
		_title(SQLite3::MapStatement::getCell<std::string>(row, "Title")),
		_abbreviation(SQLite3::MapStatement::getCell<std::string>(row, "Abbreviation")),
		_statBlock(SQLite3::MapStatement::getCell<std::string>(row, "StatBlock")),
		_category(SQLite3::MapStatement::getCell<std::string>(row, "Category")),
		_date(SQLite3::MapStatement::getCell<std::string>(row, "Date")),
		_url(SQLite3::MapStatement::getCell<std::string>(row, "URL")),
		_commentary(SQLite3::MapStatement::getCell<std::string>(row, "Commentary")),
		_paizoProductCodes(SQLite3::MapStatement::getCellArray(row, "PaizoProductCodes")),
		_isbns(SQLite3::MapStatement::getCellArray(row, "ISBN")) {

}

bool GermanPublication::hasPaizoProductCode(const std::string &paizoProductCode) const {
	return std::find(_paizoProductCodes.begin(), _paizoProductCodes.end(), paizoProductCode) != _paizoProductCodes.end();
}


FindGermanPublicationByAbbreviation::FindGermanPublicationByAbbreviation(SQLite3::DB &db) :
		SQLite3::FindExactMatch(db, "GermanPublications", "Abbreviation") {
}

std::optional<GermanPublication> FindGermanPublicationByAbbreviation::run(const std::string &abbreviation) {
	execute(abbreviation);

	std::optional<GermanPublication> publication = std::nullopt;
	if (!_rows.empty())
		publication = GermanPublication(_rows[0]);

	reset();
	return publication;
}


FindGermanPublicationsByTitle::FindGermanPublicationsByTitle(SQLite3::DB &db, size_t limit) :
		SQLite3::FindLikeMatch(db, "GermanPublications", "Title", limit) {
}

std::vector<GermanPublication> FindGermanPublicationsByTitle::run(const std::string &title, size_t &count) {
	count = execute(title);

	std::vector<GermanPublication> publications;

	publications.reserve(_rows.size());
	for (const auto &row: _rows)
		publications.emplace_back(row);

	reset();
	return publications;
}

std::vector<GermanPublication> FindGermanPublicationsByTitle::run(const std::string &title) {
	size_t count;
	return run(title, count);
}


FindGermanPublicationsByPaizoCode::FindGermanPublicationsByPaizoCode(SQLite3::DB &db) :
		SQLite3::FindLikeMatch(db, "GermanPublications", "PaizoProductCodes") {
}

std::vector<GermanPublication> FindGermanPublicationsByPaizoCode::run(const std::string &paizoCode) {
	execute(paizoCode);

	std::vector<GermanPublication> publications;

	publications.reserve(_rows.size());
	for (const auto &row: _rows) {
		GermanPublication publication(row);

		if (publication.hasPaizoProductCode(paizoCode))
			publications.push_back(publication);
	}

	reset();
	return publications;
}

} // End of namespace Pathfinder
