// Gamemode: King of the Hill
// Overrides gamemode with stock King of the Hill mode
// Requires:
// - 1 capturable control point
// TODO: Symmetrical map with no control points (CTF) <- spawn a control point?
// TODO: Symmetrical map with neutral CTF flag <- replace flag with a control point?

Convars.SetValue("tf_gamemode_override", 3)

TFSOLO.GamemodeEventTag <- UniqueString()
getroottable()[TFSOLO.GamemodeEventTag] <- {
	OnScriptHook_team_round_activate = function(params)
	{
		
	}
	
	OnGameEvent_scorestats_accumulated_update = function(_)
	{
	}
}
__CollectGameEventCallbacks(getroottable()[TFSOLO.GamemodeEventTag])