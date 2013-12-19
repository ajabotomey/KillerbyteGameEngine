#include "Node.h"

namespace KillerbyteGameEngine
{
	Node::Node()
	{

	}

	Node::~Node()
	{

	}

	Node* Node::CreateNode(unsigned int id, std::string _name, std::string _alias)
	{
		Node* node = new Node();
		node->setID(id);
		node->name = _name;
		node->alias = _alias;

		return node;
	}
}