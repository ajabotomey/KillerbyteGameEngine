#ifndef SCENE_H
#define SCENE_H

#include "Base.h"
#include "Node.h"
#include "tinyxml2.h"

using namespace tinyxml2;

namespace KillerbyteGameEngine
{
	class Scene : public Object
	{
	public:
		Scene(const char* filename);
		~Scene();

		static Scene* GetScene();

		void AddNode(Node* node);
		void ClearScene();

		void LoadScene(const char* filename);

		inline unsigned int GetNodeCount() { return nodeCount; }

		inline Node* GetFirstNode() { return firstNode; }
		inline Node* GetLastNode() { return lastNode; }

		Node* FindNode(std::string alias);
	protected:
		Scene();
	private:
		void LoadAndroidScene(const char* filename);

		Node* firstNode;
		Node* lastNode;
		unsigned int nodeCount;

		unsigned int width;
		unsigned int height;

		XMLDocument doc;
	};
}

#endif