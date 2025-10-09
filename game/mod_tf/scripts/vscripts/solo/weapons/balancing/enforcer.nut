TFSOLO.BalancingFuncs.push(function(kv)
{
	// Enforcer
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("460")
	local attrib = prefab.FindKey("attributes")
	
	attrib.RemoveSubKey("damage bonus while disguised")
	
	local a1 = attrib.GetKey("damage bonus while undisguised", true)
	a1.SetString("attribute_class","mult_dmg_undisguised")
	a1.SetFloat("value", 1.2)
	
	prefab.SetString("item_quality","moditem_rebalance")
})