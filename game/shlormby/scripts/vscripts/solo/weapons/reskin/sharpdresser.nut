TFSOLO.BalancingFuncs.push(function(kv)
{
	// Sharp Dresser
	local key1 = kv.FindKey("items")
	local prefab = key1.FindKey("638")
	local attrib = prefab.FindKey("attributes")
	
	// 15% slower fire rate
	//local a1 = attrib.GetKey("fire rate penalty", true)
	//a1.SetString("attribute_class","mult_postfiredelay")
	//a1.SetFloat("value", 1.15)
	
	// Silent Killer
	//local a2 = attrib.GetKey("silent killer", true)
	//a2.SetString("attribute_class","set_silent_killer")
	//a2.SetInt("value", 1)
	
	// 25% faster deploy
	//local a3 = attrib.GetKey("single wep deploy time decreased", true)
	//a3.SetString("attribute_class","mult_single_wep_deploy_time")
	//a3.SetFloat("value", 0.75)
	
	// 50% slower holster
	//local a4 = attrib.GetKey("single wep holster time increased", true)
	//a4.SetString("attribute_class","mult_switch_from_wep_deploy_time")
	//a4.SetFloat("value", 1.5)
})