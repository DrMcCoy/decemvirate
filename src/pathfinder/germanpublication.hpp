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
 *  German Pathfinder publications.
 */

#ifndef PATHFINDER_GERMANPUBLICATION_HPP
#define PATHFINDER_GERMANPUBLICATION_HPP

#include <string>
#include <vector>
#include <optional>

#include "external/tao/json/traits.hpp"
#include "external/tao/json/binding.hpp"
#include "external/tao/json/basic_value.hpp"

#include "src/sqlite3/findexactmatch.hpp"
#include "src/sqlite3/findlikematch.hpp"

namespace Pathfinder {

/** A German Pathfinder publication, as published by Ulisses Spiele.
 *
 *  Most German Pathfinder publications are direct 1:1 translation of Paizo's
 *  English originals, but some are combinations of several such translations.
 *
 *  Unlike for Paizo's originals, not all German Pathfinder publications have
 *  been given product codes by Ulisses Spiele. And also, unfortunately, there
 *  are a few publications that have received product codes already used by
 *  another publication, i.e. they're not all unique.
 */
class GermanPublication {
public:
	/** Read a German Pathfinder publication from a database query result. */
	GermanPublication(const SQLite3::MapStatement::Row &row);

	/** Return the product code, if any, of the publication. */
	std::string getProductCode() const { return _productCode; }

	/** Return the full title of the publication. */
	std::string getTitle() const { return _title; }

	/** Return the abbreviation of the publication when it's referenced in other works.
	 *  Each German Pathfinder publication is uniquely identified by its abbreviation. */
	std::string getAbbreviation() const { return _abbreviation; }

	/** Return the abbreviation of the publication when it's referenced in a creature stat block. */
	std::string getStatBlock() const { return _statBlock; }

	/** Return the category, or product line, this publication was published under. */
	std::string getCategory() const { return _category; }

	/** Return the date, in the form of YYYY-MM, the publication was first published. */
	std::string getDate() const { return _date; }

	/** Return a commentary, if any, that further explains the publication to a user. */
	std::string getCommentary() const { return _commentary; }

	/** Return the URL of the publication's product page on the Ulisses Spiele ebook store. */
	std::string getURL() const { return _url; }

	/** Return the Paizo product codes of the original English publications this German
	 *  publication contains translations of. */
	std::vector<std::string> getPaizoProductCodes() const { return _paizoProductCodes; }

	/** Return the ISBNs physical copies of the publication are published under.
	 *
	 *  A publication can have several ISBNs, because each new form (hardcover, softcover, ...)
	 *  requires a new ISBN.
	 *
	 *  If the publication had no physical copies, this vector is empty.
	 */
	std::vector<std::string> getISBNs() const { return _isbns; }

	/** Does this publication contain translations of a certain English publication
	 *  identified by its Paizo product code? */
	bool hasPaizoProductCode(const std::string &paizoProductCode) const;

private:
	GermanPublication() = default;

	std::string _productCode;
	std::string _title;
	std::string _abbreviation;
	std::string _statBlock;
	std::string _category;
	std::string _date;
	std::string _url;
	std::string _commentary;

	std::vector<std::string> _paizoProductCodes;
	std::vector<std::string> _isbns;


	friend ::tao::json::traits<GermanPublication>;
	template<typename T>
	friend class ::tao::json::basic_value;
};


/** Find a German publication by its abbreviation. */
class FindGermanPublicationByAbbreviation : public SQLite3::FindExactMatch {
public:
	FindGermanPublicationByAbbreviation(SQLite3::DB &db);
	FindGermanPublicationByAbbreviation(const FindGermanPublicationByAbbreviation &) = delete;
	FindGermanPublicationByAbbreviation(FindGermanPublicationByAbbreviation &&) = default;
	~FindGermanPublicationByAbbreviation() override = default;

	FindGermanPublicationByAbbreviation &operator=(const FindGermanPublicationByAbbreviation &) = delete;
	FindGermanPublicationByAbbreviation &operator=(FindGermanPublicationByAbbreviation &&) = default;

	std::optional<GermanPublication> run(const std::string &abbreviation);
};


/** Find German publications by title. */
class FindGermanPublicationsByTitle : public SQLite3::FindLikeMatch {
public:
	FindGermanPublicationsByTitle(SQLite3::DB &db, size_t limit = SQLite3::FindLikeMatch::kNoLimit);
	FindGermanPublicationsByTitle(const FindGermanPublicationsByTitle &) = delete;
	FindGermanPublicationsByTitle(FindGermanPublicationsByTitle &&) = default;
	~FindGermanPublicationsByTitle() override = default;

	FindGermanPublicationsByTitle &operator=(const FindGermanPublicationsByTitle &) = delete;
	FindGermanPublicationsByTitle &operator=(FindGermanPublicationsByTitle &&) = default;

	std::vector<GermanPublication> run(const std::string &title);
	std::vector<GermanPublication> run(const std::string &title, size_t &count);
};


/** Find German publications by which contain translations of an English publication. */
class FindGermanPublicationsByPaizoCode : public SQLite3::FindLikeMatch {
public:
	FindGermanPublicationsByPaizoCode(SQLite3::DB &db);
	FindGermanPublicationsByPaizoCode(const FindGermanPublicationsByPaizoCode &) = delete;
	FindGermanPublicationsByPaizoCode(FindGermanPublicationsByPaizoCode &&) = default;
	~FindGermanPublicationsByPaizoCode() override = default;

	FindGermanPublicationsByPaizoCode &operator=(const FindGermanPublicationsByPaizoCode &) = delete;
	FindGermanPublicationsByPaizoCode &operator=(FindGermanPublicationsByPaizoCode &&) = default;

	std::vector<GermanPublication> run(const std::string &paizoCode);
};

} // End of namespace Pathfinder

namespace tao::json {
	template<>
	struct traits<::Pathfinder::GermanPublication> :
		public binding::object<TAO_JSON_BIND_REQUIRED("product_code", &::Pathfinder::GermanPublication::_productCode),
		                       TAO_JSON_BIND_REQUIRED("title", &::Pathfinder::GermanPublication::_title),
		                       TAO_JSON_BIND_REQUIRED("abbreviation", &::Pathfinder::GermanPublication::_abbreviation),
		                       TAO_JSON_BIND_REQUIRED("stat_block", &::Pathfinder::GermanPublication::_statBlock),
		                       TAO_JSON_BIND_REQUIRED("category", &::Pathfinder::GermanPublication::_category),
		                       TAO_JSON_BIND_REQUIRED("date", &::Pathfinder::GermanPublication::_date),
		                       TAO_JSON_BIND_REQUIRED("url", &::Pathfinder::GermanPublication::_url),
		                       TAO_JSON_BIND_REQUIRED("commentary", &::Pathfinder::GermanPublication::_commentary),
		                       TAO_JSON_BIND_REQUIRED("paizo_product_codes", &::Pathfinder::GermanPublication::_paizoProductCodes),
		                       TAO_JSON_BIND_REQUIRED("isbns", &::Pathfinder::GermanPublication::_isbns)> {};
}

#endif // PATHFINDER_GERMANPUBLICATION_HPP
