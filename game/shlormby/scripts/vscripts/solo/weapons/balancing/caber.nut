TFSOLO.BalancingFuncs.push(function(kv)
{
	// Ullapool Caber
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("307")
	local attrib = prefab.FindKey("attributes")
	
	// Remove penalties
	attrib.RemoveSubKey("fire rate penalty")
	attrib.RemoveSubKey("single wep deploy time increased")
	
	prefab.SetString("item_quality","moditem_rebalance")
})