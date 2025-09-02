TFSOLO.BalancingFuncs.push(function(kv)
{
	// Direct Hit
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("127")
	local attrib = prefab.FindKey("attributes")
	
	local customModel = attrib.GetKey("custom projectile model", true)
	customModel.SetString("attribute_class","custom_projectile_model")
	customModel.SetFloat("value", "models/enhancedrockets2/w_rocket_directhit.mdl")
})