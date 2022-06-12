//Code from https://github.com/RIPmr/MoonEngine/blob/master/ToyBox/ImPie.cpp
#pragma once
#include <imgui.h>
#include <imgui_internal.h>

namespace ImGui {
	struct PieMenuContext {
		static const int	c_iMaxPieMenuStack = 8;
		static const int	c_iMaxPieItemCount = 12;
		static const int	c_iRadiusEmpty = 20;
		static const int	c_iRadiusMin = 30;
		static const int	c_iMinItemCount = 3;
		static const int	c_iMinItemCountPerLevel = 3;

		struct PieMenu {
			int				m_iCurrentIndex;
			float			m_fMaxItemSqrDiameter;
			float			m_fLastMaxItemSqrDiameter;
			int				m_iHoveredItem;
			int				m_iLastHoveredItem;
			int				m_iClickedItem;
			bool			m_oItemIsSubMenu[c_iMaxPieItemCount];
			ImVector<char>	m_oItemNames[c_iMaxPieItemCount];
			ImVec2			m_oItemSizes[c_iMaxPieItemCount];
		};

		PieMenuContext() {
			m_iCurrentIndex = -1;
			m_iLastFrame = 0;
		}

		PieMenu				m_oPieMenuStack[c_iMaxPieMenuStack];
		int					m_iCurrentIndex;
		int					m_iMaxIndex;
		int					m_iLastFrame;
		ImVec2				m_oCenter;
		int					m_iMouseButton;
		bool				m_bClose;
	};

	static PieMenuContext s_oPieMenuContext;

	bool IsPiePopupOpen(const char* pName) {
		ImGuiContext& g = *GImGui;
		return g.OpenPopupStack.Size > g.BeginPopupStack.Size && g.OpenPopupStack[g.BeginPopupStack.Size].PopupId == g.CurrentWindow->GetID(pName);
	}

	void BeginPieMenuEx() {
		IM_ASSERT(s_oPieMenuContext.m_iCurrentIndex < PieMenuContext::c_iMaxPieMenuStack);

		++s_oPieMenuContext.m_iCurrentIndex;
		++s_oPieMenuContext.m_iMaxIndex;

		PieMenuContext::PieMenu& oPieMenu = s_oPieMenuContext.m_oPieMenuStack[s_oPieMenuContext.m_iCurrentIndex];
		oPieMenu.m_iCurrentIndex = 0;
		oPieMenu.m_fMaxItemSqrDiameter = 0.f;
		if (!ImGui::IsMouseReleased(s_oPieMenuContext.m_iMouseButton))
			oPieMenu.m_iHoveredItem = -1;
		if (s_oPieMenuContext.m_iCurrentIndex > 0)
			oPieMenu.m_fMaxItemSqrDiameter = s_oPieMenuContext.m_oPieMenuStack[s_oPieMenuContext.m_iCurrentIndex - 1].m_fMaxItemSqrDiameter;
	}

	void EndPieMenuEx() {
		IM_ASSERT(s_oPieMenuContext.m_iCurrentIndex >= 0);
		PieMenuContext::PieMenu& oPieMenu = s_oPieMenuContext.m_oPieMenuStack[s_oPieMenuContext.m_iCurrentIndex];

		--s_oPieMenuContext.m_iCurrentIndex;
	}

