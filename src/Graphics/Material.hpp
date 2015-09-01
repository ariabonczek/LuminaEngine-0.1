#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "../Config.hpp"

#include "../Objects/Component.hpp"
#include "Shader.hpp"

NS_BEGIN

class Material
{
public:
	Material(Shader* shader);
	Material(Material* material);
	~Material();

	void Initialize();

	#pragma region Static Instances
	static void InitializeStatic();
	static Material* Default;
	static void ShutdownStatic();
	#pragma endregion

	void SetSpecularPower(float power);
	float GetSpecularPower()const;

	/// <summary>
	/// Sets the value of the given property to the given value
	/// </summary>
	template<typename T>
	void SetPropertyValue(std::string name, T val);
	template<typename T>
	void SetPropertyValue(std::string name, T* val);

	/// <summary>
	/// Bind the shader to the graphics pipelines
	/// </summary>
	void Bind();
private:
	void SetTextures();
	void UpdateAndSetBuffer();

	ID3D11Buffer* propertyBuffer;

	Shader* shader;

	float specularPower;
};

NS_END

#endif