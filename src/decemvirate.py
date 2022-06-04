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

PACKAGE_NAME = "decemvirate"


app = Flask(__name__)


def _get_project_info() -> dict[str, Any]:
    """! Get project metadata information.

    @return A dict containing project metadata information.
    """
    project_metadata = metadata.metadata(PACKAGE_NAME)

    info = {}  # type: dict[str, Any]
    info["Name"] = project_metadata["Name"]
    info["Version"] = project_metadata["Version"]
    info["Summary"] = project_metadata["Summary"]

    info["Project-URL"] = {}
    for i in project_metadata.get_all("Project-URL"):
        parsed = i.split(", ", 1)
        info["Project-URL"][parsed[0]] = parsed[1]

    return info


@app.context_processor
def inject_project_information() -> dict[str, Any]:
    """! Inject Decemvirate version information into templates.

    @return A dict with keys to inject into templates.
    """
    project_info = _get_project_info()
    return {"decemvirate": project_info}


@app.route("/")
def decemvirate() -> str:
    """! Decemvirate main page.
    """
    return render_template('decemvirate.html')


def main() -> None:
    """! Decemvirate main function, running the Flask app.
     """
     app.run()


if __name__ == '__main__':
    main()
