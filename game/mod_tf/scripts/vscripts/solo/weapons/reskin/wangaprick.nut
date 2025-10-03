TFSOLO.BalancingFuncs.push(function(kv)
{
	// Wanga Prick
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("574")
	local attrib = prefab.FindKey("attributes")
	
	prefab.SetString("prefab","weapon_buff_knife")
	
	prefab.SetString("item_description","#TF_Weapon_BuffKnife_desc")
	prefab.SetString("item_quality","moditem_newstats")
})