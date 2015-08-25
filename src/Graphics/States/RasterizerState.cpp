#include "RasterizerState.hpp"

#include "../GraphicsDevice.hpp"

NS_BEGIN

RasterizerState::RasterizerState()
{
	
}

RasterizerState::~RasterizerState()
{
	DELETECOM(state);
}

void RasterizerState::Set()
{

	GraphicsDevice::GetDeviceContext()->RSSetState(state);
}

NS_END