#ifndef PARSESTATES_H
#define	PARSESTATES_H

#include "Tokenizer.h"

#include <vector>
#include <map>
#include <iostream>
#include <string>

namespace Parsing
{
	struct ParseState
	{
		std::map<TokenType, ParseState*> NextStates;

		virtual ParseState* GetNext(Token& t)
		{
			if (NextStates.count(t.Type) <= 0)
			{
				std::cerr << "Unexpected token " << (std::string)t << std::endl;
				throw;
			}
		}

	};




}




#endif