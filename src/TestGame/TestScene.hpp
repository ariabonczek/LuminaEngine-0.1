#ifndef TESTSCENE_HPP
#define TESTSCENE_HPP

#include "../Lumina.hpp"
using namespace Lumina;

class TestScene : public Lumina::Scene
{
public:
	void LoadResources();
	void UnloadResources();
	void Update(float dt);
private:
};

#endif