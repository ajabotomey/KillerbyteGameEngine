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
		inline Camera* GetActiveCamera() { return activeCamera->GetCamera(); }

		Node* FindNode(std::string alias);

		// Update and render the scene
		void Update(float elapsedTime);
		void Render(float elapsedTime);
	protected:
		Scene();
	private:
		void LoadAndroidScene(const char* filename);
		Vector3 LoadVectorFromXML(XMLElement* element);

		Node* firstNode;
		Node* lastNode;
		unsigned int nodeCount;

		unsigned int width;
		unsigned int height;

		XMLDocument doc;
		Node* activeCamera;
	};
}

#endif