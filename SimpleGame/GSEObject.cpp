#include "stdafx.h"
#include "GSEObject.h"

GSEObject::GSEObject(GSEVec3 pos, GSEVec3 size, GSEVec3 vel, GSEVec3 acc, float mass)
{
	m_pos = pos;
	m_size = size;
	m_vel = vel;
	m_acc = acc;
	m_mass = mass;
}

GSEObject::~GSEObject()
{
}

GSEVec3 GSEObject::GetPos()
{
	return m_pos;
}

void GSEObject::SetPos(GSEVec3 in)
{
	m_pos = in;
}

GSEVec3 GSEObject::GetSize()
{
	return m_size;
}

void GSEObject::SetSize(GSEVec3 in)
{
	m_size = in;
}

GSEVec3 GSEObject::GetVel()
{
	return GSEVec3();
}

void GSEObject::SetVel(GSEVec3 in)
{
	m_vel = in;
}

GSEVec3 GSEObject::GetAcc()
{
	return GSEVec3();
}

void GSEObject::SetAcc(GSEVec3 in)
{
	m_acc = in;
}

float GSEObject::GetMass()
{
	return 0.0f;
}

void GSEObject::SetMass(float in)
{
	m_mass = in;
}
