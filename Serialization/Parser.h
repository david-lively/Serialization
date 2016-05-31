#ifndef PARSER_H
#define PARSER_H

#include "Tokenizer.h"
#include "ParserNodes.h"

#include <vector>
#include <map>
#include <set>
#include <functional>

#define PARSE(t) ParseNode* Parser::parse ## t()
#define PARSE_STUB(t) PARSE(t) { return nullptr; }


namespace Parsing
{
	class Parser
	{
	public:
		Parser();
		~Parser();

		void InitParseTree();

		void Parse(std::vector<Token>& tokens);
		void Error(const std::string& message);

		Token get() { return m_tokens[m_position++]; }
		Token peek() { return m_tokens[m_position]; }

	private:
		int m_position = 0;
		std::vector<Token> m_tokens;

		Object* m_root = nullptr;

		bool isEOF() { return m_position >= m_tokens.size(); }

		Object* parseObject();
		Pair* parseMember();
	};

}

#endif