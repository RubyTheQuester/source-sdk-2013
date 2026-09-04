//========= Copyright Valve Corporation, All rights reserved. ============//
//
//
//=============================================================================
#include "cbase.h"
#include "tf_weapon_smg.h"

static const float DAMAGE_TO_FILL_MINICRIT_METER = 100.0f;

// Client specific.
#ifdef CLIENT_DLL
#include "c_tf_player.h"
// Server specific.
#else
#include "tf_player.h"
#endif
//=============================================================================
//
// Weapon tables.
//

// ---------- Regular SMG -------------

CREATE_SIMPLE_WEAPON_TABLE( TFSMG, tf_weapon_smg )

// Server specific.
#ifndef CLIENT_DLL
BEGIN_DATADESC( CTFSMG )
END_DATADESC()
#endif

// ---------- Charged SMG -------------

IMPLEMENT_NETWORKCLASS_ALIASED( TFChargedSMG, DT_WeaponChargedSMG )

BEGIN_NETWORK_TABLE( CTFChargedSMG, DT_WeaponChargedSMG )
// Client specific.
#ifdef CLIENT_DLL
RecvPropFloat( RECVINFO( m_flMinicritCharge ) ),
// Server specific.
#else
SendPropFloat( SENDINFO( m_flMinicritCharge ), 4, SPROP_NOSCALE, 0.0f, DAMAGE_TO_FILL_MINICRIT_METER ),
#endif
END_NETWORK_TABLE()

// Server specific
#ifndef CLIENT_DLL
BEGIN_DATADESC( CTFChargedSMG )
END_DATADESC()
#endif

// Client specific
#ifdef CLIENT_DLL
BEGIN_PREDICTION_DATA( CTFChargedSMG )
DEFINE_FIELD(  m_flMinicritCharge, FIELD_FLOAT )
END_PREDICTION_DATA()
#endif

LINK_ENTITY_TO_CLASS( tf_weapon_charged_smg, CTFChargedSMG );
PRECACHE_WEAPON_REGISTER( tf_weapon_charged_smg );

// ---------- Medic SMG -------------

CREATE_SIMPLE_WEAPON_TABLE( TFSMG_MEDIC, tf_weapon_smg_medic )

// Server specific.
#ifndef CLIENT_DLL
BEGIN_DATADESC( CTFSMG_MEDIC )
END_DATADESC()
#endif

// ---------- Assault Rifle -------------

CREATE_SIMPLE_WEAPON_TABLE(TFRifle, tf_weapon_assault_rifle)

// Server specific.
#ifndef CLIENT_DLL
BEGIN_DATADESC(CTFRifle)
END_DATADESC()
#endif


acttable_t CTFRifle::m_acttableRifle[] =
{
	{ ACT_MP_STAND_IDLE, ACT_MERC_STAND_ASSAULT_RIFLE, false },
	{ ACT_MP_CROUCH_IDLE, ACT_MERC_CROUCH_ASSAULT_RIFLE, false },
	{ ACT_MP_RUN, ACT_MERC_RUN_ASSAULT_RIFLE, false },
	{ ACT_MP_WALK, ACT_MERC_WALK_ASSAULT_RIFLE, false },
	{ ACT_MP_AIRWALK, ACT_MERC_AIRWALK_ASSAULT_RIFLE, false },
	{ ACT_MP_CROUCHWALK, ACT_MERC_CROUCHWALK_ASSAULT_RIFLE, false },
	{ ACT_MP_SWIM, ACT_MERC_SWIM_ASSAULT_RIFLE, false },

	{ ACT_MP_JUMP, ACT_MERC_JUMP_ASSAULT_RIFLE, false },
	{ ACT_MP_JUMP_START, ACT_MERC_JUMP_START_ASSAULT_RIFLE, false },
	{ ACT_MP_JUMP_FLOAT, ACT_MERC_JUMP_FLOAT_ASSAULT_RIFLE, false },
	{ ACT_MP_JUMP_LAND, ACT_MERC_JUMP_LAND_ASSAULT_RIFLE, false },

	{ ACT_MP_ATTACK_STAND_PRIMARYFIRE, ACT_MERC_ATTACK_STAND_ASSAULT_RIFLE, false },
	{ ACT_MP_ATTACK_CROUCH_PRIMARYFIRE, ACT_MERC_ATTACK_CROUCH_ASSAULT_RIFLE, false },
	{ ACT_MP_ATTACK_SWIM_PRIMARYFIRE, ACT_MERC_ATTACK_SWIM_ASSAULT_RIFLE, false },

	{ ACT_MP_RELOAD_STAND, ACT_MERC_RELOAD_STAND_ASSAULT_RIFLE, false },
	{ ACT_MP_RELOAD_CROUCH, ACT_MERC_RELOAD_CROUCH_ASSAULT_RIFLE, false },
	{ ACT_MP_RELOAD_SWIM, ACT_MERC_RELOAD_SWIM_ASSAULT_RIFLE, false },
	{ ACT_MP_RELOAD_AIRWALK, ACT_MERC_RELOAD_AIRWALK_ASSAULT_RIFLE, false },
};


