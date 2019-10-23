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

#ifndef SQLITE3_TYPES_HPP
#define SQLITE3_TYPES_HPP

#include <string>
#include <vector>
#include <variant>

#include "src/common/types.hpp"

namespace SQLite3 {

enum class StorageClass {
	Null,
	Integer,
	Real,
	Text,
	Blob
};

StorageClass getStorageClassFromSQLite3Type(int type);

using cell_t = std::variant<std::monostate, int64_t, double, std::string, std::vector<byte>>;

} // End of namespace SQLite3

#endif // SQLITE3_TYPES_HPP
