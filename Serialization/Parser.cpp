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

Object* Parser::parseObject()
{
	auto curr = peek();

	if (curr.Type != TokenType::CurlyBrace)
	{
		Error("'{' expected. Found " + (string)curr);
		return nullptr;
	}

	Object* parent = new Object();


	// stop parsing when we encounter '}'
	do
	{
		curr = get();
	
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
	} 
	while (curr.Type != TokenType::CloseCurlyBrace);

	return parent;
}

Pair* Parser::parseMember()
{

}

