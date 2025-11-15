//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================

#ifndef TF_WEAPON_FIREAXE_H
#define TF_WEAPON_FIREAXE_H
#ifdef _WIN32
#pragma once
#endif

#include "tf_weaponbase_melee.h"

#ifdef CLIENT_DLL
#define CTFFireAxe C_TFFireAxe
#define CTFCrowbar C_TFCrowbar
#define CTFMedkit C_TFMedkit
#endif

//=============================================================================
//
// BrandingIron class.
//
//=============================================================================
class CTFFireAxe : public CTFWeaponBaseMelee
{
public:

	DECLARE_CLASS( CTFFireAxe, CTFWeaponBaseMelee );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();

	CTFFireAxe() {}
	virtual int			GetWeaponID( void ) const			{ return TF_WEAPON_FIREAXE; }

#ifdef GAME_DLL
	virtual float GetInitialAfterburnDuration() const OVERRIDE;
#endif

private:

	CTFFireAxe( const CTFFireAxe & ) {}
};

//=============================================================================
//
// Crowbar class.
//
//=============================================================================
class CTFCrowbar : public CTFWeaponBaseMelee
{
public:

	DECLARE_CLASS( CTFCrowbar, CTFWeaponBaseMelee );
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();

	CTFCrowbar() {}
	virtual int			GetWeaponID(void) const { return TF_WEAPON_CROWBAR; }

private:

	CTFCrowbar(const CTFCrowbar&) {}
};

//=============================================================================
//
// Medkit class.
//
//=============================================================================
class CTFMedkit : public CTFWeaponBaseMelee
{
public:

	DECLARE_CLASS(CTFMedkit, CTFWeaponBaseMelee);
	DECLARE_NETWORKCLASS();
	DECLARE_PREDICTABLE();

	CTFMedkit();
	virtual int			GetWeaponID(void) const { return TF_WEAPON_MEDKIT; }

	virtual void		PrimaryAttack(void);
	void				SwingMiss( CTFPlayer* pPlayer );

	virtual void		SecondaryAttack( void );
	virtual bool		UsesPrimaryAmmo() OVERRIDE;

	const char*			GetEffectLabelText(void) { return "#TF_ENERGYDRINK"; }
	float				GetProgress(void) { return GetEffectBarProgress(); }
	virtual float		InternalGetEffectBarRechargeTime(void) { return 30.0f; }

	// Prevent spamming with resupply cabinets: only 1 thrown at a time
	EHANDLE		m_hThrownPowerup;
private:
	EHANDLE				m_hVictim;

	CTFMedkit(const CTFMedkit&) {}
};
#endif // TF_WEAPON_FIREAXE_H
