#pragma once

struct vehicle_and_id {
public:
	char id[20];
	char name[30];
};

const vehicle_and_id vehicle_ids[] = {
	{"oppressor", "Opressor Mk. 1"},
	{"oppressor2", "Oppressor Mk. 2"},
	{"scramjet", "Scramjet"},
};