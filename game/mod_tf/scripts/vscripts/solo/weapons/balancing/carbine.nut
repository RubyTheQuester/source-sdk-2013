TFSOLO.BalancingFuncs.push(function(kv)
{
	// The Cleaner's Carbine
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("751")
	local attrib = prefab.FindKey("attributes")
	
	// Lowered fire rate penalty to only 10%
	//local a1 = attrib.FindKey("fire rate penalty")
	//a1.SetFloat("value", 1.0)
	attrib.RemoveSubKey("fire rate penalty")
	
	// 20% more accuracy
	local a2 = attrib.GetKey("weapon spread bonus", true)
	a2.SetString("attribute_class","mult_spread_scale")
	a2.SetFloat("value", 0.6)
	
	// Lowered clip-size penalty to only 15
	local a3 = attrib.FindKey("clip size penalty")
	a3.SetFloat("value", 0.60)
	
	prefab.SetString("item_quality","moditem_rebalance")
})