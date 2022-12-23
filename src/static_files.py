"""! Static file serving.

This module contains routes to serve static files from several different directories.
"""

# Decemvirate - A FLOSS Pathfinder TTRPG helper
#
# Decemvirate is the legal property of its developers, whose names
# can be found in the AUTHORS file distributed with this source
# distribution.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as
# published by the Free Software Foundation, either version 3 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

from flask import Response, send_from_directory

from decemvirate_flask import decemvirate_flask


@decemvirate_flask.route('/css/<path:filename>')
def css(filename: str) -> Response:
    """! Serve a css style sheet.

    @param path  Path of the style sheet to serve relative to the css directory.

    @return A response containing the static file.
    """
    return send_from_directory('css', filename)
