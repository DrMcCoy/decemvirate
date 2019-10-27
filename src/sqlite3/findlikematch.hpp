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
 *  SQLite3 database statement that SELECTS by a LIKE match.
 */

#ifndef SQLITE3_FINDLIKEMATCH_HPP
#define SQLITE3_FINDLIKEMATCH_HPP

#include <limits>

#include "src/sqlite3/mapstatement.hpp"
#include "src/sqlite3/countstatement.hpp"

namespace SQLite3 {

/** Find results in a single table by LIKE match of a single column.
 *
 *  The number of results processed can be limited. The execute() method returns
 *  the number of full results available.
 *
 *  The resulting query will be of the form
 *
 *  SELECT * FROM table WHERE column LIKE %?%
 *
 *  or
 *
 *  SELECT * FROM table WHERE column LIKE %?% LIMIT limit
 *
 *  where table, column and limit are set to fix values in the constructor and
 *  the value to search for is changeable on each execution of the search.
 */
class FindLikeMatch : public MapStatement {
public:
	static constexpr size_t kNoLimit = std::numeric_limits<size_t>::max();

	FindLikeMatch(DB &db, const std::string &table, const std::string &column, size_t limit = kNoLimit);
	FindLikeMatch(const FindLikeMatch &) = delete;
	FindLikeMatch(FindLikeMatch &&) = default;
	~FindLikeMatch() override = default;

	FindLikeMatch &operator=(const FindLikeMatch &) = delete;
	FindLikeMatch &operator=(FindLikeMatch &&) = default;

	size_t execute(const std::string &needle);

private:
	CountStatement _count;

	size_t getCount(const std::string &needle);
};

} // End of namespace SQLite3

#endif // SQLITE3_FINDLIKEMATCH_HPP
