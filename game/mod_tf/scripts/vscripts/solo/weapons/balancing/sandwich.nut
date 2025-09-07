TFSOLO.BalancingFuncs.push(function(kv)
{
	// All lunchboxes are now a new equipment
	local key1 = kv.FindKey("prefabs")
	local prefab = key1.FindKey("weapon_lunchbox")
	local attrib = prefab.FindKey("attributes")
	
	prefab.SetString("item_slot","equipment")
	
	prefab.SetString("usable_by_bots","0")
	
	prefab.SetString("item_quality","moditem_rebalance")
})