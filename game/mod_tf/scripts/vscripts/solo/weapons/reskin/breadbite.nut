TFSOLO.BalancingFuncs.push(function(kv)
{
	// Breadbite
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("1100")
	local attrib = prefab.FindKey("attributes")
	
	prefab.SetString("prefab","valve weapon_fists")

	//local a1 = attrib.GetKey("add_give_health_to_teammate_on_hit", true)
	//a1.SetString("attribute_class","add_give_health_to_teammate_on_hit")
	//a1.SetInt("value", 25)
	
	local a2 = attrib.GetKey("heal on hit for rapidfire", true)
	a2.SetString("attribute_class","add_onhit_addhealth")
	a2.SetInt("value", 15)
	
	local a3 = attrib.GetKey("fire rate bonus", true)
	a3.SetString("attribute_class","mult_postfiredelay")
	a3.SetFloat("value", 0.5)
	
	local a4 = attrib.GetKey("damage penalty", true)
	a4.SetString("attribute_class","mult_dmg")
	a4.SetFloat("value", 0.35)
	
	//local a5 = attrib.GetKey("heal on kill", true)
	//a5.SetString("attribute_class","heal_on_kill")
	//a5.SetInt("value", 50)
	
	prefab.SetString("item_quality","moditem_newstats")
})