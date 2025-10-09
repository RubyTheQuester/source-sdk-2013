TFSOLO.BalancingFuncs.push(function(kv)
{
	// Snack Attack
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("1102")
	local attrib = prefab.GetKey("attributes", true)
	
	prefab.SetString("usable_by_bots","0")
	
	// Add sapping players
	local a1 = attrib.GetKey("sapper_on_players", true)
	a1.SetString("attribute_class","sapper_on_players")
	a1.SetInt("value", 1)
	
	// Add no sapping buildings
	local a2 = attrib.GetKey("sapper_no_buildings", true)
	a2.SetString("attribute_class","sapper_no_buildings")
	a2.SetInt("value", 1)
	
	// Add destructible sapper (doesn't work on players yet)
	//local a3 = attrib.GetKey("sapper_destructible", true)
	//a3.SetString("attribute_class","sapper_destructible")
	//a3.SetInt("value", 1)
	
	// Add recharge time
	local a4 = attrib.GetKey("sapper_recharge_time", true)
	a4.SetString("attribute_class","sapper_recharge_time")
	a4.SetInt("value", 15)
	
	// Add recharge time
	//local a5 = attrib.GetKey("robo sapper", true)
	//a5.SetString("attribute_class","robo_sapper")
	//a5.SetInt("value", 1)
	
	// deploy time increased
	local a5 = attrib.GetKey("sapper_deploy_time", true)
	a5.SetString("attribute_class","sapper_deploy_time")
	a5.SetFloat("value", 1.25)
	
	prefab.SetString("item_quality","moditem_newstats")
})