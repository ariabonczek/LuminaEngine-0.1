#include "TestScene.hpp"

void MoveCamera(Transform* t, float d);

void TestScene::LoadResources()
{
	// TODO: Add a 'CreateGameObject' method to scene to handle behind the scenes

	GameObject* cam = new GameObject();
	cam->AddComponent<Camera>(new Camera());
	cam->GetComponent<Transform>()->SetLocalPosition(0.0f, 0.0f, -10.0f);
	activeCamera = cam->GetComponent<Camera>();
	AddObject(cam);

	Material* mat = new Material(Shader::Default);
	mat->SetPropertyValue<Texture2D>("diffuse", ResourceManager::LoadResource<Texture2D>("Textures/brick.jpg"));
	
	mat->SetPropertyValue<Color>("tint", Color::White);
	mat->SetPropertyValue<float>("roughness", 1.0f);
	mat->SetPropertyValue<float>("metalness", 1.0f);

	DirectionalLight* dLight = new DirectionalLight(Color::White, 1.0f);

	GameObject* texturedObj = new GameObject();
	texturedObj->AddComponent<Material>(mat);
	texturedObj->AddComponent<MeshRenderer>(new MeshRenderer(ResourceManager::CreatePrimitive(CubeMesh)));
	texturedObj->AddComponent<Light>(dLight);
	AddObject(texturedObj);

	GameObject* plane = new GameObject();
	plane->AddComponent<Material>(Material::Default);
	plane->AddComponent<MeshRenderer>(new MeshRenderer(ResourceManager::CreatePrimitive(PlaneMesh)));
	plane->GetComponent<Transform>()->SetLocalPosition(0.0f, -5.0f, 0.0f);
	AddObject(plane);
}

void TestScene::UnloadResources()
{
	for (GameObject* p : objs)
		delete p;
}

void TestScene::Update(float dt)
{
	for (GameObject* p : objs)
	{
		p->Update();
	}
	MoveCamera(activeCamera->GetGameObject()->GetComponent<Transform>(), 0.0167f);
}

void MoveCamera(Transform* t, float dt)
{
	if (GetAsyncKeyState('W') & 0x8000)
		t->Translate(t->GetForward() * dt);
	if (GetAsyncKeyState('S') & 0x8000)
		t->Translate(-t->GetForward() * dt);
	if (GetAsyncKeyState('A') & 0x8000)
		t->Translate(-t->GetRight() * dt);
	if (GetAsyncKeyState('D') & 0x8000)
		t->Translate(t->GetRight() * dt);

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		t->Rotate(t->GetRight() * dt);
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		t->Rotate(t->GetUp() * dt);
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		t->Rotate(-t->GetUp() * dt);
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		t->Rotate(-t->GetRight() * dt);
}