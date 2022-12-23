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

import argparse
from typing import Any

from decemvirate_flask import decemvirate_flask
from util import Util


class Decemvirate:  # pylint: disable=too-few-public-methods
    """! Main Decemvirate application.
    """

    @staticmethod
    def _print_version(database: str | None) -> None:
        """! Print version information.
        """
        Util.set_pathfinder_path(database)

        info: dict[str, Any] = Util.get_project_info()

        # Print program version information
        print(f"{info['name']} {info['version']}")
        print(f"{info['url']['homepage']}")
        print()
        print(f"Copyright (c) {info['years']} {', '.join(info['authors'])}")
        print()
        print("This is free software; see the source for copying conditions.  There is NO")
        print("warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.")

        # Try to open the database and print its version information as well
        if info["db"] is not None:
            print()
            print(f"Pathfinder database '{database}': Version {info['db']}")

    @staticmethod
    def _parse_args() -> argparse.Namespace:
        """! Parse command line arguments.

        @return An object containing the parsed command line arguments.
        """
        info: dict[str, Any] = Util.get_project_info()
        nameversion: str = f"{info['name']} {info['version']}"
        description: str = f"{nameversion} -- {info['summary']}"

        parser: argparse.ArgumentParser = argparse.ArgumentParser(description=description)

        # Note: we're setting required to False even on required arguments and do the checks
        # ourselves below. We're doing that because we want more dynamic --version behaviour

        parser.add_argument("-v", "--version", required=False, action="store_true",
                            help="print the version and exit")
        parser.add_argument("-d", "--database", required=True,
                            help="SQLite database to use (required)")

        subparsers = parser.add_subparsers(title="Supported commands", dest="command")

        subparsers.add_parser("web", help="Run the Decemvirate web application (default)")

        args: argparse.Namespace = parser.parse_args()

        if args.version:
            Decemvirate._print_version(args.database)
            parser.exit()

        if args.command is None:
            args.command = "web"

        if args.database is None:
            parser.error("the following arguments are required: -d/--database")

        return args

    def run(self) -> None:
        """! Run the main Decemvirate application.
        """
        args: argparse.Namespace = Decemvirate._parse_args()

        Util.set_pathfinder_path(args.database)
        Util.try_pathfinder()

        if args.command == "web":
            decemvirate_flask.run()
            return


def main() -> None:
    """! Decemvirate main function, running the main app.
    """
    decemvirate: Decemvirate = Decemvirate()
    decemvirate.run()


if __name__ == '__main__':
    main()
