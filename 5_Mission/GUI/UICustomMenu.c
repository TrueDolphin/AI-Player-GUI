class UICustomMenu extends UIScriptedMenu
{
    private bool                 m_Initialized;
    private bool                 m_IsMenuOpen;
    private bool                 m_running = false;
    private bool                 m_result = false;
    //---Elements from .layout file
    private ScrollWidget 		 m_Scroller;
    private GridSpacerWidget     m_Grid;
    private TextWidget           m_Title;
    private Widget               m_pnl_bg;
    private ButtonWidget         m_BtnSetFaction;
    private PlayerBase           m_player;
    private TextWidget           m_TxtPlayerName;
    private TextWidget           m_TxtPlayerUID;
    private TextWidget           m_TxtPlayerFaction;
    private TextWidget           m_TxtPlayerGroup;
    private EditBoxWidget        m_EdtFactionName;
    private TextWidget           m_TxtGroupnum;
    private TextWidget           m_TxtLocalCheck;

    private ref array<ref Widget> m_CustomChildrenHighIQ;

    void UICustomMenu()
    {


    	m_CustomChildrenHighIQ = new array<ref Widget>;
    }
    void ~UICustomMenu() 
    {
        PPEffects.SetBlurMenu( 0 );
        GetGame().GetUIManager().Back();
        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );
        if ( layoutRoot )
        	layoutRoot.Unlink();
    }

    //after show
    override void OnShow()
    {
        super.OnShow();
    }

    //after hide
    override void OnHide()
    {
        super.OnHide();
        g_Game.GetUIManager().ShowCursor(true);
        g_Game.GetUIManager().ShowUICursor(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetMission().GetHud().Show( true );
    }

    override Widget Init()
    {
        if (!m_Initialized) //Only draw and init widgets if not already done that, since this function is called each time you do ( ShowScriptedMenu() )
        {
            layoutRoot = GetGame().GetWorkspace().CreateWidgets( "dolphin/AI_GUI/GUI/Layouts/MyCustomMenu.layout" );
            
            //Scripts\1_Core\proto\EnWidgets.c
            //set objects
            m_Scroller = ScrollWidget.Cast( layoutRoot.FindAnyWidget( "Scroller" ) );
			m_Grid     = GridSpacerWidget.Cast( layoutRoot.FindAnyWidget( "Grid" ) );
			m_Title	   = TextWidget.Cast( layoutRoot.FindAnyWidget( "Title" ) );
			m_pnl_bg   = layoutRoot.FindAnyWidget( "pnl_bg" );
            m_BtnSetFaction = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BtnSetFaction" ) );
            m_Title	   = TextWidget.Cast( layoutRoot.FindAnyWidget( "Title" ) );
            m_TxtPlayerName = TextWidget.Cast( layoutRoot.FindAnyWidget( "TxtPlayerName" ) );
            m_TxtPlayerUID = TextWidget.Cast( layoutRoot.FindAnyWidget( "TxtPlayerUID" ) );
            m_TxtPlayerFaction = TextWidget.Cast( layoutRoot.FindAnyWidget( "TxtPlayerFaction" ) );
            m_TxtPlayerGroup = TextWidget.Cast( layoutRoot.FindAnyWidget( "TxtPlayerGroup" ) );
            m_EdtFactionName = EditBoxWidget.Cast( layoutRoot.FindAnyWidget( "EdtFactionName" ) );
            m_TxtGroupnum = TextWidget.Cast( layoutRoot.FindAnyWidget( "TxtGroupnum" ) );
            m_TxtLocalCheck = TextWidget.Cast( layoutRoot.FindAnyWidget( "TxtLocalCheck" ) );


            WidgetEventHandler.GetInstance().RegisterOnDoubleClick( m_Grid, this, "OnDoubleClicked" );
            WidgetEventHandler.GetInstance().RegisterOnDoubleClick( m_Scroller, this, "OnDoubleClicked" );

            m_Initialized = true;
        }
        return layoutRoot;
    }

    bool ShouldShowScrollBar()
    {
        float x, y;
        m_pnl_bg.GetScreenSize( x, y );
        return m_Scroller.GetContentHeight() > y;
    }

    override void Update(float timeslice)
    {
        super.Update(timeslice);

        if ( ShouldShowScrollBar() )
            m_Scroller.SetAlpha(1.0);
        else
            m_Scroller.SetAlpha(0.0);
        if (m_IsMenuOpen){
            m_player = PlayerBase.Cast( GetGame().GetPlayer() );
            if (!HasPermission(m_player.GetIdentity())) return;
            m_TxtPlayerName.SetText(m_player.GetIdentity().GetName());
            m_TxtPlayerUID.SetText(m_player.GetIdentity().ToString());
            eAIGroup playerGroup = m_player.GetGroup();
            if (playerGroup) { 
            m_TxtPlayerGroup.SetText(playerGroup.GetID().ToString());
            eAIFaction faction = playerGroup.GetFaction();
            m_TxtPlayerFaction.SetText(faction.GetName());
            m_TxtGroupnum.SetText(playerGroup.Count().ToString());
            } else {
            m_TxtPlayerGroup.SetText("None Detected");
            m_TxtPlayerFaction.SetText("None Detected");
            m_TxtGroupnum.SetText("1");
            }

            if (m_running) {
                m_TxtLocalCheck.SetText(eAIBase.IsInVicinity(m_player, 100););
            } else {
            thread localtimer();
            }
        }
    }
    override bool OnClick(Widget w, int x, int y, int button)
    {
        if (!HasPermission(m_player.GetIdentity())) return super.OnClick(w, x, y, button);
    	switch(w)
    	{
            case m_BtnSetFaction:
            if (!m_EdtFactionName.GetText()){
                break;
            }
                GetRPCManager().SendRPC("AI_GUI", "GUI_SetFaction", new Param1<string>(m_EdtFactionName.GetText()), true, NULL); 
            break;
    	}
        return super.OnClick(w, x, y, button);
    }
    void OnDoubleClicked(Widget w, int x, int y, int button) 
    {
        if (button == MouseState.LEFT)
        {
            //Do something
        }
        else if (button == MouseState.RIGHT)
        {
            //Do something
        }
    }

    bool IsMenuOpen() 
    {
        return m_IsMenuOpen;
    }

    void SetMenuOpen(bool isMenuOpen) 
    {
        m_IsMenuOpen = isMenuOpen;
    }

bool HasPermission(PlayerIdentity pId)
{
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
    void localtimer(){
    m_running = true;
    Sleep(1000);
    m_running = false;
    }
};