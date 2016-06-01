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
if (curr.Type != TokenType:: ## tt)			\
{												\
	Error("Unexpected token " + (string)curr);	\
	return nullptr;								\
}												\
}

#define ACCEPT(tt) \
{ \
	REQUIRE(tt) \
	get();		\
}

Object* Parser::parseObject()
{
	REQUIRE(CurlyBrace);

	Object* parent = new Object();

	// get the curly brace
	Token curr = get();
	bool done = false;

	// stop parsing when we encounter '}'
	do
	{
		auto next = peek();

		switch (next.Type)
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
			get();
			done = true;
			break;

		default:
			Error("Unexpected token: " + (string)next);
			delete parent;
			return nullptr;
		}
	} while (!done); //  next.Type != TokenType::CloseCurlyBrace);

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

	case TokenType::Digits:
	case TokenType::Number:
		return parseNumber();

	case  TokenType::String:
		return parseString();

	case TokenType::Chars:
		return parseChars();

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

	ACCEPT(Colon);

	pair->Value = parseValue();

	return pair;

}

Array*  Parser::parseArray()  
{

	ACCEPT(Array);

	bool done = false;

	Array* arr = new Array();

	while (!done)
	{
		auto next = peek();
	
		switch (next.Type)
		{
		case TokenType::CloseArray:
			done = true;
			break;

		case TokenType::Comma:
			get();
			break;

		default:
			arr->elements.push_back(parseValue());
		}

	}

	return arr;

}

String* Parser::parseString() {
	REQUIRE(String);

	String* s = new String();

	s->Value = get().Text;

	return s;
}

Chars* Parser::parseChars() {
	REQUIRE(Chars);

	auto* s = new Chars();

	s->Value = get().Text;

	return s;
}


Number* Parser::parseNumber()
{
	REQUIRE(Digits);

	Number* num = new Number();

	auto curr = get();

	int whole = atoi(curr.Text.c_str());

	num->Set(whole);

	if (peek().Type == TokenType::Frac)
	{
		ACCEPT(Frac);

		curr = get();
		int n = atoi(curr.Text.c_str());
		float frac = pow(10, -1.f * curr.Text.length());

		num->Set(whole + n * frac);


	}

	return num;
}




