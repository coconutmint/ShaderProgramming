#pragma once
#include "Global.h"

class GSEObject
{
public:
	GSEObject(GSEVec3 pos, GSEVec3 size, GSEVec3 vel, GSEVec3 acc, float mass);
	~GSEObject();

	void Update(float eTime);

	GSEVec3 GetPos();
	void SetPos(GSEVec3 in);
	GSEVec3 GetSize();
	void SetSize(GSEVec3 in);
	GSEVec3 GetVel();
	void SetVel(GSEVec3 in);
	GSEVec3 GetAcc();
	void SetAcc(GSEVec3 in);
	float GetMass();
	void SetMass(float in);

	void AddForce(GSEVec3 force, float eTime);

private:
	GSEVec3 m_pos;
	GSEVec3 m_size;
	GSEVec3 m_vel;
	GSEVec3 m_acc;
	float   m_mass;
};

