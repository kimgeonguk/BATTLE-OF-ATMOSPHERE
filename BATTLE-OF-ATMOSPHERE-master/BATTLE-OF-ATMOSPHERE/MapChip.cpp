#include "../BATTLE-OF-ATMOSPHERE/MapChip.h"

const INT map_chip_list[map_size_width_pos][map_size_height_pos]
{
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

VOID DRAWMAP::DrawMapChip(INT map_size_width, INT map_size_height, FLOAT texture_width, FLOAT texture_height, FLOAT mapchip_width, FLOAT mapchip_height, FLOAT draw_width, FLOAT draw_height, FLOAT draw_pos_x, FLOAT draw_pos_y, INT texture, INT** map)
{
	for (INT i = 0; i < map_size_height; i++)
	{
		for (INT j = 0; j < map_size_width; j++)
		{
			INT chip_id = map[i][j];
			if (chip_id == 0)
			{
				continue;
			}

			// テクスチャのサイズとマップチップのサイズから横と縦のチップ数を割り出す
			// (int)g_TextureList[TextureId::MapChip].m_Width       テクスチャのwidth
			//(int)g_TextureList[TextureId::MapChip].m_Height       テクスチャのheight
			//MAPCHIP_WIDTH                                         マップチップの１つのwidth大きさ
			//MAPCHIP_HEIGHT                                        マップチップの１つのheight大きさ
			INT width_num = texture_width / mapchip_width;
			INT height_num = texture_height / mapchip_height;

			// chip_idからチップのテクスチャ座標を割り出す
			// チップの描画
			//chip_pos_x                                            左上のtuの位置
			//chip_pos_y                                            左上のtvの位置
			//MAPCHIP_WIDTH                                         一マスのwidth大きさ
			//MAPCHIP_HEIGHT                                        一マスのheight大きさ
			FLOAT chip_pos_x = (FLOAT)(chip_id % width_num) * mapchip_width;
			FLOAT chip_pos_y = (FLOAT)(chip_id / height_num) * mapchip_height;

			DRAWMAP::TexturePrint(draw_pos_x + draw_width * j, draw_pos_y + draw_height * i, draw_width, draw_height, chip_pos_x / texture_width, chip_pos_y / texture_height, mapchip_width / texture_width, mapchip_height / texture_height, texture);
		}
	}
}

//マップチップ描画
VOID DRAWMAP::TexturePrint(INT drawpos_x, INT drawpos_y, INT mapcip_width, INT mapchip_height, FLOAT chip_pos_x, FLOAT chip_pos_y, FLOAT width_num, FLOAT height_num, INT texture) {

	draw.Draw(drawpos_x, drawpos_y, 0xffffffff, chip_pos_x, chip_pos_y, mapcip_width, mapchip_height, width_num, height_num, texture, 0);

}

