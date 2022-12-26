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
from waitress import serve

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

    def run_waitress(self, host: str = "127.0.01", port: int = 8080, threads: int = 4):
        """! Run the Decemvirate web service.

        @param host     Host to bind to.
        @param port     Port to bind to.
        @param threads  Threads to use to handle requests.
        """
        info: dict[str, Any] = Util.get_project_info()
        ident: str = f"{info['name']} {info['version']}"

        print(f"Running {ident} at http://{host}:{port}/", flush=True)
        serve(self, host=host, port=port, threads=threads, ident=ident)


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
def linkify(url: str, text: str | None = None) -> Markup:
    """! Format a link.
    """
    if text is None and url is None:
        return ""

    if text is None:
        text = url

    if url is None:
        return Markup("{text}").format(text=text)

    return Markup("<a href=\"{url}\" rel=\"nofollow\">{text}</a>").format(url=url, text=text)


@decemvirate_flask.template_global()
def linkify_op(operation: str, query: str) -> Markup:
    """! Format links to another database operation.
    """
    links = []
    for item in query.split(","):
        links.append(
            Markup("<a href=\"/?op={operation}&query={item}\">{item}</a>").format(operation=operation, item=item))

    return Markup(", ".join(links))


@decemvirate_flask.template_global()
def linkify_op_list(operation: str, items: list[dict[str, Any]], key: str) -> Markup:
    """! Format links to another database operation from a list of items.
    """
    links = []
    for item in items:
        links.append(
            Markup("<a href=\"/?op={operation}&query={key}\">{key}</a>").format(operation=operation, key=item[key]))

    return Markup(", ".join(links))


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
        print(f"{Util.get_remote_address()}: {err}", flush=True)

    return render_template('decemvirate.html', params=params, result_type=result_type, result=result)


import static_files  # pylint: disable=cyclic-import,wrong-import-position,unused-import # noqa: F401,E402
