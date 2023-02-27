modded class MissionGameplay {
  private ref UICustomMenu myCustomMenu;
  PlayerBase PermissionCheck;

  override void OnUpdate(float timeslice) {
    super.OnUpdate(timeslice);

    Input input = GetGame().GetInput();
    if (input.LocalPress("UAUIBack", false)) {
      if (myCustomMenu != NULL && GetGame().GetUIManager().GetMenu() == myCustomMenu) {
        myCustomMenu.SetMenuOpen(false);
        GetGame().GetUIManager().HideScriptedMenu(myCustomMenu);
        UnlockControls();
      }
    }
    if (input.LocalPress("ToggleAIMenu", false)) {
        PermissionCheck = PlayerBase.Cast( GetGame().GetPlayer() );
        if (!HasPermission(PermissionCheck.GetIdentity())) return;
      if (myCustomMenu) {

        if (myCustomMenu.IsMenuOpen()) {
          //Hide Menu
          myCustomMenu.SetMenuOpen(false);
          GetGame().GetUIManager().HideScriptedMenu(myCustomMenu);
          UnlockControls();
        } else if (GetGame().GetUIManager().GetMenu() == NULL) {
          //Show Menu
          GetGame().GetUIManager().ShowScriptedMenu(myCustomMenu, NULL);
          myCustomMenu.SetMenuOpen(true);
          LockControls();
        }
      } else if (GetGame().GetUIManager().GetMenu() == NULL && myCustomMenu == null) {
        //Create Menu
        LockControls();
        myCustomMenu = UICustomMenu.Cast(GetUIManager().EnterScriptedMenu(AI_TOGGLE_MENU, null));
        myCustomMenu.SetMenuOpen(true);
      }
    }
  }

  private void LockControls() {
    GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_ALL);
    GetGame().GetUIManager().ShowUICursor(true);
    GetGame().GetMission().GetHud().Show(false);
  }

  private void UnlockControls() {
    GetGame().GetMission().PlayerControlEnable(false);
    GetGame().GetInput().ResetGameFocus();
    GetGame().GetUIManager().ShowUICursor(false);
    GetGame().GetMission().GetHud().Show(true);
  }
  bool HasPermission(PlayerIdentity pId) {
    #ifdef VPPADMINTOOLS
    // check against permission for vppat
    if (GetPermissionManager().VerifyPermission(pId.GetPlainId(), "CanDoSpecialThing"))
      return true;
    #endif

    #ifdef JM_COT
    // check against permission for cot
    if (GetPermissionsManager().HasPermission("Special.Thing"))
      return true;
    #endif

    #ifdef VPPADMINTOOLS
    // check against superadmin for vppat
    if (GetPermissionManager().IsSuperAdmin(pId.GetPlainId()))
      return true;
    #endif

    #ifdef JM_COT
    // check against superadmin for cot
    if (GetPermissionsManager().HasPermission("COT"))
      return true;
    #endif

    return false;
  }
};