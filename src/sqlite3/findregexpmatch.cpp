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
 *  SQLite3 database statement that SELECTS by a REGEXP match.
 */

#include "external/fmt/core.hpp"

#include "src/sqlite3/findregexpmatch.hpp"

namespace SQLite3 {

FindRegexpMatch::FindRegexpMatch(DB &db, const std::string &table, const std::string &column, size_t limit) :
		MapStatement(db, fmt::format("SELECT * from {} WHERE lower({}) REGEXP lower(?) {}", table, column, (limit == kNoLimit) ? "" : fmt::format("LIMIT {}", limit))),
		_count(db, fmt::format("SELECT COUNT(*) from {} WHERE lower({}) REGEXP lower(?)", table, column)) {

}

size_t FindRegexpMatch::execute(const std::string &regexp) {
	reset();
	bind(1, regexp);

	MapStatement::execute();

	return getCount(regexp);
}

size_t FindRegexpMatch::getCount(const std::string &regexp) {
	_count.reset();
	_count.bind(1, regexp);

	return _count.getCount();
}

} // End of namespace SQLite3