acttable_t* CTFRifle::ActivityList(int& iActivityCount)
{
	if (GetTFPlayerOwner()->GetPlayerClass()->GetClassIndex() == TF_CLASS_MERCENARY)
	{
		iActivityCount = ARRAYSIZE(m_acttableRifle);
		return m_acttableRifle;
	}
	else
	{
		return BaseClass::ActivityList(iActivityCount);
	}
}

acttable_t CTFSMG_MEDIC::m_acttableSMGMerc[] =
{
	{ ACT_MP_STAND_IDLE, ACT_MERC_STAND_SMG_MERCENARY, false },
	{ ACT_MP_CROUCH_IDLE, ACT_MERC_CROUCH_SMG_MERCENARY, false },
	{ ACT_MP_RUN, ACT_MERC_RUN_SMG_MERCENARY, false },
	{ ACT_MP_WALK, ACT_MERC_WALK_SMG_MERCENARY, false },
	{ ACT_MP_AIRWALK, ACT_MERC_AIRWALK_SMG_MERCENARY, false },
	{ ACT_MP_CROUCHWALK, ACT_MERC_CROUCHWALK_SMG_MERCENARY, false },
	{ ACT_MP_SWIM, ACT_MERC_SWIM_SMG_MERCENARY, false },

	{ ACT_MP_JUMP, ACT_MERC_JUMP_SMG_MERCENARY, false },
	{ ACT_MP_JUMP_START, ACT_MERC_JUMP_START_SMG_MERCENARY, false },
	{ ACT_MP_JUMP_FLOAT, ACT_MERC_JUMP_FLOAT_SMG_MERCENARY, false },
	{ ACT_MP_JUMP_LAND, ACT_MERC_JUMP_LAND_SMG_MERCENARY, false },

	{ ACT_MP_ATTACK_STAND_PRIMARYFIRE, ACT_MERC_ATTACK_STAND_SMG_MERCENARY, false },
	{ ACT_MP_ATTACK_CROUCH_PRIMARYFIRE, ACT_MERC_ATTACK_CROUCH_SMG_MERCENARY, false },
	{ ACT_MP_ATTACK_SWIM_PRIMARYFIRE, ACT_MERC_ATTACK_SWIM_SMG_MERCENARY, false },

	{ ACT_MP_RELOAD_STAND, ACT_MERC_RELOAD_STAND_SMG_MERCENARY, false },
	{ ACT_MP_RELOAD_CROUCH, ACT_MERC_RELOAD_CROUCH_SMG_MERCENARY, false },
	{ ACT_MP_RELOAD_SWIM, ACT_MERC_RELOAD_SWIM_SMG_MERCENARY, false },
	{ ACT_MP_RELOAD_AIRWALK, ACT_MERC_RELOAD_AIRWALK_SMG_MERCENARY, false },
};


