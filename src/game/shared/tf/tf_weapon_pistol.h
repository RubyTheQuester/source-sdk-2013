//========= Copyright Valve Corporation, All rights reserved. ============//
//
//
//=============================================================================
#ifndef TF_WEAPON_PISTOL_H
#define TF_WEAPON_PISTOL_H
#ifdef _WIN32
#pragma once
#endif

#include "tf_weaponbase_gun.h"

#include "tf_weapon_shotgun.h"

// Client specific.
#ifdef CLIENT_DLL
#define CTFPistol C_TFPistol
#define CTFPistol_Scout C_TFPistol_Scout
#define CTFPistol_ScoutPrimary C_TFPistol_ScoutPrimary
#define CTFPistol_ScoutSecondary C_TFPistol_ScoutSecondary
#define CTFChargedPistol C_TFChargedPistol
#define CTFPistol_Merc C_TFPistol_Merc
#endif

// We allow the pistol to fire as fast as the player can click.
// This is the minimum time between shots.
#define	PISTOL_FASTEST_REFIRE_TIME		0.1f

// The faster the player fires, the more inaccurate he becomes
#define	PISTOL_ACCURACY_SHOT_PENALTY_TIME		0.2f	// Applied amount of time each shot adds to the time we must recover from
#define	PISTOL_ACCURACY_MAXIMUM_PENALTY_TIME	1.5f	// Maximum time penalty we'll allow

//=============================================================================
//
// TF Weapon Pistol.
//
class CTFPistol : public CTFWeaponBaseGun
{
public:

	DECLARE_CLASS( CTFPistol, CTFWeaponBaseGun );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();

// Server specific.
#ifdef GAME_DLL
	DECLARE_DATADESC();
#endif

	CTFPistol() {}
	~CTFPistol() {}

	virtual int		GetWeaponID( void ) const			{ return TF_WEAPON_PISTOL; }

private:
	CTFPistol( const CTFPistol & ) {}
};

// Scout specific version
class CTFPistol_Scout : public CTFPistol
{
public:
	DECLARE_CLASS( CTFPistol_Scout, CTFPistol );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();

	virtual int		GetWeaponID( void ) const			{ return TF_WEAPON_PISTOL_SCOUT; }
};

// Scout specific version
class CTFPistol_Merc: public CTFPistol
{
public:
	DECLARE_CLASS(CTFPistol_Merc, CTFPistol);
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();

	virtual int		GetWeaponID(void) const { return TF_WEAPON_PISTOL_MERCENARY; }
};

//Shortstop
class CTFPistol_ScoutPrimary : public CTFPistol_Scout
{
public:
	DECLARE_CLASS( CTFPistol_ScoutPrimary, CTFPistol_Scout );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();
	
	CTFPistol_ScoutPrimary();

	virtual int		GetViewModelWeaponRole() { return TF_WPN_TYPE_SECONDARY; }
	virtual int		GetWeaponID( void ) const	{ return TF_WEAPON_HANDGUN_SCOUT_PRIMARY; }
	virtual void	PlayWeaponShootSound( void );
	virtual void	SecondaryAttack( void );
	bool			CanUsePush();
	virtual void	ItemPostFrame();
	virtual bool	Holster( CBaseCombatWeapon *pSwitchingTo );
	virtual void	Precache( void );

	void			Push( void );

#ifdef CLIENT_DLL
	virtual bool	ShouldPlayClientReloadSound() { return true; }
#endif

private:
	float			m_flPushTime;
};

class CTFPistol_ScoutSecondary : public CTFPistol_Scout
{
public:
	DECLARE_CLASS( CTFPistol_ScoutSecondary, CTFPistol_Scout );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();

	virtual int		GetViewModelWeaponRole() { return TF_WPN_TYPE_SECONDARY; }
	virtual int		GetWeaponID( void ) const			{ return TF_WEAPON_HANDGUN_SCOUT_SECONDARY; }

	virtual int		GetDamageType( void ) const;
};

//=============================================================================
//
// TF Weapon Capper.
//
//=============================================================================
class CTFChargedPistol : public CTFPistol
{
public:
	DECLARE_CLASS( CTFChargedPistol, CTFPistol );
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();

#ifndef CAPPER_1
	// Server specific.
#ifdef GAME_DLL
	DECLARE_DATADESC();
#endif

#endif

	CTFChargedPistol() {}
	~CTFChargedPistol() {}

	virtual int		GetWeaponID(void) const { return TF_WEAPON_PISTOL_CHARGE; }

	const char*		GetEffectLabelText(void) { return "#TF_Capper"; }
	float			GetProgress(void);
	virtual bool	IsEnergyWeapon(void) const { return true; }

#ifndef CAPPER_1
	bool			ShouldFlashChargeBar();
	void			SecondaryAttack() OVERRIDE;
	bool			CanPerformSecondaryAttack() const OVERRIDE;
	void			WeaponReset() OVERRIDE;
#else
	virtual void		PrimaryAttack(void);
	virtual void		ModifyProjectile(CBaseEntity* pProj);

	virtual float		Energy_GetShotCost(void) const
	{
		int iNoDrain = 0;
		CALL_ATTRIB_HOOK_INT(iNoDrain, energy_weapon_no_drain);
		if (iNoDrain > 0)
		{
			return 0.0f;
		}

		return 1.f;
	}
	virtual float		Energy_GetRechargeCost(void) const { return 20.f; }
#endif

#ifndef CAPPER_1

#ifdef GAME_DLL
	void	ApplyOnHitAttributes( CBaseEntity* pVictimBaseEntity, CTFPlayer* pAttacker, const CTakeDamageInfo& info ) OVERRIDE;
#endif

protected:
	CNetworkVar( float, m_flMinicritCharge );

	float m_flMinicritStartTime;

#endif

private:
	CTFChargedPistol( const CTFChargedPistol& ) {}
};

#endif // TF_WEAPON_PISTOL_H
