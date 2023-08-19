#ifndef _NEW_LEXING_HPP
#define _NEW_LEXING_HPP

#include <boost/spirit/include/qi.hpp>
#include <fstream>
#include <string>

#define str(x) std::to_string(x)
namespace qi = boost::spirit::qi;

namespace x64::lexer {
	namespace grammar {
		// Arithmetics
		const auto mov	= qi::copy(qi::lexeme["MOV"]);
		const auto add	= qi::copy(qi::lexeme["ADD"]);
		const auto _div = qi::copy(qi::lexeme["DIV"]);
		const auto _mul = qi::copy(qi::lexeme["MUL"]);
		const auto _sub = qi::copy(qi::lexeme["SUB"]);
		const auto _and = qi::copy(qi::lexeme["AND"]);
		const auto _or	= qi::copy(qi::lexeme["OR"]);
		const auto _xor = qi::copy(qi::lexeme["XOR"]);
		const auto _not = qi::copy(qi::lexeme["NOT"]);
		const auto cmp	= qi::copy(qi::lexeme["CMP"]);

		// Branching
		const auto jmp = qi::copy(qi::lexeme["JMP"]);
		const auto je  = qi::copy(qi::lexeme["JE"]);
		const auto jne = qi::copy(qi::lexeme["JNE"]);
		const auto jg  = qi::copy(qi::lexeme["JG"]);
		const auto jge = qi::copy(qi::lexeme["JGE"]);
		const auto jl  = qi::copy(qi::lexeme["JL"]);
		const auto jle = qi::copy(qi::lexeme["JLE"]);

		// Debugging
		const auto brk = qi::copy(qi::lexeme["BRK"]);

		// n-Arity
		// MOV has [reg|address]
		const auto binary = qi::copy((add | _div | _mul | _sub | _and | _or | _xor | cmp));
		const auto unary  = qi::copy(_not);
		const auto jump	  = qi::copy(jmp | je | jne | jg | jge | jl | jle);

		// Variables
		const auto reg =
			qi::copy(qi::lexeme["R" >> qi::char_("1-4")] | qi::lexeme["r" >> qi::char_("1-4")] |
					 qi::lexeme["R" >> qi::char_("A-D") >> qi::char_('X')] |
					 qi::lexeme["r" >> qi::char_("a-d") >> qi::char_('x')]);
		const auto num	   = qi::copy(qi::lexeme[+qi::digit]);
		const auto address = qi::copy(qi::lexeme[reg | ("[" >> (reg | num) >> "]")]);

		// Labels
		const auto label = qi::copy(
			qi::lexeme[*qi::char_('_') >> +qi::char_("a-zA-Z0-9") >> ":" >> !qi::char_(':')]);
		const auto label_body =
			qi::copy(qi::lexeme[*qi::char_('_') >> +qi::char_("a-zA-Z0-9") >> !qi::char_(':')]);

		// Delimiters
		const auto comma = qi::copy(qi::lexeme[","]);

		// Line endings
		const auto newl		 = qi::copy(qi::lexeme[qi::eol | qi::eoi | qi::char_('\n')]);
		const auto semicolon = qi::copy(qi::lexeme[";"]);
		const auto le		 = qi::copy(newl | semicolon);

		// Comments
		const auto comment = qi::copy(qi::lexeme[";" >> *(qi::char_ - qi::eol)]);

		// Operands
		const auto operand	= qi::copy(reg | num | address);
		const auto jumpable = qi::copy(address | label_body);

		// Instructions
		const auto mov_rule = qi::copy(mov >> address >> comma >> operand);
		const auto binary_rule =
			qi::copy((mov_rule | (binary >> operand >> comma >> operand)) >> (comment | le));
		const auto unary_rule = qi::copy(unary >> operand);
		const auto jump_rule  = qi::copy(jump >> jumpable);
		const auto instruction =
			qi::copy((binary_rule | unary_rule | jump_rule) | (label | brk) | le);
	} // namespace grammar

	// ------------------------------
	// Lexer definitions
	// ------------------------------

	bool lex_line(std::string line);
	bool lex_file(std::string filename);

} // namespace x64::lexer

#endif // _NEW_LEXING_HPP