acttable_t* CTFSMG_MEDIC::ActivityList(int& iActivityCount)
{
	if (GetTFPlayerOwner()->GetPlayerClass()->GetClassIndex() == TF_CLASS_MERCENARY)
	{
		iActivityCount = ARRAYSIZE(m_acttableSMGMerc);;

		return m_acttableSMGMerc;
	}
	else
	{
		return BaseClass::ActivityList(iActivityCount);
	}
}
//=============================================================================
//
// Weapon SMG functions.

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
int	CTFSMG::GetDamageType( void ) const
{
	if ( CanHeadshot() )
	{
		int iDamageType = BaseClass::GetDamageType() | DMG_USE_HITLOCATIONS;
		return iDamageType;
	}

	return BaseClass::GetDamageType();
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
bool CTFSMG::CanFireCriticalShot( bool bIsHeadshot, CBaseEntity *pTarget /*= NULL*/ )
{
	if ( !BaseClass::CanFireCriticalShot( bIsHeadshot, pTarget ) )
		return false;

	CTFPlayer *pPlayer = GetTFPlayerOwner();
	if ( pPlayer && pPlayer->m_Shared.IsCritBoosted() )
		return true;

	if ( !bIsHeadshot )
		return !CanHeadshot();

	return true;
}

//-----------------------------------------------------------------------------
// Purpose:	Determine if secondary fire is available.
//-----------------------------------------------------------------------------
bool CTFChargedSMG::CanPerformSecondaryAttack() const
{
	return ( m_flMinicritCharge >= DAMAGE_TO_FILL_MINICRIT_METER && BaseClass::CanPerformSecondaryAttack() );
}

//-----------------------------------------------------------------------------
// Purpose: Determine whether to flash the HUD element showing the charge bar
//-----------------------------------------------------------------------------
bool CTFChargedSMG::ShouldFlashChargeBar()
{
	return m_flMinicritCharge >= DAMAGE_TO_FILL_MINICRIT_METER;
}

//-----------------------------------------------------------------------------
// Purpose: Get HUD charge bar progress amount
//-----------------------------------------------------------------------------
float CTFChargedSMG::GetProgress( void )
{
	// Progress bar shows charge amount if we're charging up, otherwise drains over time if we're mini-crit boosted.
	CTFPlayer *pPlayer = ToTFPlayer( GetOwner() );
	if ( pPlayer && pPlayer->m_Shared.InCond( TF_COND_ENERGY_BUFF ) )
	{
		int flBuffDuration = 0;
		CALL_ATTRIB_HOOK_FLOAT( flBuffDuration, minicrit_boost_when_charged );
		if ( flBuffDuration > 0 )
		{
			float flElapsed = gpGlobals->curtime - m_flMinicritStartTime;
			float flRemainingPortion = Clamp( (flBuffDuration - flElapsed) / flBuffDuration, 0.0f, 1.0f );
			return flRemainingPortion;
		}
		else
		{
			return 0.0f;
		}
	}
	else
	{
		return m_flMinicritCharge / DAMAGE_TO_FILL_MINICRIT_METER;
	}
}

//-----------------------------------------------------------------------------
// Purpose: Reset weapon state
//-----------------------------------------------------------------------------
void CTFChargedSMG::WeaponReset()
{
	BaseClass::WeaponReset();
	m_flMinicritCharge = 0.0f;
	m_flMinicritStartTime = 0.0f;
}

//-----------------------------------------------------------------------------
// Purpose: Perform secondary attack
//-----------------------------------------------------------------------------
void CTFChargedSMG::SecondaryAttack()
{
	BaseClass::SecondaryAttack();

	m_flMinicritCharge = 0.0f;

	CTFPlayer *pPlayer = ToTFPlayer( GetOwner() );
	if ( pPlayer )
	{
		float flBuffDuration = 0;
		CALL_ATTRIB_HOOK_FLOAT( flBuffDuration, minicrit_boost_when_charged );
		if ( flBuffDuration > 0 )
		{
			pPlayer->m_Shared.AddCond( TF_COND_ENERGY_BUFF, flBuffDuration );
			m_flMinicritStartTime = gpGlobals->curtime;
		}
	}
}

#ifdef GAME_DLL
//-----------------------------------------------------------------------------
// Purpose: Update state when we score a hit with this weapon
//-----------------------------------------------------------------------------
void CTFChargedSMG::ApplyOnHitAttributes( CBaseEntity *pVictimBaseEntity, CTFPlayer *pAttacker, const CTakeDamageInfo &info )
{
	BaseClass::ApplyOnHitAttributes( pVictimBaseEntity, pAttacker, info );
	if ( pAttacker )
	{
		CTFPlayer *pPlayer = ToTFPlayer( GetOwner() );
		if ( pPlayer && !pPlayer->m_Shared.InCond( TF_COND_ENERGY_BUFF ) )
		{
			float damage = info.GetDamage();
			float flChargeRate = 0.0f;
			CALL_ATTRIB_HOOK_FLOAT( flChargeRate, minicrit_boost_charge_rate );
			m_flMinicritCharge += damage * flChargeRate;
			if ( m_flMinicritCharge > DAMAGE_TO_FILL_MINICRIT_METER )
			{
				m_flMinicritCharge = DAMAGE_TO_FILL_MINICRIT_METER;
			}
		}
	}
}
#endif
