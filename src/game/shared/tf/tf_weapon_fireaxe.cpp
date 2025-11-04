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

	WeaponSound( MELEE_MISS );
}