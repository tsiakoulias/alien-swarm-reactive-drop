#pragma once

#include "tabbedgriddetails.h"
#include "gameui/swarm/vgenericpanellist.h"
#include "gameui/swarm/vhybridbutton.h"

class CRD_Collection_Tab_Crafting : public TGD_Tab_Panel
{
	DECLARE_CLASS_SIMPLE( CRD_Collection_Tab_Crafting, TGD_Tab_Panel );
public:
	CRD_Collection_Tab_Crafting( TabbedGridDetails *parent, const char *szLabel );

	vgui::Panel *CreatePanel() override;
};

class CRD_Crafting_Panel : public vgui::EditablePanel
{
	DECLARE_CLASS_SIMPLE( CRD_Crafting_Panel, vgui::EditablePanel );
public:
	explicit CRD_Crafting_Panel( CRD_Collection_Tab_Crafting *pTab );
	virtual ~CRD_Crafting_Panel();

	void ApplySchemeSettings( vgui::IScheme *pScheme ) override;
	void OnThink() override;
	void OnCommand( const char *szCommand ) override;
	void UpdateCraftState();

	CRD_Collection_Tab_Crafting *m_pParent;
	BaseModUI::GenericPanelList *m_pGplRecipes;
	vgui::Label *m_pLblRecipeTitle;
	vgui::Label *m_pLblFlavor;
	vgui::Label *m_pLblWarning;
	CNB_Button *m_pBtnCraft;
	CUtlVector<SteamItemInstanceID_t> m_SelectedItems;
	CUtlVector<SteamItemInstanceID_t> m_AutoSelectedItems;
	CUtlVector<const struct RD_Crafting_Recipe_Variant *> m_FilteredVariants;
	SteamItemDef_t m_SelectedRecipeOutput;
	int m_iSelectedRecipe;
	int m_iLastFullInventoryUpdates;
};

namespace BaseModUI
{
	class CRD_Crafting_Recipe_Button : public BaseModHybridButton
	{
		DECLARE_CLASS_SIMPLE( CRD_Crafting_Recipe_Button, BaseModHybridButton );

	public:
		CRD_Crafting_Recipe_Button( CRD_Crafting_Panel *pParent, const char *szRecipeLabel, int iRecipeIndex );

		void ApplySchemeSettings( vgui::IScheme *pScheme ) override;
	};
}
