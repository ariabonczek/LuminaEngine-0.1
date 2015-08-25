#ifndef CUBE_HPP
#define CUBE_HPP

#include "../../Config.hpp"
#include "../GameObject.hpp"

NS_BEGIN

class Cube : public GameObject
{
public:
	Cube();
	~Cube();

	void Update();
private:

};

NS_END

#endif