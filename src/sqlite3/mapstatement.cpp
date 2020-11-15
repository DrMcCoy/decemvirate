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
 *  SQLite3 database statement that accumulates results into a map vector.
 */

#include <cassert>

#include <algorithm>

#include <sqlite3.h>

#include "external/fmt/core.hpp"

#include "src/common/string.hpp"
#include "src/common/error.hpp"

#include "src/sqlite3/mapstatement.hpp"

namespace SQLite3 {

void MapStatement::reset() noexcept {
	Statement::reset();

	_columns.clear();
	_columnMap.clear();
	_rows.clear();
}

void MapStatement::queryColumns() {
	if (!_columns.empty() || !_columnMap.empty())
		return;

	const int columnCount = sqlite3_column_count(_statement);
	if (columnCount < 0)
		return;

	_columns.reserve(columnCount);

	for (int i = 0; i < columnCount; i++) {
		const char *name = sqlite3_column_name(_statement, i);
		const int   type = sqlite3_column_type(_statement, i);

		_columns.emplace_back(i, getStorageClassFromSQLite3Type(type), name ? name : "");
		const Column &column = _columns.back();

		_columnMap.emplace(column.name, column);
	}
}

bool MapStatement::callback() {
	queryColumns();

	const int columnCount = sqlite3_column_count(_statement);
	if (static_cast<size_t>(columnCount) != _columns.size())
		throw Common::Exception("Column count mismatch while accumulating Statement results");

	const size_t n = _rows.size();
	_rows.resize(n + 1);

	for (int i = 0; i < columnCount; i++) {
		Column &column = _columns[i];

		const StorageClass type = getStorageClassFromSQLite3Type(sqlite3_column_type(_statement, i));
		if ((column.type != StorageClass::Null) && (type != StorageClass::Null) && (column.type != type))
			throw Common::Exception("Column type mismatch while accumulating Statement results");

		if (type != StorageClass::Null)
			column.type = type;

		cell_t cell;

		switch (type) {
			case StorageClass::Null:
				break;

			case StorageClass::Integer:
				cell.emplace<int64_t>(sqlite3_column_int64(_statement, i));
				break;

			case StorageClass::Real:
				cell.emplace<double>(sqlite3_column_double(_statement, i));
				break;

			case StorageClass::Text:
				{
					const char *text = reinterpret_cast<const char *>(sqlite3_column_text(_statement, i));
					cell.emplace<std::string>(text ? text : "");
				}
				break;

			case StorageClass::Blob:
				{
					const int   size = sqlite3_column_bytes(_statement, i);
					const void *blob = sqlite3_column_blob (_statement, i);
					if (size <= 0 || !blob)
						break;

					cell.emplace<std::vector<byte>>(static_cast<const byte *>(blob), static_cast<const byte *>(blob) + size);
				}
				break;
		}

		_rows.back().emplace(column.name, cell);
	}

	return true;
}

std::vector<std::string> MapStatement::getCellArray(const Row &row, const std::string &name) {
	const std::string str = getCell<std::string>(row, name);

	std::vector<std::string> array;
	Common::String::split(str, ',', array);

	return array;
}

} // End of namespace SQLite3
