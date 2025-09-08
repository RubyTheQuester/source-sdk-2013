TFSOLO.BalancingFuncs.push(function(kv)
{
	// Pomson 6000
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("442")
	local attrib = prefab.FindKey("attributes")
	
	// Add projectile penetration/bison projectile properties
	local a1 = attrib.GetKey("Projectile speed increased", true)
	a1.SetString("attribute_class","mult_projectile_speed")
	a1.SetInt("value", 2)
	
	local a2 = attrib.GetKey("clip size bonus upgrade", true)
	a2.SetString("attribute_class","mult_clipsize_upgrade")
	a2.SetFloat("value", 1.5)

	prefab.SetString("item_quality","moditem_rebalance")
})