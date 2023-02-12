class CfgMods
{
	class AI_GUI
	{
		dir="AI_GUI";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Expansion AI Debug UI Extended";
		credits="Dolphin";
		author="Dolphin";
		inputs="dolphin/AI_GUI/inputs.xml";
		version="Version 0.1";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game",
			"Mission"
		};
		class defs
		{
			class imageSets
			{
				files[]=
				{
					"dolphin/AI_GUI/GUI/Data/bg-footer-header.imageset",
					"dolphin/AI_GUI/GUI/Data/dz-bg-black.imageset",
					"dolphin/AI_GUI/GUI/Data/vpp_logo_main_menu.imageset"
				};
			};
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"dolphin/AI_GUI/3_Game"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"dolphin/AI_GUI/5_Mission"
				};
			};
		};
	};
};
class CfgPatches
{
	class DZM_AI_GUI
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"RPC_Scripts", "DayZExpansion_AI_Scripts"
		};
	};
};