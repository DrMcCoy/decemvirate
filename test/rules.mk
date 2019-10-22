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

# Unit tests.

# Our Unit test framework, Google Test

include test/googletest/rules.mk

test_LIBS  = \
    test/googletest/libgtest.la \
    test/googletest/libgtest_main.la \
    $(GTEST_LIBS)
    $(EMPTY)

test_CXXFLAGS = $(GTEST_FLAGS) $(AM_CXXFLAGS)

include test/version/rules.mk
include test/common/rules.mk

TESTS += $(check_PROGRAMS)
