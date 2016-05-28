#ifndef	JSONPARSER_H
#define JSONPARSER_H

#include <string>
#include <map>
#include <iostream>

namespace Parsing
{
	// from http://www.json.org/
	enum class TokenType
	{
		String
		,Chars
		,Char
		,Number
		,Int
		,Frac
		,Exp
		,Digit
		,Digit1Through9
		,Digits
		,E
		,WhiteSpace
	};

	struct Token
	{
		TokenType Type;
		int Line;
		int Column;


		std::string Text;
	};


	class JSONParser
	{
	public:
		JSONParser();
		JSONParser(const std::string& source);
		~JSONParser();

		void Reset(const std::string& source);

		Token GetNextToken();

		bool IsEOF();

		void Error(const std::string& message)
		{
			std::cerr << "ERROR (" << m_line << "," << m_column << ") " << message << std::endl;

		}

	private:
		// source text
		std::string m_source;

		// character position within the source stream.
		int m_position;

		int m_line;
		int m_column;

		std::string readString();
		float readFloat();
		int readInt();
		char readSymbol();
		char readChar();

		void skipWhiteSpace();

		char current();
	};
}

#endif