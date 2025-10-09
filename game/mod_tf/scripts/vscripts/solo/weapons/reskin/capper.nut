TFSOLO.BalancingFuncs.push(function(kv)
{
	// Capper
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("30666")
	local attrib = prefab.FindKey("attributes")
	local statsattrib = prefab.FindKey("static_attrs")
	
	//prefab.SetString("item_class","tf_weapon_pistol_charge")
	prefab.SetString("prefab","weapon_capper")
	
	// No Ammo
	//local a1 = attrib.GetKey("energy weapon no ammo", true)
	//a1.SetString("attribute_class","energy_weapon_no_ammo")
	//a1.SetInt("value", 1)
	
	// Lowered clip-size penalty to only 15
	//local a2 = attrib.FindKey("clip size penalty")
	//a2.SetString("attribute_class","mult_clipsize")
	//a2.SetFloat("value", 0.60)
	
	prefab.SetString("item_quality","moditem_newstats")
})