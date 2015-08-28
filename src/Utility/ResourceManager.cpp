#include "ResourceManager.hpp"

#include "Resource.hpp"
#include "../Graphics/GraphicsDevice.hpp"
#include "../Graphics/Image.hpp"
#include "../Graphics/Texture2D.hpp"
#include "../Graphics/Mesh.hpp"
#include "../Graphics/MeshData.hpp"
#include "../Graphics/Shader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

NS_BEGIN

std::map<std::string, Resource*> ResourceManager::resourceCollection;
std::map<std::string, std::string> ResourceManager::typemap;

bool ResourceManager::Initialize(GraphicsDevice* _graphicsDevice)
{
	InitializeTypemap();
	return true;
}

template<class T>
T* ResourceManager::LoadResource(std::string filepath)
{
	T* ret;
	// Checks if the resource we're looking for
	if (ret = dynamic_cast<T*>(CheckResourceCollection(filepath)))
	{		
		dynamic_cast<Resource*>(ret)->IncreaseReferenceCount();
		return ret;
	}

	// Checks the file extension to see if the file is of correct type
	uint index = (uint)filepath.find_last_of('.');
	std::string ext = filepath.substr(index, filepath.length() - 1);

	// If the given extension is not a valid key...
	if (typemap.find(ext) == typemap.end())
	{
#ifdef DEBUG
		Debug::LogError("[ResourceManager] File extension is invalid.");
#endif
		return 0;
	}

	// Call the appropriate loading function
	if (typemap[ext] == "Texture2D")
	{
		ret = dynamic_cast<T*>(LoadTexture2D(filepath));
	}
	else if (typemap[ext] == "Mesh")
	{
		ret = dynamic_cast<T*>(LoadMesh(filepath));
	}
	else
	{
#ifdef DEBUG
		Debug::LogError("[ResourceManager] Resource type not initialized in typemap");
#endif
		return 0;
	}

#ifdef DEBUG
	if (!ret)
	{
		Debug::LogError("[ResourceManager] File could not be loaded.");
	}
#endif
	return ret;
}

template Resource* ResourceManager::LoadResource<Resource>(std::string filepath);
template Texture2D* ResourceManager::LoadResource<Texture2D>(std::string filepath);
template Mesh* ResourceManager::LoadResource<Mesh>(std::string filepath);

Mesh* ResourceManager::CreatePrimitive(PrimitiveType pType)
{
	Mesh* mesh;
	switch (pType)
	{
	case PlaneMesh:
		if (mesh = dynamic_cast<Mesh*>(CheckResourceCollection("Plane")))
		{
			mesh->IncreaseReferenceCount();
			return mesh;
		}
		break;
	case CubeMesh:
		if (mesh = dynamic_cast<Mesh*>(CheckResourceCollection("Cube")))
		{
			mesh->IncreaseReferenceCount();
			return mesh;
		}
		break;
	case SphereMesh:
		if (mesh = dynamic_cast<Mesh*>(CheckResourceCollection("Sphere")))
		{
			mesh->IncreaseReferenceCount();
			return mesh;
		}
		break;
	case ConeMesh:
		if (mesh = dynamic_cast<Mesh*>(CheckResourceCollection("Cone")))
		{
			mesh->IncreaseReferenceCount();
			return mesh;
		}
		break;
	case CylinderMesh:
		if (mesh = dynamic_cast<Mesh*>(CheckResourceCollection("Cylinder")))
		{
			mesh->IncreaseReferenceCount();
			return mesh;
		}
		break;
	}

	MeshData data;
	data = MeshBuilder::CreatePrimitive(pType);

	mesh = new Mesh(data);

	switch (pType)
	{
	case PlaneMesh:
		resourceCollection["Plane"] = mesh;
		break;
	case CubeMesh:
		resourceCollection["Cube"] = mesh;
		break;
	case SphereMesh:
		resourceCollection["Sphere"] = mesh;
		break;
	case ConeMesh:
		resourceCollection["Cone"] = mesh;
		break;
	case CylinderMesh:
		resourceCollection["Cylinder"] = mesh;
		break;
	}

	// TODO: Remove this once all MeshBuilder functions are implemented
	if (mesh)
	{
		mesh->IncreaseReferenceCount();
		return mesh;
	}

	return 0;
}

