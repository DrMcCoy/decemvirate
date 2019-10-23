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
 *  Fundamental SQLite3 types.
 */

#include <sqlite3.h>

#include "src/sqlite3/types.hpp"

namespace SQLite3 {

StorageClass getStorageClassFromSQLite3Type(int type) {
	switch (type) {
		default:
		case SQLITE_NULL:
			return StorageClass::Null;

		case SQLITE_INTEGER:
			return StorageClass::Integer;

		case SQLITE_FLOAT:
			return StorageClass::Real;

		case SQLITE_TEXT:
			return StorageClass::Text;

		case SQLITE_BLOB:
			return StorageClass::Blob;
	}
}

} // End of namespace SQLite3
