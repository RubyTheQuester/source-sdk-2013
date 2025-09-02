TFSOLO.BalancingFuncs.push(function(kv)
{
	// Spy-cicle Fix
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("649")
	local attrib = prefab.FindKey("attributes")
	
	// Taunt
	local a1 = attrib.GetKey("special taunt", true)
	a1.SetString("attribute_class","special_taunt")
	a1.SetInt("value",1)
})