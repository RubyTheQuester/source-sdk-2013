//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================

#include "cbase.h"
#include "tf_weapon_fireaxe.h"
#include "tf_gamerules.h"

// Client specific.
#ifdef CLIENT_DLL
#include "c_tf_player.h"
#include "c_tf_gamestats.h"
// Server specific.
#else
#include "tf_player.h"
#include "tf_gamestats.h"
#include "entity_healthkit.h"
#endif

#ifdef GAME_DLL
#include "tf_gamestats.h"
#include "ilagcompensationmanager.h"
#endif

//=============================================================================
//
// Weapon FireAxe tables.
//
//=============================================================================
IMPLEMENT_NETWORKCLASS_ALIASED( TFFireAxe, DT_TFWeaponFireAxe )

BEGIN_NETWORK_TABLE( CTFFireAxe, DT_TFWeaponFireAxe )
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA( CTFFireAxe )
END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS( tf_weapon_fireaxe, CTFFireAxe );
PRECACHE_WEAPON_REGISTER( tf_weapon_fireaxe );
//=============================================================================
IMPLEMENT_NETWORKCLASS_ALIASED( TFCrowbar, DT_TFWeaponCrowbar )

BEGIN_NETWORK_TABLE( CTFCrowbar, DT_TFWeaponCrowbar )
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA( CTFCrowbar )
END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS( tf_weapon_crowbar, CTFCrowbar);
PRECACHE_WEAPON_REGISTER( tf_weapon_crowbar );
//=============================================================================
IMPLEMENT_NETWORKCLASS_ALIASED( TFMedkit, DT_TFWeaponMedkit)

BEGIN_NETWORK_TABLE( CTFMedkit, DT_TFWeaponMedkit )
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA( CTFMedkit)
END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS( tf_weapon_medkit, CTFMedkit);
PRECACHE_WEAPON_REGISTER(tf_weapon_medkit);

#ifdef GAME_DLL
//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
float CTFFireAxe::GetInitialAfterburnDuration() const 
{ 
	int iAddBurningDamageType = 0;
	CALL_ATTRIB_HOOK_INT( iAddBurningDamageType, set_dmgtype_ignite );
	if ( iAddBurningDamageType )
	{
		return 7.5f;
	}

	return BaseClass::GetInitialAfterburnDuration();
}
#endif

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
CTFMedkit::CTFMedkit()
{
}

//-----------------------------------------------------------------------------
// Purpose: Set stealth attack bool
//-----------------------------------------------------------------------------
void CTFMedkit::PrimaryAttack( void )
{
	CTFPlayer* pPlayer = ToTFPlayer( GetPlayerOwner() );

	if (!CanAttack())
		return;

	// Set the weapon usage mode - primary, secondary.
	m_iWeaponMode = TF_WEAPON_PRIMARY_MODE;

#if !defined (CLIENT_DLL)
	// Move other players back to history positions based on local player's lag
	lagcompensation->StartLagCompensation( pPlayer, pPlayer->GetCurrentCommand() );
#endif

	trace_t trace;
	if ( DoSwingTrace(trace) == true )
	{
		// we will hit something with the attack
		if ( trace.m_pEnt && ( trace.m_pEnt->IsPlayer() ) )
		{
			CBaseCombatCharacter* pTarget = trace.m_pEnt->MyCombatCharacterPointer();

			if ( pTarget )
			{
				m_iWeaponMode = TF_WEAPON_SECONDARY_MODE;

				Swing( pPlayer );

				// store the victim to compare when we do the damage
				m_hVictim = trace.m_pEnt;
			}
		}
		else if ( !trace.m_pEnt )
		{
			SwingMiss( pPlayer );
		}
	}

#if !defined (CLIENT_DLL)
	lagcompensation->FinishLagCompensation( pPlayer );
#endif

#if !defined( CLIENT_DLL ) 
	pPlayer->SpeakWeaponFire();
	//CTF_GameStats.Event_PlayerFiredWeapon( pPlayer, IsCurrentAttackACritical() );
#endif
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *pPlayer - 
//-----------------------------------------------------------------------------
void CTFMedkit::SwingMiss( CTFPlayer* pPlayer )
{
	// Play the melee swing and miss (whoosh) always.
	pPlayer->DoAnimationEvent( PLAYERANIMEVENT_ATTACK_PRIMARY );

	// Set next attack times.
	m_flNextPrimaryAttack = gpGlobals->curtime + GetFireRate();

	WeaponSound( MELEE_HIT_WORLD );
}

#define LUNCHBOX_DROPPED_MINS	Vector( -17, -17, -10 )
#define LUNCHBOX_DROPPED_MAXS	Vector( 17, 17, 10 )


//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CTFMedkit::SecondaryAttack(void)
{
	CTFPlayer* pPlayer = ToTFPlayer(GetPlayerOwner());
	if (!pPlayer)
		return;

	if (!HasAmmo())
		return;

#ifndef CLIENT_DLL

	if (m_hThrownPowerup)
	{
		UTIL_Remove(m_hThrownPowerup);
	}

	// Throw out the medikit
	Vector vecSrc = pPlayer->EyePosition() + Vector( 0, 0, -8 );
	QAngle angForward = pPlayer->EyeAngles() + QAngle( -10, 0, 0 );

	CHealthKit* pMedKit = assert_cast<CHealthKit*>( CBaseEntity::Create( "item_healthkit_medium", vecSrc, angForward, pPlayer ) );

	if (pMedKit)
	{
		Vector vecForward, vecRight, vecUp;
		AngleVectors(angForward, &vecForward, &vecRight, &vecUp);
		Vector vecVelocity = vecForward * 500.0;

		pMedKit->SetModel( "models/items/plate.mdl" );

		pMedKit->SetAbsAngles( vec3_angle );
		pMedKit->SetSize( LUNCHBOX_DROPPED_MINS, LUNCHBOX_DROPPED_MAXS );

		// the thrower has to wait 0.3 to pickup the powerup (so he can throw it while running forward)
		pMedKit->DropSingleInstance( vecVelocity, pPlayer, 0.3 );
	}

	m_hThrownPowerup = pMedKit;
#endif

	pPlayer->RemoveAmmo( m_pWeaponInfo->GetWeaponData(m_iWeaponMode).m_iAmmoPerShot, m_iPrimaryAmmoType );
	//g_pGameRules->SwitchToNextBestWeapon( pPlayer, this );

	//pPlayer->m_Shared.SetItemChargeMeter( LOADOUT_POSITION_MELEE, 0.f );
	StartEffectBarRegen();
}

// Purpose:
//-----------------------------------------------------------------------------
bool CTFMedkit::UsesPrimaryAmmo(void)
{
	return CBaseCombatWeapon::UsesPrimaryAmmo();
}