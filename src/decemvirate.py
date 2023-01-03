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
from pathfinder import Pathfinder
from util import Util


class _HelpAction(argparse._HelpAction):  # pylint: disable=protected-access
    """! Helper class to display help strings for all commands in one go.
    """

    def __call__(self, parser, namespace, values, option_string=None):
        parser.print_help()
        print()
        print()

        subparsers_actions = [
            action for action in parser._actions
            if isinstance(action, argparse._SubParsersAction)]

        for subparsers_action in subparsers_actions:
            for choice, subparser in subparsers_action.choices.items():
                print(f"Command {choice}:")
                print(subparser.format_help())

        parser.exit()


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

        parser: argparse.ArgumentParser = argparse.ArgumentParser(description=description, add_help=False)

        # Note: we're setting required to False even on required arguments and do the checks
        # ourselves below. We're doing that because we want more dynamic --version behaviour

        parser.add_argument('-h', '--help', action=_HelpAction, help='show this help message and exit')
        parser.add_argument("-v", "--version", required=False, action="store_true",
                            help="print the version and exit")
        parser.add_argument("-d", "--database", required=True,
                            help="SQLite database to use (required)")

        subparsers = parser.add_subparsers(title="Supported commands", dest="command")

        parser_web: argparse.ArgumentParser = subparsers.add_parser(
            "web", help="Run the Decemvirate web application (default)",
            formatter_class=argparse.ArgumentDefaultsHelpFormatter)
        parser_web.add_argument("-l", "--host", default="127.0.0.0",
                                help="hostname or IP address on which to listen")
        parser_web.add_argument("-p", "--port", type=int, default=8080,
                                help="TCP port on which to listen")
        parser_web.add_argument("-t", "--threads", type=int, default=4,
                                help="the number of threads used to process application logic")

        parser_finddepub: argparse.ArgumentParser = subparsers.add_parser(
            "finddepub", help="Search German publication by abbreviation or title")
        parser_finddepub.add_argument("query", metavar="abbreviation/title",
                                      help="abbreviation or title to search for")

        parser_findenpub: argparse.ArgumentParser = subparsers.add_parser(
            "findenpub", help="Search English publication by product code, abbreviation or title")
        parser_findenpub.add_argument("query", metavar="code/abbreviation/title",
                                      help="product code, abbreviation or title to search for")

        parser_finddespell: argparse.ArgumentParser = subparsers.add_parser(
            "finddespell", help="Search German spells by name")
        parser_finddespell.add_argument("query", metavar="name",
                                        help="spell to search for")

        parser_findenspell: argparse.ArgumentParser = subparsers.add_parser(
            "findenspell", help="Search English spells by name")
        parser_findenspell.add_argument("query", metavar="name",
                                        help="spell to search for")

        parser_findspellbyclass: argparse.ArgumentParser = subparsers.add_parser(
            "findspellbyclass", help="Search spells by class (and level)")
        parser_findspellbyclass.add_argument("query", metavar="class",
                                             help="class name to search for")
        parser_findspellbyclass.add_argument("param", metavar="level", nargs='?',
                                             help="class level search for")

        parser_finddefeat: argparse.ArgumentParser = subparsers.add_parser(
            "finddefeat", help="Search German feats by name")
        parser_finddefeat.add_argument("query", metavar="name",
                                       help="feat to search for")

        parser_findenfeat: argparse.ArgumentParser = subparsers.add_parser(
            "findenfeat", help="Search English feats by name")
        parser_findenfeat.add_argument("query", metavar="name",
                                       help="feat to search for")

        args: argparse.Namespace = parser.parse_args()

        if args.version:
            Decemvirate._print_version(args.database)
            parser.exit()

        if args.command is None:
            args, extras = parser.parse_known_args()
            args.command = "web"
            parser_web.parse_args(extras, namespace=args)

        if args.database is None:
            parser.error("the following arguments are required: -d/--database")

        if not hasattr(args, "param"):
            args.param = None

        return args

    @staticmethod
    def _none_to_empty(value: str | None) -> str:
        return "" if value is None else value

    @staticmethod
    def _print_result_feats(result: list[dict[str, Any]]) -> None:
        for feat in result:
            print(f"German Name: {feat['GermanName']}")
            print(f"English Name: {feat['EnglishName']}")
            print(f"Book: {feat['Book']}, Page: {feat['Page']}")
            print(f"Description: {feat['Description']}")
            print(f"Type: {', '.join(feat['Type'].split(','))}")
            for url in feat['URLs']:
                print(f"URL: {url}")
            print()

    @staticmethod
    def _print_result_spells(result: list[dict[str, Any]]) -> None:
        for spell in result:
            print(f"German Name: {spell['GermanName']}")
            print(f"English Name: {spell['EnglishName']}")
            print(f"Book: {spell['Book']}, Page: {spell['Page']}")
            print(f"Class: {', '.join(spell['Classes'].split(','))}")
            print(f"Meta: {spell['Meta']}")
            print(f"Description: {spell['Description']}")
            for url in spell['URLs']:
                print(f"URL: {url}")
            print()

    @staticmethod
    def _print_result_german_publications(result: list[dict[str, Any]]) -> None:
        for pub in result:
            print(f"Title: {pub['Title']}")
            print(f"Product Code: {pub['ProductCode']}")
            print(f"Abbreviation: {pub['Abbreviation']}")
            print(f"StatBlock: {pub['StatBlock']}")
            print(f"Category: {pub['Category']}")
            print(f"Date: {Decemvirate._none_to_empty(pub['Date'])}")
            print(f"URL: {Decemvirate._none_to_empty(pub['URL'])}")
            print(f"ISBN: {', '.join(Decemvirate._none_to_empty(pub['ISBN']).split(','))}")
            print()

        if len(result) == 1 and "Originals" in result[0] and result[0]["Originals"]:
            print("This publication translates the following originals:")
            print()
            Decemvirate._print_result_english_publications(result[0]["Originals"])

    @staticmethod
    def _print_result_english_publications(result: list[dict[str, Any]]) -> None:
        for pub in result:
            print(f"Title: {pub['Title']}")
            print(f"Product Code: {pub['ProductCode']}")
            print(f"Abbreviation: {pub['Abbreviation']}")
            print(f"Category: {pub['Category']}")
            print(f"Date: {Decemvirate._none_to_empty(pub['Date'])}")
            print(f"URL: {Decemvirate._none_to_empty(pub['URL'])}")
            print(f"ISBN: {', '.join(Decemvirate._none_to_empty(pub['ISBN']).split(','))}")
            print()

        if len(result) == 1 and "Translations" in result[0] and result[0]["Translations"]:
            print("This publication is translated in the following publications:")
            print()
            Decemvirate._print_result_german_publications(result[0]["Translations"])

    @staticmethod
    def _print_result(result_type: str, result: list[dict[str, Any]]):
        if result_type == "feat":
            Decemvirate._print_result_feats(result)
            return

        if result_type == "spell":
            Decemvirate._print_result_spells(result)
            return

        if result_type == "depub":
            Decemvirate._print_result_german_publications(result)
            return

        if result_type == "enpub":
            Decemvirate._print_result_english_publications(result)
            return

    def run(self) -> None:
        """! Run the main Decemvirate application.
        """
        args: argparse.Namespace = Decemvirate._parse_args()

        Util.set_pathfinder_path(args.database)
        Util.try_pathfinder()

        if args.command == "web":
            decemvirate_flask.run_waitress(host=args.host, port=args.port, threads=args.threads)
            return

        pathfinder: Pathfinder = Util.get_pathfinder()
        print(f"Openend Pathfinder database '{args.database}': Version {pathfinder.version}")
        print()

        Decemvirate._print_result(*pathfinder.run_query(args.command, args.query, args.param))


def main() -> None:
    """! Decemvirate main function, running the main app.
    """
    decemvirate: Decemvirate = Decemvirate()
    decemvirate.run()


if __name__ == '__main__':
    main()
