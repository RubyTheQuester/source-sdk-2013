TFSOLO.BalancingFuncs.push(function(kv)
{
	// Nessie's Nine Iron
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("482")
	local attrib = prefab.GetKey("attributes", true)
	
	local visuals = prefab.FindKey("visuals")
	
	visuals.SetString("sound_melee_hit","Weapon_GolfClub.PushImpact")
	
	prefab.SetString("prefab","weapon_sword")
	prefab.SetString("item_class","tf_weapon_katana")
	
	prefab.RemoveSubKey("item_description")
	
	local a1 = attrib.GetKey("sword deflect", true)
	a1.SetString("attribute_class","sword_deflect")
	a1.SetInt("value", 1)
	
	local a2 = attrib.GetKey("sword push", true)
	a2.SetString("attribute_class","sword_push")
	a2.SetInt("value", 1)
	
	local a3 = attrib.GetKey("is_a_sword", true)
	a3.SetString("attribute_class","is_a_sword")
	a3.SetInt("value", 72)
	
	prefab.SetString("item_quality","moditem_newstats")
})