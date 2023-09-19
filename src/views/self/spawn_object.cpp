#include "natives.hpp"
#include "pointers.hpp"
#include "script.hpp"
#include "services/context_menu/context_menu_service.hpp"
#include "util/entity.hpp"
#include "util/strings.hpp"
#include "util/world_model.hpp"
#include "views/view.hpp"

#include <chrono>
#include <ctime>
#include <sstream>

std::string getFriendlyTime(const std::chrono::system_clock::time_point& timePoint)
{
	std::time_t t = std::chrono::system_clock::to_time_t(timePoint);
	std::tm* now  = std::localtime(&t);

	std::ostringstream oss;
	// oss << (now->tm_year + 1900) << "-" << (now->tm_mon + 1) << "-" << now->tm_mday << " ";
	oss << now->tm_hour << ":" << now->tm_min << ":" << now->tm_sec;

	return oss.str();
}
std::string getFriendlyTimeRightNow()
{
	return getFriendlyTime(std::chrono::system_clock::now());
}

using json = nlohmann::json;

// https://gtaforums.com/topic/801074-list-of-entity-bone-index-hashes/
const char* boneCenter[] = {"BONETAG_PELVIS", "BONETAG_SPINE_ROOT", "BONETAG_SPINE", "BONETAG_SPINE1", "BONETAG_SPINE2", "BONETAG_SPINE3", "BONETAG_NECK", "BONETAG_HEAD"};
const char* boneSideways[] = {"THIGH", "CALF", "FOOT", "PH_FOOT", "CLAVICLE", "UPPERARM", "FOREARM", "HAND", "FINGER0", "FINGER01", "FINGER02", "FINGER1", "FINGER11", "FINGER12", "FINGER2", "FINGER21", "FINGER22", "FINGER3", "FINGER31", "FINGER32", "FINGER4", "FINGER41", "FINGER42", "PH_HAND"};

int getBoneIndex(Entity& entity, const char* boneStr, bool isLeftSide)
{
	if (startsWithPrefix(boneStr, "BONE"))
		return ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(entity, boneStr);
	else
	{
		std::string bone("BONETAG");
		bone += (isLeftSide ? "_L_" : "_R_") + std::string(boneStr);
		return ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(entity, bone.c_str());
	}
}

namespace spawnObjs
{
	enum SelectedEntityTypeForSpawnedObjs
	{
		SelectedEntityTypeSelfPed,
		SelectedEntityTypeContextMenuEntity
	};

	struct SavedObj
	{
		std::string name, objName;
	};

	struct SpawnedObject
	{
		std::string objName;
		float x, y, z;
		float xr, yr, zr;
		float pitch, roll, yaw;
		bool isAttached;
		bool isLeftAttached;
		std::string bone;
		float xa, ya, za, rxa, rya, rza;
		Object ob;
	};

	struct Collection
	{
		std::string name;
		std::vector<SpawnedObject> objects;
	};