	bool BeginPiePopup(const char* pName, int iMouseButton) {
		if (IsPiePopupOpen(pName)) {
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 250));
			ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0, 0, 0, 250));
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 0.0f);

			ImVec2 oDisplaySize = ImGui::GetIO().DisplaySize;

			s_oPieMenuContext.m_iMouseButton = iMouseButton;
			s_oPieMenuContext.m_bClose = false;

			//ImGui::SetNextWindowPos(ImVec2(-100.f, -100.f), ImGuiSetCond_Appearing);
			ImGui::SetNextWindowPos(ImVec2(-100.f, -100.f));
			bool bOpened = ImGui::BeginPopup(pName);
			if (bOpened) {
				int iCurrentFrame = ImGui::GetFrameCount();
				if (s_oPieMenuContext.m_iLastFrame < (iCurrentFrame - 1)) {
					s_oPieMenuContext.m_oCenter = ImGui::GetIO().MousePos;
				}
				s_oPieMenuContext.m_iLastFrame = iCurrentFrame;

				s_oPieMenuContext.m_iMaxIndex = -1;
				BeginPieMenuEx();

				return true;
			}
			else {
				ImGui::End();
				ImGui::PopStyleColor(2);
				ImGui::PopStyleVar(2);
			}
		}
		return false;
	}

	void EndPiePopup() {
		EndPieMenuEx();

		ImGuiStyle& oStyle = ImGui::GetStyle();

		ImDrawList* pDrawList = ImGui::GetWindowDrawList();
		pDrawList->PushClipRectFullScreen();

		const ImVec2 oMousePos = ImGui::GetIO().MousePos;
		const ImVec2 oDragDelta = ImVec2(oMousePos.x - s_oPieMenuContext.m_oCenter.x, oMousePos.y - s_oPieMenuContext.m_oCenter.y);
		const float fDragDistSqr = oDragDelta.x * oDragDelta.x + oDragDelta.y * oDragDelta.y;

		float fCurrentRadius = (float)PieMenuContext::c_iRadiusEmpty;

		ImRect oArea = ImRect(s_oPieMenuContext.m_oCenter, s_oPieMenuContext.m_oCenter);

		bool bItemHovered = false;

		const int	subdiv = 2;
		const float c_fDefaultRotate = -IM_PI / 2.f;
		float fLastRotate = c_fDefaultRotate;
		for (int iIndex = 0; iIndex <= s_oPieMenuContext.m_iMaxIndex; ++iIndex) {
			PieMenuContext::PieMenu& oPieMenu = s_oPieMenuContext.m_oPieMenuStack[iIndex];

			float fMenuHeight = sqrt(oPieMenu.m_fMaxItemSqrDiameter);

			const float fMinRadius = fCurrentRadius;
			//const float fMaxRadius = fMinRadius + (fMenuHeight * oPieMenu.m_iCurrentIndex) / (3.f);
			const float fMaxRadius = fMinRadius + fMenuHeight + (!iIndex ? 12.0f : iIndex * 6.0f);

			const float item_arc_span = 2 * IM_PI / ImMax(PieMenuContext::c_iMinItemCount + PieMenuContext::c_iMinItemCountPerLevel * iIndex, oPieMenu.m_iCurrentIndex);
			float drag_angle = atan2f(oDragDelta.y, oDragDelta.x);

			float fRotate = fLastRotate - item_arc_span * (oPieMenu.m_iCurrentIndex - 1.f) / 2.f;
			int item_hovered = -1;
			for (int item_n = 0; item_n < oPieMenu.m_iCurrentIndex; item_n++) {
				const char* item_label = oPieMenu.m_oItemNames[item_n].Data;
				const float inner_spacing = oStyle.ItemInnerSpacing.x / fMinRadius / 2;
				const float fMinInnerSpacing = oStyle.ItemInnerSpacing.x / (fMinRadius * 2.f);
				const float fMaxInnerSpacing = oStyle.ItemInnerSpacing.x / (fMaxRadius * 2.f);
				const float item_inner_ang_min = item_arc_span * (item_n - 0.5f + fMinInnerSpacing) + fRotate;
				const float item_inner_ang_max = item_arc_span * (item_n + 0.5f - fMinInnerSpacing) + fRotate;
				const float item_outer_ang_min = item_arc_span * (item_n - 0.5f + fMaxInnerSpacing) + fRotate;
				const float item_outer_ang_max = item_arc_span * (item_n + 0.5f - fMaxInnerSpacing) + fRotate;

				bool hovered = false;
				if (fDragDistSqr >= fMinRadius * fMinRadius && fDragDistSqr < fMaxRadius * fMaxRadius) {
					while ((drag_angle - item_inner_ang_min) < 0.f)
						drag_angle += 2.f * IM_PI;
					while ((drag_angle - item_inner_ang_min) > 2.f * IM_PI)
						drag_angle -= 2.f * IM_PI;

					if (drag_angle >= item_inner_ang_min && drag_angle < item_inner_ang_max) {
						hovered = true;
						bItemHovered = !oPieMenu.m_oItemIsSubMenu[item_n];
					}
				}

				int arc_segments = (int)(32 * subdiv * item_arc_span / (2 * IM_PI)) + 1;

				ImU32 iColor = hovered ? ImColor(100, 100, 150) : ImColor(70, 70, 70);
				iColor = ImGui::GetColorU32(hovered ? ImGuiCol_HeaderHovered : ImGuiCol_FrameBg);
				//iColor = ImGui::GetColorU32(hovered ? ImGuiCol_Button : ImGuiCol_ButtonHovered);
				//iColor |= 0xFF000000;

				const float fAngleStepInner = (item_inner_ang_max - item_inner_ang_min) / arc_segments;
				const float fAngleStepOuter = (item_outer_ang_max - item_outer_ang_min) / arc_segments;
				pDrawList->PrimReserve(arc_segments * 6, (arc_segments + 1) * 2);
				for (int iSeg = 0; iSeg <= arc_segments; ++iSeg) {
					float fCosInner = cosf(item_inner_ang_min + fAngleStepInner * iSeg);
					float fSinInner = sinf(item_inner_ang_min + fAngleStepInner * iSeg);
					float fCosOuter = cosf(item_outer_ang_min + fAngleStepOuter * iSeg);
					float fSinOuter = sinf(item_outer_ang_min + fAngleStepOuter * iSeg);

					if (iSeg < arc_segments) {
						pDrawList->PrimWriteIdx(pDrawList->_VtxCurrentIdx + 0);
						pDrawList->PrimWriteIdx(pDrawList->_VtxCurrentIdx + 2);
						pDrawList->PrimWriteIdx(pDrawList->_VtxCurrentIdx + 1);
						pDrawList->PrimWriteIdx(pDrawList->_VtxCurrentIdx + 3);
						pDrawList->PrimWriteIdx(pDrawList->_VtxCurrentIdx + 2);
						pDrawList->PrimWriteIdx(pDrawList->_VtxCurrentIdx + 1);
					}
					pDrawList->PrimWriteVtx(ImVec2(s_oPieMenuContext.m_oCenter.x + fCosInner * (fMinRadius + oStyle.ItemInnerSpacing.x), s_oPieMenuContext.m_oCenter.y + fSinInner * (fMinRadius + oStyle.ItemInnerSpacing.x)), ImVec2(0.f, 0.f), iColor);
					pDrawList->PrimWriteVtx(ImVec2(s_oPieMenuContext.m_oCenter.x + fCosOuter * (fMaxRadius - oStyle.ItemInnerSpacing.x), s_oPieMenuContext.m_oCenter.y + fSinOuter * (fMaxRadius - oStyle.ItemInnerSpacing.x)), ImVec2(0.f, 0.f), iColor);
				}

				float fRadCenter = (item_arc_span * item_n) + fRotate;
				ImVec2 oOuterCenter = ImVec2(s_oPieMenuContext.m_oCenter.x + cosf(fRadCenter) * fMaxRadius, s_oPieMenuContext.m_oCenter.y + sinf(fRadCenter) * fMaxRadius);
				oArea.Add(oOuterCenter);

				if (oPieMenu.m_oItemIsSubMenu[item_n]) {
					ImVec2 oTrianglePos[3];

					float fRadLeft = fRadCenter - 5.f / fMaxRadius;
					float fRadRight = fRadCenter + 5.f / fMaxRadius;

					oTrianglePos[0].x = s_oPieMenuContext.m_oCenter.x + cosf(fRadCenter) * (fMaxRadius - 5.f);
					oTrianglePos[0].y = s_oPieMenuContext.m_oCenter.y + sinf(fRadCenter) * (fMaxRadius - 5.f);
					oTrianglePos[1].x = s_oPieMenuContext.m_oCenter.x + cosf(fRadLeft) * (fMaxRadius - 10.f);
					oTrianglePos[1].y = s_oPieMenuContext.m_oCenter.y + sinf(fRadLeft) * (fMaxRadius - 10.f);
					oTrianglePos[2].x = s_oPieMenuContext.m_oCenter.x + cosf(fRadRight) * (fMaxRadius - 10.f);
					oTrianglePos[2].y = s_oPieMenuContext.m_oCenter.y + sinf(fRadRight) * (fMaxRadius - 10.f);

					pDrawList->AddTriangleFilled(oTrianglePos[0], oTrianglePos[1], oTrianglePos[2], ImColor(255, 255, 255));
				}

				ImVec2 text_size = oPieMenu.m_oItemSizes[item_n];
				ImVec2 text_pos = ImVec2(
					s_oPieMenuContext.m_oCenter.x + cosf((item_inner_ang_min + item_inner_ang_max) * 0.5f) * (fMinRadius + fMaxRadius) * 0.5f - text_size.x * 0.5f,
					s_oPieMenuContext.m_oCenter.y + sinf((item_inner_ang_min + item_inner_ang_max) * 0.5f) * (fMinRadius + fMaxRadius) * 0.5f - text_size.y * 0.5f
				);
				pDrawList->AddText(text_pos, ImColor(255, 255, 255), item_label);

				if (hovered) item_hovered = item_n;
			}

			fCurrentRadius = fMaxRadius;

			oPieMenu.m_fLastMaxItemSqrDiameter = oPieMenu.m_fMaxItemSqrDiameter;

			oPieMenu.m_iHoveredItem = item_hovered;

			if (fDragDistSqr >= fMaxRadius * fMaxRadius)
				item_hovered = oPieMenu.m_iLastHoveredItem;

			oPieMenu.m_iLastHoveredItem = item_hovered;

			fLastRotate = item_arc_span * oPieMenu.m_iLastHoveredItem + fRotate;
			if (item_hovered == -1 || !oPieMenu.m_oItemIsSubMenu[item_hovered])
				break;
		}

		pDrawList->PopClipRect();

		if (oArea.Min.x < 0.f) {
			s_oPieMenuContext.m_oCenter.x = (s_oPieMenuContext.m_oCenter.x - oArea.Min.x);
		}
		if (oArea.Min.y < 0.f) {
			s_oPieMenuContext.m_oCenter.y = (s_oPieMenuContext.m_oCenter.y - oArea.Min.y);
		}

		ImVec2 oDisplaySize = ImGui::GetIO().DisplaySize;
		if (oArea.Max.x > oDisplaySize.x) {
			s_oPieMenuContext.m_oCenter.x = (s_oPieMenuContext.m_oCenter.x - oArea.Max.x) + oDisplaySize.x;
		}
		if (oArea.Max.y > oDisplaySize.y) {
			s_oPieMenuContext.m_oCenter.y = (s_oPieMenuContext.m_oCenter.y - oArea.Max.y) + oDisplaySize.y;
		}

		if (s_oPieMenuContext.m_bClose ||
			(!bItemHovered && ImGui::IsMouseReleased(s_oPieMenuContext.m_iMouseButton))) {
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
		ImGui::PopStyleColor(2);
		ImGui::PopStyleVar(2);
	}

	bool BeginPieMenu(const char* pName, bool bEnabled = true) {
		IM_ASSERT(s_oPieMenuContext.m_iCurrentIndex >= 0 && s_oPieMenuContext.m_iCurrentIndex < PieMenuContext::c_iMaxPieItemCount);

		PieMenuContext::PieMenu& oPieMenu = s_oPieMenuContext.m_oPieMenuStack[s_oPieMenuContext.m_iCurrentIndex];

		ImVec2 oTextSize = ImGui::CalcTextSize(pName, NULL, true);
		oPieMenu.m_oItemSizes[oPieMenu.m_iCurrentIndex] = oTextSize;

		float fSqrDiameter = oTextSize.x * oTextSize.x + oTextSize.y * oTextSize.y;

		if (fSqrDiameter > oPieMenu.m_fMaxItemSqrDiameter) {
			oPieMenu.m_fMaxItemSqrDiameter = fSqrDiameter;
		}

		oPieMenu.m_oItemIsSubMenu[oPieMenu.m_iCurrentIndex] = true;

		int iLen = strlen(pName);
		ImVector<char>& oName = oPieMenu.m_oItemNames[oPieMenu.m_iCurrentIndex];
		oName.resize(iLen + 1);
		oName[iLen] = '\0';
		memcpy(oName.Data, pName, iLen);

		if (oPieMenu.m_iLastHoveredItem == oPieMenu.m_iCurrentIndex) {
			++oPieMenu.m_iCurrentIndex;

			BeginPieMenuEx();
			return true;
		}
		++oPieMenu.m_iCurrentIndex;

		return false;
	}

	void EndPieMenu() {
		IM_ASSERT(s_oPieMenuContext.m_iCurrentIndex >= 0 && s_oPieMenuContext.m_iCurrentIndex < PieMenuContext::c_iMaxPieItemCount);
		--s_oPieMenuContext.m_iCurrentIndex;
	}

	bool PieMenuItem(const char* pName, bool bEnabled = true) {
		IM_ASSERT(s_oPieMenuContext.m_iCurrentIndex >= 0 && s_oPieMenuContext.m_iCurrentIndex < PieMenuContext::c_iMaxPieItemCount);

		PieMenuContext::PieMenu& oPieMenu = s_oPieMenuContext.m_oPieMenuStack[s_oPieMenuContext.m_iCurrentIndex];

		ImVec2 oTextSize = ImGui::CalcTextSize(pName, NULL, true);
		oPieMenu.m_oItemSizes[oPieMenu.m_iCurrentIndex] = oTextSize;

		float fSqrDiameter = oTextSize.x * oTextSize.x + oTextSize.y * oTextSize.y;

		if (fSqrDiameter > oPieMenu.m_fMaxItemSqrDiameter) {
			oPieMenu.m_fMaxItemSqrDiameter = fSqrDiameter;
		}

		oPieMenu.m_oItemIsSubMenu[oPieMenu.m_iCurrentIndex] = false;

		int iLen = strlen(pName);
		ImVector<char>& oName = oPieMenu.m_oItemNames[oPieMenu.m_iCurrentIndex];
		oName.resize(iLen + 1);
		oName[iLen] = '\0';
		memcpy(oName.Data, pName, iLen);

		bool bActive = oPieMenu.m_iCurrentIndex == oPieMenu.m_iHoveredItem;
		++oPieMenu.m_iCurrentIndex;

		if (bActive) s_oPieMenuContext.m_bClose = true;
		return bActive;
	}
}