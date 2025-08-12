TFSOLO.BalancingFuncs.push(function(kv)
{
	// Ambassador
	local key1 = kv.FindKey("prefabs")
	local prefab = key1.FindKey("weapon_ubersaw")
	local attrib = prefab.FindKey("attributes")
	
	// Add +50% eating speed
	local a1 = attrib.GetKey("max health additive penalty", true)
	a1.SetString("attribute_class","add_maxhealth")
	a1.SetInt("value", -25)
})