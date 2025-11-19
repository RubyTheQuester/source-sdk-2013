TFSOLO.BalancingFuncs.push(function(kv)
{
	// Eviction Notice
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("426")
	local attrib = prefab.FindKey("attributes")
	local statattr = prefab.GetKey("static_attrs", true)
	
	// Remove health drain
	statattr.RemoveSubKey("mod_maxhealth_drain_rate")
	statattr.RemoveSubKey("mult_player_movespeed_active")
	
	attrib.RemoveSubKey("speed_boost_on_hit")
	
	local a1 = attrib.GetKey("bleeding duration", true)
	a1.SetString("attribute_class","bleeding_duration")
	a1.SetInt("value", 2)
	
	local a2 = attrib.GetKey("damage penalty", true)
	a2.SetString("attribute_class","mult_dmg")
	a2.SetFloat("value", 0.5)
	
	prefab.SetString("item_quality","moditem_newstats")
})