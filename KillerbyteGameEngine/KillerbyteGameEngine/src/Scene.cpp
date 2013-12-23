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
			AudioClip* clip = new AudioClip;
			clip->OpenClip(name.c_str());
			node->SetAudioClip(clip);

			AddNode(node);
		}

		// Loading Resources
		XMLElement* image = resources->FirstChildElement("image");
		

		// Loading the level itself
		XMLElement* level = root->FirstChildElement("level");

		// Get the camera xml element
		XMLElement* cameraElement = level->FirstChildElement("camera");

		// Get the type of camera
		std::string cameraType = cameraElement->Attribute("type");

		// Load where the camera will be pointing as well as its position
		XMLElement* positionElement = cameraElement->FirstChildElement("lookAt")->FirstChildElement("position");
		XMLElement* targetElement = cameraElement->FirstChildElement("lookAt")->FirstChildElement("target");
		Vector3 position = LoadVectorFromXML(positionElement);
		Vector3 target = LoadVectorFromXML(targetElement);
		
		// Now create the camera node
		Node* cameraNode = Node::CreateNode(nodeCount + 1, "MainCamera", "Camera");
		Camera* camera = new Camera;
		camera->SetPosition(position);
		camera->SetTarget(target);
		cameraNode->SetCamera(camera);
		AddNode(cameraNode);
		activeCamera = cameraNode;
		
		// First we need to load the player information
		XMLElement* player = level->FirstChildElement("player");

		// Start with the position of the player
		int playerX = atoi(player->FirstChildElement("position")->FirstChildElement("X")->GetText());
		int playerY = atoi(player->FirstChildElement("position")->FirstChildElement("Y")->GetText());

		// Then the player width and height
		int playerWidth = atoi(player->FirstChildElement("width")->GetText());
		int playerHeight = atoi(player->FirstChildElement("height")->GetText());

		// Then the shader path info
		XMLElement* shader = player->FirstChildElement("shader");
		const char* vertexPath = shader->FirstChildElement("vertex")->Attribute("path");
		const char* fragmentPath = shader->FirstChildElement("fragment")->Attribute("path");

		//Node* playerNode = Node::CreateNode(nodeCount + 1, "PlayerNode", "Player");
		//Model* model = new Model;
		//model->SetPosition(Vector3(playerX, playerY, 0.0));
		//model->CreateRectangle(Vector2(playerWidth, playerHeight), vertexPath, fragmentPath);
		//playerNode->SetModel(model);
		//AddNode(playerNode);

		// Now to create that node
		return;
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

	Vector3 Scene::LoadVectorFromXML(XMLElement* element)
	{
		int x = atoi(element->FirstChildElement("X")->GetText());
		int y = atoi(element->FirstChildElement("Y")->GetText());
		int z = atoi(element->FirstChildElement("Z")->GetText());

		return Vector3(x, y, z);
	}
}