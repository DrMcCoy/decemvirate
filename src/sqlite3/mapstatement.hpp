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

#ifndef SQLITE3_MAPSTATEMENT_HPP
#define SQLITE3_MAPSTATEMENT_HPP

#include <string>
#include <vector>
#include <map>

#include "src/sqlite3/types.hpp"
#include "src/sqlite3/statement.hpp"

namespace SQLite3 {

/** A SQL statement that populates a a map vector.
 *
 *  The returned rows of this arbitrary SQL query are accumulated into a
 *  vector of maps of variants. One map per row containing variants of cells,
 *  indexed by column name.
 */
class MapStatement : public Statement {
public:
	struct Column {
		size_t index;
		StorageClass type;
		std::string name;

		Column(size_t i, StorageClass t, const std::string &n) : index(i), type(t), name(n) { }
	};

	using Columns = std::vector<Column>;
	using ColumnMap = std::map<std::string, Column>;
	using Row = std::map<std::string, cell_t>;
	using Rows = std::vector<Row>;

	MapStatement(DB &db, const std::string &query) : Statement(db, query) { }
	MapStatement(const MapStatement &) = delete;
	MapStatement(MapStatement &&) = default;
	~MapStatement() override = default;

	MapStatement &operator=(const MapStatement &) = delete;
	MapStatement &operator=(MapStatement &&) = default;

	void reset() noexcept override;

	const Columns &getColumns() const { return _columns; }
	const ColumnMap &getColumnMap() const { return _columnMap; }

	const Rows &getRows() const { return _rows; }

	template<typename T>
	static T getCell(const Row &row, const std::string &name) {
		T value { };

		const Row::const_iterator cell = row.find(name);
		if (cell != row.end())
			if (std::holds_alternative<T>(cell->second))
				value = std::get<T>(cell->second);

		return value;
	}

	static std::vector<std::string> getCellArray(const Row &row, const std::string &name);


protected:
	bool callback() override;


	Columns _columns;
	ColumnMap _columnMap;

	Rows _rows;


	void queryColumns();
};

} // End of namespace SQLite3

#endif // SQLITE3_MAPSTATEMENT_HPP
