#ifndef PLANE_HPP
#define PLANE_HPP

#include "../../Config.hpp"
#include "../GameObject.hpp"

NS_BEGIN

class Plane : public GameObject
{
public:
	Plane();
	~Plane();

	void Update();
private:

};

NS_END

#endif