#pragma once
#include "Global.h"
#include "GSEObject.h"

class GSEObjectMgr
{
public:
	GSEObjectMgr();
	~GSEObjectMgr();

	int AddObject(GSEVec3 pos, GSEVec3 size, GSEVec3 vel, GSEVec3 acc, float mass);
	GSEObject * GetObject(int index);
	bool DeleteObject(int index);
	int FindEmptySlot();
	void UpdateObjects(float eTime);
	void AddForce(int index, GSEVec3 force, float eTime);

	void DoGarbageCollect();
private:
	GSEObject* m_objects[MAX_OBJECT_COUNT];

};

