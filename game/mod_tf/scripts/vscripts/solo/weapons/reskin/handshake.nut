TFSOLO.BalancingFuncs.push(function(kv)
{
	// Scottish Handshake
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("609")
	local attrib = prefab.FindKey("attributes")
	
	// Bonus when half dead
	local a1 = attrib.GetKey("dmg bonus while half dead", true)
	a1.SetString("attribute_class","mult_dmg_bonus_while_half_dead")
	a1.SetFloat("value", 1.25)
	
	// Penalty when half alive
	local a2 = attrib.GetKey("dmg penalty while half alive", true)
	a2.SetString("attribute_class","mult_dmg_penalty_while_half_alive")
	a2.SetFloat("value", 0.75)
	
	local a3 = attrib.GetKey("special taunt", true)
	a3.SetString("attribute_class","special_taunt")
	a3.SetInt("value", 1)
	
	prefab.SetString("item_quality","moditem_newstats")
})