	struct SpawnedCollection
	{
		std::string name;
		std::vector<Object> objects;
	};

	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SavedObj, name, objName);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(SpawnedObject, objName, xr, yr, zr, pitch, roll, yaw, isAttached, isLeftAttached, bone, xa, ya, za, rxa, rya, rza);
	NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Collection, name, objects);

	inline SpawnedObject* currentSpawnedObj     = NULL;
	inline int selectedEntityTypeForSpawnedObjs = SelectedEntityTypeSelfPed;

	Entity getSelectedEntity()
	{
		if (selectedEntityTypeForSpawnedObjs == SelectedEntityTypeContextMenuEntity)
		{
			bool cond1 = big::g_context_menu_service->m_handle && ENTITY::DOES_ENTITY_EXIST(big::g_context_menu_service->m_handle)
			    && big::g_context_menu_service->m_pointer,
			     cond2;
			if (cond1)
			{
				auto modelType = big::g_context_menu_service->m_pointer->m_model_info->m_model_type;
				cond2          = modelType == eModelType::Ped;
			}

			if (cond1 && cond2)
				return big::g_context_menu_service->m_handle;
		}

		return self::ped;
	}

	std::filesystem::path getSavedObjFilePath()
	{
		return big::g_file_manager.get_project_file("savedObjects.json").get_path();
	}
	std::filesystem::path getSavedCollFilePath()
	{
		return big::g_file_manager.get_project_file("savedObjectCollections.json").get_path();
	}

	void loadSavedObjects(std::map<std::string, std::string>& list)
	{
		auto savedObjFilePath = getSavedObjFilePath();
		list.clear();
		try
		{
			if (std::filesystem::exists(savedObjFilePath))
			{
				std::ifstream f(savedObjFilePath);
				if (f.is_open())
				{
					std::vector<SavedObj> savedObjects = json::parse(f);
					for (const auto& p : savedObjects)
						list[p.objName] = p.name;
					f.close();
				}
			}
		}
		catch (std::exception e)
		{
			LOG(WARNING) << "Failed" << e.what();
		}
	}

	void saveObject(std::map<std::string, std::string>& list)
	{
		if (list.size() == 0)
			return;

		auto savedObjFilePath = getSavedObjFilePath();

		try
		{
			std::vector<SavedObj> savedObjects;

			for (const auto& pair : list)
			{
				SavedObj obj = {pair.second, pair.first};
				savedObjects.push_back(obj);
			}

			json j = savedObjects;

			std::ofstream o(savedObjFilePath);
			if (o.is_open())
			{
				o << std::setw(4) << j << std::endl;
				o.close();
			}
		}
		catch (std::exception e)
		{
			LOG(WARNING) << "Failed" << e.what();
		}
	}

	void loadSavedCollections(std::map<std::string, std::vector<SpawnedObject>>& list)
	{
		auto savedFilePath = getSavedCollFilePath();
		list.clear();
		try
		{
			if (std::filesystem::exists(savedFilePath))
			{
				std::ifstream f(savedFilePath);
				if (f.is_open())
				{
					std::vector<Collection> objs = json::parse(f);
					for (const auto& p : objs)
						list[p.name] = p.objects;
					f.close();
				}
			}
		}
		catch (std::exception e)
		{
			LOG(WARNING) << "Failed" << e.what();
		}
	}

	void saveCollection(std::map<std::string, std::vector<SpawnedObject>>& list)
	{
		auto savedFilePath = getSavedCollFilePath();

		try
		{
			std::vector<Collection> objs;

			for (const auto& pair : list)
			{
				Collection obj = {pair.first, pair.second};
				objs.push_back(obj);
			}

			json j = objs;

			std::ofstream o(savedFilePath);
			if (o.is_open())
			{
				o << std::setw(4) << j << std::endl;
				o.close();
			}
		}
		catch (std::exception e)
		{
			LOG(WARNING) << "Failed" << e.what();
		}
	}

	void loadObjList(std::vector<std::string>& objectList)
	{
		try
		{
			auto objectListPath = big::g_file_manager.get_project_file("ObjectList.ini").get_path();

			if (std::filesystem::exists(objectListPath))
			{
				std::ifstream f(objectListPath);

				if (f.is_open())
				{
					std::string line;
					while (std::getline(f, line))
						objectList.push_back(line);
					f.close();
				}
			}
			else
				big::g_notification_service->push_warning("objectList", "Please download the appropriate json and put it in the mod directory.");
		}
		catch (std::exception e)
		{
			LOG(WARNING) << "Failed fetching all scenarios: " << e.what();
		}
	}

	SpawnedObject spawnObj(std::string objStr, SpawnedObject ob1 = SpawnedObject())
	{
		rage::joaat_t objectHash = isHexadecimal(objStr) ? std::stoul(objStr, nullptr, 16) : rage::joaat(objStr);
		Entity entity            = getSelectedEntity();

		Vector3 location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(entity, 0, 1.f, 0);
		Object ob        = big::world_model::spawn(objectHash, location, *big::g_pointers->m_gta.m_is_session_started);
		OBJECT::PLACE_OBJECT_ON_GROUND_OR_OBJECT_PROPERLY(ob);
		location = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ob, 0, 0, 0);

		// LOG(WARNING) << "Object spawned" << objStr << " " << ob;

		ob1.objName = objStr;
		ob1.x       = location.x;
		ob1.y       = location.y;
		ob1.z       = location.z;
		ob1.ob      = ob;

		if (ob1.xr || ob1.yr || ob1.zr)
			ENTITY::SET_ENTITY_COORDS(ob, ob1.x + ob1.xr, ob1.y + ob1.yr, ob1.z + ob1.zr, 0, 0, 0, 1);
		if (ob1.pitch || ob1.roll || ob1.yaw)
			ENTITY::SET_ENTITY_ROTATION(spawnObjs::currentSpawnedObj->ob, ob1.pitch, ob1.roll, ob1.yaw, 0, 1);
		if (ob1.isAttached)
			ENTITY::ATTACH_ENTITY_TO_ENTITY(ob1.ob, entity, getBoneIndex(entity, ob1.bone.c_str(), ob1.isLeftAttached), ob1.xa, ob1.ya, ob1.za, ob1.rxa, ob1.rya, ob1.rza, 1, 0, 0, 0, 0, 1, 0);

		return ob1;
	}
}

