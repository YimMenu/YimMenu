#include "fiber_pool.hpp"
#include "services/mobile/mobile_service.hpp"
#include "util/mobile.hpp"
#include "views/view.hpp"
#include "core/data/clothes.hpp"

namespace big
{
	void view::outfit_editor(Ped ped_to_edit) 
	{
		components::sub_title("Clothes");
		
		if (ImGui::BeginCombo("###cloth_parts", clothes_strings[g->outfit_editor.componentId]))
		{
			for (int i = 0; i < clothes_strings.size(); i++)
			{
				components::selectable(clothes_strings[i], g->outfit_editor.componentId == i, [i, ped_to_edit] {
					g->outfit_editor.componentId = i;
					g->outfit_editor.drawableId = PED::GET_PED_DRAWABLE_VARIATION(ped_to_edit, i);
					g->outfit_editor.textureId = PED::GET_PED_TEXTURE_VARIATION(ped_to_edit, i);
					g->outfit_editor.paletteId = PED::GET_PED_PALETTE_VARIATION(ped_to_edit, i);
				});
			}
			ImGui::EndCombo();
		}
		
		if (ImGui::InputInt("Drawable Id", &g->outfit_editor.drawableId)) {
			g_fiber_pool->queue_job( [ped_to_edit] {
				PED::SET_PED_COMPONENT_VARIATION(ped_to_edit, g->outfit_editor.componentId, g->outfit_editor.drawableId, g->outfit_editor.textureId, g->outfit_editor.paletteId);
			});
		}

		if (ImGui::InputInt("Texture Id", &g->outfit_editor.textureId)) {
			g_fiber_pool->queue_job([ped_to_edit] {
				PED::SET_PED_COMPONENT_VARIATION(ped_to_edit, g->outfit_editor.componentId, g->outfit_editor.drawableId, g->outfit_editor.textureId, g->outfit_editor.paletteId);
			});
		}

		if (ImGui::InputInt("Palette Id", &g->outfit_editor.paletteId)) {
			g_fiber_pool->queue_job([ped_to_edit] {
				PED::SET_PED_COMPONENT_VARIATION(ped_to_edit, g->outfit_editor.componentId, g->outfit_editor.drawableId, g->outfit_editor.textureId, g->outfit_editor.paletteId);
			});
		}

		components::sub_title("Props");
		
		if (ImGui::BeginCombo("###prop_parts", clothes_props_strings[g->outfit_editor.propId]))
		{
			for (int i = 0; i < clothes_props_strings.size(); i++)
			{
				components::selectable(clothes_props_strings[i], g->outfit_editor.propId == i, [i, ped_to_edit] {
					g->outfit_editor.propId = i;
					g->outfit_editor.propDrawableId = PED::GET_PED_PROP_INDEX(ped_to_edit, i);
					g->outfit_editor.propTextureId = PED::GET_PED_PROP_TEXTURE_INDEX(ped_to_edit, i);
					});
			}
			ImGui::EndCombo();
		}

		if (ImGui::InputInt("Drawable Id ###prop_drawable_id", &g->outfit_editor.propDrawableId)) {
			g_fiber_pool->queue_job([ped_to_edit] {
				PED::SET_PED_PROP_INDEX(ped_to_edit, g->outfit_editor.propId, g->outfit_editor.propDrawableId, g->outfit_editor.propTextureId, true);
			});
		}

		if (ImGui::InputInt("Texture Id ###prop_texture_id", &g->outfit_editor.propTextureId)) {
			g_fiber_pool->queue_job([ped_to_edit] {
				PED::SET_PED_PROP_INDEX(ped_to_edit, g->outfit_editor.propId, g->outfit_editor.propDrawableId, g->outfit_editor.propTextureId, true);
			});
		}

	}
}
