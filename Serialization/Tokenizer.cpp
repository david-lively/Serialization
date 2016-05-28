#include "Tokenizer.h"

using namespace Parsing;

#include <string>

using namespace std;

Tokenizer::Tokenizer()
{
}

Tokenizer::Tokenizer(const string& source) : Tokenizer()
{
	Reset(source);
}


Tokenizer::~Tokenizer()
{
}

void Tokenizer::Reset(const string& source)
{
	m_position = 0;
	m_line = 0;
	m_column = 0;
	m_source = source;
}

bool Tokenizer::IsEOF()
{
	return m_position >= m_source.length();
}

string Tokenizer::readString()
{
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

		m_currentText += c;
	}

	++m_position;

	if (IsEOF())
	{
		Error("Unterminated string constant, started at (" + to_string(lin) + "," + to_string(col) + ").");
	}

	return m_currentText;
}


inline char Tokenizer::current()
{
	return m_source[m_position];
}

void Tokenizer::skipWhiteSpace()
{
	while (!IsEOF() && iswspace(m_source[m_position]))
	{
		++m_position;
	}
}


Token Tokenizer::GetNextToken()
{
	m_currentText.clear();

	skipWhiteSpace();

	Token result;

	result.Line = m_line;
	result.Column = m_column;

	if (IsEOF())
	{
		result.Type = TokenType::Eof;
		result.Text = "\n\r";

		return result;
	}


	char curr = current();
	char prev = 0;

	if ('\"' == curr)
	{
		result.Type = TokenType::String;
		result.Text = readString();
	}
	else if ('.' == curr)
	{
		result.Type = TokenType::Frac;
		result.Text = readChar();
	}
	else if (isdigit(curr))
	{
		result.Type = TokenType::Digits;
		result.Text = readDigits();
	}
	else if (isalpha(curr) || ('_' == curr))
	{
		result.Type = TokenType::Chars;
		result.Text = readChars();
	}
	else if (ispunct(curr))
	{
		result.Type = TokenType::Symbol;
		result.Text = readChar();
	}
	else
	{
		cerr << "Unhandled character '" << curr << "'" << endl;
		readChar();
	}

	return result;
}


char Tokenizer::readChar()
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

string Tokenizer::readDigits()
{
	m_currentText.clear();

	while (!IsEOF() && isdigit(current()))
	{
		m_currentText += readChar();
	}

	return m_currentText;
}

string Tokenizer::readChars()
{
	m_currentText.clear();

	while (!IsEOF() && (isalpha(current()) || current() == '_'))
	{
		m_currentText += readChar();
	}

	return m_currentText;
}

map<TokenType, string> initTokenTypeNames()
{
	map<TokenType, string> names;

	names[TokenType::Unknown		] = "Unknown"		;
	names[TokenType::String			] = "String"		;
	names[TokenType::Chars			] = "Chars"			;
	names[TokenType::Char			] = "Char"			;
	names[TokenType::Number			] = "Number"		;
	names[TokenType::Int			] = "Int"			;
	names[TokenType::Frac			] = "Frac"			;
	names[TokenType::Exp			] = "Exp"			;
	names[TokenType::Digit			] = "Digit"			;
	names[TokenType::Digit1Through9	] = "Digit1Through9";
	names[TokenType::Digits			] = "Digits"		;
	names[TokenType::E				] = "E"				;
	names[TokenType::WhiteSpace		] = "WhiteSpace"	;
	names[TokenType::Eof			] = "Eof"			;
	names[TokenType::Symbol			] = "Symbol";

	return names;
}

map<TokenType, string> tokenTypeNames = initTokenTypeNames();

string to_string(const  TokenType t)
{
	if (tokenTypeNames.count(t) <= 0)
		throw;

	return tokenTypeNames[t];
}

Token::operator string()
{
	return to_string(Type) + " \"" + Text + '\"';
}





