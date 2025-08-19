::TFSOLO.BalancingFuncs <- []
//==========================//
//========Rebalances========//
//==========================//

//-Scout-//
IncludeScript("solo/balancing/shortstop.nut")
IncludeScript("solo/balancing/sandman.nut")

//-Soldier-//
IncludeScript("solo/balancing/libertylauncher.nut")

//-Pyro-//
IncludeScript("solo/balancing/gaspasser.nut")

//-Demoman-//
IncludeScript("solo/balancing/caber.nut")

//-Heavy-//
IncludeScript("solo/balancing/natascha.nut")
IncludeScript("solo/balancing/steak.nut")
IncludeScript("solo/balancing/dalokohsbar.nut")
IncludeScript("solo/balancing/evictionnotice.nut")
IncludeScript("solo/balancing/warriorsspirit.nut")

IncludeScript("solo/balancing/test/sandwich.nut")

//-Engineer-//
IncludeScript("solo/balancing/southernhospitality.nut")
IncludeScript("solo/balancing/pomson.nut")

//-Medic-//
IncludeScript("solo/balancing/ubersaw.nut")

//-Sniper-//

//-Spy-//
IncludeScript("solo/balancing/ambassador.nut") 
IncludeScript("solo/balancing/enforcer.nut")
IncludeScript("solo/balancing/yer.nut")

//===========================//
//========Not reskins========//
//===========================//

//-Scout-//
IncludeScript("solo/balancing/reskin/threeruneblade.nut") 		//Design stats

//-Pyro-//
IncludeScript("solo/balancing/reskin/maul.nut") 				//Design stats
IncludeScript("solo/balancing/reskin/nineiron.nut") 			//Design stats
IncludeScript("solo/balancing/reskin/postalpummeler.nut") 		//Design stats

//-Demoman-//
IncludeScript("solo/balancing/reskin/bootlegger.nut") 			//Design stats

//-Heavy-//
IncludeScript("solo/balancing/reskin/ironcurtain.nut") 			// Unsure
IncludeScript("solo/balancing/reskin/fishcake.nut")				// Design stats
IncludeScript("solo/balancing/reskin/robosandvich.nut") 		// Design stats
IncludeScript("solo/balancing/reskin/apocofists.nut") 			// Design stats
IncludeScript("solo/balancing/reskin/breadbite.nut") 			

//-Engineer-//
IncludeScript("solo/balancing/reskin/pipboy.nut") 				// Unsure

//-Sniper-//
IncludeScript("solo/balancing/reskin/shootingstar.nut") 		//Design stats
IncludeScript("solo/balancing/reskin/fortifiedcompound.nut") 	// Unsure
IncludeScript("solo/balancing/reskin/awperhand.nut") 			//Design stats

//-Spy-//
IncludeScript("solo/balancing/reskin/sharpdresser.nut") 		//Design stats
IncludeScript("solo/balancing/reskin/wangaprick.nut") 			//Design stats
IncludeScript("solo/balancing/reskin/blackrose.nut") 			//Design stats
IncludeScript("solo/balancing/reskin/apsap.nut") 				//Design stats
IncludeScript("solo/balancing/reskin/timepiece.nut") 			//Design stats
IncludeScript("solo/balancing/reskin/quackenbirdt.nut") 		/// Unsure
IncludeScript("solo/balancing/reskin/snackattack.nut") 			// Unsure

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