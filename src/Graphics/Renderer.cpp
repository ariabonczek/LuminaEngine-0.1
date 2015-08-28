#include "Renderer.hpp"
#include "../Utility/Scene.hpp"
#include <d3dcompiler.h>
#include "GraphicsDevice.hpp"
#include "../Objects/GameObject.hpp"

NS_BEGIN

Renderer Renderer::instance;
ID3D11InputLayout* Renderer::inputLayout;

PerFrameData Renderer::perFrameData;
ID3D11Buffer* Renderer::perFrameBuffer;
MiscData Renderer::miscData;
ID3D11Buffer* Renderer::miscBuffer;
PerObjectData Renderer::perObjectData;
ID3D11Buffer* Renderer::perObjectBuffer;
LightData Renderer::lightData;
ID3D11Buffer* Renderer::lightingBuffer;
ID3D11Buffer* Renderer::shadowBuffer;

Renderer::Renderer()
{}

Renderer::~Renderer()
{}

bool Renderer::Initialize()
{
	if (!InitializePipeline())
	{
#if DEBUG
		Debug::LogError("[Renderer] Initialize Pipeline failed!");
#endif
		return false;
	}

	return true;
}

bool Renderer::InitializePipeline()
{
	D3D11_INPUT_ELEMENT_DESC vDesc[] =
	{
		{ "POSITION", NULL, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, NULL },
		{ "COLOR", NULL, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, NULL },
		{ "TEXCOORD", NULL, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, NULL },
		{ "NORMAL", NULL, DXGI_FORMAT_R32G32B32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, NULL },
		{ "TANGENT", NULL, DXGI_FORMAT_R32G32B32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, NULL }
	};

	ID3DBlob* vertexByte;
	D3DReadFileToBlob(L"Shaders/DefaultVertex.cso", &vertexByte);

	GraphicsDevice::GetDevice()->CreateInputLayout(vDesc, ARRAYSIZE(vDesc), vertexByte->GetBufferPointer(), vertexByte->GetBufferSize(), &inputLayout);
	DELETECOM(vertexByte);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;

	bd.ByteWidth = sizeof(perFrameData);
	GraphicsDevice::GetDevice()->CreateBuffer(&bd, NULL, &perFrameBuffer);

	bd.ByteWidth = sizeof(miscData);	
	GraphicsDevice::GetDevice()->CreateBuffer(&bd, NULL, &miscBuffer);

	bd.ByteWidth = sizeof(perObjectData);
	GraphicsDevice::GetDevice()->CreateBuffer(&bd, NULL, &perObjectBuffer);

	bd.ByteWidth = sizeof(lightData);
	GraphicsDevice::GetDevice()->CreateBuffer(&bd, NULL, &lightingBuffer);

	// TODO: Consolidate these into less calls

	GraphicsDevice::GetDeviceContext()->VSSetConstantBuffers(PER_FRAME_SLOT, 1, &perFrameBuffer);
	GraphicsDevice::GetDeviceContext()->PSSetConstantBuffers(PER_FRAME_SLOT, 1, &perFrameBuffer);

	GraphicsDevice::GetDeviceContext()->VSSetConstantBuffers(PER_OBJECT_SLOT, 1, &perObjectBuffer);

	GraphicsDevice::GetDeviceContext()->PSSetConstantBuffers(LIGHTING_SLOT, 1, &lightingBuffer);

	GraphicsDevice::GetDeviceContext()->PSSetConstantBuffers(MISC_SLOT, 1, &miscBuffer);

	return true;
}

