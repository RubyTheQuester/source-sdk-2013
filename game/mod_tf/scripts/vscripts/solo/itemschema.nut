::TFSOLO.BalancingFuncs <- []
//==========================//
//========Rebalances========//
//==========================//
//-Multiclass-//


//-Scout-//
IncludeScript("solo/weapons/balancing/backscatter.nut")
IncludeScript("solo/weapons/balancing/shortstop.nut")
IncludeScript("solo/weapons/balancing/sandman.nut")
IncludeScript("solo/weapons/balancing/bfb.nut")

//-Soldier-//
IncludeScript("solo/weapons/balancing/libertylauncher.nut")
IncludeScript("solo/weapons/balancing/bison.nut")

//-Pyro-//
IncludeScript("solo/weapons/balancing/gaspasser.nut")
IncludeScript("solo/weapons/balancing/axtinguisher.nut")

//-Demoman-//
IncludeScript("solo/weapons/balancing/caber.nut")

//-Heavy-//
//IncludeScript("solo/weapons/balancing/natascha.nut") // Better redesign needed
IncludeScript("solo/weapons/balancing/steak.nut")
IncludeScript("solo/weapons/balancing/dalokohsbar.nut")
IncludeScript("solo/weapons/balancing/evictionnotice.nut")
IncludeScript("solo/weapons/balancing/warriorsspirit.nut")
IncludeScript("solo/weapons/balancing/sandwich.nut")

//-Engineer-//
IncludeScript("solo/weapons/balancing/southernhospitality.nut")
IncludeScript("solo/weapons/balancing/pomson.nut")

//-Medic-//
IncludeScript("solo/weapons/balancing/ubersaw.nut")

//-Sniper-//
IncludeScript("solo/weapons/balancing/carbine.nut")

//-Spy-//
IncludeScript("solo/weapons/balancing/ambassador.nut") 
IncludeScript("solo/weapons/balancing/enforcer.nut")
IncludeScript("solo/weapons/balancing/yer.nut")

//=======================//
//========Reskins========//
//=======================//
//-Multiclass-//
IncludeScript("solo/weapons/reskin/capper.nut") 

//-Scout-//
IncludeScript("solo/weapons/reskin/threeruneblade.nut") 		// Design stats

//-Pyro-//
IncludeScript("solo/weapons/reskin/maul.nut") 				// Design stats
IncludeScript("solo/weapons/reskin/nineiron.nut") 			// Design stats
IncludeScript("solo/weapons/reskin/postalpummeler.nut") 		// Design stats

//-Demoman-//
IncludeScript("solo/weapons/reskin/handshake.nut")				//Unsure
IncludeScript("solo/weapons/reskin/bootlegger.nut") 			//Design stats

//-Heavy-//
IncludeScript("solo/weapons/reskin/ironcurtain.nut") 			// Unsure
IncludeScript("solo/weapons/reskin/fishcake.nut")				// Design stats
IncludeScript("solo/weapons/reskin/robosandvich.nut") 			// Design stats
IncludeScript("solo/weapons/reskin/apocofists.nut") 			// Design stats
IncludeScript("solo/weapons/reskin/breadbite.nut") 			

//-Sniper-//
IncludeScript("solo/weapons/reskin/shootingstar.nut") 			// Design stats
IncludeScript("solo/weapons/reskin/fortifiedcompound.nut") 		// Unsure
IncludeScript("solo/weapons/reskin/awperhand.nut") 				// Design stats

//-Spy-//
IncludeScript("solo/weapons/reskin/sharpdresser.nut") 			// Unsure
IncludeScript("solo/weapons/reskin/wangaprick.nut") 			// Unsure
IncludeScript("solo/weapons/reskin/blackrose.nut") 				// Design stats
IncludeScript("solo/weapons/reskin/apsap.nut") 					// Design stats
IncludeScript("solo/weapons/reskin/timepiece.nut") 				// Design stats
IncludeScript("solo/weapons/reskin/quackenbirdt.nut") 			// Unsure
IncludeScript("solo/weapons/reskin/snackattack.nut") 			// Unsure

//=======================//
//======New Weapons======//
//=======================//

//-Engineer-//
IncludeScript("solo/weapons/new/pipboy.nut") 					// Unsure


//================================//
//=======Enchacements/Fixes=======//
//================================//

IncludeScript("solo/weapons/misc/misc_changes.nut")

//-Medic-//
IncludeScript("solo/weapons/fixes/vow.nut")

//-Spy-//
IncludeScript("solo/weapons/fixes/spycicle.nut")

::TFSOLO.SetupItemSchema <- function()
{
	local kv = Solo.ItemSchemaGetKV()
	foreach (func in TFSOLO.BalancingFuncs)
	{
		func(kv)
	}
	
	Solo.ItemSchemaReload(kv)
	printl("[TFSOLO] Item schema setup")
}

TFSOLO.SetupItemSchema()
TFSOLO.BalancingFuncs.clear()