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
 *  English Pathfinder publications.
 */

#ifndef PATHFINDER_ENGLISHPUBLICATION_HPP
#define PATHFINDER_ENGLISHPUBLICATION_HPP

#include <string>
#include <vector>
#include <optional>

#include "src/sqlite3/findexactmatch.hpp"

namespace Pathfinder {

/** An English Pathfinder publication, as published by Paizo. */
class EnglishPublication {
public:
	/** Read an English Pathfinder publication from a database query result. */
	EnglishPublication(const SQLite3::MapStatement::Row &row);

	/** Return the publication's product code of the form PZO..., uniquely identifying a publication. */
	std::string getProductCode() const { return _productCode; }

	/** Return the date, in the form of YYYY-MM, the publication was first published. */
	std::string getDate() const { return _date; }

	/** Return the full title of the publication. */
	std::string getTitle() const { return _title; }

	/** Return the category, or product line, this publication was published under. */
	std::string getCategory() const { return _category; }

	/** Return the abbreviation, if any, of the publication when it's referenced in other works. */
	std::string getAbbreviation() const { return _abbreviation; }

	/** Return the URL of the publication's product page on the Paizo website. */
	std::string getURL() const { return _url; }

	/** Return the ISBNs physical copies of the publication are published under.
	 *
	 *  A publication can have several ISBNs, because each new form (hardcover, softcover, ...)
	 *  requires a new ISBN.
	 *
	 *  If the publication had no physical copies, this vector is empty.
	 */
	std::vector<std::string> getISBNs() const { return _isbns; }


private:
	std::string _productCode;
	std::string _date;
	std::string _title;
	std::string _category;
	std::string _abbreviation;
	std::string _url;

	std::vector<std::string> _isbns;
};


/** Find an English publication by its Paizo code. */
class FindEnglishPublicationByProductCode : public SQLite3::FindExactMatch {
public:
	FindEnglishPublicationByProductCode(SQLite3::DB &db);
	FindEnglishPublicationByProductCode(const FindEnglishPublicationByProductCode &) = delete;
	FindEnglishPublicationByProductCode(FindEnglishPublicationByProductCode &&) = default;
	~FindEnglishPublicationByProductCode() override = default;

	FindEnglishPublicationByProductCode &operator=(const FindEnglishPublicationByProductCode &) = delete;
	FindEnglishPublicationByProductCode &operator=(FindEnglishPublicationByProductCode &&) = default;

	std::optional<EnglishPublication> run(const std::string &productCode);
};


/** Find an English publication by its Paizo code. */
class FindEnglishPublicationByAbbreviation : public SQLite3::FindExactMatch {
public:
	FindEnglishPublicationByAbbreviation(SQLite3::DB &db);
	FindEnglishPublicationByAbbreviation(const FindEnglishPublicationByAbbreviation &) = delete;
	FindEnglishPublicationByAbbreviation(FindEnglishPublicationByAbbreviation &&) = default;
	~FindEnglishPublicationByAbbreviation() override = default;

	FindEnglishPublicationByAbbreviation &operator=(const FindEnglishPublicationByAbbreviation &) = delete;
	FindEnglishPublicationByAbbreviation &operator=(FindEnglishPublicationByAbbreviation &&) = default;

	std::optional<EnglishPublication> run(const std::string &abbreviation);
};

} // End of namespace Pathfinder

#endif // PATHFINDER_ENGLISHPUBLICATION_HPP
