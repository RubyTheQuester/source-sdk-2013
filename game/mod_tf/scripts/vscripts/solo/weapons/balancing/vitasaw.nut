TFSOLO.BalancingFuncs.push(function(kv)
{
	// Your Eternal Reward
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("173")
	local attrib = prefab.FindKey("attributes")
	
	// Remove penalties
	attrib.RemoveSubKey("ubercharge_preserved_on_spawn_max")
	
	// add organs on hit
	local a1 = attrib.GetKey("add organ on hit", true)
	a1.SetString("attribute_class","add_organ_on_hit")
	a1.SetInt("value",1)
	
	prefab.RemoveSubKey("item_description")
	
	prefab.SetString("item_quality","moditem_newstats")
})