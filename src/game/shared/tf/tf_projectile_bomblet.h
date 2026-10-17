//====== Copyright © 1996-2005, Valve Corporation, All rights reserved. ========//
//
// Purpose: TFMOD Bomb functions
//
//=============================================================================//
#ifndef TF_PROJECTILE_BOMBLET_H
#define TF_PROJECTILE_BOMBLET_H
#ifdef _WIN32
#pragma once
#endif

#include "tf_weapon_grenade_pipebomb.h"

#ifdef CLIENT_DLL
#define CTFGrenadeMirvBomb C_TFGrenadeMirvBomb
#endif

#ifdef GAME_DLL
// Bomblet Data is stored here
struct bomblet_t
{
public:
	bomblet_t()
	{
		m_iAmmount = 0;
	};
public:
	EHANDLE	m_pLauncher;
	EHANDLE	m_pOwner;

	float m_flBombletDamage;
	float m_flBombletTimer;
	float m_flBombletDamageRadius;

	int		m_iAmmount;
	int		m_bCritical;
	bool	m_bExplodeOnImpact;

	bool m_bBombletEffectTeamColored;
	char m_szKillIcon[128];
	char m_szBombletTrailParticle[128];
	char m_szBombletModel[128];
};

extern void SpawnBomblets(bomblet_t* pInfo, trace_t* pTrace, int iTeam);
extern void SetupBombletInfo(bomblet_t* m_pBombletInfo, CTFWeaponBase* pWeapon, int bCritical);
extern void SetupBombletInfo(bomblet_t* m_pBombletInfo, bomblet_t* pBombletInfo);
#endif

class CTFGrenadeMirvBomb : public CTFGrenadePipebombProjectile
{
public:

	DECLARE_CLASS(CTFGrenadeMirvBomb, CTFGrenadePipebombProjectile);
	DECLARE_NETWORKCLASS();

	virtual int			GetWeaponID(void) const { return TF_WEAPON_GRENADE_MIRVBOMB; }

	virtual void	Spawn();
	virtual void	Precache();
#ifdef GAME_DLL
	// Creation.
	static CTFGrenadeMirvBomb* Create(const Vector& position, const QAngle& angles, const Vector& velocity,
		const AngularImpulse& angVelocity, CBaseCombatCharacter* pOwner, bomblet_t* pInfo, int teamnumber);
	virtual void	BounceSound(void);
	virtual bool	ExplodeOnImpact(void);
	KeyValues* pStatValues;
	bool			m_bExplodeOnImpact;
#else

	virtual void			OnDataChanged(DataUpdateType_t type);
	virtual const char* GetTrailParticleName(void);
#endif
#ifdef CLIENT_DLL
	char	m_szBombletTrailParticle[MAX_WEAPON_STRING];
#else
	CNetworkVar(string_t, m_szBombletTrailParticle);
#endif
};

#endif //TF_PROJECTILE_BOMBLET_H