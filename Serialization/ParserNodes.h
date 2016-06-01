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
		, KeyValue
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

	struct Number : public Value
	{
		enum class Type
		{
			Integer
			, Float
		};

		char data[sizeof(double)];

		template<typename T>
		T Get()
		{
			T* ptr = (T*)data;

			return *ptr;
		}

		template<typename T>
		void Set(const T& val)
		{
			T* target = (T*)data;

			*target = val;
		}
	};

	struct Chars : public String
	{

	};

	struct Array : public Value
	{
		std::vector<Value*> elements;

		~Array()
		{
			for (auto el : elements) {
				if (nullptr != el)
					delete el;
			}

			elements.clear();
		}
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

	struct Object : public Value
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