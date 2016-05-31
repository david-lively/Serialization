#ifndef	PARSERNODES_H
#define PARSERNODES_H

#include "Tokenizer.h"

#include <vector>
#include <map>
#include <string>
#include <memory>
#include <tuple>

namespace Parsing
{
	enum class NodeType
	{
		Object
		,KeyValue
	};

	struct ParseNode
	{

	};

	struct Value : public ParseNode
	{
	};

	struct String : public Value
	{
		std::string Value;
	};

	struct Integer : public Value
	{
		int Value;
	};

	struct Float : public Value
	{
		float Value;
	};

	struct Chars : public String
	{

	};

	struct Array : public Value
	{
		std::vector<Value*> elements;
	};

	struct Pair
	{
		std::string Name;
		Value* Value;

		~Pair()
		{
			if (nullptr != Value)
				delete Value;
		}
	};

	struct Object : public ParseNode
	{
		std::vector<Pair*> members;
		std::vector<Object*> objects;

		~Object()
		{
			for (auto member : members)
			if (nullptr != member)
				delete member;

			members.clear();

			for (auto obj : objects)
			{
				if (nullptr != obj)
					delete obj;
			}

			objects.clear();
		}
	};



}

#endif