TFSOLO.BalancingFuncs.push(function(kv)
{
	// Pomson 6000
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("588")
	local attrib = prefab.FindKey("attributes")
	
	// Add projectile penetration/bison projectile properties
	local a1 = attrib.GetKey("energy weapon penetration", true)
	a1.SetString("attribute_class","energy_weapon_penetration")
	a1.SetInt("value", 1)
	
	local a2 = attrib.GetKey("Projectile speed increased", true)
	a2.SetString("attribute_class","mult_projectile_speed")
	a2.SetInt("value", 2)
	
	local a3 = attrib.GetKey("clip size bonus upgrade", true)
	a3.SetString("attribute_class","mult_clipsize_upgrade")
	a3.SetFloat("value", 1.5)
	
	// Remove penalties
	attrib.RemoveSubKey("subtract victim medigun charge on hit")
	attrib.RemoveSubKey("subtract victim cloak on hit")
	
	prefab.SetString("item_quality","moditem_rebalance")
})