"""! Main entry point for Decemvirate.
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

from decemvirate_flask import decemvirate_flask
from util import Util


class Decemvirate:  # pylint: disable=too-few-public-methods
    """! Main Decemvirate application.
    """

    def run(self) -> None:
        """! Run the main Decemvirate application.
        """
        Util.set_pathfinder_path("data/pathfinder.sqlite")

        decemvirate_flask.run()


def main() -> None:
    """! Decemvirate main function, running the main app.
    """
    decemvirate: Decemvirate = Decemvirate()
    decemvirate.run()


if __name__ == '__main__':
    main()
