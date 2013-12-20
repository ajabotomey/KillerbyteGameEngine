#include "Scene.h"
#include "File.h"

namespace KillerbyteGameEngine
{
	static Scene* instance = NULL;

	Scene::Scene()
	{
		nodeCount = 0;
	}

	Scene::Scene(const char* filename)
	{
		nodeCount = 0;
		LoadScene(filename);
		instance = this;
	}

	Scene::~Scene()
	{

	}

	Scene* Scene::GetScene()
	{
		return instance;
	}

	void Scene::LoadScene(const char* filename)
	{
#ifdef __ANDROID__
		LoadAndroidScene(filename);
#else
		XMLError success = doc.LoadFile(filename);
#endif

		// Get the root element
		XMLElement* root = doc.FirstChildElement();

		// Now load the width and height of the level
		width = atoi(root->FirstChildElement("width")->GetText());
		height = atoi(root->FirstChildElement("height")->GetText());

		// Now to load the resources
		XMLElement* resources = root->FirstChildElement("resources");

		// Loading Audio
		XMLElement* audio = resources->FirstChildElement("audio");
		XMLElement* e = audio->FirstChildElement("file");
		for (; e != NULL; e = e->NextSiblingElement("file"))
		{
			// Check if the node already exists

			// Retrive the data second
			std::string name = e->Attribute("name");
			std::string alias = e->Attribute("alias");

			// Create the scene node
			Node* node = Node::CreateNode(nodeCount + 1, name, alias);
			AudioClip clip;
			clip.OpenClip(name.c_str());
			node->SetAudioClip(clip);

			AddNode(node);
		}

		// Loading Resources
		XMLElement* image = resources->FirstChildElement("image");
		

		// Loading the level itself

	}

	// Simply add the node onto the end of the line
	void Scene::AddNode(Node* node)
	{
		if (firstNode == NULL)
		{
			firstNode = node;
			lastNode = node;
		}
		else
		{
			node->prevNode = lastNode;
			lastNode->nextNode = node;
			lastNode = lastNode->nextNode;
		}

		nodeCount++;
	}

	Node* Scene::FindNode(std::string alias)
	{
		for (Node* child = GetFirstNode(); child != NULL; child = child->GetNextNode())
		{
			if (child->alias == alias)
			{
				return child;
			}
		}
	}

	// I have essentiall copied the TinyXML2 definition for loading a file and edited it for Android purposes
	void Scene::LoadAndroidScene(const char* filename)
	{
#ifdef __ANDROID__
		LOGI("Loading Android Scene now");
		doc.Clear();

		File file;
		file.Open(filename, "rb");
		if (!file.DoesExist())
		{
			// Return an error
			return;
		}

		doc.LoadFile(file.GetCFile());
		file.CloseFile();
#endif
	}
}