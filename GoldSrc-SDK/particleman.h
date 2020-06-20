/*
*
*    Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*    This product contains software technology licensed from Id
*    Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*    All Rights Reserved.
*
*    Use, distribution, and modification of this source code and/or resulting
*    object code is restricted to non-commercial enhancements to products from
*    Valve LLC.  All other use, distribution, or modification is prohibited
*    without written permission from Valve LLC.
*
*/

#pragma once

#include "tier1/interface.h"
#include "pman_triangleffect.h"

#define PARTICLEMAN_INTERFACE "create_particleman"

#if defined(_WIN32)
	constexpr auto PARTICLEMAN_LIB = "cl_dlls\\particleman.dll";
#elif defined(LINUX)
	constexpr auto PARTICLEMAN_LIB = "cl_dlls/particleman.so";
#elif defined(OSX)
	constexpr auto PARTICLEMAN_LIB = "cl_dlls/particleman.dylib";
#else
	#error "Unsupported Platform."
#endif // #if defined(_WIN32) || defined(LINUX) || defined(OSX)

class CBaseParticle;

class IParticleMan: public IBaseInterface
{
protected:
	virtual ~IParticleMan() {}

public:
	virtual void SetUp(cl_enginefunc_t *pEnginefuncs) = 0;
	virtual void Update() = 0;
	virtual void SetVariables(float flGravity, Vector vViewAngles) = 0;
	virtual void ResetParticles() = 0;
	virtual void ApplyForce(Vector vOrigin, Vector vDirection, float flRadius, float flStrength, float flDuration) = 0;
	virtual void AddCustomParticleClassSize(unsigned long lSize) = 0;

	// Use this if you want to create a new particle without any overloaded functions, Think, Touch, etc.
	// Just call this function, set the particle's behavior and let it rip.
	virtual CBaseParticle *CreateParticle(Vector org, Vector normal, struct model_s *sprite, float size, float brightness, const char *classname ) = 0;

	// Use this to take a block from the mempool for custom particles (used in new).
	virtual char *RequestNewMemBlock(int iSize) = 0;

	// These ones are used along a custom Create for new particles you want to override their behavior.
	// You can call these whenever you want, but they are mainly used by CBaseParticle.
	virtual void CoreInitializeSprite(CCoreTriangleEffect *pParticle, Vector org, Vector normal, struct model_s *sprite, float size, float brightness) = 0; // Only use this for TrianglePlanes
	virtual void CoreThink(CCoreTriangleEffect *pParticle, float time) = 0;
	virtual void CoreDraw(CCoreTriangleEffect *pParticle) = 0;
	virtual void CoreAnimate(CCoreTriangleEffect *pParticle, float time) = 0;
	virtual void CoreAnimateAndDie(CCoreTriangleEffect *pParticle, float time) = 0;
	virtual void CoreExpand(CCoreTriangleEffect *pParticle, float time) = 0;
	virtual void CoreContract(CCoreTriangleEffect *pParticle, float time) = 0;
	virtual void CoreFade(CCoreTriangleEffect *pParticle, float time) = 0;
	virtual void CoreSpin(CCoreTriangleEffect *pParticle, float time) = 0;
	virtual void CoreCalculateVelocity(CCoreTriangleEffect *pParticle, float time) = 0;
	virtual void CoreCheckCollision(CCoreTriangleEffect *pParticle, float time) = 0;
	virtual void CoreTouch(CCoreTriangleEffect *pParticle, Vector pos, Vector normal, int index) = 0;
	virtual void CoreDie(CCoreTriangleEffect *pParticle) = 0;
	virtual void CoreForce(CCoreTriangleEffect *pParticle) = 0;
	virtual bool CoreCheckVisibility(CCoreTriangleEffect *pParticle) = 0;
	virtual void SetRender(int iRender) = 0;
};

extern IParticleMan *g_pParticleMan;

class CBaseParticle: public CCoreTriangleEffect
{
public:
	virtual void Think(float time) { g_pParticleMan->CoreThink(this, time); }
	virtual void Draw() { g_pParticleMan->CoreDraw(this); }
	virtual void Animate(float time) { g_pParticleMan->CoreAnimate(this, time); }
	virtual void AnimateAndDie(float time) { g_pParticleMan->CoreAnimateAndDie(this, time); }
	virtual void Expand(float time) { g_pParticleMan->CoreExpand(this, time); }
	virtual void Contract(float time) { g_pParticleMan->CoreContract(this, time); }
	virtual void Fade(float time) { g_pParticleMan->CoreFade(this, time); }
	virtual void Spin(float time) { g_pParticleMan->CoreSpin(this, time); }
	virtual void CalculateVelocity(float time) { g_pParticleMan->CoreCalculateVelocity(this, time); }
	virtual void CheckCollision(float time) { g_pParticleMan->CoreCheckCollision(this, time); }
	virtual void Touch(Vector pos, Vector normal, int index) { g_pParticleMan->CoreTouch(this, pos, normal, index); }
	virtual void Die() { g_pParticleMan->CoreDie(this); }
	virtual void Force() { g_pParticleMan->CoreForce(this); }
	virtual bool CheckVisibility() { return g_pParticleMan->CoreCheckVisibility(this); }

	virtual void InitializeSprite(Vector org, Vector normal, struct model_s *sprite, float size, float brightness)
	{
		g_pParticleMan->CoreInitializeSprite(this, org, normal, sprite, size, brightness);
	}

	// allow particleman to allocate instance data
	void *operator new(size_t size) // this asks for a new block of memory from the MiniMem class
	{
		return g_pParticleMan->RequestNewMemBlock(size);
	}

#ifdef POSIX
	void *operator new(size_t size, const std::nothrow_t&) throw() // this asks for a new block of memory from the MiniMem class
	{
		return g_pParticleMan->RequestNewMemBlock(size);
	}
#endif
};
