TFSOLO.BalancingFuncs.push(function(kv)
{
	// Enforcer
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("460")
	local attrib = prefab.FindKey("attributes")
	
	local a1 = attrib.GetKey("last_shot_crits", true)
	a1.SetString("attribute_class","last_shot_crits")
	a1.SetInt("value", 1)
	
	prefab.SetString("item_quality","moditem_rebalance")
})