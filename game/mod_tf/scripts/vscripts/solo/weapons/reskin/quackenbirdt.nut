TFSOLO.BalancingFuncs.push(function(kv)
{
	// Quackenbirdt
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("947")
	local attrib = prefab.GetKey("attributes", true)
	
	// Set weapon mode to 11
	//local a1 = attrib.GetKey("", true)
	//a1.SetString("attribute_class","set_weapon_mode")
	//a1.SetInt("value", 11)
	
	// Wet Immunity
	local a1 = attrib.GetKey("wet_immunity", true)
	a1.SetString("attribute_class","wet_immunity")
	a1.SetInt("value", 1)
	
	// Can Breathe Under Water
	local a2 = attrib.GetKey("can_breathe_under_water", true)
	a2.SetString("attribute_class","can_breathe_under_water")
	a2.SetInt("value", 1)
	
	// Swimming Mastery
	local a3 = attrib.GetKey("swimming_mastery", true)
	a3.SetString("attribute_class","swimming_mastery")
	a3.SetInt("value", 1)
	
	// No Cloak When Cloaked
	local a4 = attrib.GetKey("NoCloakWhenCloaked", true)
	a4.SetString("attribute_class","NoCloakWhenCloaked")
	a4.SetInt("value", 1)
	
	// Reduced Cloak From Ammo
	local a4 = attrib.GetKey("ReducedCloakFromAmmo", true)
	a4.SetString("attribute_class","ReducedCloakFromAmmo")
	a4.SetFloat("value", 0.65)
	
	prefab.SetString("item_quality","moditem_newstats")
})