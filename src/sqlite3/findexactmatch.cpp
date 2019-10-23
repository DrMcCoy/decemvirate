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
 *  SQLite3 database statement that SELECTS by an exact match.
 */

#include "external/fmt/core.hpp"

#include "src/sqlite3/findexactmatch.hpp"

namespace SQLite3 {

FindExactMatch::FindExactMatch(DB &db, const std::string &table, const std::string &column) :
		MapStatement(db, fmt::format("SELECT * from {} WHERE {} = ? COLLATE NOCASE", table, column)) {
}

} // End of namespace SQLite3
