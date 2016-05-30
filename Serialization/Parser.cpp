#include "Parser.h"
#include "Tokenizer.h"
#include "ParseStates.h"

using namespace Parsing;

#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

Parser::Parser()
{
	InitParseTree();
}


Parser::~Parser()
{
}

void Parser::Parse(std::vector<Token>& tokens)
{
	for (int i = 0; i < tokens.size(); ++i)
	{
		auto& token = tokens[i];

		switch (token.Type)
		{
		case TokenType::Symbol:
			break;

		}
	}
}

void Parser::InitParseTree()
{



}

#define PARSE_STUB(t) PARSE(t) { return nullptr; }

PARSE(Symbol)
//ParseNode* Parser::parseSymbol(vector<Token>& tokens, int& index)
{
	auto& token = tokens[index];

	char symbol = token.Text[0];


	ParseNode* node = nullptr;

	switch (symbol)
	{
	case '{': return parseObject(tokens, index); break;
	}

	return nullptr;
}

PARSE(Object)
{

}





PARSE_STUB(Members )
PARSE_STUB(Pair	   )
PARSE_STUB(String  )
PARSE_STUB(Value   )
PARSE_STUB(Array   )
PARSE_STUB(Elements)
PARSE_STUB(Number  )
PARSE_STUB(True	   )
PARSE_STUB(False   )
PARSE_STUB(Null	   )
