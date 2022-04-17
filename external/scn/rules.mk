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

# scnlib (<https://github.com/eliaskosunen/scnlib/>)

noinst_LTLIBRARIES += external/scn/libscn.la
external_scn_libscn_la_SOURCES =

external_scn_libscn_la_SOURCES += \
    external/scn/all.hpp \
    external/scn/detail/args.hpp \
    external/scn/detail/config.hpp \
    external/scn/detail/context.hpp \
    external/scn/detail/error.hpp \
    external/scn/detail/file.hpp \
    external/scn/detail/fwd.hpp \
    external/scn/detail/locale.hpp \
    external/scn/detail/parse_context.hpp \
    external/scn/detail/range.hpp \
    external/scn/detail/result.hpp \
    external/scn/detail/visitor.hpp \
    external/scn/fwd.hpp \
    external/scn/istream.hpp \
    external/scn/ranges/custom_impl.hpp \
    external/scn/ranges/ranges.hpp \
    external/scn/ranges/std_impl.hpp \
    external/scn/ranges/util.hpp \
    external/scn/reader/common.hpp \
    external/scn/reader/float.hpp \
    external/scn/reader/int.hpp \
    external/scn/reader/reader.hpp \
    external/scn/reader/string.hpp \
    external/scn/reader/types.hpp \
    external/scn/scan/common.hpp \
    external/scn/scan/getline.hpp \
    external/scn/scan/ignore.hpp \
    external/scn/scan/istream.hpp \
    external/scn/scan/list.hpp \
    external/scn/scan/scan.hpp \
    external/scn/scan/vscan.hpp \
    external/scn/scn.hpp \
    external/scn/tuple_return.hpp \
    external/scn/tuple_return/tuple_return.hpp \
    external/scn/tuple_return/util.hpp \
    external/scn/unicode/common.hpp \
    external/scn/unicode/unicode.hpp \
    external/scn/unicode/utf16.hpp \
    external/scn/unicode/utf8.hpp \
    external/scn/util/algorithm.hpp \
    external/scn/util/array.hpp \
    external/scn/util/expected.hpp \
    external/scn/util/math.hpp \
    external/scn/util/memory.hpp \
    external/scn/util/meta.hpp \
    external/scn/util/optional.hpp \
    external/scn/util/small_vector.hpp \
    external/scn/util/span.hpp \
    external/scn/util/string_view.hpp \
    external/scn/util/unique_ptr.hpp \
    external/scn/fast_float/fast_float.hpp \
    $(EMPTY)

external_scn_libscn_la_SOURCES += \
    external/scn/file.cpp \
    external/scn/locale.cpp \
    external/scn/reader_int.cpp \
    external/scn/vscan.cpp \
    external/scn/reader_float.cpp \
    $(EMPTY)

EXTRA_DIST += \
    external/scn/LICENSE \
    external/scn/README.Decemvirate \
    external/scn/README.md \
    external/scn/licenses/README.md \
    external/scn/licenses/fast_float-apache.txt \
    external/scn/licenses/fast_float-mit.txt \
    external/scn/licenses/fmt.rst \
    external/scn/licenses/nanorange.txt \
    external/scn/licenses/utfcpp.txt \
    $(EMPTY)
