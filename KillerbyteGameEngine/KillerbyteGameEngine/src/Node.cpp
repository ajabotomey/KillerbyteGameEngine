#include "Node.h"

namespace KillerbyteGameEngine
{
	Node::Node()
	{
		type = EMPTY_NODE;
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

	Node& Node::operator = (const Node& other)
	{
		name = other.name;
		alias = other.alias;
		
		if (other.audioClip)
		{
			audioClip = other.audioClip;
		}

		if (other.camera)
		{
			camera = other.camera;
		}

		if (other.model)
		{
			model = other.model;
		}

		parentNode = other.parentNode;
		firstNode = other.firstNode;
		nextNode = other.nextNode;
		prevNode = other.prevNode;

		return *this;
	}
}