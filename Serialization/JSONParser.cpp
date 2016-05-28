#include "JSONParser.h"

using namespace Parsing;

#include <string>

using namespace std;

JSONParser::JSONParser()
{
}

JSONParser::JSONParser(const string& source) : JSONParser()
{
	Reset(source);
}


JSONParser::~JSONParser()
{
}

void JSONParser::Reset(const string& source)
{
	m_position = 0;
	m_line = 0;
	m_column = 0;
	m_source = source;
}

bool JSONParser::IsEOF()
{
	return m_position >= m_source.length();
}



string JSONParser::readString()
{
	string text;

	text.reserve(1024);

	bool done = false;

	++m_position;

	int lin = m_line;
	int col = m_column;

	while (!IsEOF() && '"' != current())
	{
		char c = readChar();

		if (c == '\\')
		{
			// escape sequence
			c = readChar();
		}

		text += c;
	}

	++m_position;

	if (IsEOF())
	{
		Error("Unterminated string constant, started at (" + to_string(lin) + "," + to_string(col) + ").");
	}

	return text;
}


char JSONParser::current()
{
	return m_source[m_position];
}

void JSONParser::skipWhiteSpace()
{
	while (!IsEOF() && iswspace(m_source[m_position]))
	{
		++m_position;
	}
}


Token JSONParser::GetNextToken()
{
	skipWhiteSpace();

	Token result;

	result.Line = m_line;
	result.Column = m_column;

	char curr = current();
	char prev = 0;

	if ('\"' == curr)
	{
		result.Type = TokenType::String;
		result.Text = readString();

		return result;
	}
	else
		++m_position;

	return result;
}


char JSONParser::readChar()
{
	char curr = m_source[m_position];

	if (curr == '\n')
	{
		++m_line;
		m_column = 0;
	}
	else
		++m_column;

	++m_position;
	
	return curr;
}


