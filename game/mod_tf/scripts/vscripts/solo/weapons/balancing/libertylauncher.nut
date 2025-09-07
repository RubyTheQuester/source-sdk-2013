TFSOLO.BalancingFuncs.push(function(kv)
{
	// Liberty Launcher
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("414")
	local attrib = prefab.FindKey("attributes")
	
	// Set damage penalty to 0.85
	//attrib.RemoveSubKey("damage penalty")
	
	local a1 = attrib.GetKey("damage penalty", true)
	a1.SetString("attribute_class","mult_dmg")
	a1.SetFloat("value", 0.85)
	
	prefab.SetString("item_quality","moditem_rebalance")
})