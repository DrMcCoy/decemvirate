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

#include <cassert>

#include <sqlite3.h>

#include "src/common/error.hpp"

#include "src/sqlite3/statement.hpp"
#include "src/sqlite3/db.hpp"

namespace SQLite3 {

Statement::Statement(DB &db, const std::string &query) {
	try {
		if (sqlite3_prepare_v2(db._db, query.c_str(), query.size() + 1, &_statement, nullptr) != 0)
			throw Common::Exception("Failed to prepare SQLite statement: {}", sqlite3_errmsg(db._db));
	} catch (...) {
		sqlite3_finalize(_statement);
		throw;
	}

	assert(_statement);
}

Statement::~Statement() {
	sqlite3_finalize(_statement);
}

void Statement::bind(size_t i) {
	if (sqlite3_bind_null(_statement, i) != 0)
		throw Common::Exception("Failed to bind SQLite statement NULL parameter: {}",
		                        sqlite3_errmsg(sqlite3_db_handle(_statement)));
}

void Statement::bind(size_t i, int64_t integer) {
	if (sqlite3_bind_int64(_statement, i, integer) != 0)
		throw Common::Exception("Failed to bind SQLite statement int64 parameter: {}",
		                        sqlite3_errmsg(sqlite3_db_handle(_statement)));
}

void Statement::bind(size_t i, double floating) {
	if (sqlite3_bind_double(_statement, i, floating) != 0)
		throw Common::Exception("Failed to bind SQLite statement double parameter: {}",
		                        sqlite3_errmsg(sqlite3_db_handle(_statement)));
}

void Statement::bind(size_t i, const std::string &text) {
	if (sqlite3_bind_text(_statement, i, text.c_str(), text.size(), SQLITE_TRANSIENT) != 0)
		throw Common::Exception("Failed to bind SQLite statement text parameter: {}",
		                        sqlite3_errmsg(sqlite3_db_handle(_statement)));
}

void Statement::bind(size_t i, void *data, size_t size) {
	if (sqlite3_bind_blob64(_statement, i, data, size, SQLITE_TRANSIENT) != 0)
		throw Common::Exception("Failed to bind SQLite statement blob parameter: {}",
		                        sqlite3_errmsg(sqlite3_db_handle(_statement)));
}

void Statement::reset() noexcept {
	sqlite3_reset(_statement);
	sqlite3_clear_bindings(_statement);
}

void Statement::execute() {
	bool finished = false;

	while (!finished) {
		const int status = sqlite3_step(_statement);
		switch (status) {
			case SQLITE_BUSY:
				continue;

			case SQLITE_DONE:
				finished = true;
				break;

			case SQLITE_ROW:
				finished = !callback();
				break;

			default:
				throw Common::Exception("Failed to execute SQLite statement: {}",
				                        sqlite3_errmsg(sqlite3_db_handle(_statement)));
		}
	}
}

} // End of namespace SQLite3
