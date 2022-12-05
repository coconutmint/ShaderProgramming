#include "stdafx.h"
#include "GSEObject.h"
#include <math.h>
#include <float.h>
#include <iostream>
GSEObject::GSEObject(GSEVec3 pos, GSEVec3 size, GSEVec3 vel, GSEVec3 acc, float mass)
{
	m_pos = pos;
	m_size = size;
	m_vel = vel;
	m_acc = acc;
	m_mass = mass;
	m_fricCoef = 0.5f;
	m_type = OBJ_TYPE_NORMAL;

	m_coolTime = 0.5f;
	m_coolTime_remaining = 0.f;
}

GSEObject::~GSEObject()
{
}

void GSEObject::Update(float eTime)
{
	float normalForce = m_mass * GRAVITY;
	float fric = m_fricCoef * normalForce;
	float mag = sqrtf(m_vel.x * m_vel.x + m_vel.y * m_vel.y);
	

	
	if (mag > FLT_EPSILON)
	{
		GSEVec3 velDir = { m_vel.x / mag, m_vel.y / mag };
		velDir.x *= -1.f;
		velDir.y *= -1.f;
		velDir.x *= fric;
		velDir.y *= fric;
		velDir.x /= m_mass;
		velDir.y /= m_mass;
		GSEVec2 resultVel = { 0,0 };
		resultVel.x = m_vel.x + velDir.x;
		resultVel.y = m_vel.y + velDir.y;

		if (resultVel.x * m_vel.x < 0.f)
		{
			m_vel.x = 0.f;
		}
		else
		{
			m_vel.x += velDir.x;
		}
		if (resultVel.y * m_vel.y < 0.f)
		{
			m_vel.y = 0.f;
		}
		else
		{
			m_vel.y += velDir.y;
		}
		m_vel.x += velDir.x;
		m_vel.y += velDir.y;
	}
	else
	{

	}

	m_pos.x = m_pos.x + m_vel.x * eTime;
	m_pos.y = m_pos.y + m_vel.y * eTime;
	m_pos.z = m_pos.z + m_vel.z * eTime;
//	std::cout << "x velocity: " << m_vel.x << std::endl;

//cool time 
	m_coolTime_remaining -= eTime;
	if (m_coolTime_remaining < FLT_EPSILON)
	{
		m_coolTime_remaining = 0.f;
	}
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
	return m_vel;
}

void GSEObject::SetVel(GSEVec3 in)
{
	m_vel = in;
}

GSEVec3 GSEObject::GetAcc()
{
	return m_acc;
}

void GSEObject::SetAcc(GSEVec3 in)
{
	m_acc = in;
}

GSEVec4 GSEObject::GetColor()
{
	return m_color;
}

void GSEObject::SetColor(GSEVec4 in)
{
	m_color = in;
}

float GSEObject::GetMass()
{
	return m_mass;
}

void GSEObject::SetMass(float in)
{
	m_mass = in;
}

float GSEObject::GetFricCoef()
{
	return m_fricCoef;
}

void GSEObject::SetFricCoef(float in)
{
	m_fricCoef = in;
}

int GSEObject::GetType()
{
	return m_type;
}

void GSEObject::SetType(float in)
{
	m_type = in;
}

float GSEObject::GetCoolTime()
{
	return m_coolTime;
}

void GSEObject::SetCoolTime(float in)
{
	m_coolTime = in;
}

void GSEObject::SetParent(GSEObject* in)
{
	m_parent = in;
}

bool GSEObject::IsAncester(GSEObject* in)
{
	if (in == m_parent)
	{
		return true;
	}
	return false;
}

int GSEObject::GetHP()
{
	return m_HP;
}

void GSEObject::SetHP(float in)
{
	m_HP = in;
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

bool GSEObject::CanFire()
{
	if (m_coolTime_remaining < FLT_EPSILON)
	{
		return true;
	}
	return false;
}

void GSEObject::ResetCoolTime()
{
	m_coolTime_remaining = m_coolTime;
}
