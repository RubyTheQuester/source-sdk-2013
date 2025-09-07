TFSOLO.BalancingFuncs.push(function(kv)
{
	// Iron Curtain
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("298")
	local attrib = prefab.FindKey("attributes")
	
	// 20% more pellets
	local a1 = attrib.GetKey("bullets per shot bonus", true)
	a1.SetString("attribute_class","mult_bullets_per_shot")
	a1.SetFloat("value", 1.2)
	
	// 50% slower fire rate
	local a2 = attrib.GetKey("fire rate penalty", true)
	a2.SetString("attribute_class","mult_postfiredelay")
	a2.SetFloat("value", 1.5)
	
	// 10% less spread
	local a3 = attrib.GetKey("weapon spread bonus", true)
	a3.SetString("attribute_class","mult_spread_scale")
	a3.SetFloat("value", 0.9)
	
	// 20% less damage
	local a4 = attrib.GetKey("damage penalty", true)
	a4.SetString("attribute_class","mult_dmg")
	a4.SetFloat("value", 0.8)
	
	prefab.SetString("item_quality","moditem_newstats")
})