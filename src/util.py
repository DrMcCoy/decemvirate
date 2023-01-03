"""! Utility functions.
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

import email.utils
from importlib import metadata
from pathlib import Path
from typing import Any

from flask import g, has_app_context, request

from pathfinder import Pathfinder

PACKAGE_NAME = "decemvirate"
COPYRIGHT_YEARS = "2019-2023"

PATHFINDER_VERSION_REQ_MAJOR = 0
PATHFINDER_VERSION_MIN_MINOR = 8


class Util:
    """! Utility functions.
    """

    pathfinder_path: Path | None = None

    @staticmethod
    def _path_nonempty(path: Path | str | None) -> Path | None:
        """! Make sure a path is non-empty.

        @param path  The path to check for non-emptyness.

        @return A non-empty Path or None if the path is empty.
        """
        if path is None or str(path) == "" or str(path).isspace():
            return None

        return Path(path)

    @staticmethod
    def get_project_info() -> dict[str, Any]:
        """! Get project metadata information.

        @return A dict containing project metadata information.
        """
        project_metadata = metadata.metadata(PACKAGE_NAME)

        info: dict[str, Any] = {}
        info["name"] = project_metadata["Name"]
        info["version"] = project_metadata["Version"]
        info["summary"] = project_metadata["Summary"]
        info["years"] = COPYRIGHT_YEARS

        # Project URLs are stored with the "type" information pasted in front
        info["url"] = {}
        for i in project_metadata.get_all("Project-URL"):
            parsed = i.split(", ", 1)
            info["url"][parsed[0]] = parsed[1]

        # Authors are stored in an email address format, pasted together into one string
        info["authors"] = []
        for address in project_metadata["Author-email"].split(", "):
            parsed = email.utils.parseaddr(address)
            info["authors"].append(f"{parsed[0]} <{parsed[1]}>")

        info["db"] = None

        # Add the Pathfinder database version if available
        try:
            pathfinder: Pathfinder = Util.get_pathfinder()
            info["db"] = str(pathfinder.version)
        except BaseException:  # pylint: disable=broad-except
            pass

        return info

    @staticmethod
    def set_pathfinder_path(path: Path | str | None = None) -> None:
        """! Set the Pathfinder database path to use.
        """
        Util.pathfinder_path = Util._path_nonempty(path)

    @staticmethod
    def try_pathfinder() -> None:
        """! Try open the currently set Pathfinder database.
        """
        pathfinder: Pathfinder = Util.get_pathfinder()
        Util.close_pathfinder(pathfinder)

    @staticmethod
    def get_pathfinder() -> Pathfinder:
        """! Open the Pathfinder database and return it.

        Stored in Flask's app context if available.
        """
        path: Path | None = Util.pathfinder_path
        if path is None:
            raise ValueError("No Pathfinder database set")

        # No app context? Open and return the database directly.
        if not has_app_context():
            return Pathfinder(path, PATHFINDER_VERSION_REQ_MAJOR, PATHFINDER_VERSION_MIN_MINOR)

        # We've got a different database open -> close it
        if hasattr(g, "pathfinder_path") and path != g.pathfinder_path:
            Util.close_pathfinder()

        # Open the database, if necessary
        if not hasattr(g, "pathfinder"):
            g.pathfinder = Pathfinder(path, PATHFINDER_VERSION_REQ_MAJOR, PATHFINDER_VERSION_MIN_MINOR)

        return g.pathfinder

    @staticmethod
    def close_pathfinder(pathfinder: Pathfinder | None = None) -> None:
        """! Close the currently opened Pathfinder database.
        """
        if not has_app_context():
            del pathfinder
            return

        if hasattr(g, "pathfinder_path"):
            del g.pathfinder_path
        if hasattr(g, "pathfinder"):
            del g.pathfinder

    @staticmethod
    def get_remote_address():
        """! Return the remote address accessing Decemvirate.
        """
        if 'X-Forwarded-For' in request.headers:
            return request.headers.getlist("X-Forwarded-For")[0].rpartition(' ')[-1]

        return request.remote_addr or 'unknown'
