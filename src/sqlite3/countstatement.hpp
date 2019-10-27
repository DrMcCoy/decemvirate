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
 *  Simple SQLite3 database statement that return a single count.
 */

#ifndef SQLITE3_COUNTSTATEMENT_HPP
#define SQLITE3_COUNTSTATEMENT_HPP

#include <string>

#include "src/sqlite3/statement.hpp"

namespace SQLite3 {

/** Query a singular numerical count value from a database.
 *
 *  This is a helper class intended for queries such as
 *
 *  SELECT COUNT(*) FROM ...
 *
 *  Just a single integer cell from a single row is evaluated.
 */
class CountStatement : public Statement {
public:
	CountStatement(DB &db, const std::string &query) : Statement(db, query) { }
	CountStatement(const CountStatement &) = delete;
	CountStatement(CountStatement &&) = default;
	~CountStatement() override = default;

	CountStatement &operator=(const CountStatement &) = delete;
	CountStatement &operator=(CountStatement &&) = default;

	size_t getCount();

protected:
	size_t _count { 0 };

	bool callback() override;
};

} // End of namespace SQLite3

#endif // SQLITE3_COUNTSTATEMENT_HPP
