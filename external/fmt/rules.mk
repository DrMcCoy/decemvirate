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

# fmt (<http://fmtlib.net/latest/>).

noinst_LTLIBRARIES += external/fmt/libfmt.la
external_fmt_libfmt_la_SOURCES =

external_fmt_libfmt_la_SOURCES += \
    external/fmt/chrono.hpp \
    external/fmt/color.hpp \
    external/fmt/compile.hpp \
    external/fmt/core.hpp \
    external/fmt/format-inl.hpp \
    external/fmt/format.hpp \
    external/fmt/locale.hpp \
    external/fmt/ostream.hpp \
    external/fmt/posix.hpp \
    external/fmt/printf.hpp \
    external/fmt/ranges.hpp \
    external/fmt/safe-duration-cast.hpp \
    $(EMPTY)

external_fmt_libfmt_la_SOURCES += \
    external/fmt/format.cpp \
    external/fmt/posix.cpp \
    $(EMPTY)

EXTRA_DIST += \
    external/fmt/README.Decemvirate \
    external/fmt/LICENSE.rst \
    external/fmt/README.rst \
    $(EMPTY)
