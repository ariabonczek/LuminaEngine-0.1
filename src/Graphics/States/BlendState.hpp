#ifndef BLENDSTATE_HPP
#define BLENDSTATE_HPP

#include "../../Config.hpp"
#include "../GraphicsDevice.hpp"

NS_BEGIN

enum BlendType
{
	Transparency,
	NoTransparency,
	Additive,
	Subtractive
};

class BlendState
{
public:
	BlendState(BlendType blendType);
	~BlendState();

	/// <summary>
	///
	/// </summary>
	void BindBlendState();

private:
	ID3D11BlendState* blendState;
};

NS_END

#endif