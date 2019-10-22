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

# Unit tests for the Common namespace.

common_LIBS = \
    $(test_LIBS) \
    src/common/libcommon.la \
    test/version/libversion.la \
    external/fmt/libfmt.la \
    $(LDADD)

check_PROGRAMS                  += test/common/test_string
test_common_test_string_SOURCES  = test/common/string.cpp
test_common_test_string_LDADD    = $(common_LIBS)
test_common_test_string_CXXFLAGS = $(test_CXXFLAGS)
