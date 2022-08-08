namespace big::gta_data_service
{
	class weapon_item {
    public:
        const Hash hash;
        const int type_idx;
		const char* name;
		const bool throwable;
		const Hash reward_hash;
		const Hash reward_ammo_hash;

        weapon_item(const Hash hash, const int type_idx, const char* name, const bool throwable, const Hash reward_hash, const Hash reward_ammo_hash);
        ~weapon_item();

		const char* get_type();
	};
}
