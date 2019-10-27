/* Decemvirate - A FLOSS Pathfinder TTRPG helper
 *
 * Decemvirate is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * Decemvirate is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * Decemvirate is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with Decemvirate. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file
 *  The project's main entry point.
 */

#include <vector>
#include <string>

#include "external/fmt/core.hpp"

#include "external/cxxopts/cxxopts.hpp"

#include "src/version/version.hpp"

#include "src/common/util.hpp"
#include "src/common/error.hpp"
#include "src/common/platform.hpp"

#include "src/pathfinder/db.hpp"

int main(int argc, char **argv) {
	try {
		const std::vector<std::string> params = Common::Platform::getParameters(argc, argv);

		cxxopts::Options options(params[0], std::string(Version::getProjectNameVersion()) + " - A FLOSS Pathfinder TTRPG helper");
		options.add_options()
				( "h,help", "Show this text and exit" )
				( "d,database", "SQLite database to use (required)", cxxopts::value<std::string>() )
			;

		cxxopts::ParseResult result = options.parse(params);

		if (result.count("help") > 0) {
			fmt::print("{}\n", options.help());
			return 0;
		}

		const std::string databaseFile = (result.count("database") > 0) ? result["database"].as<std::string>() : "";
		if (databaseFile.empty()) {
			fmt::print("{}\n", options.help());
			return 1;
		}

		Pathfinder::DB db(databaseFile, 0, 0);

		info("Openend Pathfinder database \"{}\": Version {}\n", db.getFile(), db.getVersionString());

	} catch (...) {
		Common::exceptionDispatcherError();
	}

	return 0;
}
