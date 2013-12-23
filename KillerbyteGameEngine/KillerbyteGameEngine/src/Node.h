#ifndef NODE_H
#define NODE_H

#include "Object.h"
#include "Audio/AudioClip.h"
#include "Model.h"
#include "Camera.h"

namespace KillerbyteGameEngine
{
	class Node : public Object
	{
		friend class Scene;
	public:

		enum NodeType
		{
			AUDIO_NODE,
			CAMERA_NODE,
			MODEL_NODE,
			EMPTY_NODE
		};

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
		inline void SetScene(Scene* currentScene) { scene = currentScene; }
		inline void SetAudioClip(AudioClip* clip) { audioClip = clip; type = AUDIO_NODE; }
		inline void SetModel(Model* newModel) { model = newModel; type = MODEL_NODE; }
		inline void SetCamera(Camera* newCamera) { camera = newCamera; type = CAMERA_NODE; }

		// Accessors
		inline Scene* GetScene() { return scene; }
		inline AudioClip* GetAudioClip() const { return audioClip; }
		inline Model* GetModel() const { return model; }
		inline Camera* GetCamera() const { return camera; }

		// Deep copy operator
		Node& operator = (const Node& other);
	protected:
		Node();
		~Node();

		std::string name;
		std::string alias;

		Node* parentNode;
		Node* firstNode;
		Node* prevNode;
		Node* nextNode;

		// A pointer to the scene that this node is a part of
		Scene* scene;

		// Need a node type
		NodeType type;

		AudioClip* audioClip;
		Model* model;
		Camera* camera;
	};
}

#endif