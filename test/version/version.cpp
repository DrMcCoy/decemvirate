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
 *  Unit test mock of src/version/version.cpp.
 */

namespace Version {

const char *getProjectName() {
	return "";
}

const char *getProjectVersion() {
	return "";
}

const char *getProjectNameVersion() {
	return "";
}

const char *getProjectNameVersionFull() {
	return "";
}

const char *getProjectAuthors() {
	return "";
}

const char *getTagline() {
	return "";
}

} // End of namespace Version
