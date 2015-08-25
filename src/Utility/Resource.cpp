#include "Resource.hpp"

NS_BEGIN

Resource::Resource():
referenceCount(0)
{}

Resource::~Resource()
{
}

void inline Resource::IncreaseReferenceCount()
{
	referenceCount++;
}

void inline Resource::DecreaseReferenceCount()
{
	referenceCount--;
}

NS_END