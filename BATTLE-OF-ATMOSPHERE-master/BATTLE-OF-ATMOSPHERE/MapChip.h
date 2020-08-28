#ifndef MAPCHIP_H
#define MAPCHIP_H

#include "../BATTLE-OF-ATMOSPHERE/Main.h"

#include<iostream>
#include<stdio.h>

const INT map_size_width_pos = 8;
const INT map_size_height_pos = 15;

class DRAWMAP {
public:

	VOID DrawMapChip(INT map_size_width, INT map_size_height, FLOAT texture_width, FLOAT texture_height, FLOAT mapchip_width, FLOAT mapchip_height, FLOAT draw_width, FLOAT draw_height, FLOAT draw_pos_x, FLOAT draw_pos_y, INT texture, INT** map);

	VOID TexturePrint(INT drawpos_x, INT drawpos_y, INT mapcip_width, INT mapchip_height, FLOAT chip_pos_x, FLOAT chip_pos_y, FLOAT width_num, FLOAT height_num, INT texture);

	INT map[map_size_width_pos][map_size_height_pos];

};
#endif // !MAPCHIP