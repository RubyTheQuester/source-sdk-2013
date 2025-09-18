TFSOLO.BalancingFuncs.push(function(kv)
{
	// Baby Face's Blaster
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("772")
	local attrib = prefab.FindKey("attributes")
	
	// Lower boost loss on damage
	local a1 = attrib.FindKey("lose hype on take damage")
	a1.SetInt("value", 1)
	
	// Reduce boost loss on air jumps from 75% to 10%
	local a1 = attrib.FindKey("hype resets on jump")
	a1.SetInt("value", 10)
	
	prefab.SetString("item_quality","moditem_rebalance")
})