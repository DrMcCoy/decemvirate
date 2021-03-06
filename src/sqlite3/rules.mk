# Decemvirate - A FLOSS Pathfinder TTRPG helper
#
# Decemvirate is the legal property of its developers, whose names
# can be found in the AUTHORS file distributed with this source
# distribution.
#
# Decemvirate is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of
# the License, or (at your option) any later version.
#
# Decemvirate is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public
# License along with Decemvirate. If not, see <http://www.gnu.org/licenses/>.

# Working with SQLite3.

noinst_LTLIBRARIES += src/sqlite3/libsqlite3.la
src_sqlite3_libsqlite3_la_SOURCES =

src_sqlite3_libsqlite3_la_SOURCES += \
    src/sqlite3/types.hpp \
    src/sqlite3/db.hpp \
    src/sqlite3/statement.hpp \
    src/sqlite3/countstatement.hpp \
    src/sqlite3/mapstatement.hpp \
    src/sqlite3/findexactmatch.hpp \
    src/sqlite3/findlikematch.hpp \
    $(EMPTY)

src_sqlite3_libsqlite3_la_SOURCES += \
    src/sqlite3/types.cpp \
    src/sqlite3/db.cpp \
    src/sqlite3/statement.cpp \
    src/sqlite3/countstatement.cpp \
    src/sqlite3/mapstatement.cpp \
    src/sqlite3/findexactmatch.cpp \
    src/sqlite3/findlikematch.cpp \
    $(EMPTY)