namespace big
{
	void view::spawn_objects()
	{
		static std::vector<std::string> objectList;

		static std::string selectedObjectNameOrHash, searchObjectText, customObjectName, searchSavedObjectText, savedObjectToDelete;
		static std::map<std::string, std::string> savedObjectList;

		ImGui::BeginGroup();

		ImGui::SeparatorText("Select Entity");

		ImGui::RadioButton("Current player", &spawnObjs::selectedEntityTypeForSpawnedObjs, static_cast<int>(spawnObjs::SelectedEntityTypeSelfPed));
		ImGui::SameLine();
		ImGui::RadioButton("Context menu ped/player", &spawnObjs::selectedEntityTypeForSpawnedObjs, static_cast<int>(spawnObjs::SelectedEntityTypeContextMenuEntity));

		ImGui::PushItemWidth(200);
		components::input_text_with_hint("##searchObj", "search", searchObjectText);
		ImGui::SameLine();
		components::button("load objects list", [&] {
			spawnObjs::loadObjList(objectList);
		});

		if (ImGui::BeginListBox("##objectList", {400, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.4)}))
		{
			std::vector<std::string> objs = searchObjectText.length() > 0 ? filterStrings(objectList, searchObjectText) : objectList;

			for (auto element : objs)
				if (ImGui::Selectable(element.c_str(), selectedObjectNameOrHash == element))
					selectedObjectNameOrHash = element;

			ImGui::EndListBox();
		}

		ImGui::SeparatorText("Save objects");

		ImGui::PushItemWidth(200);
		components::small_text("selcted/pasted object name or hash");
		components::input_text_with_hint("##selectedObjec", "selectedObjectNameOrHash", selectedObjectNameOrHash);
		components::small_text("custom name you want to give to the object");
		components::input_text_with_hint("##customObjectName", "customObjectName", customObjectName);
		components::button("save###saveObjectBtn", [&] {
			std::string name    = trimString(selectedObjectNameOrHash);
			std::string newName = trimString(customObjectName);

			if (name.size() > 0 && newName.size() > 0)
			{
				if (savedObjectList.size() == 0)
					spawnObjs::loadSavedObjects(savedObjectList);
				savedObjectList[name] = newName;
				spawnObjs::saveObject(savedObjectList);
			}
		});

		ImGui::SeparatorText("Saved Object List");

		components::input_text_with_hint("##searchSavedObjectText", "searchSavedObjectText", searchSavedObjectText);
		ImGui::SameLine();
		components::button("load saved obj list", [&] {
			spawnObjs::loadSavedObjects(savedObjectList);
		});

