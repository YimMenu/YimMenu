#include <imgui.h>
#include "fiber_pool.hpp"
#include "natives.hpp"
#include "gta\VehicleValues.h"
#include "script.hpp"
#include "gui/window/main/main_tabs.hpp"
#include "LSCTab.h"
//#include "helpers\NetworkHelper.h"

namespace big
{
    void lsc_tab::render_lsc_tab()
    {
        static Vehicle player_vehicle{};
        static std::vector<std::string> slot_display_names{};
        static std::map<int, int> owned_mods{};
        static std::map<int, std::vector<std::string>> mod_display_names{};
        static int selected_slot = -1;
        static bool can_tires_burst{}, tiresmoke{}, turbo{}, xenon{};
        static int primary_color{}, secondary_color{}, pearlescent{}, wheel_color{}, interior_color{}, dashboard_color{};
        g_fiber_pool->queue_job([]
            {
                if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), FALSE))
                {
                    if (player_vehicle != PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE))
                    {
                        if (!HUD::HAS_THIS_ADDITIONAL_TEXT_LOADED("MOD_MNU", 10))
                        {
                            HUD::CLEAR_ADDITIONAL_TEXT(10, TRUE);
                            HUD::REQUEST_ADDITIONAL_TEXT("MOD_MNU", 10);
                            script::get_current()->yield();
                        }

                        player_vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), FALSE);
                        can_tires_burst = !VEHICLE::GET_VEHICLE_TYRES_CAN_BURST(player_vehicle);
                        tiresmoke = VEHICLE::IS_TOGGLE_MOD_ON(player_vehicle, MOD_TIRESMOKE);
                        turbo = VEHICLE::IS_TOGGLE_MOD_ON(player_vehicle, MOD_TURBO);
                        xenon = VEHICLE::IS_TOGGLE_MOD_ON(player_vehicle, MOD_XENONHEADLIGHTS);
                        VEHICLE::GET_VEHICLE_COLOURS(player_vehicle, &primary_color, &secondary_color);
                        VEHICLE::GET_VEHICLE_EXTRA_COLOURS(player_vehicle, &pearlescent, &wheel_color);
                        VEHICLE::GET_VEHICLE_INTERIOR_COLOR_(player_vehicle, &interior_color);
                        VEHICLE::GET_VEHICLE_DASHBOARD_COLOR_(player_vehicle, &dashboard_color);
                        std::vector<std::string> dsp_names{};
                        for (int slot = MOD_SPOILERS; slot <= MOD_LIVERY; slot++)
                        {
                            int count = VEHICLE::GET_NUM_VEHICLE_MODS(player_vehicle, slot);
                            if (count > 0)
                            {
                                owned_mods[slot] = (VEHICLE::GET_VEHICLE_MOD(player_vehicle, selected_slot) + 1);
                                dsp_names.push_back(get_mod_slot_name(slot, player_vehicle));
                                std::vector<std::string> names;
                                for (int mod = -1; mod < count; mod++)
                                    names.push_back(get_mod_name(mod, slot, count, player_vehicle));
                                mod_display_names[slot] = names;
                            }
                            else
                            {
                                dsp_names.push_back("");
                            }
                        }
                        slot_display_names = dsp_names;
                    }
                }
                else if (!slot_display_names.empty())
                {
                    player_vehicle = NULL;
                    mod_display_names.clear();
                    slot_display_names.clear();
                }
            });

        if (!slot_display_names.empty())
        {
            if (ImGui::BeginTabItem("LSC"))
            {
                if (ImGui::Button("Max Vehicle"))
                {
                    g_fiber_pool->queue_job([]
                        {
                            Vehicle vehicle = PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false);
                            VEHICLE::SET_VEHICLE_MOD_KIT(vehicle, 0);
                            for (int i = 0; i < 50; i++)
                            {
                                VEHICLE::SET_VEHICLE_MOD(vehicle, i, VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, i) - 1, false);
                            }
                        });
                }
                ImGui::Separator();
                if (ImGui::Checkbox("Bulletproof Tires", &can_tires_burst))
                {
                    g_fiber_pool->queue_job([]
                        {
                            VEHICLE::SET_VEHICLE_TYRES_CAN_BURST(player_vehicle, !can_tires_burst);
                        });
                }
                ImGui::SameLine();
                if (ImGui::Checkbox("Tiresmoke", &tiresmoke))
                {
                    g_fiber_pool->queue_job([]
                        {
                            VEHICLE::TOGGLE_VEHICLE_MOD(player_vehicle, MOD_TIRESMOKE, tiresmoke);
                        });
                }
                ImGui::SameLine();
                if (ImGui::Checkbox("Turbo", &turbo))
                {
                    g_fiber_pool->queue_job([]
                        {
                            VEHICLE::TOGGLE_VEHICLE_MOD(player_vehicle, MOD_TURBO, turbo);
                        });
                }
                ImGui::SameLine();
                if (ImGui::Button("F1 Wheels"))
                {
                    g_fiber_pool->queue_job([]
                        {
                            VEHICLE::SET_VEHICLE_WHEEL_TYPE(player_vehicle, WHEEL_TYPE_F1);
                        });
                }
                ImGui::SameLine();
                if (ImGui::Checkbox("Xenon", &xenon))
                {
                    g_fiber_pool->queue_job([]
                        {
                            VEHICLE::TOGGLE_VEHICLE_MOD(player_vehicle, MOD_XENONHEADLIGHTS, xenon);
                        });
                }

                if (ImGui::ListBoxHeader("Slot", ImVec2(200, 200)))
                {
                    for (int slot = MOD_SPOILERS; slot <= MOD_LIVERY; slot++)
                    {
                        if (slot_display_names[slot].empty())
                            continue;
                        if (ImGui::Selectable(slot_display_names[slot].c_str(), slot == selected_slot))
                            selected_slot = slot;
                    }
                    ImGui::ListBoxFooter();
                }
                if (selected_slot != -1)
                {
                    ImGui::SameLine();
                    if (ImGui::ListBoxHeader("Mod", ImVec2(200, 200)))
                    {
                        for (int i = 0; i < mod_display_names[selected_slot].size(); i++)
                        {
                            if (mod_display_names[selected_slot][i].empty())
                                continue;

                            if (ImGui::Selectable(mod_display_names[selected_slot][i].c_str(), i == owned_mods[selected_slot]))
                            {
                                g_fiber_pool->queue_job([i]
                                    {
                                        NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(PED::GET_VEHICLE_PED_IS_IN(PLAYER::PLAYER_PED_ID(), false));

                                        owned_mods[selected_slot] = i;
                                        VEHICLE::SET_VEHICLE_MOD(player_vehicle, selected_slot, i - 1, false);
                                    });
                            }
                        }
                        ImGui::ListBoxFooter();
                    }
                }
                static int windowtint{};
                static char* windowtint_combo[] = { "None", "Black", "Dark", "Light" };
                if (ImGui::Combo("Window Tint", &windowtint, windowtint_combo, IM_ARRAYSIZE(windowtint_combo)))
                {
                    g_fiber_pool->queue_job([]
                        {
                            VEHICLE::SET_VEHICLE_WINDOW_TINT(player_vehicle, windowtint);
                        });
                }


                static int main_color{};
                ImGui::RadioButton("Primary Color", &main_color, 0);
                ImGui::SameLine();
                ImGui::RadioButton("Secondary Color", &main_color, 1);
                ImGui::BeginGroup();
                static int color_type{};
                if (ImGui::ListBoxHeader("##colors", ImVec2(200, 200)))
                {
                    if (ImGui::Selectable("Chrome", color_type == 0))
                        color_type = 0;
                    if (ImGui::Selectable("Classic", color_type == 1))
                        color_type = 1;
                    if (ImGui::Selectable("Matte", color_type == 2))
                        color_type = 2;
                    if (ImGui::Selectable("Metals", color_type == 3))
                        color_type = 3;
                    if (ImGui::Selectable("Pearlescent", color_type == 4))
                        color_type = 4;
                    if (ImGui::Selectable("Wheel Color", color_type == 5))
                        color_type = 5;
                    if (ImGui::Selectable("Interior Color", color_type == 6))
                        color_type = 6;
                    if (ImGui::Selectable("Dashboard Color", color_type == 7))
                        color_type = 7;
                    ImGui::ListBoxFooter();
                }
                static const char* classic_names[] = { "Black", "Carbon Black", "Graphite", "Anthracite Black", "Black Steel", "Dark Steel", "Silver", "Bluish Silver", "Rolled Steel", "Shadow SIlver", "Stone Silver", "Midnight Silver", "Cast Iron Silver", "Red", "Torino Red", "Formula Red", "Lava Red", "Blaze Red", "Grace Red", "Garnet Red", "Sunset Red", "Cabernet Red", "Wine Red", "Candy Red", "Hot Pink", "Pfister Pink", "Salmon Pink", "Sunrise Orange", "Orange", "Bright Orange", "Gold", "Bronze", "Yellow", "Race Yellow", "Dew Yellow", "Dark Green", "Racing Green", "Sea Green", "Olive Green", "Bright Green", "Gasoline Green", "Lime Green", "Midnight Blue", "Galaxy Blue", "Dark Blue", "Saxon Blue", "Blue", "Mariner Blue", "Harbor Blue", "Diamond Blue", "Surf Blue", "Nautical Blue", "Racing Blue", "Ultra Blue", "Light Blue", "Chocolate Brown", "Bison Brown", "Creek Brown", "Feltzer Brown", "Maple Brown", "Beechwood Brown", "Sienna Brown", "Saddle Brown", "Moss Brown", "Woodbeech Brown", "Straw Brown", "Sandy Brown", "Bleached Brown", "Schafter Purple", "Spinnaker Purple", "Midnight Purple", "Bright Purple", "Cream", "Ice White", "Frost White" };
                static int classic_ids[] = { COLOR_CLASSIC_BLACK, COLOR_CLASSIC_CARBON_BLACK, COLOR_CLASSIC_GRAPHITE, COLOR_CLASSIC_ANHRACITE_BLACK, COLOR_CLASSIC_BLACK_STEEL, COLOR_CLASSIC_DARK_STEEL, COLOR_CLASSIC_SILVER, COLOR_CLASSIC_BLUISH_SILVER, COLOR_CLASSIC_ROLLED_STEEL, COLOR_CLASSIC_SHADOW_SILVER, COLOR_CLASSIC_STONE_SILVER, COLOR_CLASSIC_MIDNIGHT_SILVER, COLOR_CLASSIC_CAST_IRON_SILVER, COLOR_CLASSIC_RED, COLOR_CLASSIC_TORINO_RED, COLOR_CLASSIC_FORMULA_RED, COLOR_CLASSIC_LAVA_RED, COLOR_CLASSIC_BLAZE_RED, COLOR_CLASSIC_GRACE_RED, COLOR_CLASSIC_GARNET_RED, COLOR_CLASSIC_SUNSET_RED, COLOR_CLASSIC_CABERNET_RED, COLOR_CLASSIC_WINE_RED, COLOR_CLASSIC_CANDY_RED, COLOR_CLASSIC_HOT_PINK, COLOR_CLASSIC_PFSITER_PINK, COLOR_CLASSIC_SALMON_PINK, COLOR_CLASSIC_SUNRISE_ORANGE, COLOR_CLASSIC_ORANGE, COLOR_CLASSIC_BRIGHT_ORANGE, COLOR_CLASSIC_GOLD, COLOR_CLASSIC_BRONZE, COLOR_CLASSIC_YELLOW, COLOR_CLASSIC_RACE_YELLOW, COLOR_CLASSIC_DEW_YELLOW, COLOR_CLASSIC_DARK_GREEN, COLOR_CLASSIC_RACING_GREEN, COLOR_CLASSIC_SEA_GREEN, COLOR_CLASSIC_OLIVE_GREEN, COLOR_CLASSIC_BRIGHT_GREEN, COLOR_CLASSIC_GASOLINE_GREEN, COLOR_CLASSIC_LIME_GREEN, COLOR_CLASSIC_MIDNIGHT_BLUE, COLOR_CLASSIC_GALAXY_BLUE, COLOR_CLASSIC_DARK_BLUE, COLOR_CLASSIC_SAXON_BLUE, COLOR_CLASSIC_BLUE, COLOR_CLASSIC_MARINER_BLUE, COLOR_CLASSIC_HARBOR_BLUE, COLOR_CLASSIC_DIAMOND_BLUE, COLOR_CLASSIC_SURF_BLUE, COLOR_CLASSIC_NAUTICAL_BLUE, COLOR_CLASSIC_RACING_BLUE, COLOR_CLASSIC_ULTRA_BLUE, COLOR_CLASSIC_LIGHT_BLUE, COLOR_CLASSIC_CHOCOLATE_BROWN, COLOR_CLASSIC_BISON_BROWN, COLOR_CLASSIC_CREEEN_BROWN, COLOR_CLASSIC_FELTZER_BROWN, COLOR_CLASSIC_MAPLE_BROWN, COLOR_CLASSIC_BEECHWOOD_BROWN, COLOR_CLASSIC_SIENNA_BROWN, COLOR_CLASSIC_SADDLE_BROWN, COLOR_CLASSIC_MOSS_BROWN, COLOR_CLASSIC_WOODBEECH_BROWN, COLOR_CLASSIC_STRAW_BROWN, COLOR_CLASSIC_SANDY_BROWN, COLOR_CLASSIC_BLEACHED_BROWN, COLOR_CLASSIC_SCHAFTER_PURPLE, COLOR_CLASSIC_SPINNAKER_PURPLE, COLOR_CLASSIC_MIDNIGHT_PURPLE, COLOR_CLASSIC_BRIGHT_PURPLE, COLOR_CLASSIC_CREAM, COLOR_CLASSIC_ICE_WHITE, COLOR_CLASSIC_FROST_WHITE };
                static const char* matte_names[] = { "Black", "Gray", "Light Gray", "Ice White", "Blue", "Dark Blue", "Midnight Blue", "Midnight Purple", "Shafter Purple", "Red", "Dark Red", "Orange", "Yellow", "Lime Green", "Green", "Forest Green", "Foliage Green", "Olive Drab", "Dark Earth", "Desert Tan" };
                static int matte_ids[] = { COLOR_MATTE_BLACK, COLOR_MATTE_GRAY, COLOR_MATTE_LIGHT_GRAY, COLOR_MATTE_ICE_WHITE, COLOR_MATTE_BLUE, COLOR_MATTE_DARK_BLUE, COLOR_MATTE_MIDNIGHT_BLUE, COLOR_MATTE_MIDNIGHT_PURPLE, COLOR_MATTE_SCHAFTER_PURPLE, COLOR_MATTE_RED, COLOR_MATTE_DARK_RED, COLOR_MATTE_ORANGE, COLOR_MATTE_YELLOW, COLOR_MATTE_LIME_GREEN, COLOR_MATTE_GREEN, COLOR_MATTE_FOREST_GREEN, COLOR_MATTE_FOLIAGE_GREEN, COLOR_MATTE_OLIVE_DARB, COLOR_MATTE_DARK_EARTH, COLOR_MATTE_DESERT_TAN };
                static const char* metal_names[] = { "Brushed Steel", "Brushed Black Steel", "Brushed Aluminium", "Pure Gold", "Brushed Gold" };
                static int metal_ids[] = { COLOR_METALS_BRUSHED_STEEL, COLOR_METALS_BRUSHED_BLACK_STEEL, COLOR_METALS_BRUSHED_ALUMINUM, COLOR_METALS_PURE_GOLD, COLOR_METALS_BRUSHED_GOLD };

                int color_check{};
                switch (color_type)
                {
                case 4:
                    color_check = pearlescent;
                    break;
                case 5:
                    color_check = wheel_color;
                    break;
                case 6:
                    color_check = interior_color;
                    break;
                case 7:
                    color_check = dashboard_color;
                    break;
                default:
                    color_check = (main_color == 0) ? primary_color : secondary_color;
                }
                ImGui::SameLine();
                if (ImGui::ListBoxHeader("##color", ImVec2(200, 200)))
                {
                    switch (color_type)
                    {
                    case 0: //Chrome
                    {
                        if (ImGui::Selectable("Chrome", color_check == COLOR_CHROME))
                        {
                            if (main_color == 0)
                                primary_color = COLOR_CHROME;
                            else
                                secondary_color = COLOR_CHROME;
                            g_fiber_pool->queue_job([]
                                {
                                    VEHICLE::SET_VEHICLE_COLOURS(player_vehicle, primary_color, secondary_color);
                                });
                        }
                        break;
                    }
                    case 1: //Classic
                    {
                        for (int i = 0; i < 74; i++)
                        {
                            if (ImGui::Selectable(classic_names[i], color_check == classic_ids[i]))
                            {
                                if (main_color == 0)
                                    primary_color = classic_ids[i];
                                else
                                    secondary_color = classic_ids[i];
                                g_fiber_pool->queue_job([]
                                    {
                                        VEHICLE::SET_VEHICLE_COLOURS(player_vehicle, primary_color, secondary_color);
                                    });
                            }
                        }
                        break;
                    }
                    case 2: //Matte
                    {
                        for (int i = 0; i < 20; i++)
                        {
                            if (ImGui::Selectable(matte_names[i], color_check == matte_ids[i]))
                            {
                                if (main_color == 0)
                                    primary_color = matte_ids[i];
                                else
                                    secondary_color = matte_ids[i];
                                g_fiber_pool->queue_job([]
                                    {
                                        VEHICLE::SET_VEHICLE_COLOURS(player_vehicle, primary_color, secondary_color);
                                    });
                            }
                        }
                        break;
                    }
                    case 3: //Metals
                    {
                        for (int i = 0; i < 5; i++)
                        {
                            if (ImGui::Selectable(metal_names[i], color_check == metal_ids[i]))
                            {
                                if (main_color == 0)
                                    primary_color = metal_ids[i];
                                else
                                    secondary_color = metal_ids[i];
                                g_fiber_pool->queue_job([]
                                    {
                                        VEHICLE::SET_VEHICLE_COLOURS(player_vehicle, primary_color, secondary_color);
                                    });
                            }
                        }
                        break;
                    }
                    case 4: //Pearlescent
                    {
                        for (int i = 0; i < 74; i++)
                        {
                            if (ImGui::Selectable(classic_names[i], color_check == classic_ids[i]))
                            {
                                pearlescent = classic_ids[i];
                                g_fiber_pool->queue_job([]
                                    {
                                        VEHICLE::SET_VEHICLE_EXTRA_COLOURS(player_vehicle, pearlescent, wheel_color);
                                    });
                            }
                        }
                        break;
                    }
                    case 5: //Wheel Color
                    {
                        for (int i = 0; i < 74; i++)
                        {
                            if (ImGui::Selectable(classic_names[i], color_check == classic_ids[i]))
                            {
                                wheel_color = classic_ids[i];
                                g_fiber_pool->queue_job([]
                                    {
                                        VEHICLE::SET_VEHICLE_EXTRA_COLOURS(player_vehicle, pearlescent, wheel_color);
                                    });
                            }
                        }
                        break;
                    }
                    case 6: //Interior Color
                    {
                        for (int i = 0; i < 74; i++)
                        {
                            if (ImGui::Selectable(classic_names[i], color_check == classic_ids[i]))
                            {
                                interior_color = classic_ids[i];
                                g_fiber_pool->queue_job([]
                                    {
                                        VEHICLE::SET_VEHICLE_INTERIOR_COLOR_(player_vehicle, interior_color);
                                    });
                            }
                        }
                        break;
                    }
                    case 7: //Dashboard Color
                    {
                        for (int i = 0; i < 74; i++)
                        {
                            if (ImGui::Selectable(classic_names[i], color_check == classic_ids[i]))
                            {
                                dashboard_color = classic_ids[i];
                                g_fiber_pool->queue_job([]
                                    {
                                        VEHICLE::SET_VEHICLE_DASHBOARD_COLOR_(player_vehicle, dashboard_color);
                                    });
                            }
                        }
                        break;
                    }
                    }
                    ImGui::ListBoxFooter();
                    ImGui::EndGroup();
                }

                ImGui::Separator();

                if (ImGui::CollapsingHeader("Custom Color"))
                {
                    ImGui::PushItemWidth(400);
                    static float color[3]{};
                    static int color_type{};
                    if (ImGui::ColorPicker3("Custom Vehicle Color", color, ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoDragDrop | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_DisplayHex))
                    {
                        g_fiber_pool->queue_job([]
                            {
                                switch (color_type)
                                {
                                case 0:
                                    VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(player_vehicle, (int)(color[0] * 255), (int)(color[1] * 255), (int)(color[2] * 255));
                                    break;
                                case 1:
                                    VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(player_vehicle, (int)(color[0] * 255), (int)(color[1] * 255), (int)(color[2] * 255));
                                    break;
                                case 2:
                                    VEHICLE::SET_VEHICLE_TYRE_SMOKE_COLOR(player_vehicle, (int)(color[0] * 255), (int)(color[1] * 255), (int)(color[2] * 255));
                                    break;
                                }
                            });
                    }
                    ImGui::SameLine();
                    ImGui::BeginGroup();
                    if (ImGui::RadioButton("Primary", &color_type, 0))
                    {
                        g_fiber_pool->queue_job([]
                            {
                                int color_get[3];
                                VEHICLE::GET_VEHICLE_CUSTOM_PRIMARY_COLOUR(player_vehicle, &color_get[0], &color_get[1], &color_get[2]);
                                color[0] = (float)color_get[0] / 255;
                                color[1] = (float)color_get[1] / 255;
                                color[2] = (float)color_get[2] / 255;
                            });
                    }
                    ImGui::SameLine();
                    if (ImGui::RadioButton("Secondary", &color_type, 1))
                    {
                        g_fiber_pool->queue_job([]
                            {
                                int color_get[3];
                                VEHICLE::GET_VEHICLE_CUSTOM_SECONDARY_COLOUR(player_vehicle, &color_get[0], &color_get[1], &color_get[2]);
                                color[0] = (float)color_get[0] / 255;
                                color[1] = (float)color_get[1] / 255;
                                color[2] = (float)color_get[2] / 255;
                            });
                    }
                    if (tiresmoke)
                    {
                        ImGui::SameLine();
                        if (ImGui::RadioButton("Tire Smoke", &color_type, 2))
                        {
                            g_fiber_pool->queue_job([]
                                {
                                    int color_get[3];
                                    VEHICLE::GET_VEHICLE_TYRE_SMOKE_COLOR(player_vehicle, &color_get[0], &color_get[1], &color_get[2]);
                                    color[0] = (float)color_get[0] / 255;
                                    color[1] = (float)color_get[1] / 255;
                                    color[2] = (float)color_get[2] / 255;
                                });
                        }
                    }
                    if (ImGui::Button("Remove Custom Color"))
                    {
                        g_fiber_pool->queue_job([]
                            {
                                VEHICLE::CLEAR_VEHICLE_CUSTOM_PRIMARY_COLOUR(player_vehicle);
                                VEHICLE::CLEAR_VEHICLE_CUSTOM_SECONDARY_COLOUR(player_vehicle);
                                VEHICLE::SET_VEHICLE_COLOURS(player_vehicle, primary_color, secondary_color);
                            });
                    }
                    ImGui::EndGroup();
                    ImGui::PopItemWidth();
                }
                ImGui::EndTabItem();
            }
        }
    }

    const char* lsc_tab::get_mod_slot_name(int mod_slot, Vehicle vehicle)
    {
        Hash model = ENTITY::GET_ENTITY_MODEL(vehicle);
        switch (mod_slot)
        {
        case MOD_HOOD:
            return HUD::GET_LABEL_TEXT_("CMOD_MOD_HOD");
        case MOD_ARMOR:
            return HUD::GET_LABEL_TEXT_("CMOD_MOD_ARM");
        case MOD_BRAKES:
            return HUD::GET_LABEL_TEXT_("CMOD_MOD_BRA");
        case MOD_ENGINE:
            return HUD::GET_LABEL_TEXT_("CMOD_MOD_ENG");
        case MOD_SUSPENSION:
            return HUD::GET_LABEL_TEXT_("CMOD_MOD_SUS");
        case MOD_TRANSMISSION:
            return HUD::GET_LABEL_TEXT_("CMOD_MOD_TRN");
        case MOD_HORNS:
            return HUD::GET_LABEL_TEXT_("CMOD_MOD_HRN");
        case MOD_FRONTWHEEL:
            if (!VEHICLE::IS_THIS_MODEL_A_BIKE(model) && VEHICLE::IS_THIS_MODEL_A_BICYCLE(model))
                return HUD::GET_LABEL_TEXT_("CMOD_MOD_WHEM");
            else
                return HUD::GET_LABEL_TEXT_("CMOD_WHE0_0");
        case MOD_REARWHEEL:
            return HUD::GET_LABEL_TEXT_("CMOD_WHE0_1");
            //Bennys
        case MOD_PLATEHOLDER:
            return HUD::GET_LABEL_TEXT_("CMM_MOD_S0");
        case MOD_VANITYPLATES:
            return HUD::GET_LABEL_TEXT_("CMM_MOD_S1");
        case MOD_TRIMDESIGN:
            if (model == VEHICLE_SULTANRS)
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S2b");
            else
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S2");
        case MOD_ORNAMENTS:
            return HUD::GET_LABEL_TEXT_("CMM_MOD_S3");
        case MOD_DASHBOARD:
            return HUD::GET_LABEL_TEXT_("CMM_MOD_S4");
        case MOD_DIALDESIGN:
            return HUD::GET_LABEL_TEXT_("CMM_MOD_S5");
        case MOD_DOORSPEAKERS:
            return HUD::GET_LABEL_TEXT_("CMM_MOD_S6");
        case MOD_SEATS:
            return HUD::GET_LABEL_TEXT_("CMM_MOD_S7");
        case MOD_STEERINGWHEELS:
            return HUD::GET_LABEL_TEXT_("CMM_MOD_S8");
        case MOD_COLUMNSHIFTERLEVERS:
            return HUD::GET_LABEL_TEXT_("CMM_MOD_S9");
        case MOD_PLAQUES:
            return HUD::GET_LABEL_TEXT_("CMM_MOD_S10");
        case MOD_SPEAKERS:
            return HUD::GET_LABEL_TEXT_("CMM_MOD_S11");
        case MOD_TRUNK:
            return HUD::GET_LABEL_TEXT_("CMM_MOD_S12");
        case MOD_HYDRAULICS:
            return HUD::GET_LABEL_TEXT_("CMM_MOD_S13");
        case MOD_ENGINEBLOCK:
            return HUD::GET_LABEL_TEXT_("CMM_MOD_S14");
        case MOD_AIRFILTER:
            if (model == VEHICLE_SULTANRS)
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S15b");
            else
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S15");
        case MOD_STRUTS:
            if (model == VEHICLE_SULTANRS || model == VEHICLE_BANSHEE2)
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S16b");
            else
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S16");
        case MOD_ARCHCOVER:
            if (model == VEHICLE_SULTANRS)
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S17b");
            else
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S17");
        case MOD_AERIALS:
            if (model == VEHICLE_SULTANRS)
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S18b");
            else if (model == VEHICLE_BTYPE3)
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S18c");
            else
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S18");
        case MOD_TRIM:
            if (model == VEHICLE_SULTANRS)
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S19b");
            else if (model == VEHICLE_BTYPE3)
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S19c");
            else if (model == VEHICLE_VIRGO2)
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S19d");
            else
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S19");
        case MOD_TANK:
            if (model == VEHICLE_SLAMVAN3)
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S27");
            else
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S20");
        case MOD_WINDOWS:
            if (model == VEHICLE_BTYPE3)
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S21b");
            else
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S21");
        case MOD_DOORS:
            if (model == VEHICLE_SLAMVAN3)
                return HUD::GET_LABEL_TEXT_("SLVAN3_RDOOR");
            else
                return HUD::GET_LABEL_TEXT_("CMM_MOD_S22");
        case MOD_LIVERY:
            return HUD::GET_LABEL_TEXT_("CMM_MOD_S23");
        default:
            auto name = VEHICLE::GET_MOD_SLOT_NAME(vehicle, mod_slot);
            if (name == nullptr)
                return "";
            if (strstr(name, "_"))
                return HUD::GET_LABEL_TEXT_(name);
            return name;
        }
    }

    static const std::map<int, const char*> horn_map = {
        {-1, "CMOD_HRN_0"}, {0, "CMOD_HRN_TRK"}, {1, "CMOD_HRN_COP"}, {2, "CMOD_HRN_CLO"}, {3, "CMOD_HRN_MUS1"}, {4, "CMOD_HRN_MUS2"}, {5, "CMOD_HRN_MUS3"},
        {6, "CMOD_HRN_MUS4"}, {7, "CMOD_HRN_MUS5"}, {8, "CMOD_HRN_SAD"}, {9, "HORN_CLAS1"}, {10, "HORN_CLAS2"},
        {11, "HORN_CLAS3"}, {12, "HORN_CLAS4"}, {13, "HORN_CLAS5"}, {14, "HORN_CLAS6"}, {15, "HORN_CLAS7"},
        {16, "HORN_CNOTE_C0"}, {17, "HORN_CNOTE_D0"}, {18, "HORN_CNOTE_E0"}, {19, "HORN_CNOTE_F0"}, {20, "HORN_CNOTE_G0"},
        {21, "HORN_CNOTE_A0"}, {22, "HORN_CNOTE_B0"}, {23, "HORN_CNOTE_C1"}, {24, "HORN_HIPS1"}, {25, "HORN_HIPS2"},
        {26, "HORN_HIPS3"}, {27, "HORN_HIPS4"}, {28, "HORN_INDI_1"}, {29, "HORN_INDI_2"}, {30, "HORN_INDI_3"},
        {31, "HORN_INDI_4"}, {32, "HORN_LUXE2"}, {33, "HORN_LUXE1"}, {34, "HORN_LUXE3"}, /*{35, "HORN_LUXE2"},
        {36, "HORN_LUXE1"}, {37, "HORN_LUXE3"},*/ {38, "HORN_HWEEN1"}, /*{39, "HORN_HWEEN1"},*/ {40, "HORN_HWEEN2"},
        /*{41, "HORN_HWEEN2"},*/ {42, "HORN_LOWRDER1"}, /*{43, "HORN_LOWRDER1"},*/ {44, "HORN_LOWRDER2"}, /*{45, "HORN_LOWRDER2"},*/
        {46, "HORN_XM15_1"}, {47, "HORN_XM15_2"}, {48, "HORN_XM15_3"}
    };

    const char* lsc_tab::get_mod_name(int mod, int mod_slot, int mod_count, Vehicle vehicle)
    {
        if (mod_count == 0)
            return "";
        if (mod < -1 || mod >= mod_count)
            return "";
        if (mod_slot == MOD_HORNS)
        {
            if (horn_map.find(mod) != horn_map.end())
            {
                return HUD::GET_LABEL_TEXT_(horn_map.find(mod)->second);
            }
            return "";
        }
        Hash model = ENTITY::GET_ENTITY_MODEL(vehicle);
        if (mod_slot == MOD_FRONTWHEEL || mod_slot == MOD_REARWHEEL)
        {
            if (mod == -1)
            {
                if (!VEHICLE::IS_THIS_MODEL_A_BIKE(model) && VEHICLE::IS_THIS_MODEL_A_BICYCLE(model))
                    return HUD::GET_LABEL_TEXT_("CMOD_WHE_0");
                else
                    return HUD::GET_LABEL_TEXT_("CMOD_WHE_B_0");
            }
            if (mod >= mod_count / 2)
                //return fmt::format("{} {}", HUD::GET_LABEL_TEXT_("CHROME"), HUD::GET_LABEL_TEXT_(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, mod_slot, mod))).c_str(); //Bug with FMT library? Returns Chrome Chrome...
                return fmt::format("Chrome {}", HUD::GET_LABEL_TEXT_(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, mod_slot, mod))).c_str();
            else
                return HUD::GET_LABEL_TEXT_(VEHICLE::GET_MOD_TEXT_LABEL(vehicle, mod_slot, mod));
        }

        switch (mod_slot)
        {
        case MOD_ARMOR:
            return HUD::GET_LABEL_TEXT_(fmt::format("CMOD_ARM_{}", (mod + 1)).c_str());
        case MOD_BRAKES:
            return HUD::GET_LABEL_TEXT_(fmt::format("CMOD_BRA_{}", (mod + 1)).c_str());
        case MOD_ENGINE:
            if (mod == -1)
                return HUD::GET_LABEL_TEXT_("CMOD_ARM_0");
            return HUD::GET_LABEL_TEXT_(fmt::format("CMOD_ENG_{}", (mod + 1)).c_str());
        case MOD_SUSPENSION:
            return HUD::GET_LABEL_TEXT_(fmt::format("CMOD_SUS_{}", (mod + 1)).c_str());
        case MOD_TRANSMISSION:
            return HUD::GET_LABEL_TEXT_(fmt::format("CMOD_GBX_{}", (mod + 1)).c_str());
        }
        if (mod > -1)
        {
            if (mod_slot == MOD_SIDESKIRT && VEHICLE::GET_NUM_VEHICLE_MODS(vehicle, MOD_SIDESKIRT) < 2)
            {
                return HUD::GET_LABEL_TEXT_("CMOD_SKI_1");
            }
            auto label = VEHICLE::GET_MOD_TEXT_LABEL(vehicle, mod_slot, mod);
            if (label == nullptr || strlen(label) == 0)
                return "MISSING_LABEL";
            return HUD::GET_LABEL_TEXT_(label);
        }
        else
        {
            switch (mod_slot)
            {
            case MOD_AIRFILTER:
                break;
            case MOD_STRUTS:
                switch (model)
                {
                case VEHICLE_BANSHEE:
                case VEHICLE_BANSHEE2:
                case VEHICLE_SULTANRS:
                    return HUD::GET_LABEL_TEXT_("CMOD_COL5_41");
                }
                break;

            }
            return HUD::GET_LABEL_TEXT_("CMOD_DEF_0");
        }
    }
}