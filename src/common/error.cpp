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
 *  Basic exceptions to throw.
 */

#include <cstdlib>

#include "src/common/error.hpp"
#include "src/common/util.hpp"

namespace Common {

StackException::StackException(const std::exception &e) {
	add(e);
}

void StackException::vadd(const std::string &format, fmt::format_args args) {
	_stack.push(fmt::vformat(format, args));
}

void StackException::add(const StackException &e) {
	Stack orig = e._stack;

	Stack reverse;
	while (!orig.empty()) {
		reverse.push(orig.top());
		orig.pop();
	}

	while (!reverse.empty()) {
		_stack.push(reverse.top());
		reverse.pop();
	}
}

void StackException::add(const std::exception &e) {
	add("{}", e.what());
}

const char *StackException::what() const noexcept {
	try {
		if (!_stack.empty())
			return _stack.top().c_str();
	} catch (...) {
	}

	return "";
}


const Exception kOpenError("Can't open file");
const Exception kReadError("Read error");
const Exception kSeekError("Seek error");
const Exception kWriteError("Write error");


void printException(Exception e, const std::string &prefix) {
	try {
		Exception::Stack &stack = e.getStack();

		if (stack.empty()) {
			status("FATAL ERROR");
			return;
		}

		status("{}{}", prefix.c_str(), stack.top().c_str());

		stack.pop();

		while (!stack.empty()) {
			status("    Because: {}", stack.top().c_str());
			stack.pop();
		}
	} catch (...) {
		status("FATAL ERROR: Exception while printing exception stack");
		std::exit(1);
	}
}

void printExceptionWarning(const Exception &e) {
	printException(e, "WARNING: ");
}

static void exceptionDispatcher(const std::string &prefix, const std::string &reason = "") {
	try {
		try {
			throw;
		} catch (Exception &e) {
			if (reason[0] != 0)
				e.add("{}", reason);

			printException(e, prefix);
		} catch (std::exception &e) {
			Exception se(e);
			if (reason[0] != 0)
				se.add("{}", reason);

			printException(se, prefix);
		} catch (...) {
			if (reason[0] != 0) {
				Exception se("{}", reason);
				printException(se, prefix);
			}
		}
	} catch (...) {
	}
}

void vexceptionDispatcherError(const std::string &format, fmt::format_args args) {
	exceptionDispatcher("ERROR: ", fmt::vformat(format, args));
}

void exceptionDispatcherError() {
	exceptionDispatcher("ERROR: ");
}

void vexceptionWarning(const std::string &format, fmt::format_args args) {
	exceptionDispatcher("WARNING: ", fmt::vformat(format, args));
}

void exceptionDispatcherWarning() {
	exceptionDispatcher("WARNING: ");
}

} // End of namespace Common
