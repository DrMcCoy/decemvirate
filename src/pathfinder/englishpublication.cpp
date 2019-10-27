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

} // End of namespace Pathfinder
