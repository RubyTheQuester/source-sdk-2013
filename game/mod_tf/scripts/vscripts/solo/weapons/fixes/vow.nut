TFSOLO.BalancingFuncs.push(function(kv)
{
	// Spy-cicle Fix
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("413")
	
	prefab.SetString("prefab","weapon_bonesaw")
})