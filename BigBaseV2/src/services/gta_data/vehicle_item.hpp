namespace big::gta_data_service
{
	class vehicle_item {
    public:
        const Hash hash;
        const int class_idx;
		const char* name;
		const int manufacturer_idx;

        vehicle_item(const Hash hash, const int class_idx, const char* name, const int manufacturer_idx);
        ~vehicle_item();

        const char* get_class() const;
        const char* get_manufacturer() const;
	};
}
