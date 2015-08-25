#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include "../Config.hpp"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "../Graphics/MeshData.hpp"
#include "../Graphics/MeshBuilder.hpp"

NS_BEGIN

class GraphicsDevice;
class Resource;
class Texture2D;
class Mesh;

typedef std::map<std::string, Resource*> Resourcemap;

/// <summary>
/// Manager class to statically handle resource loading, referencing, and deleting
/// </summary>
class ResourceManager
{
public:
	/// <summary>
	/// Initializes the ResourceManager, allowing it to be used
	/// </summary>
	static bool Initialize(GraphicsDevice* graphicsDevice);

	/// <summary>
	/// Loads a resource of specified type. Returns a nullptr if the resource could not be loaded.
	/// </summary>
	template<class T>
	static T* LoadResource(std::string filepath);

	/// <summary>
	/// Uses the MeshBuilder to create primitives from scratch
	/// </summary>
	static Mesh* CreatePrimitive(PrimitiveType pType);

	/// <summary>
	/// Frees all of the memory used by the ResourceManager
	/// </summary>
	static void FreeResources();
private:
	static Resourcemap resourceCollection;
	static std::map<std::string, std::string> typemap;

	/// <summary>
	/// Sets up the typemap for use
	/// </summary>
	static void InitializeTypemap();

	/// <summary>
	/// Returns the resource if it is loaded or null if it is not
	/// </summary>
	static Resource* CheckResourceCollection(std::string s);

	// TODO: Future: Separate loading code to a FileManager for threaded loading operations

	/// <summary>
	/// Loads a Texture2D, returns a pointer to it and stores it in the resourceCollection hashtable
	/// </summary>
	static Resource* LoadTexture2D(std::string filepath);

	/// <summary>
    /// Loads a Mesh, returns a pointer to it and stores it in the resourceCollection hashtable
	/// </summary>
	static Resource* LoadMesh(std::string filepath);

	#pragma region Assimp Mesh Loading

	static MeshData AssimpProcessScene(aiNode* node, const aiScene* scene);
	static MeshData AssimpProcessMesh(aiMesh* mesh, const aiScene* scene);

	#pragma endregion

};

NS_END

#endif