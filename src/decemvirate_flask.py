"""! Main Flask app.

This module contains the main Flask app for Decemvirate.
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

from typing import Any

from flask import Flask, render_template, request
from markupsafe import Markup

from pathfinder import Pathfinder
from util import Util


class DecemvirateFlask(Flask):
    """! Main Decemvirate Flask application.
    """

    def _inject_project_information(self) -> dict[str, Any]:
        """! Inject Decemvirate version information into templates.

        @return A dict with keys to inject into templates.
        """
        project_info: dict[str, Any] = Util.get_project_info()
        return {"decemvirate": project_info}

    def __init__(self, import_name):
        super().__init__(import_name)

        self.context_processor(self._inject_project_information)


decemvirate_flask: DecemvirateFlask = DecemvirateFlask(__name__)


@decemvirate_flask.teardown_appcontext
def close_pathfinder(*_):
    """! Close the Pathfinder database on teardown.
    """
    Util.close_pathfinder()


@decemvirate_flask.template_global()
def format_list(db_list: str) -> str:
    """! Format a database list.
    """
    return ", ".join(db_list.split(","))


@decemvirate_flask.template_global()
def linkify_op(operation: str, query: str) -> Markup:
    """! Format a link to another database operation.
    """
    return Markup("<a href=\"/?op={operation}&query={query}\">{query}</a>").format(operation=operation, query=query)


@decemvirate_flask.route("/", methods=['GET'])
def main_page() -> str:
    """! Decemvirate main page.
    """
    params = {"op": "", "query": ""}
    params.update(request.args.to_dict())

    pathfinder: Pathfinder = Util.get_pathfinder()

    result_type: str = "none"
    result: list[dict[str, Any]] = []

    try:
        result_type, result = pathfinder.run_query(params["op"], params["query"])
    except ValueError as err:
        print(err)

    return render_template('decemvirate.html', params=params, result_type=result_type, result=result)


import static_files  # pylint: disable=cyclic-import,wrong-import-position,unused-import # noqa: F401,E402
