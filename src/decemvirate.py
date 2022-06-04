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

from importlib import metadata
from typing import Any

from flask import Flask, render_template

from pathfinder import Pathfinder

PACKAGE_NAME = "decemvirate"


class Decemvirate(Flask):
    """! Main Decemvirate Flask application.
    """

    def _get_project_info(self) -> dict[str, Any]:
        """! Get project metadata information.

        @return A dict containing project metadata information.
        """
        project_metadata = metadata.metadata(PACKAGE_NAME)

        info = {}  # type: dict[str, Any]
        info["name"] = project_metadata["Name"]
        info["version"] = project_metadata["Version"]
        info["summary"] = project_metadata["Summary"]

        info["url"] = {}
        for i in project_metadata.get_all("Project-URL"):
            parsed = i.split(", ", 1)
            info["url"][parsed[0]] = parsed[1]

        info["db"] = str(self._pathfinder.version)

        return info

    def _inject_project_information(self) -> dict[str, Any]:
        """! Inject Decemvirate version information into templates.

        @return A dict with keys to inject into templates.
        """
        project_info = self._get_project_info()
        return {"decemvirate": project_info}

    def __init__(self, import_name):
        super().__init__(import_name)

        self._pathfinder = Pathfinder("data/pathfinder.sqlite", 0, 5)

        self.context_processor(self._inject_project_information)


decemvirate = Decemvirate(__name__)


@decemvirate.route("/")
def main_page() -> str:
    """! Decemvirate main page.
    """
    return render_template('decemvirate.html')


import static_files  # pylint: disable=cyclic-import,wrong-import-position,unused-import # noqa: F401,E402


def main() -> None:
    """! Decemvirate main function, running the Flask app.
     """
    decemvirate.run()


if __name__ == '__main__':
    main()
