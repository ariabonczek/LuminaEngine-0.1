#include "TestScene.hpp"

void MoveCamera(Transform* t, float d);

void TestScene::LoadResources()
{
	// TODO: Add a 'CreateGameObject' method to scene to handle behind the scenes
	ambientLight = Color(0.2f, 0.2f, 0.2f, 1.0f);

	GameObject* cam = new GameObject("Camera");
	cam->AddComponent<Camera>(new Camera());
	cam->GetComponent<Transform>()->SetLocalPosition(0.0f, 0.0f, -10.0f);
	activeCamera = cam->GetComponent<Camera>();
	AddObject(cam);

	Material* mat = new Material(Shader::Default);
	mat->SetPropertyValue<Texture2D>("diffuse", ResourceManager::LoadResource<Texture2D>("Textures/brick_diff.jpg"));
	mat->SetPropertyValue<Texture2D>("normal", ResourceManager::LoadResource<Texture2D>("Textures/brick_nor.jpg"));
	
	mat->SetPropertyValue<Color>("tint", Color::White);
	mat->SetPropertyValue<float>("roughness", 1.0f);
	mat->SetPropertyValue<float>("metalness", 1.0f);

	mat->SetSpecularPower(32.0f);

	GameObject* light = new GameObject("DirectionalLight");
	light->AddComponent<Light>(new DirectionalLight(Color::White, 1.0f));
	light->GetTransform()->Rotate(Quaternion::CreateFromEulerAngles(Vector3(45.0f, 45.0f, 0.0f)));
	AddObject(light);

	GameObject* pLight = new GameObject("PointLight");
	pLight->AddComponent<Light>(new PointLight(Color::White, 1.0f, 10.0f));
	pLight->GetTransform()->SetLocalPosition(Vector3(5.0f, 0.0f, 0.0f));
	AddObject(pLight);

	GameObject* texturedObj = new GameObject("Cube");
	texturedObj->AddComponent<Material>(mat);
	texturedObj->AddComponent<MeshRenderer>(new MeshRenderer(ResourceManager::CreatePrimitive(CubeMesh)));
	AddObject(texturedObj);

	GameObject* plane = new GameObject("Plane");
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
		if (p->GetName() == "Cube")
		{
			p->GetTransform()->Rotate(Quaternion::CreateFromEulerAngles(Vector3(0.0f, 0.5f, 0.0f)));
		}
		p->Update();
	}
	MoveCamera(activeCamera->GetGameObject()->GetComponent<Transform>(), 0.167f);
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

	dt *= 10;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		t->Rotate(Quaternion::CreateFromAxisAngle(t->GetRight(), -dt));
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		t->Rotate(Quaternion::CreateFromAxisAngle(Vector3::Up, -dt));
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		t->Rotate(Quaternion::CreateFromAxisAngle(Vector3::Up, dt));
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		t->Rotate(Quaternion::CreateFromAxisAngle(t->GetRight(), dt));
}