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
 *  SQLite3 database statement.
 */

#ifndef SQLITE3_STATEMENT_HPP
#define SQLITE3_STATEMENT_HPP

#include <string>

#include "src/common/types.hpp"

namespace SQLite3 {

class DB;

/** A SQL statement over a SQLite3 database.
 *
 *  A statement contains a single SQL query, with optional positional, variable parameters.
 *  Each parameter can be bound, that is have a value assigned, before the statement
 *  is executed.
 */
class Statement {
public:
	Statement(DB &db, const std::string &query);
	Statement(const Statement &) = delete;
	Statement(Statement &&) = default;
	virtual ~Statement();

	Statement &operator=(const Statement &) = delete;
	Statement &operator=(Statement &&) = default;

	void bind(size_t i);
	void bind(size_t i, int64_t integer);
	void bind(size_t i, double floating);
	void bind(size_t i, const std::string &text);
	void bind(size_t i, void *data, size_t size);

	/** Completely reset the statement, including unbinding all parameters. */
	virtual void reset() noexcept;

	/** Execute the statement, calling the callback for every row returned. */
	void execute();


protected:
	struct sqlite3_stmt *_statement { nullptr };

	virtual bool callback() = 0;
};

} // End of namespace SQLite3

#endif // SQLITE3_STATEMENT_HPP