bool Renderer::InitializeScene(Scene& scene)
{
	for (GameObject* obj : scene.objs)
	{
		obj->Initialize();
	}

	lightData.ambientLight = scene.ambientLight;

	// TODO: THIS IS AWFUL
	for (Light* l : scene.lights)
	{
		if(DirectionalLight* d = dynamic_cast<DirectionalLight*>(l))
		{
			if(lightData.numDL == NUM_DIRECTIONAL_LIGHTS)
			{
#if DEBUG
				Debug::LogError("[Renderer] Maximum # of Directional Lights reached, discarded additional lights.");
#endif
			}

			DLightData dd;
			dd.color = d->GetColor();
			dd.direction = d->GetGameObject()->GetComponent<Transform>()->GetForward();
			dd.intensity = d->GetIntensity();
			dd.hasShadows = d->GetHasShadows();

			// this not gon work
			lightData.dLightData[lightData.numDL] = dd;
			lightData.numDL++;
		}
		if(SpotLight* s = dynamic_cast<SpotLight*>(l))
		{
			if(lightData.numSL == NUM_SPOT_LIGHTS)
			{
#if DEBUG
				Debug::LogError("[Renderer] Maximum # of Spot Lights reached, discarded additional lights.");
#endif
			}

			SLightData sd;
			sd.color = s->GetColor();
			sd.direction = s->GetGameObject()->GetComponent<Transform>()->GetForward();
			sd.intensity = s->GetIntensity();
			sd.hasShadows = s->GetHasShadows();
			sd.spot = s->GetSpot();
			sd.position = s->GetGameObject()->GetComponent<Transform>()->GetWorldPosition();
			sd.range = s->GetRange();

			lightData.sLightData[lightData.numSL] = sd;
			lightData.numSL++;
		}
		if(PointLight* p = dynamic_cast<PointLight*>(l))
		{
			if(lightData.numPL == NUM_POINT_LIGHTS)
			{
#if DEBUG
				Debug::LogError("[Renderer] Maximum # of Point Lights reached, discarded additional lights.");
#endif
			}

			PLightData pd;
			pd.color = p->GetColor();
			pd.intensity = p->GetIntensity();
			pd.hasShadows = p->GetHasShadows();
			pd.range = p->GetRange();
			pd.position = p->GetGameObject()->GetComponent<Transform>()->GetWorldPosition();

			lightData.pLightData[lightData.numPL] = pd;
			lightData.numPL++;
		}
	}

	return true;
}

void Renderer::Shutdown()
{
	DELETECOM(inputLayout);
	DELETECOM(perFrameBuffer);
	DELETECOM(perObjectBuffer);
	DELETECOM(miscBuffer);
	DELETECOM(lightingBuffer);
	DELETECOM(shadowBuffer);
}

void Renderer::RenderScene(const Scene& scene)
{
	UpdateFrameData(scene);
	UpdateLightData(scene);

	RenderPass(OpaqueGeometry, scene);
}

void Renderer::RenderPass(RenderPassType pass, const Scene& scene)
{
	switch(pass)
	{
	case OpaqueGeometry:	
		GraphicsDevice::GetDeviceContext()->IASetInputLayout(inputLayout);
		GraphicsDevice::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		for (GameObject* obj : scene.objs)
		{
			UpdateMaterialData(obj);
			UpdateObjectData(obj);
			obj->Render();
		}
		break;
	}
}

void Renderer::UpdateFrameData(const Scene& scene)
{
	perFrameData.view = Matrix::Transpose(scene.activeCamera->GetView());
	perFrameData.projection = Matrix::Transpose(scene.activeCamera->GetProj());
	perFrameData.eyePos = scene.activeCamera->GetGameObject()->GetComponent<Transform>()->GetWorldPosition();
	perFrameData.elapsedTime = 0.0f;
	GraphicsDevice::GetDeviceContext()->UpdateSubresource(perFrameBuffer, 0, NULL, &perFrameData, 0, 0);
}

void Renderer::UpdateMaterialData(GameObject* obj)
{
	if (Material* cache = obj->GetComponent<Material>())
	{
		cache->Bind();
		miscData.specularPower = cache->GetSpecularPower();
		GraphicsDevice::GetDeviceContext()->UpdateSubresource(miscBuffer, 0, NULL, &miscData, 0, 0);
	}	
}

void Renderer::UpdateObjectData(GameObject* obj)
{
	Transform* cache = obj->GetComponent<Transform>();
	perObjectData.world = Matrix::Transpose(cache->GetWorldMatrix());
	// TODO: This transposes the transpose of the inverse... this is obnoxious
	perObjectData.worldInverseTranspose = Matrix::Transpose(cache->GetWorldInverseTranspose());
	GraphicsDevice::GetDeviceContext()->UpdateSubresource(perObjectBuffer, 0, NULL, &perObjectData, 0, 0);
}

void Renderer::UpdateLightData(const Scene& scene)
{
	GraphicsDevice::GetDeviceContext()->UpdateSubresource(lightingBuffer, 0, NULL, &lightData, 0, 0);
}

NS_END