#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include "../Config.hpp"

NS_BEGIN

class Resource
{
	friend class ResourceManager;
public:
	Resource();
	virtual ~Resource();

protected:
	/// <summary>
	/// Increases the reference count by 1 when a new reference is made
	/// </summary>
	virtual void inline IncreaseReferenceCount();

	/// <summary>
	/// Decreases the reference count by 1 when a reference is deleted
	/// </summary>
	virtual void inline DecreaseReferenceCount();
private:
	int referenceCount;
};

NS_END

#endif