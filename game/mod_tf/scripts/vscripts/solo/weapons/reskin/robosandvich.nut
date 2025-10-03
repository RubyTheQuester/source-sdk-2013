TFSOLO.BalancingFuncs.push(function(kv)
{
	// Robo-Sandvich
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("863")
	local attrib = prefab.FindKey("attributes")
	local statattrib = prefab.FindKey("static_attrs")
	
	statattrib.RemoveSubKey("item_meter_charge_rate")
	
	prefab.SetString("item_description","#TF_Weapon_Lunchbox_Ammo_desc")
	
	// TODO: New design
	
	local a1 = attrib.GetKey("lunchbox adds minicrits", true)
	a1.SetString("attribute_class","set_weapon_mode")
	a1.SetInt("value", 5)
	
	local a2 = attrib.GetKey("lunchbox healing decreased", true)
	a2.SetString("attribute_class","lunchbox_healing_scale")
	a2.SetFloat("value", 0.34)
	
	local a3 = attrib.GetKey("charge recharge rate increased", true)
	a3.SetString("attribute_class","charge_recharge_rate")
	a3.SetFloat("value", 1.5)
	
	local a4 = attrib.GetKey("item_meter_charge_rate", true)
	a4.SetString("attribute_class","item_meter_charge_rate")
	a4.SetFloat("value", 10)
	
	prefab.SetString("item_quality","moditem_newstats")
})