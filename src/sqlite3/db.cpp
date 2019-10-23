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
 *  SQLite3 database.
 */

#include <cassert>

#include <sqlite3.h>

#include "src/common/error.hpp"

#include "src/sqlite3/db.hpp"

namespace SQLite3 {

DB::DB(const std::string &file, Mode mode) : _file(file) {
	int flags = 0;
	switch (mode) {
		case Mode::ReadOnly:
			flags = SQLITE_OPEN_READONLY;
			break;

		case Mode::ReadWrite:
			flags = SQLITE_OPEN_READWRITE;
			break;

		case Mode::ReadWriteCreate:
			flags = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
			break;
	}

	try {
		if (sqlite3_open_v2(_file.c_str(), &_db, flags, nullptr) != 0)
			throw Common::Exception("Failed to open SQLite DB: {}", sqlite3_errmsg(_db));
	} catch (...) {
		sqlite3_close(_db);
		throw;
	}

	assert(_db);
}

DB::~DB() {
	sqlite3_close(_db);
};

} // End of namespace SQLite3
