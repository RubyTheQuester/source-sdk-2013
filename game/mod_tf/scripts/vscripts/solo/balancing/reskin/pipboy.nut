TFSOLO.BalancingFuncs.push(function(kv)
{
	// Pip-Boy
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("519")
	local attrib = prefab.FindKey("attributes")
	
	// Match PDA prefab
	prefab.SetString("prefab","weapon_pda")
	prefab.RemoveSubKey("item_class")
	prefab.RemoveSubKey("item_slot")
	prefab.RemoveSubKey("model_player")
	prefab.SetString("extra_wearable","models/workshop_partner/player/items/engineer/bet_pb/bet_pb.mdl")
	
	// Metal regen
	local a1 = attrib.GetKey("metal regen", true)
	a1.SetString("attribute_class","add_metal_regen")
	a1.SetFloat("value", 10)
	
	// Ammo regen
	local a2 = attrib.GetKey("ammo regen", true)
	a2.SetString("attribute_class","addperc_ammo_regen")
	a2.SetFloat("value", 0.1)
	
	// No hauling
	local a3 = attrib.GetKey("no hauling", true)
	a3.SetString("attribute_class","building_no_pickup")
	a3.SetInt("value", 1)
	
	// 100% extra primary ammo
	//local a1 = attrib.GetKey("maxammo primary increased", true)
	//a1.SetString("attribute_class","mult_maxammo_primary")
	//a1.SetFloat("value", 2)
	
	// 100% extra secondary ammo
	//local a2 = attrib.GetKey("maxammo secondary increased", true)
	//a2.SetString("attribute_class","mult_maxammo_secondary")
	//a2.SetFloat("value", 2)
	
	// 25% less metal ammo
	//local a3 = attrib.GetKey("maxammo metal reduced", true)
	//a3.SetString("attribute_class","mult_maxammo_metal")
	//a3.SetFloat("value", 0.75)
})