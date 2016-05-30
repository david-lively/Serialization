#ifndef PARSER_H
#define PARSER_H

#include "Tokenizer.h"

#include <vector>
#include <map>

namespace Parsing
{
	enum class NodeType
	{
		Object
		,Members
		,Pair
		,String
		,Value
		,Array
		,Elements
		,Number
		,True
		,False
		,Null
	};

	struct ParseNode
	{
		TokenType TType;
		NodeType NType;

		std::map<TokenType, ParseNode*> Nodes;
	};

	class Parser
	{
	public:
		Parser();
		~Parser();

		void InitParseTree();

		void Parse(std::vector<Token>& tokens);
		void Error(const std::string& message);
	
	private:
#define PARSE(t) ParseNode* Parser::parse ## t(std::vector<Token>& tokens, int& index)

		PARSE(Symbol);
		PARSE(Object);
		PARSE(Members );
		PARSE(Pair	  );
		PARSE(String  );
		PARSE(Value	  );
		PARSE(Array	  );
		PARSE(Elements);
		PARSE(Number  );
		PARSE(True	  );
		PARSE(False	  );
		PARSE(Null	  );
			/*
		*/

	};

}

#endif