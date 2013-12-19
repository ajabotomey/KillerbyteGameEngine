#ifndef NODE_H
#define NODE_H

#include "Object.h"
#include "Audio/AudioClip.h"

namespace KillerbyteGameEngine
{
	class Node : public Object
	{
		friend class Scene;

	public:
		static Node* CreateNode(unsigned int id, std::string _name, std::string _alias);

		// Addition / Removal nodes
		void AddChild(Node* node);
		void RemoveChild(Node* node);
		void RemoveAllChildren();

		// Node Access
		inline Node* GetPreviousNode() { return prevNode; }
		inline Node* GetNextNode() { return nextNode; }
		inline Node* GetParentNode() { return parentNode; }
		inline Node* GetFirstNode() { return firstNode; }
		Node* searchNode(std::string name);

		// Mutators
		inline void SetAudioClip(AudioClip clip) { audioClip = clip; }

		// Accessors
		inline AudioClip GetAudioClip() const { return audioClip; }
	protected:
		Node();
		~Node();

		std::string name;
		std::string alias;

		Node* parentNode;
		Node* firstNode;
		Node* prevNode;
		Node* nextNode;

		AudioClip audioClip;
	};
}

#endif