
//========= Copyright Valve Corporation, All rights reserved. ============//
//
// TF Rocket
//
//=============================================================================
#include "cbase.h"
#include "tf_weaponbase.h"
#include "tf_projectile_rocket.h"
#include "tf_player.h"

//=============================================================================
//
// TF Rocket functions (Server specific).
//
#define ROCKET_MODEL "models/weapons/w_models/w_rocket.mdl"

LINK_ENTITY_TO_CLASS( tf_projectile_rocket, CTFProjectile_Rocket );
PRECACHE_REGISTER( tf_projectile_rocket );

IMPLEMENT_NETWORKCLASS_ALIASED( TFProjectile_Rocket, DT_TFProjectile_Rocket )

BEGIN_NETWORK_TABLE( CTFProjectile_Rocket, DT_TFProjectile_Rocket )
	SendPropBool( SENDINFO( m_bCritical ) ),
END_NETWORK_TABLE()

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
CTFProjectile_Rocket *CTFProjectile_Rocket::Create( CBaseEntity *pLauncher, const Vector &vecOrigin, const QAngle &vecAngles, CBaseEntity *pOwner, CBaseEntity *pScorer )
{
	CTFProjectile_Rocket *pRocket = static_cast<CTFProjectile_Rocket*>( CTFBaseRocket::Create( pLauncher, "tf_projectile_rocket", vecOrigin, vecAngles, pOwner ) );

	if ( pRocket )
	{
		pRocket->SetScorer( pScorer );
		pRocket->SetEyeBallRocket( false );
		pRocket->SetSpell( false );

		CTFWeaponBase *pWeapon = dynamic_cast< CTFWeaponBase * >( pLauncher );
		bool bDirectHit = pWeapon ? ( pWeapon->GetWeaponID() == TF_WEAPON_ROCKETLAUNCHER_DIRECTHIT ) : false;
		pRocket->SetDirectHit( bDirectHit );
	}

	return pRocket;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CTFProjectile_Rocket::Spawn()
{
	SetModel( ROCKET_MODEL );
	BaseClass::Spawn();
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CTFProjectile_Rocket::Precache()
{
	int iModel = PrecacheModel( ROCKET_MODEL );

	PrecacheGibsForModel( iModel );
	PrecacheParticleSystem( "critical_rocket_blue" );
	PrecacheParticleSystem( "critical_rocket_red" );
	PrecacheParticleSystem( "eyeboss_projectile" );
	PrecacheParticleSystem( "rockettrail" );
	PrecacheParticleSystem( "rockettrail_RocketJumper" );

	PrecacheParticleSystem( "rocket_trail_classic" );	
	PrecacheParticleSystem( "rocket_trail_classic_crit_blue" );
	PrecacheParticleSystem( "rocket_trail_classic_crit_red" );

	iModel = PrecacheModel("models/enhancedrockets2/w_rocket_blackbox.mdl");
	iModel = PrecacheModel("models/enhancedrockets2/w_rocket_directhit.mdl");
	iModel = PrecacheModel("models/enhancedrockets2/w_rocket_original.mdl");
	iModel = PrecacheModel("models/enhancedrockets2/w_rocket_libertylauncher.mdl");
	iModel = PrecacheModel("models/enhancedrockets2/w_rocket_rocketjumper.mdl");
	iModel = PrecacheModel("models/enhancedrockets2/w_rocket_beggarsbazooka.mdl");
	iModel = PrecacheModel("models/weapons/w_models/w_rocket_dm.mdl");

	BaseClass::Precache();
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CTFProjectile_Rocket::SetScorer( CBaseEntity *pScorer )
{
	m_Scorer = pScorer;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
CBasePlayer *CTFProjectile_Rocket::GetScorer( void )
{
	return dynamic_cast<CBasePlayer *>( m_Scorer.Get() );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
int	CTFProjectile_Rocket::GetDamageType() 
{ 
	int iDmgType = BaseClass::GetDamageType();
	if ( m_bCritical )
	{
		iDmgType |= DMG_CRITICAL;
	}

	return iDmgType;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
int	CTFProjectile_Rocket::GetDamageCustom()
{
	if ( m_bDirectHit )
	{
		return TF_DMG_CUSTOM_ROCKET_DIRECTHIT;
	}
	else if ( m_bEyeBallRocket )
	{
		return TF_DMG_CUSTOM_EYEBALL_ROCKET;
	}
	else if ( m_bSpell )
	{
		return TF_DMG_CUSTOM_SPELL_MONOCULUS;
	}
	else
		return BaseClass::GetDamageCustom();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CTFProjectile_Rocket::RocketTouch( CBaseEntity *pOther )
{
	BaseClass::RocketTouch( pOther );
		
	if (m_bCritical && pOther && pOther->IsPlayer())
	{		
		CTFPlayer *pHitPlayer = ToTFPlayer( pOther );
		int iHitPlayerTeamNumber = pHitPlayer->GetTeamNumber();
		int iRocketTeamNumber = BaseClass::GetTeamNumber();

		if (pHitPlayer->IsPlayerClass(TF_CLASS_HEAVYWEAPONS) && !pHitPlayer->m_Shared.InCond( TF_COND_INVULNERABLE)
			&& pHitPlayer->IsAlive() && iHitPlayerTeamNumber != iRocketTeamNumber)
		{
			pHitPlayer->AwardAchievement( ACHIEVEMENT_TF_HEAVY_SURVIVE_CROCKET );
		}
	}
}
//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CTFProjectile_Rocket::ResolveFlyCollisionCustom(trace_t& trace, Vector& vecMove)
{
	// Verify that we have an entity.
	CBaseEntity* pEntity = trace.m_pEnt;
	Assert(pEntity);

	//Assume all surfaces have the same elasticity
	float flSurfaceElasticity = 1.0;

	//Don't bounce off of players with perfect elasticity
	if ( pEntity && pEntity->IsPlayer() )
	{
		if ( GetTeamNumber() != pEntity->GetTeamNumber() )
		{
			const trace_t* pTrace = &CBaseEntity::GetTouchTrace();

			trace_t trace;
			memcpy( &trace, pTrace, sizeof( trace_t ) );
			Explode( &trace, pEntity);
		}
		else
		{
			return;
		}
	}

	float flTotalElasticity = GetElasticity() * flSurfaceElasticity;
	flTotalElasticity = clamp( flTotalElasticity, 0.0f, 0.9f );

	// NOTE: A backoff of 2.0f is a reflection
	Vector vecAbsVelocity;
	PhysicsClipVelocity( GetAbsVelocity(), trace.plane.normal, vecAbsVelocity, 2.0f );
	vecAbsVelocity *= flTotalElasticity;

	// Get the total velocity (player + conveyors, etc.)
	VectorAdd( vecAbsVelocity, GetBaseVelocity(), vecMove );
	float flSpeedSqr = DotProduct( vecMove, vecMove );

	// Stop if on ground.
	if ( trace.plane.normal.z > 0.7f )			// Floor
	{
		// Verify that we have an entity.
		CBaseEntity *pEntity = trace.m_pEnt;
		Assert( pEntity );

		SetAbsVelocity( vecAbsVelocity );

		if ( flSpeedSqr < ( 30 * 30 ) )
		{
			if ( pEntity->IsStandable() )
			{
				SetGroundEntity( pEntity );
			}

			// Reset velocities.
			SetAbsVelocity( vec3_origin );
			SetLocalAngularVelocity( vec3_angle );

			//align to the ground so we're not standing on end
			QAngle angle;
			VectorAngles( trace.plane.normal, angle );

			// rotate randomly in yaw
			angle[1] = random->RandomFloat( 0, 360 );

			SetAbsAngles( angle );

			const trace_t* pTrace = &CBaseEntity::GetTouchTrace();

			trace_t trace;
			memcpy(&trace, pTrace, sizeof(trace_t));
			Explode(&trace, pEntity);
		}
		else
		{
			Vector vecDelta = GetBaseVelocity() - vecAbsVelocity;	
			Vector vecBaseDir = GetBaseVelocity();
			VectorNormalize( vecBaseDir );
			float flScale = vecDelta.Dot( vecBaseDir );

			VectorScale( vecAbsVelocity, ( 1.0f - trace.fraction ) * gpGlobals->frametime, vecMove );
			VectorMA( vecMove, ( 1.0f - trace.fraction ) * gpGlobals->frametime, GetBaseVelocity() * flScale, vecMove );
			PhysicsPushEntity( vecMove, &trace );
		}
	}
	else
	{
		// If we get *too* slow, we'll stick without ever coming to rest because
		// we'll get pushed down by gravity faster than we can escape from the wall.
		if ( flSpeedSqr < ( 30 * 30 ) )
		{
			// Reset velocities.
			SetAbsVelocity( vec3_origin );
			SetLocalAngularVelocity( vec3_angle );
		}
		else
		{
			SetAbsVelocity( vecAbsVelocity );
		}
	}

	//BounceSound();

	if ( m_nBounces > 20 )
	{
		//failsafe detonate after 20 bounces
		SetAbsVelocity( vec3_origin );

		const trace_t* pTrace = &CBaseEntity::GetTouchTrace();

		trace_t trace;
		memcpy( &trace, pTrace, sizeof(trace_t) );
		Explode( &trace, pEntity );

		SetNextThink( gpGlobals->curtime );
		SetMoveType( MOVETYPE_NONE );
	}
	else
	{
		m_nBounces++;
	}

}
//-----------------------------------------------------------------------------
// Purpose: Rocket was deflected.
//-----------------------------------------------------------------------------
void CTFProjectile_Rocket::Deflected( CBaseEntity *pDeflectedBy, Vector &vecDir )
{
	CTFPlayer *pTFDeflector = ToTFPlayer( pDeflectedBy );
	if ( !pTFDeflector )
		return;

	ChangeTeam( pTFDeflector->GetTeamNumber() );
	SetLauncher( pTFDeflector->GetActiveWeapon() );

	CTFPlayer* pOldOwner = ToTFPlayer( GetOwnerEntity() );
	SetOwnerEntity( pTFDeflector );

	if ( pOldOwner )
	{
		pOldOwner->SpeakConceptIfAllowed( MP_CONCEPT_DEFLECTED, "projectile:1,victim:1" );
	}

	if ( pTFDeflector->m_Shared.IsCritBoosted() )
	{
		SetCritical( true );
	}

	CTFWeaponBase::SendObjectDeflectedEvent( pTFDeflector, pOldOwner, GetWeaponID(), this );

	IncrementDeflected();
	m_nSkin = ( GetTeamNumber() == TF_TEAM_BLUE ) ? 1 : 0;
}