void ResourceManager::FreeResources()
{
	for (Resourcemap::iterator i = resourceCollection.begin(); i != resourceCollection.end(); i++)
	{
		delete i->second;
	}
	resourceCollection.clear();
}

void ResourceManager::InitializeTypemap()
{
	// TODO: May want to find some way to make this less hardcoded
	// TODO: Also, this will not support one extension being valid for more than one resource type
	typemap[".jpg"] = "Texture2D";
	typemap[".png"] = "Texture2D";
	typemap[".bmp"] = "Texture2D";

	typemap[".fbx"] = "Mesh";
	typemap[".obj"] = "Mesh";
}

Resource* ResourceManager::CheckResourceCollection(std::string s)
{
	if (resourceCollection.find(s) != resourceCollection.end())
	{
		return resourceCollection[s];
	}
	else
	{
		return nullptr;
	}
}

Resource* ResourceManager::LoadTexture2D(std::string filepath)
{
	Image image;
	int width, height, components;
	image.data = stbi_load(filepath.c_str(), &width, &height, &components, 0);
	image.width = width;
	image.height = height;
	image.components = components;

	// This may not work as intended
	if (image.data == NULL)
	{
#ifdef DEBUG
		Debug::LogError("[ResourceManager] Texture2D could not be loaded.");
#endif
		return 0;
	}

	Texture2D* texture = new Texture2D(image);

	texture->IncreaseReferenceCount();
	resourceCollection[filepath] = texture;
	return dynamic_cast<Resource*>(texture);
}

Resource* ResourceManager::LoadMesh(std::string filepath)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filepath, aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_SortByPType);
	
	// NOTE: Depending on what ReadFile returns, this may not work as intended
	if (!scene)
	{
#if DEBUG
		Debug::LogError("[ResourceManager] Assimp importer could not read file.");
#endif
		return 0;
	}
	MeshData data = AssimpProcessScene(scene->mRootNode, scene);
	
	Mesh* mesh = new Mesh(data);

	mesh->IncreaseReferenceCount();
	resourceCollection[filepath] = mesh;
	return dynamic_cast<Resource*>(mesh);
}

MeshData ResourceManager::AssimpProcessScene(aiNode* node, const aiScene* scene)
{
	MeshData data;

	for (UINT i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[i];
		data.Append(AssimpProcessMesh(mesh, scene));
	}

	for (UINT i = 0; i < node->mNumChildren; i++)
	{
		AssimpProcessScene(node->mChildren[i], scene);
	}

	return data;
}

MeshData ResourceManager::AssimpProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	MeshData data;

	for (UINT i = 0; i < mesh->mNumVertices; i++)
	{
		MeshVertex temp;
		Vector3 tempvec;

		// Vertices
		tempvec.x = mesh->mVertices[i].x;
		tempvec.y = mesh->mVertices[i].y;
		tempvec.z = mesh->mVertices[i].z;
		temp.position = tempvec;

		// Normals
		tempvec.x = mesh->mNormals[i].x;
		tempvec.y = mesh->mNormals[i].y;
		tempvec.z = mesh->mNormals[i].z;
		temp.normal = tempvec;

		// Tangents
		if (mesh->mTangents)
		{
			tempvec.x = mesh->mTangents[i].x;
			tempvec.y = mesh->mTangents[i].y;
			tempvec.z = mesh->mTangents[i].z;
		}
		else
		{
			tempvec.x = 1.0;
			tempvec.y = tempvec.z = 0.0;
		}
		temp.tangent = tempvec;

		// Colors
		if (mesh->mColors[0])
		{
			tempvec.x = mesh->mColors[0][i].r;
			tempvec.y = mesh->mColors[0][i].g;
			tempvec.z = mesh->mColors[0][i].b;
		}
		else
		{
			tempvec.x = tempvec.y = tempvec.z = 0.7f;
		}
		temp.color = Color(tempvec.x, tempvec.y, tempvec.z, 1.0);

		// UVs
		if (mesh->mTextureCoords[0])
		{
			tempvec.x = mesh->mTextureCoords[0][i].x;
			tempvec.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			tempvec.x = tempvec.y = tempvec.z = 0.0;
		}
		temp.texCoord.x = tempvec.x;
		temp.texCoord.y = tempvec.y;
		data.vertices.push_back(temp);
	}

	for (UINT i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (UINT j = 0; j < face.mNumIndices; j++)
		{
			data.indices.push_back(face.mIndices[j]);
		}
	}

	return data;
}
NS_END