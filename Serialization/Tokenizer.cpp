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

	//TODO: move this into a std::map<string,std::funcion<std::string()>>
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
	else if (':' == curr)
	{
		result.Type = TokenType::Colon;
		result.Text = readChar();
	}
	else if (';' == curr)
	{
		result.Type = TokenType::Semicolon;
		result.Text = readChar();
	}
	else if (',' == curr)
	{
		result.Type = TokenType::Comma;
		result.Text = readChar();
	}
	else if ('{' == curr)
	{
		result.Type = TokenType::CurlyBrace;
		result.Text = readChar();
	}
	else if ('}' == curr)
	{
		result.Type = TokenType::CloseCurlyBrace;
		result.Text = readChar();
	}
	else if ('[' == curr)
	{
		result.Type = TokenType::Array;
		result.Text = readChar();
	}
	else if (']' == curr)
	{
		result.Type = TokenType::CloseArray;
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
		result.Type = TokenType::Unknown;
		result.Text = readChars();
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

	while (!IsEOF() && !iswspace(current()))
	{
		m_currentText += readChar();
	}

	return m_currentText;
}

map<TokenType, string> initTokenTypeNames()
{
	map<TokenType, string> names;

#define ADDNAME(name) names[TokenType:: ## name] = #name;

	ADDNAME(Unknown);
	ADDNAME(String);
	ADDNAME(Chars);
	ADDNAME(Char);
	ADDNAME(Number);
	ADDNAME(Int);
	ADDNAME(Frac);
	ADDNAME(Exp);
	ADDNAME(Digit);
	ADDNAME(Digit1Through9);
	ADDNAME(Digits);
	ADDNAME(E);
	ADDNAME(WhiteSpace);
	ADDNAME(Eof);
	ADDNAME(Symbol);
	ADDNAME(CurlyBrace);
	ADDNAME(CloseCurlyBrace);
	ADDNAME(Comma);
	ADDNAME(Semicolon);
	ADDNAME(Colon);
	ADDNAME(Array);
	ADDNAME(CloseArray);

#undef ADDNAME

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





