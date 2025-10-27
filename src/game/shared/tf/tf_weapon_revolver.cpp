//========= Copyright Valve Corporation, All rights reserved. ============//
//
//
//=============================================================================
#include "cbase.h"
#include "tf_weapon_revolver.h"
#include "tf_fx_shared.h"
#include "datamap.h"
#include "tf_weaponbase_gun.h"

// Client specific.
#ifdef CLIENT_DLL
#include "c_tf_player.h"
// Server specific.
#else
#include "tf_player.h"
#endif

//=============================================================================
//
// Weapon Revolver tables.
//
//=============================================================================
IMPLEMENT_NETWORKCLASS_ALIASED( TFRevolver, DT_WeaponRevolver )

BEGIN_NETWORK_TABLE( CTFRevolver, DT_WeaponRevolver )
END_NETWORK_TABLE()

#ifdef CLIENT_DLL
BEGIN_PREDICTION_DATA( CTFRevolver )
DEFINE_PRED_FIELD( m_flLastAccuracyCheck, FIELD_FLOAT, 0 ),
END_PREDICTION_DATA()
#endif

LINK_ENTITY_TO_CLASS( tf_weapon_revolver, CTFRevolver );
PRECACHE_WEAPON_REGISTER( tf_weapon_revolver );

// Server specific.
#ifndef CLIENT_DLL
BEGIN_DATADESC( CTFRevolver )
END_DATADESC()
#endif

//============================
CREATE_SIMPLE_WEAPON_TABLE(TFRevolver_Secondary, tf_weapon_revolver_secondary)

CREATE_SIMPLE_WEAPON_TABLE(TFRevolver_Merc, tf_weapon_revolver_mercenary)
//============================

acttable_t CTFRevolver_Merc::m_acttableRevolver[] =
{
	{ ACT_MP_STAND_IDLE, ACT_MERC_STAND_REVOLVER_MERCENARY, false },
	{ ACT_MP_CROUCH_IDLE, ACT_MERC_CROUCH_REVOLVER_MERCENARY, false },
	{ ACT_MP_RUN, ACT_MERC_RUN_REVOLVER_MERCENARY, false },
	{ ACT_MP_WALK, ACT_MERC_WALK_REVOLVER_MERCENARY, false },
	{ ACT_MP_AIRWALK, ACT_MERC_AIRWALK_REVOLVER_MERCENARY, false },
	{ ACT_MP_CROUCHWALK, ACT_MERC_CROUCHWALK_REVOLVER_MERCENARY, false },
	{ ACT_MP_SWIM, ACT_MERC_SWIM_REVOLVER_MERCENARY, false },

	{ ACT_MP_JUMP, ACT_MERC_JUMP_REVOLVER_MERCENARY, false },
	{ ACT_MP_JUMP_START, ACT_MERC_JUMP_START_REVOLVER_MERCENARY, false },
	{ ACT_MP_JUMP_FLOAT, ACT_MERC_JUMP_FLOAT_REVOLVER_MERCENARY, false },
	{ ACT_MP_JUMP_LAND, ACT_MERC_JUMP_LAND_REVOLVER_MERCENARY, false },

	{ ACT_MP_ATTACK_STAND_PRIMARYFIRE, ACT_MERC_ATTACK_STAND_REVOLVER_MERCENARY, false },
	{ ACT_MP_ATTACK_CROUCH_PRIMARYFIRE, ACT_MERC_ATTACK_CROUCH_REVOLVER_MERCENARY, false },
	{ ACT_MP_ATTACK_SWIM_PRIMARYFIRE, ACT_MERC_ATTACK_SWIM_REVOLVER_MERCENARY, false },

	{ ACT_MP_RELOAD_STAND, ACT_MERC_RELOAD_STAND_REVOLVER_MERCENARY, false },
	{ ACT_MP_RELOAD_CROUCH, ACT_MERC_RELOAD_CROUCH_REVOLVER_MERCENARY, false },
	{ ACT_MP_RELOAD_SWIM, ACT_MERC_RELOAD_SWIM_REVOLVER_MERCENARY, false },
	{ ACT_MP_RELOAD_AIRWALK, ACT_MERC_RELOAD_AIRWALK_REVOLVER_MERCENARY, false },
};


