modded class MissionBase {
  ref array < Man > m_PlayerList = new array < Man > ;
  void MissionBase() {
    GetRPCManager().AddRPC("AI_GUI", "GUI_SetFaction", this, SingleplayerExecutionType.Both);
  }

  void GUI_SetFaction(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target) {
    //if this function is trigger anywhere but on server, we return without continuing.
    if (type != CallType.Server)
      return;

    Param1 < string > data;
    //if the data is not retrieved we return to avoid issue
    if (!ctx.Read(data))
      return;

    if (sender == null)
      return;

    string clientResponse = data.param1;

    GetGame().GetPlayers(m_PlayerList);

    for (int i = 0; i < m_PlayerList.Count(); i++) //! because we love loops
    {
      PlayerBase player = PlayerBase.Cast(m_PlayerList[i]);
      if (!player)
        return;
      if (!player.GetIdentity())
        return;
      if (player.GetIdentity().GetName() == sender.GetName()) {
        eAIGroup playerGroup = player.GetGroup();
        if (!playerGroup) playerGroup = eAIGroup.GetGroupByLeader(player);
        eAIFaction faction = eAIFaction.Create(clientResponse);
        if (faction) {
          playerGroup.SetFaction(faction);
          player.SetSynchDirty();
          Print(string.Format("%1 set to faction: %2", sender.GetName(), clientResponse));
        }
      }
    }
  }

  override UIScriptedMenu CreateScriptedMenu(int id) {
    UIScriptedMenu menu = NULL;
    menu = super.CreateScriptedMenu(id);
    if (!menu) {
      switch (id) {
      case AI_TOGGLE_MENU:
        menu = new UICustomMenu;
        break;
      }
      if (menu) {
        menu.SetID(id);
      }
    }
    return menu;
  }
}