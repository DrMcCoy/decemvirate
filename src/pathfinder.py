"""! Pathfinder database handling.

This module handles all interactions with the Pathfinder SQLite3 database.
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

import sqlite3
from os import path
from pathlib import Path
from typing import Any


class Pathfinder:  # pylint: disable=too-few-public-methods
    """! Pathfinder database handling.

    This handles all interactions with the Pathfinder SQLite3 database.
    """

    class Version:
        """! Pathfinder database version information.
        """

        def __init__(self, major: int, minor: int, patch: int) -> None:
            """! Create a Pathfinder database version object.
            """
            self._major: int = major
            self._minor: int = minor
            self._patch: int = patch

        def __str__(self) -> str:
            """! Return a human-readable string describing this version object.
            """
            return f"{self._major}.{self._minor}.{self._patch}"

        def is_compatible(self, wanted: 'Pathfinder.Version') -> bool:
            """! Is this version compatible with the wanted version?

            Compatible means that the major version matches exactly and the wanted minor version is at least matched.

            @param wanted  The wanted version to match against.
            @return True if compatible, False otherwise.
            """
            if not isinstance(wanted, self.__class__):
                raise NotImplementedError

            return self.major == wanted.major and self.minor >= wanted.minor

        @property
        def major(self) -> int:
            """! The major part of the version number.
            """
            return self._major

        @property
        def minor(self) -> int:
            """! The minor part of the version number.
            """
            return self._minor

        @property
        def patch(self) -> int:
            """! The patch part of the version number.
            """
            return self._patch

    @staticmethod
    def _get_version(database: sqlite3.Connection) -> Version:
        """! Read version information out of the db.

        @param database  SQLite3 database to use.
        @return A dict containing the version information
        """
        result: sqlite3.Row = database.execute("SELECT * from Version LIMIT 1").fetchone()
        return Pathfinder.Version(result["Major"], result["Minor"], result["Patch"])

    def __init__(self, filename: Path, req_major_version: int, min_minor_version: int) -> None:
        """! Initialize the Pathfinder database instance.

        @param filename           Path to the pathfinder.sqlite database file.
        @param req_major_version  Major version the database has to be in.
        @param min_minor_version  Minimum minor version the database has to be in.
        """
        if not path.exists(filename):
            raise FileNotFoundError

        self._db: sqlite3.Connection = sqlite3.connect(filename)
        self._db.row_factory = sqlite3.Row

        self._version: Pathfinder.Version = Pathfinder._get_version(self._db)

        want_version: Pathfinder.Version = Pathfinder.Version(req_major_version, min_minor_version, 0)
        if not self._version.is_compatible(want_version):
            raise ValueError(f"Incompatible database version (want ~= {want_version}, got {self._version})")

    @property
    def version(self) -> Version:
        """! Return the version of the opened Pathfinder database.

        @return The version of the openend Pathfinder database.
        """
        return self._version

    def run_query(self, operation: str, query: str) -> tuple[str, list[dict[str, Any]]]:
        """! Run a database query and return the result

        @param operation  The name of the operation to run.
        @param query      The query parameter to run the operation with.
        @return The type of the result and the result itself.
        """
        if operation == "" or query == "":
            return "none", []
        if operation == "finddefeat":
            return "feat", [dict(row) for row in self.find_german_feat(query)]
        if operation == "findenfeat":
            return "feat", [dict(row) for row in self.find_english_feat(query)]

        raise ValueError(f"Invalid query operation '{operation}'")

    def find_german_feat(self, name: str) -> list[sqlite3.Row]:
        """! Return a list of feats matching a German name.

        @param name  The German name to search for.
        @return A list of matching feats.
        """
        return self._db.execute("SELECT * from GermanFeats WHERE GermanName LIKE :name",
                                {"name": f"%{name}%"}).fetchall()

    def find_english_feat(self, name: str) -> list[sqlite3.Row]:
        """! Return a list of feats matching an English name.

        @param name  The English name to search for.
        @return A list of matching feats.
        """
        return self._db.execute("SELECT * from GermanFeats WHERE EnglishName LIKE :name",
                                {"name": f"%{name}%"}).fetchall()
