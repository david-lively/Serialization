#ifndef	TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <map>
#include <iostream>

namespace Parsing
{
	// from http://www.json.org/
	enum class TokenType
	{
		Unknown

		//, Object
		//, Members
		//, Pair
		//, Value
		//, Array
		//, Elements
		//, True
		//, False
		//, Null

		,Array
		,CloseArray
		, CurlyBrace
		, CloseCurlyBrace
		, Comma
		, Colon
		, Semicolon
		
		
		, String
		, Chars
		, Char
		, Number
		, Int
		, Frac
		, Exp
		, Digit
		, Digit1Through9
		, Digits
		, E
		, WhiteSpace
		, Eof
		, Symbol
	};


	//std::string to_string(const TokenType t);

	struct Token
	{
		TokenType Type;
		int Line;
		int Column;

		std::string Text;

		operator std::string();
	};


	class Tokenizer
	{
	public:
		Tokenizer();
		Tokenizer(const std::string& source);
		~Tokenizer();

		void Reset(const std::string& source);

		Token GetNextToken();

		bool IsEOF();

		void Error(const std::string& message)
		{
			std::cerr << "ERROR (" << m_line << "," << m_column << ") " << message << std::endl;
		}

	private:
		// text buffer for read*() methods, avoids a lot of reallocations.
		std::string m_currentText;
		// source text
		std::string m_source;

		// character position within the source stream.
		int m_position;

		int m_line;
		int m_column;

		std::string readString();
		std::string readDigits();
		std::string readChars();

		char readSymbol();
		char readChar();

		void skipWhiteSpace();

		char current();
	};
}


#endif