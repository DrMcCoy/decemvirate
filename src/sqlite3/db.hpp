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

#ifndef SQLITE3_DB_HPP
#define SQLITE3_DB_HPP

#include <string>

namespace SQLite3 {

class DB {
public:
	enum class Mode {
		ReadOnly,       ///< Open the database for reading only.
		ReadWrite,      ///< Open the database for reading and writing.
		ReadWriteCreate ///< Open the database for reading and writing, and create if it doesn't exist yet.
	};

	DB(const std::string &file, Mode mode = Mode::ReadWriteCreate);
	DB(const DB &) = delete;
	DB(DB &&) = default;
	~DB();

	DB &operator=(const DB &) = delete;
	DB &operator=(DB &&) = default;

	std::string getFile() const noexcept { return _file; }

private:
	std::string _file;
	struct sqlite3 *_db { nullptr };

	friend class Statement;
};

} // End of namespace SQLite3

#endif // SQLITE3_DB_HPP
