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
	
	// 20 Metal every 5 seconds
	local a1 = attrib.GetKey("metal regen", true)
	a1.SetString("attribute_class","add_metal_regen")
	a1.SetFloat("value", 20)
	
	// 100% extra primary ammo
	//local a2 = attrib.GetKey("maxammo primary increased", true)
	//a2.SetString("attribute_class","mult_maxammo_primary")
	//a2.SetFloat("value", 2)
	
	// 100% extra secondary ammo
	//local a3 = attrib.GetKey("maxammo secondary increased", true)
	//a3.SetString("attribute_class","mult_maxammo_secondary")
	//a3.SetFloat("value", 2)
	
	// Add +15% movement speed penalty
	local a4 = attrib.GetKey("move speed penalty", true)
	a4.SetString("attribute_class","mult_player_movespeed")
	a4.SetFloat("value", 0.85)
	
	// 25% less metal ammo
	//local a3 = attrib.GetKey("maxammo metal reduced", true)
	//a3.SetString("attribute_class","mult_maxammo_metal")
	//a3.SetFloat("value", 0.75)
	
	// Ammo regen
	//local a2 = attrib.GetKey("ammo regen", true)
	//a2.SetString("attribute_class","addperc_ammo_regen")
	//a2.SetFloat("value", 0.15)
	
	// No hauling
	//local a3 = attrib.GetKey("no hauling", true)
	//a3.SetString("attribute_class","building_no_pickup")
	//a3.SetInt("value", 1)
	
	prefab.SetString("item_quality","moditem_newstats")
})