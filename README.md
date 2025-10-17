# Shlormby Source Code
This is just a for fun project, so keep in mind alot of this code is just sourced from other places or poorly done

## Credits

- **Weapon Models**
	- ** WIP, I PROMISE I'LL CREDIT EVERYONE HERE **
		- Model credits page exists within the game itself
	
- **Community Help/Contributions**
	- ** WIP, I PROMISE I'LL CREDIT EVERYONE HERE **
	
	- ** BetaM **  – Created the mod that made Shlormby possible in the first place.
		https://www.youtube.com/BetaM
		
	- ** Better Fortress 2 ** – Various bits of code is taken from here.
		https://github.com/ALIEN31ITA/Better-Fortress-2
	
	- ** Team Fortress: Grub ** – RPG Code
		https://github.com/grub-fortress/grub_fortress_src
		
	- ** Team Comtress 2 ** – Instant Respawn Code
		https://github.com/mastercomfig/tc2
		
	- ** Various Communty Pull Request ** – For a bunch of minor things I didn't do myself.
	
### Windows

Requirements:
 - Source SDK 2013 Multiplayer installed via Steam
 - Visual Studio 2022 with the following workload and components:
   - Desktop development with C++:
     - MSVC v143 - VS 2022 C++ x64/x86 build tools (Latest)
     - Windows 11 SDK (10.0.22621.0) or Windows 10 SDK (10.0.19041.1)
 - Python 3.13 or later

Inside the cloned directory, navigate to `src`, run:
```bat
createallprojects.bat
```
or
```bat
creategameprojects.bat
```

This will generate the Visual Studio project `everything.sln` which will be used to build the mod. You can also use `games.sln` to only build the files needed for the mod.

Then, on the menu bar, go to `Build > Build Solution`, and wait for everything to build.

You can then select the `Client (Mod Name)` project you wish to run, right click and select `Set as Startup Project` and hit the big green `> Local Windows Debugger` button on the tool bar in order to launch your mod.

The default launch options should be already filled in for the `Release` configuration.

### Linux

Requirements:
 - Source SDK 2013 Multiplayer installed via Steam
 - podman

Inside the cloned directory, navigate to `src`, run:
```bash
./buildallprojects
```

This will build all the projects related to the SDK and your mods automatically against the Steam Runtime.

You can then, in the root of the cloned directory, you can navigate to `game` and run your mod by launching the build launcher for your mod project, eg:
```bash
./mod_tf
```