		if (ImGui::BeginListBox("##savedObjectList", {400, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.4)}))
		{
			std::map<std::string, std::string> objs = searchSavedObjectText.length() > 0 ? filterStrings(savedObjectList, searchSavedObjectText, false) : savedObjectList;

			for (auto element : objs)
				if (ImGui::Selectable(element.second.c_str(), selectedObjectNameOrHash == element.first))
				{
					if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
					{
						savedObjectToDelete = element.first;
					}
					else
						selectedObjectNameOrHash = element.first;
				}


			ImGui::EndListBox();
		}

		ImGui::SeparatorText("Spawn object");

		static int sliderRange = 50;
		static bool spawnedObjectLocationChanged, spawnedObjectRotationChanged;
		static std::map<std::string, spawnObjs::SpawnedObject> spawnedObjList;
		static bool hasAttachedEnityParametersChanged;

		components::button("Spawn Object", [&] {
			std::string v = trimString(selectedObjectNameOrHash);
			if (v.size() > 0)
			{
				spawnObjs::SpawnedObject o   = spawnObjs::spawnObj(v);
				std::string name             = getFriendlyTimeRightNow() + " " + v + std::to_string(o.ob);
				spawnedObjList[name]         = o;
				spawnObjs::currentSpawnedObj = &spawnedObjList[name];
			}
		});

		if (spawnObjs::currentSpawnedObj)
		{
			components::small_text("The range for spObjLocX,Y,Z and attEntityX,Y,Z");
			ImGui::InputInt("Slider Range", &sliderRange);

			ImGui::PushItemWidth(200);
			if (ImGui::SliderFloat("spObjLocX", &spawnObjs::currentSpawnedObj->xr, -sliderRange, sliderRange))
				spawnedObjectLocationChanged = true;
			ImGui::SameLine();
			ImGui::PushItemWidth(200);
			if (ImGui::SliderFloat("spObjLocY", &spawnObjs::currentSpawnedObj->yr, -sliderRange, sliderRange))
				spawnedObjectLocationChanged = true;
			ImGui::SameLine();
			ImGui::PushItemWidth(200);
			if (ImGui::SliderFloat("spObjLocZ", &spawnObjs::currentSpawnedObj->zr, -sliderRange, sliderRange))
				spawnedObjectLocationChanged = true;

			ImGui::PushItemWidth(200);
			if (ImGui::SliderFloat("spObjPitch", &spawnObjs::currentSpawnedObj->pitch, 0, 360))
				spawnedObjectRotationChanged = true;
			ImGui::SameLine();
			ImGui::PushItemWidth(200);
			if (ImGui::SliderFloat("spObjRoll", &spawnObjs::currentSpawnedObj->roll, 0, 360))
				spawnedObjectRotationChanged = true;
			ImGui::SameLine();
			ImGui::PushItemWidth(200);
			if (ImGui::SliderFloat("spObjYaw", &spawnObjs::currentSpawnedObj->yaw, 0, 360))
				spawnedObjectRotationChanged = true;

			ImGui::SeparatorText("Attach selected spawned object");

			if (ImGui::BeginCombo("BONE_CENTER", spawnObjs::currentSpawnedObj->bone.c_str()))
			{
				for (auto p : boneCenter)
					if (ImGui::Selectable(p, p == spawnObjs::currentSpawnedObj->bone))
					{
						spawnObjs::currentSpawnedObj->bone = p;
						hasAttachedEnityParametersChanged  = true;
					}

				ImGui::EndCombo();
			}
			ImGui::SameLine();
			if (ImGui::BeginCombo("BONE_SIDEWAYS", spawnObjs::currentSpawnedObj->bone.c_str()))
			{
				for (auto p : boneSideways)
					if (ImGui::Selectable(p, p == spawnObjs::currentSpawnedObj->bone))
					{
						spawnObjs::currentSpawnedObj->bone = p;
						hasAttachedEnityParametersChanged  = true;
					}
				ImGui::EndCombo();
			}
			ImGui::SameLine();
			if (ImGui::Checkbox("isBoneLeftAttached", &spawnObjs::currentSpawnedObj->isLeftAttached))
				hasAttachedEnityParametersChanged = true;

			ImGui::PushItemWidth(200);
			if (ImGui::SliderFloat("attEntityX", &spawnObjs::currentSpawnedObj->xa, -sliderRange, sliderRange))
				hasAttachedEnityParametersChanged = true;
			ImGui::SameLine();
			ImGui::PushItemWidth(200);
			if (ImGui::SliderFloat("attEntityY", &spawnObjs::currentSpawnedObj->ya, -sliderRange, sliderRange))
				hasAttachedEnityParametersChanged = true;
			ImGui::SameLine();
			ImGui::PushItemWidth(200);
			if (ImGui::SliderFloat("attEntityZ", &spawnObjs::currentSpawnedObj->za, -sliderRange, sliderRange))
				hasAttachedEnityParametersChanged = true;
			ImGui::PushItemWidth(200);
			if (ImGui::SliderFloat("attEntityRX", &spawnObjs::currentSpawnedObj->rxa, 0, 360))
				hasAttachedEnityParametersChanged = true;
			ImGui::SameLine();
			ImGui::PushItemWidth(200);
			if (ImGui::SliderFloat("attEntityRY", &spawnObjs::currentSpawnedObj->rya, 0, 360))
				hasAttachedEnityParametersChanged = true;
			ImGui::SameLine();
			ImGui::PushItemWidth(200);
			if (ImGui::SliderFloat("attEntityRZ", &spawnObjs::currentSpawnedObj->rza, 0, 360))
				hasAttachedEnityParametersChanged = true;

			components::button("attach to self", [&] {
				try
				{
					if (!spawnObjs::currentSpawnedObj->bone.length())
						spawnObjs::currentSpawnedObj->bone = boneCenter[0];

					auto entity = spawnObjs::getSelectedEntity();

					ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnObjs::currentSpawnedObj->ob,
					    entity,
					    getBoneIndex(entity, spawnObjs::currentSpawnedObj->bone.c_str(), spawnObjs::currentSpawnedObj->isLeftAttached),
					    spawnObjs::currentSpawnedObj->xa,
					    spawnObjs::currentSpawnedObj->ya,
					    spawnObjs::currentSpawnedObj->za,
					    spawnObjs::currentSpawnedObj->rxa,
					    spawnObjs::currentSpawnedObj->rya,
					    spawnObjs::currentSpawnedObj->rza,
					    1,
					    0,
					    0,
					    0,
					    0,
					    1,
					    0);

					spawnObjs::currentSpawnedObj->isAttached = true;
				}
				catch (const std::exception& e)
				{
					LOG(WARNING) << "failed" << e.what();
				}
			});
			ImGui::SameLine();
			components::button("detach from self", [&] {
				try
				{
					ENTITY::DETACH_ENTITY(spawnObjs::currentSpawnedObj->ob, 0, 0);
					OBJECT::PLACE_OBJECT_ON_GROUND_OR_OBJECT_PROPERLY(spawnObjs::currentSpawnedObj->ob);
					spawnObjs::currentSpawnedObj->isAttached = false;
				}
				catch (const std::exception& e)
				{
					LOG(WARNING) << "failed" << e.what();
				}
			});

			ImGui::SeparatorText("Spawned objs");

			components::small_text("Shift click to delete a given spawned object");

			if (ImGui::BeginListBox("##spawnedObjList", {400, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.4)}))
			{
				for (auto element : spawnedObjList)
					if (ImGui::Selectable(element.first.c_str(), element.second.ob == spawnObjs::currentSpawnedObj->ob))
					{
						if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
						{
							big::entity::delete_entity(element.second.ob);
							spawnedObjList.erase(element.first);
							if (spawnedObjList.size() == 0)
								spawnObjs::currentSpawnedObj = NULL;
						}
						else
						{
							spawnObjs::currentSpawnedObj = &spawnedObjList[element.first];
						}
					}

				ImGui::EndListBox();
			}
		}

		ImGui::SeparatorText("Collections");

		static std::map<std::string, std::vector<spawnObjs::SpawnedObject>> collections;
		static std::string collectionName, selectedCollection, collectionToDelete;
		static std::vector<spawnObjs::SpawnedCollection> spawnedCollections;
		static int indexOfcollectionObjectToDelete = -1;

		ImGui::PushItemWidth(200);
		components::input_text_with_hint("##collectionName", "collectionName", collectionName);
		ImGui::SameLine();
		components::button("Create###createCollecBtn", [&] {
			std::string name = trimString(collectionName);
			if (name.size() > 0)
			{
				if (collections.size() == 0)
					spawnObjs::loadSavedCollections(collections);
				collections[name] = {};
				spawnObjs::saveCollection(collections);
			}
		});
		ImGui::SameLine();
		components::button("load collections", [&] {
			spawnObjs::loadSavedCollections(collections);
		});

		if (selectedCollection.size())
		{
			if (spawnObjs::currentSpawnedObj)
				components::button("save selected object to selected collection", [&] {
					spawnObjs::SpawnedObject ob = *spawnObjs::currentSpawnedObj;
					collections[selectedCollection].push_back(ob);
					spawnObjs::saveCollection(collections);
				});

			components::button("spawn selected collection", [&] {
				std::vector<spawnObjs::SpawnedObject> objs = collections[selectedCollection];
				spawnObjs::SpawnedCollection spawnedCollection;
				spawnedCollection.name = getFriendlyTimeRightNow() + " " + selectedCollection;

				for (auto obj : objs)
				{
					spawnObjs::SpawnedObject o = spawnObjs::spawnObj(obj.objName, obj);
					spawnedCollection.objects.push_back(o.ob);
				}
				spawnedCollections.push_back(spawnedCollection);
			});
		}


		components::small_text("Shift click in collection list to delete a selected collection");
		components::small_text("Shift click in object list to delete an object from selected collection");

		ImGui::BeginGroup();
		components::small_text("CollectionName");
		if (ImGui::BeginListBox("##collections", {200, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.4)}))
		{
			for (auto collec : collections)
			{
				std::string collName = collec.first;
				if (ImGui::Selectable(collName.c_str(), collName == selectedCollection))
				{
					if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
					{
						collectionToDelete              = collName;
						indexOfcollectionObjectToDelete = -1;
					}
					else
						selectedCollection = collName;
				}
			}
			ImGui::EndListBox();
		}
		ImGui::EndGroup();
		ImGui::SameLine();
		ImGui::BeginGroup();
		components::small_text("CollectionObjects");
		if (ImGui::BeginListBox("##collectionObjects", {200, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.4)}))
		{
			if (selectedCollection.size())
			{
				std::vector<spawnObjs::SpawnedObject>& objs = collections[selectedCollection];
				for (int i = 0; i < objs.size(); ++i)
					if (ImGui::Selectable(objs[i].objName.c_str(), false))
						if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
						{
							collectionToDelete              = selectedCollection;
							indexOfcollectionObjectToDelete = i;
						}
			}

			ImGui::EndListBox();
		}
		ImGui::EndGroup();

		if (spawnedCollections.size())
		{
			ImGui::SeparatorText("Spawned Collections");

			if (ImGui::BeginListBox("##spawnedCollections", {400, static_cast<float>(*g_pointers->m_gta.m_resolution_y * 0.4)}))
			{
				for (int i = 0; i < spawnedCollections.size(); ++i)
					if (ImGui::Selectable(spawnedCollections[i].name.c_str(), false))
						if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
						{
							for (auto obj : spawnedCollections[i].objects)
								entity::delete_entity(obj);
							spawnedCollections.erase(spawnedCollections.begin() + i);
						}
				ImGui::EndListBox();
			}
		}

		ImGui::EndGroup();

		if (spawnedObjectLocationChanged)
		{
			spawnedObjectLocationChanged = false;
			ENTITY::SET_ENTITY_COORDS(spawnObjs::currentSpawnedObj->ob,
			    spawnObjs::currentSpawnedObj->x + spawnObjs::currentSpawnedObj->xr,
			    spawnObjs::currentSpawnedObj->y + spawnObjs::currentSpawnedObj->yr,
			    spawnObjs::currentSpawnedObj->z + spawnObjs::currentSpawnedObj->zr,
			    0,
			    0,
			    0,
			    1);
		}
		if (spawnedObjectRotationChanged)
		{
			spawnedObjectRotationChanged = false;
			ENTITY::SET_ENTITY_ROTATION(spawnObjs::currentSpawnedObj->ob,
			    spawnObjs::currentSpawnedObj->pitch,
			    spawnObjs::currentSpawnedObj->roll,
			    spawnObjs::currentSpawnedObj->yaw,
			    0,
			    1);
		}
		if (hasAttachedEnityParametersChanged && spawnObjs::currentSpawnedObj->isAttached)
		{
			hasAttachedEnityParametersChanged = false;
			auto entity                       = spawnObjs::getSelectedEntity();

			ENTITY::ATTACH_ENTITY_TO_ENTITY(spawnObjs::currentSpawnedObj->ob,
			    entity,
			    getBoneIndex(entity, spawnObjs::currentSpawnedObj->bone.c_str(), spawnObjs::currentSpawnedObj->isLeftAttached),
			    spawnObjs::currentSpawnedObj->xa,
			    spawnObjs::currentSpawnedObj->ya,
			    spawnObjs::currentSpawnedObj->za,
			    spawnObjs::currentSpawnedObj->rxa,
			    spawnObjs::currentSpawnedObj->rya,
			    spawnObjs::currentSpawnedObj->rza,
			    1,
			    0,
			    0,
			    0,
			    0,
			    1,
			    0);
		}

		if (!std::string(savedObjectToDelete).empty())
			ImGui::OpenPopup("##deleteSavedObject");
		if (ImGui::BeginPopupModal("##deleteSavedObject", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
		{
			ImGui::Text("Are you sure you want to delete saved object");
			ImGui::Spacing();
			if (ImGui::Button("Yes"))
			{
				savedObjectList.erase(savedObjectToDelete);
				spawnObjs::saveObject(savedObjectList);

				savedObjectToDelete = "";
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("No"))
			{
				savedObjectToDelete = "";
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}


		if (!std::string(collectionToDelete).empty() || indexOfcollectionObjectToDelete != -1)
			ImGui::OpenPopup("##collectionToDelete");
		if (ImGui::BeginPopupModal("##collectionToDelete", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
		{
			ImGui::Text(std::format("Are you sure you want to delete {}", (indexOfcollectionObjectToDelete != -1 ? "object" : "collection"))
			                .c_str());
			ImGui::Spacing();
			if (ImGui::Button("Yes"))
			{
				if (indexOfcollectionObjectToDelete != -1)
					collections[collectionToDelete].erase(collections[collectionToDelete].begin() + indexOfcollectionObjectToDelete);
				else
				{
					collections.erase(collectionToDelete);
					if (selectedCollection == collectionToDelete || collections.size() == 0)
						selectedCollection = "";
				}
				spawnObjs::saveCollection(collections);

				collectionToDelete              = "";
				indexOfcollectionObjectToDelete = -1;
				ImGui::CloseCurrentPopup();
			}
			ImGui::SameLine();
			if (ImGui::Button("No"))
			{
				collectionToDelete              = "";
				indexOfcollectionObjectToDelete = -1;
				ImGui::CloseCurrentPopup();
			}
			ImGui::EndPopup();
		}
	}
}
