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

# Top-level automake build recipe.

# Extra files to help with the sources
EXTRA_DIST += \
    .uncrustifyrc \
    $(EMPTY)

# Extra autotools files
EXTRA_DIST += \
    autogen.sh \
    $(EMPTY)

# Subdirectories

include doc/rules.mk

include src/rules.mk