acttable_t* CTFRevolver_Merc::ActivityList(int& iActivityCount)
{
	if (GetTFPlayerOwner()->GetPlayerClass()->GetClassIndex() == TF_CLASS_MERCENARY)
	{
		iActivityCount = ARRAYSIZE(m_acttableRevolver);
		return m_acttableRevolver;
	}
	else
	{
		return BaseClass::ActivityList(iActivityCount);
	}
}

//=============================================================================
//
// Weapon Revolver functions.
//

CTFRevolver::CTFRevolver()
{
	m_flLastAccuracyCheck = 0.f;
	m_flAccuracyCheckTime = 0.f;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
bool CTFRevolver::DefaultReload( int iClipSize1, int iClipSize2, int iActivity )
{
	// The the owning local player.
	CTFPlayer *pPlayer = GetTFPlayerOwner();
	if ( !pPlayer )
		return false;

	if ( pPlayer->IsPlayerClass( TF_CLASS_SPY ) )
	{
		if ( pPlayer->m_Shared.InCond( TF_COND_STEALTHED ) )
		{
			return false;
		}
	}

	if ( pPlayer->m_Shared.IsFeignDeathReady() )
		return false; // Can't reload if our feign death arm is up.

	return BaseClass::DefaultReload( iClipSize1, iClipSize2, iActivity );

}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
int	CTFRevolver::GetDamageType( void ) const
{
	if ( CanHeadshot() && (gpGlobals->curtime - m_flLastAccuracyCheck > 1.f) )
	{
		int iDamageType = BaseClass::GetDamageType() | DMG_USE_HITLOCATIONS;
		return iDamageType;
	}

	return BaseClass::GetDamageType();
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
bool CTFRevolver::CanFireCriticalShot( bool bIsHeadshot, CBaseEntity *pTarget /*= NULL*/ )
{
	if ( !BaseClass::CanFireCriticalShot( bIsHeadshot, pTarget ) )
		return false;

	CTFPlayer *pPlayer = GetTFPlayerOwner();
	if ( pPlayer && pPlayer->m_Shared.IsCritBoosted() )
		return true;

	// Magic.
	if ( pTarget && ( pPlayer->GetAbsOrigin() - pTarget->GetAbsOrigin() ).Length2DSqr() > Square( 1200.f ) )
		return false;

	// can only fire a crit shot if this is a headshot, unless we're critboosted
	if ( !bIsHeadshot )
	{
		// Base revolver still randomly crits. Ambassador doesn't.
		return !CanHeadshot();
	}

	return true;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CTFRevolver::PrimaryAttack( void )
{
	// Check for ammunition.
	if ( m_iClip1 <= 0 && m_iClip1 != -1 )
		return;

	// Are we capable of firing again?
	if ( m_flNextPrimaryAttack > gpGlobals->curtime )
		return;

	// Get the player owning the weapon.
	CTFPlayer *pPlayer = ToTFPlayer( GetPlayerOwner() );
	if ( !pPlayer )
		return;

	if ( !CanAttack() )
		return;

	BaseClass::PrimaryAttack();

	if ( HasLastShotCritical() )
	{
		pPlayer->m_Shared.AddCond( TF_COND_CRITBOOSTED_SELF );
	}
	else
	{
		int iAttr = 0;
		CALL_ATTRIB_HOOK_INT( iAttr, last_shot_crits );
		if ( iAttr )
		{
			pPlayer->m_Shared.RemoveCond( TF_COND_CRITBOOSTED_SELF );
		}
	}

	m_flLastAccuracyCheck = gpGlobals->curtime;

	if ( SapperKillsCollectCrits() )
	{
		// Do this after the attack, so that we know if we are doing custom damage
		CTFPlayer *pOwner = ToTFPlayer( GetPlayerOwner() );
		if ( pOwner )
		{
			int iRevengeCrits = pOwner->m_Shared.GetRevengeCrits();
			if ( iRevengeCrits > 0 )
			{
				pOwner->m_Shared.SetRevengeCrits( iRevengeCrits-1 );
			}
		}
	}
#ifdef GAME_DLL
	// Lower bonus for each attack
	int iExtraDamageOnHitPenalty = 0;
	CALL_ATTRIB_HOOK_INT( iExtraDamageOnHitPenalty, extra_damage_on_hit_penalty );
	if ( iExtraDamageOnHitPenalty )
	{
		int iDecaps = pPlayer->m_Shared.GetDecapitations();
		pPlayer->m_Shared.SetDecapitations( Max( 0, iDecaps - iExtraDamageOnHitPenalty ) );
	}
#endif
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
float CTFRevolver::GetWeaponSpread( void )
{
	float fSpread = BaseClass::GetWeaponSpread();

	if ( CanHeadshot() )
	{
		// We are highly accurate for our first shot.
		float flTimeSinceCheck = gpGlobals->curtime - m_flLastAccuracyCheck;
		fSpread = RemapValClamped( flTimeSinceCheck, 1.0f, 0.5f, 0.f, fSpread );
	}

	//DevMsg( "Spread: base %3.5f mod: %3.5f\n", BaseClass::GetWeaponSpread(), fSpread );

	return fSpread;
}

#ifdef CLIENT_DLL
//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CTFRevolver::GetWeaponCrosshairScale(float& flScale)
{
	C_TFPlayer* pTFPlayer = ToTFPlayer(GetOwner());
	if (!pTFPlayer)
		return;

	BaseClass::GetWeaponCrosshairScale(flScale);

	if (true)//tf_revolver_dynamic_crosshair.GetBool())
	{
		const bool bCanHeadShot = CanHeadshot();
		float flHeadShotCooldown = 1.0f;
		const float flAccuracyCooldown = bCanHeadShot ? flHeadShotCooldown : 1.25f;
		float curtime = pTFPlayer->GetFinalPredictedTime() + (gpGlobals->interpolation_amount * TICK_INTERVAL);
		float flTimeSinceCheck = curtime - m_flLastAccuracyCheck;
		float flMaxSize = 2.5f;
		// when is it fully accurate?

		if (bCanHeadShot)
		{
			if (flAccuracyCooldown == flHeadShotCooldown)
			{
				// headshot cooldown is the same as our accuracy cooldown.
				flScale = RemapValClamped(flTimeSinceCheck, flHeadShotCooldown, 0.5f, 0.75f, flMaxSize);
			}
			else
			{
				if (flTimeSinceCheck < flAccuracyCooldown)
				{
					// show the accuracy time
					flScale = RemapValClamped(flTimeSinceCheck, 0.5f, flAccuracyCooldown, flMaxSize, 1.0f);
				}
				else
				{
					// headshot time.
					flScale = RemapValClamped(flTimeSinceCheck, flAccuracyCooldown, flHeadShotCooldown, 1.0f, 0.75f);
				}
			}
		}
		else
		{
			flScale = RemapValClamped(flTimeSinceCheck, 0.5f, flAccuracyCooldown, 2.5f, 1.0f);
		}

	}
}
#endif

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
int CTFRevolver::GetCount( void )
{
	CTFPlayer *pOwner = ToTFPlayer( GetPlayerOwner() );
	if ( !pOwner )
		return 0;

	if ( SapperKillsCollectCrits() )
	{
		return pOwner->m_Shared.GetRevengeCrits();
	}

	int iExtraDamageOnHit = 0;
	CALL_ATTRIB_HOOK_INT( iExtraDamageOnHit, extra_damage_on_hit );
	if ( iExtraDamageOnHit )
	{
		return Min( 200, pOwner->m_Shared.GetDecapitations() );
	}

	return 0;
}

//-----------------------------------------------------------------------------
const char* CTFRevolver::GetEffectLabelText( void )
{
	int iExtraDamageOnHit = 0;
	CALL_ATTRIB_HOOK_INT( iExtraDamageOnHit, extra_damage_on_hit );
	if ( iExtraDamageOnHit )
	{
		return "#TF_BONUS";
	}
	return "#TF_CRITS";
}
//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
int CTFRevolver::GetActivityWeaponRole() const
{
	CTFPlayer* pPlayer = GetTFPlayerOwner();
	if (pPlayer && pPlayer->GetPlayerClass()->GetClassIndex() == TF_CLASS_ENGINEER)
	{
		// demo should use act table item1
		return TF_WPN_TYPE_SECONDARY;
	}

	return BaseClass::GetActivityWeaponRole();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
Activity CTFRevolver::TranslateViewmodelHandActivityInternal(Activity actBase)
{
	CTFPlayer* pPlayer = GetTFPlayerOwner();
	if (!pPlayer)
		return BaseClass::TranslateViewmodelHandActivityInternal(actBase);

	// Alright, so we have some decapitation weapons (katana) that can be used
	// by both the soldier and the demoman, but the classes play totally different
	// animations using the same weapon.
	//
	// This logic is also responsible for playing the correct animations on the
	// demo when he's using non-shared weapons like the Eyelanders.
	if (pPlayer->GetPlayerClass()->GetClassIndex() == TF_CLASS_ENGINEER)
	{
		switch (actBase)
		{
		case ACT_VM_IDLE:
			actBase = ACT_ENGINEER_REVOLVER_IDLE;
			break;
		case ACT_VM_DRAW:
			actBase = ACT_ENGINEER_REVOLVER_DRAW;
			break;
		case ACT_VM_PRIMARYATTACK:
			actBase = ACT_ENGINEER_REVOLVER_PRIMARYATTACK;
			break;
		case ACT_VM_RELOAD:
			actBase = ACT_ENGINEER_REVOLVER_RELOAD;
			break;
		case ACT_PRIMARY_VM_INSPECT_START:
			actBase = ACT_SECONDARY_VM_INSPECT_START;
			break;
		case ACT_PRIMARY_VM_INSPECT_IDLE:
			actBase = ACT_SECONDARY_VM_INSPECT_IDLE;
			break;
		case ACT_PRIMARY_VM_INSPECT_END:
			actBase = ACT_SECONDARY_VM_INSPECT_END;
			break;
		default:
			break;
		}
	}

	return BaseClass::TranslateViewmodelHandActivityInternal(actBase);
}
//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
bool CTFRevolver::Holster( CBaseCombatWeapon *pSwitchingTo )
{
#ifdef GAME_DLL
	CTFPlayer *pOwner = ToTFPlayer( GetPlayerOwner() );
	if ( pOwner )
	{
		if ( SapperKillsCollectCrits() )
		{	
			if ( pOwner->m_Shared.GetRevengeCrits() )
			{
				pOwner->m_Shared.RemoveCond( TF_COND_CRITBOOSTED_SELF );
			}
		}

		if ( HasLastShotCritical() )
		{
			pOwner->m_Shared.RemoveCond( TF_COND_CRITBOOSTED_SELF );
		}
	}
#endif

	return BaseClass::Holster( pSwitchingTo );
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
bool CTFRevolver::Deploy( void )
{
#ifdef GAME_DLL
	CTFPlayer *pOwner = ToTFPlayer( GetPlayerOwner() );
	if ( pOwner )
	{
		if ( SapperKillsCollectCrits() )
		{
			if ( pOwner->m_Shared.GetRevengeCrits() )
			{
				pOwner->m_Shared.AddCond( TF_COND_CRITBOOSTED_SELF );
			}
		}

		if ( HasLastShotCritical() )
		{
			pOwner->m_Shared.AddCond( TF_COND_CRITBOOSTED_SELF );
		}
	}
#endif

	return BaseClass::Deploy();
}

#ifdef GAME_DLL
//-----------------------------------------------------------------------------
// Purpose: Reset revenge crits when the revolver is changed
//-----------------------------------------------------------------------------
void CTFRevolver::Detach( void )
{
	if ( SapperKillsCollectCrits() )
	{
		CTFPlayer *pPlayer = GetTFPlayerOwner();
		if ( pPlayer )
		{
			pPlayer->m_Shared.SetRevengeCrits( 0 );
			pPlayer->m_Shared.RemoveCond( TF_COND_CRITBOOSTED_SELF );
		}
	}

	BaseClass::Detach();
}

//-----------------------------------------------------------------------------
float CTFRevolver::GetProjectileDamage( void )
{
	float flDamageMod = 1.0f;
	int iExtraDamageOnHit = 0;
	CALL_ATTRIB_HOOK_INT( iExtraDamageOnHit, extra_damage_on_hit );
	if ( iExtraDamageOnHit )
	{
		CTFPlayer *pOwner = ToTFPlayer( GetOwner() );
		if ( pOwner )
		{
			flDamageMod = 1.0f + ( Min( 200, pOwner->m_Shared.GetDecapitations() ) * 0.01f );
		}
	}

	return BaseClass::GetProjectileDamage() * flDamageMod;
}
#endif
