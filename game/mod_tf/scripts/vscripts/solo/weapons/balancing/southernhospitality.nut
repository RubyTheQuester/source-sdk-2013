TFSOLO.BalancingFuncs.push(function(kv)
{
	// Southern Hospitality
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("155")
	local attrib = prefab.FindKey("attributes")
	
	// Remove existing attribues
	attrib.RemoveSubKey("crit mod disabled")
	attrib.RemoveSubKey("dmg taken from fire increased")
	
	local a1 = attrib.GetKey("damage penalty", true)
	a1.SetString("attribute_class","mult_dmg")
	a1.SetFloat("value", 0.5)
	
	local a2 = attrib.GetKey("bleeding duration", true)
	a2.SetString("attribute_class","bleeding_duration")
	a2.SetInt("value", 6)
	
	prefab.SetString("item_quality","moditem_rebalance")
})