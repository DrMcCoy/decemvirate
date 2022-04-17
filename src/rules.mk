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

# Main Decemvirate entry point.

bin_PROGRAMS += src/decemvirate
src_decemvirate_SOURCES =

src_decemvirate_SOURCES += \
    $(EMPTY)

src_decemvirate_SOURCES += \
    src/decemvirate.cpp \
    $(EMPTY)

src_decemvirate_LDADD = \
    src/pathfinder/libpathfinder.la \
    src/sqlite3/libsqlite3.la \
    src/common/libcommon.la \
    src/version/libversion.la \
    external/fmt/libfmt.la \
    external/scn/libscn.la \
    $(LDADD) \
    $(EMPTY)

# Subdirectories

include src/version/rules.mk
include src/common/rules.mk
include src/sqlite3/rules.mk
include src/pathfinder/rules.mk
