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

# The main "controller" automake recipe. We're setting up all our
# global build variables here, then recursively include all other
# build recipe, creating a flat non-recursive automake setup.

# Use the m4 directory for extra m4 autoconf scripts.
ACLOCAL_AMFLAGS = -I m4 --install
# Build objects in the same directory as their source files.
AUTOMAKE_OPTIONS = subdir-objects

# Empty element to make the source lists easier editable.
EMPTY =

# Initialize the global lists.

noinst_HEADERS     =
noinst_LTLIBRARIES =

bin_PROGRAMS =

check_LTLIBRARIES =
check_PROGRAMS    =
TESTS             =

CLEANFILES =

EXTRA_DIST        =
dist_doc_DATA     =
dist_man1_MANS    =
dist_pkgdata_DATA =

# Library compile flags

LIBSF_DECEMVIRATE = $(DECEMVIRATE_CFLAGS)

LIBSF_GENERAL =

LIBSF = $(LIBSF_DECEMVIRATE) $(LIBSF_GENERAL)

# Library linking flags

LIBSL_DECEMVIRATE = $(DECEMVIRATE_LIBS)

LIBSL_GENERAL =

LIBSL = $(LIBSL_DECEMVIRATE) $(LIBSL_GENERAL)

# Other compiler flags

FLAGS_DIR   = -I$(srcdir)
FLAGS_DEBUG = $(GGDB)
FLAGS_STD   = $(STD)
FLAGS_OPT   = $(LTO) $(NATIVE)
FLAGS_WARN  = $(WARN) $(WERROR)

FLAGS       = $(FLAGS_DIR) $(FLAGS_DEBUG) $(FLAGS_STD) \
              $(FLAGS_OPT) $(FLAGS_WARN)

# Use pthread, if we can (not supported with MinGW)
if HAVE_PTHREAD
if !WIN32
FLAGS += $(PTHREAD_CFLAGS)
LIBSL += $(PTHREAD_LIBS)
endif
endif

# Putting it all together...

AM_CXXFLAGS = $(FLAGS) $(LIBSF)
AM_LDFLAGS  = $(FLAGS_OPT)
LDADD       = $(LIBSL)
LIBS        =

# Now include the top-level recipe file and through it, all the
# other build recipes.

include rules.mk
