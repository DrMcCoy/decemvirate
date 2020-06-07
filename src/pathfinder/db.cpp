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
 *  Pathfinder database.
 */

#include "external/fmt/core.hpp"

#include "src/common/util.hpp"
#include "src/common/error.hpp"

#include "src/pathfinder/db.hpp"

namespace Pathfinder {

VersionDB::VersionDB(const std::string &file, int64_t reqVersionMajor, int64_t minVersionMinor) :
		_db(file, SQLite3::DB::Mode::ReadOnly) {

	SQLite3::MapStatement version(_db, "SELECT * from Version LIMIT 1");

	try {
		version.execute();

		const SQLite3::MapStatement::Rows &rows = version.getRows();

		if (rows.empty())
			throw Common::Exception("Version table empty");

		SQLite3::MapStatement::Row::const_iterator versionMajor = rows[0].find("Major");
		SQLite3::MapStatement::Row::const_iterator versionMinor = rows[0].find("Minor");
		SQLite3::MapStatement::Row::const_iterator versionPatch = rows[0].find("Patch");

		if (versionMajor == rows[0].end() || !std::holds_alternative<int64_t>(versionMajor->second) ||
		    versionMinor == rows[0].end() || !std::holds_alternative<int64_t>(versionMinor->second) ||
		    versionPatch == rows[0].end() || !std::holds_alternative<int64_t>(versionPatch->second))
			throw Common::Exception("Version table doesn't contain the version");

		_versionMajor = std::get<int64_t>(versionMajor->second);
		_versionMinor = std::get<int64_t>(versionMinor->second);
		_versionPatch = std::get<int64_t>(versionPatch->second);

		_versionString = fmt::format("{}.{}.{}", _versionMajor, _versionMinor, _versionPatch);

	} catch (Common::Exception &e) {
		e.add("Failed to get the database's version");

		throw e;
	}

	if (_versionMajor != reqVersionMajor)
		throw Common::Exception("Wrong database major version ({} != {}.{}.0)",
		                        _versionString, reqVersionMajor, minVersionMinor);
	if (_versionMinor < minVersionMinor)
		throw Common::Exception("Database version too low ({} < {}.{}.0)",
		                        _versionString, reqVersionMajor, minVersionMinor);
}


DB::DB(const std::string &file, int64_t minVersionMajor, int64_t minVersionMinor) :
		VersionDB(file, minVersionMajor, minVersionMinor),
		_findGermanPublicationByAbbreviation(_db),
		_findEnglishPublicationByProductCode(_db),
		_findEnglishPublicationByAbbreviation(_db),
		_findGermanPublicationsByTitle(_db, 12),
		_findEnglishPublicationsByTitle(_db, 12),
		_findGermanPublicationsByPaizoCode(_db),
		_findGermanSpellsByGermanName(_db),
		_findGermanSpellsByEnglishName(_db) {

}

std::optional<GermanPublication> DB::findGermanPublicationByAbbreviation(const std::string &abbreviation) {
	return _findGermanPublicationByAbbreviation.run(abbreviation);
}

std::optional<EnglishPublication> DB::findEnglishPublicationByProductCode(const std::string &productCode) {
	return _findEnglishPublicationByProductCode.run(productCode);
}

std::optional<EnglishPublication> DB::findEnglishPublicationByAbbreviation(const std::string &abbreviation) {
	return _findEnglishPublicationByAbbreviation.run(abbreviation);
}

std::vector<GermanPublication> DB::findGermanPublicationsByTitle(const std::string &title) {
	return _findGermanPublicationsByTitle.run(title);
}

std::vector<GermanPublication> DB::findGermanPublicationsByTitle(const std::string &title, size_t &count) {
	return _findGermanPublicationsByTitle.run(title, count);
}

std::vector<EnglishPublication> DB::findEnglishPublicationsByTitle(const std::string &title) {
	return _findEnglishPublicationsByTitle.run(title);
}

std::vector<EnglishPublication> DB::findEnglishPublicationsByTitle(const std::string &title, size_t &count) {
	return _findEnglishPublicationsByTitle.run(title, count);
}

std::vector<EnglishPublication> DB::findOriginals(const GermanPublication &german) {
	std::vector<EnglishPublication> originals;

	for (const std::string &code : german.getPaizoProductCodes())
		if (std::optional<EnglishPublication> o = findEnglishPublicationByProductCode(code); o)
			originals.push_back(*o);

	return originals;
}

std::vector<GermanPublication> DB::findTranslations(const EnglishPublication &english) {
	return _findGermanPublicationsByPaizoCode.run(english.getProductCode());
}

std::vector<GermanSpell> DB::findGermanSpellsByGermanName(const std::string &name) {
	return _findGermanSpellsByGermanName.run(name);
}

std::vector<GermanSpell> DB::findGermanSpellsByEnglishName(const std::string &name) {
	return _findGermanSpellsByEnglishName.run(name);
}

} // End of namespace Pathfinder
