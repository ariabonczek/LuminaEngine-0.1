#ifndef SHADER_HPP
#define SHADER_HPP

#include "../Config.hpp"

NS_BEGIN

struct Vector2;
struct Vector3; 
struct Vector4;
class Color;
struct Matrix;
class Texture2D;

enum ShaderType
{
	Vertex,
	Hull,
	Domain,
	Geometry,
	Pixel,
	Compute
};

class Shader
{
	friend class Material;
public:
	Shader();
	~Shader();

	/// <summary>
	/// Called when the material is initialized (after LoadResources)
	/// </summary>
	void Initialize();

	#pragma region Static Instances
	static void InitializeStatic();
	static Shader* Default;
	static void Shutdown();
	#pragma endregion

	/// <summary>
	/// Load a shader program from a file and store it
	/// </summary>
	bool LoadFromFile(std::string filepath, ShaderType sType);

	/// <summary>
	/// Adds a new property 
	/// </summary>
	template<typename T>
	void AddProperty(std::string name);

	void Bind();
private:
	bool initialized;
	std::vector<float> data;
	std::vector<Texture2D*> textures; // TODO: WILL NEED TO WORK WITH MORE THAN JUST 2D TEXTURES!!
	std::map<std::string, uint> propertyMap;
	std::map<std::string, uint> textureMap;

	ID3D11VertexShader*   vertexShader;
	ID3D11HullShader*     hullShader;
	ID3D11DomainShader*   domainShader;
	ID3D11GeometryShader* geometryShader;
	ID3D11PixelShader*    pixelShader;
	ID3D11ComputeShader*  computeShader;
};

NS_END

#endif