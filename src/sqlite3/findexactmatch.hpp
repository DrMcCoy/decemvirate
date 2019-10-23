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

#ifndef SQLITE3_FINDEXACTMATCH_HPP
#define SQLITE3_FINDEXACTMATCH_HPP

#include "src/sqlite3/mapstatement.hpp"

namespace SQLite3 {

/** Find results in a single table by exact match of a single column.
 *
 *  The resulting query will be of the form
 *
 *  SELECT * FROM table WHERE column = ? COLLATE NOCASE
 *
 *  where table and column are set to fix values in the constructor and
 *  the value to search for is changeable on each execution of the search.
 */
class FindExactMatch : public MapStatement {
public:
	FindExactMatch(DB &db, const std::string &table, const std::string &column);
	FindExactMatch(const FindExactMatch &) = delete;
	FindExactMatch(FindExactMatch &&) = default;
	~FindExactMatch() override = default;

	FindExactMatch &operator=(const FindExactMatch &) = delete;
	FindExactMatch &operator=(FindExactMatch &&) = default;

	template<typename T>
	void execute(T needle) {
		reset();
		bind(1, needle);

		MapStatement::execute();
	}
};

} // End of namespace SQLite3

#endif // SQLITE3_FINDEXACTMATCH_HPP
