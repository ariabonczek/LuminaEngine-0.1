#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../Config.hpp"
#include "../Math/Math.hpp"
#include "Color.hpp"

NS_BEGIN

class Scene;
class GameObject;

enum RenderPassType
{
	OpaqueGeometry,
	TransparentGeometry,
	DeferredGeometry,
	DeferredLighting,
	DeferredFinal,
	ShadowPass,
	ReflectionPass,
};

struct PerFrameData
{
	Matrix view;
	Matrix projection;
	Vector3 eyePos;
	float elapsedTime;
};

struct PerObjectData
{
	Matrix world;
	Matrix worldInverseTranspose;
};

struct DLightData
{
	Color color;
	Vector3 direction;
	float intensity;
	bool hasShadows;
	float pad[3];
};

struct PLightData
{
	Color color;
	Vector3 position;
	float range;
	float intensity;
	bool hasShadows;
	float pad[2];
};

struct SLightData
{
	Color color;
	Vector3 direction;
	float intensity;
	Vector3 position;
	float range;
	float spot;
	bool hasShadows;
	float pad[2];
};

struct LightData
{
	DLightData dLightData[NUM_DIRECTIONAL_LIGHTS];
	PLightData pLightData[NUM_POINT_LIGHTS];
	SLightData sLightData[NUM_SPOT_LIGHTS];
	uint numDL;
	uint numPL;
	uint numSL;
	float pad;
};

class Renderer
{
	friend class Game;
public:	
	~Renderer();
private:
	Renderer();
	static Renderer instance;

	static bool Initialize();
	static bool InitializePipeline();

	// TODO: Move this to the SceneManager when handling more than one scene
	static bool InitializeScene(Scene& scene);

	static void Shutdown();

	static void RenderScene(const Scene& scene);
	static void RenderPass(RenderPassType pass,const Scene& scene);
	static void UpdateFrameData(const Scene& scene);
	static void UpdateMaterialData(GameObject* obj);
	static void UpdateObjectData(GameObject* obj);
	static void UpdateLightData(const Scene& scene);

	static ID3D11InputLayout* inputLayout;

	static PerFrameData perFrameData;
	static ID3D11Buffer* perFrameBuffer;

	static ID3D11Buffer* perMaterialBuffer;

	static PerObjectData perObjectData;
	static ID3D11Buffer* perObjectBuffer;

	static LightData lightData;
	static ID3D11Buffer* lightingBuffer;

	static ID3D11Buffer* shadowBuffer;
};

NS_END

#endif