TFSOLO.BalancingFuncs.push(function(kv)
{
	local key1 = kv.FindKey("items")
	local key2 = kv.FindKey("prefabs")
	
	// Sniper Rifles
	local change1 = key1.FindKey("14")
	local change2 = key1.FindKey("201")
	
	// Family Business
	local change3 = key1.FindKey("425")
	
	// Gunboats
	local change4 = key1.FindKey("133")
	
	// Winger
	local change5 = key1.FindKey("449")
	
	// ???
	local change6 = key1.FindKey("444")
	
	// ???
	local change7 = key1.FindKey("773")
	
	change1.SetString("item_quality","moditem_rebalance")
	change2.SetString("item_quality","moditem_rebalance")
	change3.SetString("item_quality","moditem_rebalance")
	change4.SetString("item_quality","moditem_rebalance")
	change5.SetString("item_quality","moditem_rebalance")
	change6.SetString("item_quality","moditem_rebalance")
	change7.SetString("item_quality","moditem_rebalance")
})