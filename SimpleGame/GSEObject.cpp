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

void GSEObject::Update(float eTime)
{
	m_pos.x = m_pos.x + m_vel.x * eTime;
	m_pos.y = m_pos.y + m_vel.y * eTime;
	m_pos.z = m_pos.z + m_vel.z * eTime;
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

void GSEObject::AddForce(GSEVec3 force, float eTime)
{
	GSEVec3 acc;
	acc.x = force.x / m_mass;
	acc.y = force.y / m_mass;
	acc.z = force.z / m_mass;
	m_vel.x += acc.x * eTime;
	m_vel.y += acc.y * eTime;
	m_vel.z += acc.z * eTime;
}
