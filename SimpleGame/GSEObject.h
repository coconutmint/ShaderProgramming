#pragma once
#include "Global.h"

class GSEObject
{
public:
	GSEObject(GSEVec3 pos, GSEVec3 size);
	~GSEObject();

	GSEVec3 GetPos();
	GSEVec3 GetSize();

private:
	GSEVec3 m_pos;
	GSEVec3 m_size;
};

