#ifndef RASTERIZERSTATE_HPP
#define RASTERIZERSTATE_HPP

#include "../../Config.hpp"

NS_BEGIN

// TODO: Fillout RasterizerState class
class RasterizerState
{
public:
	RasterizerState();
	~RasterizerState();

	void Set();
private:
	ID3D11RasterizerState* state;
};

NS_END

#endif