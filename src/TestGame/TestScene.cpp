#include "TestScene.hpp"

void MoveCamera(Transform* t, float d);

void TestScene::LoadResources()
{
	q1 = Quaternion::CreateFromEulerAngles(Vector3(0.0f, 0.0f, 0.0f));
	q2 = Quaternion::CreateFromEulerAngles(Vector3(0.0f, 180.0f, 0.0f));
	t = 0.0f;

	// TODO: Add a 'CreateGameObject' method to scene to handle behind the scenes
	ambientLight = Color(0.2f, 0.2f, 0.2f, 1.0f);

	GameObject* cam = new GameObject("Camera");
	cam->AddComponent<Camera>(new Camera());
	cam->GetComponent<Transform>()->SetLocalPosition(0.0f, 0.0f, -20.0f);
	activeCamera = cam->GetComponent<Camera>();
	AddObject(cam);
	
	GameObject* light = new GameObject("Light");
	light->AddComponent<Light>(new DirectionalLight(Color::White, 1.0f));
	AddObject(light);

	// TODO: Need a way to prevent Material memory leaks now that it is no longer a component
	Material* earthMat = new Material(Shader::Default);
	earthMat->SetPropertyValue<Texture2D>("diffuse", ResourceManager::LoadResource<Texture2D>("Textures/planet-diffuse.png"));
	earthMat->SetPropertyValue<Texture2D>("normal", ResourceManager::LoadResource<Texture2D>("Textures/planet-normals.png"));

	Material* moonMat = new Material(Shader::Default);
	moonMat->SetPropertyValue<Texture2D>("diffuse", ResourceManager::LoadResource<Texture2D>("Textures/moon.jpg"));

	GameObject* earth = new GameObject("Earth");
	earth->AddComponent<MeshRenderer>(new MeshRenderer(ResourceManager::CreatePrimitive(PrimitiveType::SphereMesh))); 
	earth->GetComponent<MeshRenderer>()->SetMaterial(earthMat);
	//earth->GetTransform()->SetLocalRotation(Quaternion::CreateFromAxisAngle(Vector3::Right, 23.4f));
	AddObject(earth);
	
	GameObject* moon = new GameObject("Moon");
	moon->AddComponent<MeshRenderer>(new MeshRenderer(ResourceManager::CreatePrimitive(PrimitiveType::SphereMesh)));
	moon->GetComponent<MeshRenderer>()->SetMaterial(moonMat);
	moon->GetTransform()->SetParent(earth->GetTransform());
	moon->GetTransform()->SetLocalPosition(3.0f, 0.0f, 0.0f);
	moon->GetTransform()->SetLocalScale(0.2f, 0.2f, 0.2f);
	AddObject(moon);
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
		if (p->GetName() == "Earth")
		{
			p->GetTransform()->Rotate(Quaternion::CreateFromAxisAngle(Vector3::Up, 0.567f));
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
