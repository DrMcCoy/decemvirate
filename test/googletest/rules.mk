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

# Google Test, Google's C++ test framework.

# Common build properties needed to build binaries with Google Test

GTEST_FLAGS =
GTEST_LIBS  =

# We need to include the Google Test include directory as a system
# include, to override any existing Google Test system includes.
# This is the recommended way (by Google) to deal with that issue.
GTEST_FLAGS += -isystem $(srcdir)/test/googletest/include \
               -isystem $(srcdir)/test/googletest/

# Use pthread, if we can (not supported with MinGW)
if HAVE_PTHREAD
if !WIN32
GTEST_FLAGS += $(PTHREAD_CFLAGS) -DGTEST_HAS_PTHREAD=1
GTEST_LIBS  += $(PTHREAD_LIBS)
else
GTEST_FLAGS += -DGTEST_HAS_PTHREAD=0
endif
else
GTEST_FLAGS += -DGTEST_HAS_PTHREAD=0
endif

# We don't want the macro TEST() to mess up the global namespace.
# Instead, we're going to call it by its longer name, GTEST_TEST().
GTEST_FLAGS += -DGTEST_DONT_DEFINE_TEST=1

# The same is true for TEST_F().
GTEST_FLAGS += -DGTEST_DONT_DEFINE_TEST_F=1

# Likewise, we don't want FAIL() and SUCCEED() defined either.
# We don't even use those.
GTEST_FLAGS += -DGTEST_DONT_DEFINE_SUCCEED=1 -DGTEST_DONT_DEFINE_FAIL=1

# The Google Test libraries

check_LTLIBRARIES += test/googletest/libgtest.la
test_googletest_libgtest_la_SOURCES =

test_googletest_libgtest_la_SOURCES += \
    test/googletest/include/gtest/gtest-death-test.hpp \
    test/googletest/include/gtest/gtest-message.hpp \
    test/googletest/include/gtest/gtest-param-test.hpp \
    test/googletest/include/gtest/gtest-printers.hpp \
    test/googletest/include/gtest/gtest-spi.hpp \
    test/googletest/include/gtest/gtest-test-part.hpp \
    test/googletest/include/gtest/gtest-typed-test.hpp \
    test/googletest/include/gtest/gtest.hpp \
    test/googletest/include/gtest/gtest_pred_impl.hpp \
    test/googletest/include/gtest/gtest_prod.hpp \
    test/googletest/include/gtest/internal/gtest-death-test-internal.hpp \
    test/googletest/include/gtest/internal/gtest-filepath.hpp \
    test/googletest/include/gtest/internal/gtest-internal.hpp \
    test/googletest/include/gtest/internal/gtest-linked_ptr.hpp \
    test/googletest/include/gtest/internal/gtest-param-util-generated.hpp \
    test/googletest/include/gtest/internal/gtest-param-util.hpp \
    test/googletest/include/gtest/internal/gtest-port-arch.hpp \
    test/googletest/include/gtest/internal/gtest-port.hpp \
    test/googletest/include/gtest/internal/gtest-string.hpp \
    test/googletest/include/gtest/internal/gtest-tuple.hpp \
    test/googletest/include/gtest/internal/gtest-type-util.hpp \
    test/googletest/include/gtest/internal/custom/gtest-port.hpp \
    test/googletest/include/gtest/internal/custom/gtest-printers.hpp \
    test/googletest/include/gtest/internal/custom/gtest.hpp \
    $(EMPTY)

test_googletest_libgtest_la_SOURCES += \
    test/googletest/src/gtest-all.cpp \
    $(EMPTY)

test_googletest_libgtest_la_CXXFLAGS = $(GTEST_FLAGS) $(AM_CXXFLAGS)

test_googletest_libgtest_la_LIBADD = \
    $(GTEST_LIBS) \
    $(EMPTY)

check_LTLIBRARIES += test/googletest/libgtest_main.la
test_googletest_libgtest_main_la_SOURCES =

test_googletest_libgtest_main_la_SOURCES += \
    test/googletest/src/gtest_main.cpp \
    $(EMPTY)

test_googletest_libgtest_main_la_LIBADD = \
    test/googletest/libgtest.la \
    $(GTEST_LIBS) \
    $(EMPTY)

test_googletest_libgtest_main_la_CXXFLAGS = $(GTEST_FLAGS) $(AM_CXXFLAGS)

EXTRA_DIST += \
    test/googletest/src/gtest-death-test.cpp \
    test/googletest/src/gtest-filepath.cpp \
    test/googletest/src/gtest-internal-inl.hpp \
    test/googletest/src/gtest-port.cpp \
    test/googletest/src/gtest-printers.cpp \
    test/googletest/src/gtest-test-part.cpp \
    test/googletest/src/gtest-typed-test.cpp \
    test/googletest/src/gtest.cpp \
    test/googletest/CONTRIBUTORS \
    test/googletest/LICENSE \
    test/googletest/README.Decemvirate \
    $(EMPTY)
