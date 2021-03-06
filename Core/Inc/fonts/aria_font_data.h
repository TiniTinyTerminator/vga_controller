#include <fonts.h>

#ifndef __INC_ARIAL_FONT_DATA_H__
#define __INC_ARIAL_FONT_DATA_H__

#include "arial.xbm"

static Glyph_t arial_glyphs[] =
{
    {'a',5, 12, 0, 0},
    {'b',5, 12, 9, 0},
    {'c',5, 12, 18,0},
    {'d',5, 12, 27,0},
    {'e',5, 12, 36,0},
    {'f',3, 12, 45,0},
    {'g',5, 12, 52,0},
    {'h',5, 12, 61,0},
    {'i',1, 12, 70,0},
    {'j',2, 12, 74,0},
    {'k',4, 12, 80,0},
    {'l',1, 12, 88, 0},
    {'m',7, 12, 93, 0},
    {'n',5, 12, 104, 0},
    {'o',5, 12, 113, 0},
    {'p',5, 12, 122, 0},
    {'q',5, 12, 131, 0},
    {'r',3, 12, 140, 0},
    {'s',5, 12, 147, 0},
    {'t',3, 12, 155, 0},
    {'u',5, 12, 162, 0},
    {'v',5, 12, 171, 0},
    {'w',9, 12, 180, 0},
    {'x',5, 12, 193, 0},
    {'y',5, 12, 202, 0},
    {'z',5, 12, 211, 0},
    {'A',7, 12, 220, 0},
    {'B',6, 12, 231, 0},
    {'C',6, 12, 241, 0},
    {'D',6, 12, 251, 0},
    {'E',5, 12, 261, 0},
    {'F',5, 12, 270, 0},
    {'G',7, 12, 279, 0},
    {'H',7, 12, 290, 0},
    {'I',1, 12, 300, 0},
    {'J',4, 12, 305, 0},
    {'K',6, 12, 313, 0},
    {'L',5, 12, 323, 0},
    {'M',7, 12, 332, 0},
    {'N',6, 12, 343, 0},
    {'O',7, 12, 353, 0},
    {'P',5, 12, 364, 0},
    {'Q',7, 12, 373, 0},
    {'R',6, 12, 384, 0},
    {'S',6, 12, 394, 0},
    {'T',5, 12, 404, 0},
    {'U',6, 12, 413, 0},
    {'V',7, 12, 423, 0},
    {'W',11, 12, 433, 0},
    {'X',6, 12, 447, 0},
    {'Y',7, 12, 457, 0},
    {'Z',6, 12, 468, 0},
    {'1',3, 12, 478, 0},
    {'2',5, 12, 486, 0},
    {'3',5, 12, 495, 0},
    {'4',5, 12, 504, 0},
    {'5',5, 12, 513, 0},
    {'6',5, 12, 522, 0},
    {'7',5, 12, 531, 0},
    {'8',5, 12, 540, 0},
    {'9',5, 12, 549, 0},
    {'0',5, 12, 558, 0},
    {'!',1, 12, 567, 0},
    {'@',10, 12, 572, 0},
    {'#',5, 12, 0, 0},
    {'$',5, 12, 0, 0},
    {'%',9, 12, 0, 0},
    {'^',5, 12, 0, 0},
    {'&',6, 12, 0, 0},
    {'*',3, 12, 0, 0},
    {'(',3, 12, 0, 0},
    {')',3, 12, 0, 0},
    {'-',3, 12, 0, 0},
    {'+',5, 12, 0, 0},
    {'=',5, 12, 0, 0},
    {'{',3, 12, 0, 0},
    {'}',3, 12, 0, 0},
    {':',1, 12, 0, 0},
    {';',1, 12, 0, 0},
    {'|',1, 12, 0, 0},
    {'/',3, 12, 0, 0},
    {'?',5, 12, 0, 0},
    {'>',5, 12, 0, 0},
    {'.',1, 12, 0, 0},
    {'<',5, 12, 0, 0},
    {',',1, 12, 0, 0},
    {' ',4, 12, 5, 0}
};

static Font_t arial = {
    .name = "arial",

    .size = (sizeof(arial_glyphs))/(sizeof(Glyph_t)),

    .glyphs = arial_glyphs,

    .frame = {
        (uint8_t *)arial_bits,
        arial_width,
        arial_height
    },

};

#endif// INC_ARIA_FONT_DATA_H_
