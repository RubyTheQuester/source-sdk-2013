::TFSOLO.BalancingFuncs <- []
//IncludeScript("solo/balancing/shortstop.nut")

IncludeScript("solo/balancing/ambassador.nut")
IncludeScript("solo/balancing/caber.nut")
IncludeScript("solo/balancing/dalokohsbar.nut")
IncludeScript("solo/balancing/evictionnotice.nut")
IncludeScript("solo/balancing/hothand.nut")
IncludeScript("solo/balancing/pomson.nut")
IncludeScript("solo/balancing/sandman.nut")
IncludeScript("solo/balancing/sunonastick.nut")
IncludeScript("solo/balancing/volcanofragment.nut")
IncludeScript("solo/balancing/warriorsspirit.nut")
IncludeScript("solo/balancing/yer.nut")
IncludeScript("solo/balancing/steak.nut")

IncludeScript("solo/balancing/ubersaw.nut")
IncludeScript("solo/balancing/shortstop.nut")

IncludeScript("solo/balancing/pipboy.nut")
IncludeScript("solo/balancing/blackrose.nut")

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