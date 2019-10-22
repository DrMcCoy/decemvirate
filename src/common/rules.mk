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

# Common support code used all over the codebase.

noinst_LTLIBRARIES += src/common/libcommon.la
src_common_libcommon_la_SOURCES =

src_common_libcommon_la_SOURCES += \
    src/common/system.hpp \
    src/common/noreturn.hpp \
    src/common/fallthrough.hpp \
    src/common/types.hpp \
    src/common/endianness.hpp \
    src/common/util.hpp \
    src/common/error.hpp \
    src/common/string.hpp \
    $(EMPTY)

src_common_libcommon_la_SOURCES += \
    src/common/util.cpp \
    src/common/error.cpp \
    src/common/string.cpp \
    $(EMPTY)
