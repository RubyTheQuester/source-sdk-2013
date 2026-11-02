TFSOLO.BalancingFuncs.push(function(kv)
{
	// Natascha
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("41")
	local attrib = prefab.FindKey("attributes")
	
	// TODO 
	
	// Remove slow on hit, Spinup time, and Spunup Damage Resistance
	attrib.RemoveSubKey("slow enemy on hit")
	attrib.RemoveSubKey("minigun spinup time increased")
	attrib.RemoveSubKey("spunup_damage_resistance")
	
	// 15% bullets
	local a1 = attrib.GetKey("bullets per shot bonus", true)
	a1.SetString("attribute_class","mult_bullets_per_shot")
	a1.SetFloat("value", 1.15)
	
	// 100% more max primary ammo
	local a2 = attrib.GetKey("maxammo primary increased", true)
	a2.SetString("attribute_class","mult_maxammo_primary")
	a2.SetFloat("value", 2)
	
	// 50% more spread
	local a3 = attrib.GetKey("spread penalty", true)
	a3.SetString("attribute_class","mult_spread_scale")
	a3.SetFloat("value", 1.5)
	
	// 10% less damage
	//local a4 = attrib.GetKey("damage penalty", true)
	//a4.SetString("attribute_class","mult_dmg")
	//a4.SetFloat("value", 0.9)
	
	prefab.SetString("item_quality","moditem_rebalance")
})