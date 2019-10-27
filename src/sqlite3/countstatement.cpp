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

#include <sqlite3.h>

#include "src/sqlite3/countstatement.hpp"

namespace SQLite3 {

size_t CountStatement::getCount() {
	_count = 0;
	execute();

	return _count;
}

bool CountStatement::callback() {
	if (sqlite3_column_count(_statement) != 1)
		return false;

	if (sqlite3_column_type(_statement, 0) != SQLITE_INTEGER)
		return false;

	_count = sqlite3_column_int64(_statement, 0);

	return false;
}

} // End of namespace SQLite3
