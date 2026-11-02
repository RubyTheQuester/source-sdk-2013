TFSOLO.BalancingFuncs.push(function(kv)
{
	// Back Scatter
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("1103")
	local attrib = prefab.FindKey("attributes")
	
	attrib.RemoveSubKey("closerange backattack minicrits")
	attrib.RemoveSubKey("spread penalty")
	attrib.RemoveSubKey("crit mod disabled")
	
	// 25% Less bullets
	//local a1 = attrib.GetKey("bullets per shot bonus", true)
	//a1.SetString("attribute_class","mult_bullets_per_shot")
	//a1.SetFloat("value", 0.75)
	
	// 90% less spread
	local a2 = attrib.GetKey("weapon spread bonus", true)
	a2.SetString("attribute_class","mult_spread_scale")
	a2.SetFloat("value", 0.1)
	
	// 10% less damage
	local a3 = attrib.GetKey("damage penalty", true)
	a3.SetString("attribute_class","mult_dmg")
	a3.SetFloat("value", 0.9)
	
	// 10% slower fire rate
	//local a4 = attrib.GetKey("fire rate penalty", true)
	//a4.SetString("attribute_class","mult_postfiredelay")
	//a4.SetFloat("value", 1.1)
	
	// 10% slower reload rate
	//local a5 = attrib.GetKey("Reload time increased", true)
	//a5.SetString("attribute_class","mult_reload_time")
	//a5.SetFloat("value", 1.1)

	prefab.SetString("item_quality","moditem_newstats")
	prefab.SetString("item_name","#TF_Weapon_3lbTrigger")
})