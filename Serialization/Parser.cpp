#include "Parser.h"
#include "Tokenizer.h"

using namespace Parsing;

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <cassert>
#include <stack>
#include <queue>


using namespace std;

Parser::Parser()
{
	InitParseTree();
}


Parser::~Parser()
{
	if (nullptr != m_root)
		delete m_root;
}

void Parser::Error(const string& message)
{
	cerr << "Parsing error: \"" << message << "\"" << endl;
}

void Parser::Parse(std::vector<Token>& tokens)
{
	m_tokens = tokens;
	m_position = 0;

	if (nullptr != m_root)
		delete m_root;

	m_root = new Object();

	while (!isEOF())
	{
		auto obj = parseObject();

		if (nullptr == obj)
		{
			cerr << "Parsing error!" << endl;
			return;
		}

		m_root->objects.push_back(obj);
	}

}

#define REQUIRE(tt) \
{ \
	auto curr = peek();								\
if (curr.Type != TokenType::CurlyBrace)			\
{												\
	Error("Unexpected token " + (string)curr);	\
	return nullptr;								\
}												\
}

Object* Parser::parseObject()
{
	REQUIRE(CurlyBrace);

	Object* parent = new Object();

	Token curr;

	// stop parsing when we encounter '}'
	do
	{
		auto curr = get();

		switch (curr.Type)
		{
		case TokenType::CurlyBrace:
			parent->objects.push_back(parseObject());
			break;

		case TokenType::String:
			parent->members.push_back(parseMember());
			break;

		case TokenType::Comma:
			curr = get();
			break;

		case TokenType::CloseCurlyBrace:
			break;

		default:
			Error("Unexpected token: " + (string)curr);
			delete parent;
			return nullptr;
		}
	} while (curr.Type != TokenType::CloseCurlyBrace);

	return parent;
}

Value* Parser::parseValue()
{
	Value* value = nullptr;

	auto next = peek();

	switch (next.Type)
	{
	case TokenType::CurlyBrace:
		return parseObject();

	case TokenType::Number:
		return parseNumber();

	case  TokenType::String:
		return parseString();

	case TokenType::Array:
		return parseArray();
	default:
		Error("Unexpected token " + (string)next);
		delete value;
		return nullptr;
	}

	return value;

}

Pair* Parser::parseMember()
{
	REQUIRE(String);

	Pair* pair = new Pair();


	auto curr = get();

	pair->Name = curr.Text;
	pair->Value = parseValue();

	return pair;

}

Array*  Parser::parseArray()  { return nullptr; } 

String* Parser::parseString() { 
	REQUIRE(String);

	String* s = new String();

	s->Value = get().Text;

	return s;
} 

Number* Parser::parseNumber() 
{
	REQUIRE(Digits);

	Number* num = new Number();

	auto curr = get();

	if (peek().Type == TokenType::Frac)
	{
		float val = 0; // to float  (curr.Text)

		auto next = get();



		


	}


	return nullptr; 

} 




