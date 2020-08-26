#include "seed.h"
#include <string>

#define REVERSE(n) (((n) >> 24) | (((n) & 0xff0000) >> 8) | (((n) & 0xff00) << 8) | ((n) << 24))
#define SSBOX(n) (ss3[((n) >> 24) & 0xff] ^ ss2[((n) >> 16) & 0xff] ^ ss1[((n) >> 8) & 0xff] ^ ss0[(n) & 0xff])

static const unsigned ss0[] = {
    0x2989A1A8,     0x5858184,    0x16C6D2D4,    0x13C3D3D0,
    0x14445054,    0x1D0D111C,    0x2C8CA0AC,    0x25052124,
    0x1D4D515C,     0x3434340,    0x18081018,    0x1E0E121C,
    0x11415150,    0x3CCCF0FC,     0xACAC2C8,    0x23436360,
    0x28082028,     0x4444044,    0x20002020,    0x1D8D919C,
    0x20C0E0E0,    0x22C2E2E0,     0x8C8C0C8,    0x17071314,
    0x2585A1A4,     0xF8F838C,     0x3030300,    0x3B4B7378,
    0x3B8BB3B8,    0x13031310,    0x12C2D2D0,    0x2ECEE2EC,
    0x30407070,     0xC8C808C,    0x3F0F333C,    0x2888A0A8,
    0x32023230,    0x1DCDD1DC,    0x36C6F2F4,    0x34447074,
    0x2CCCE0EC,    0x15859194,     0xB0B0308,    0x17475354,
    0x1C4C505C,    0x1B4B5358,    0x3D8DB1BC,     0x1010100,
    0x24042024,    0x1C0C101C,    0x33437370,    0x18889098,
    0x10001010,     0xCCCC0CC,    0x32C2F2F0,    0x19C9D1D8,
    0x2C0C202C,    0x27C7E3E4,    0x32427270,     0x3838380,
    0x1B8B9398,    0x11C1D1D0,     0x6868284,     0x9C9C1C8,
    0x20406060,    0x10405050,    0x2383A3A0,    0x2BCBE3E8,
    0xD0D010C,    0x3686B2B4,    0x1E8E929C,     0xF4F434C,
    0x3787B3B4,    0x1A4A5258,     0x6C6C2C4,    0x38487078,
    0x2686A2A4,    0x12021210,    0x2F8FA3AC,    0x15C5D1D4,
    0x21416160,     0x3C3C3C0,    0x3484B0B4,     0x1414140,
    0x12425250,    0x3D4D717C,     0xD8D818C,     0x8080008,
    0x1F0F131C,    0x19899198,           0x0,    0x19091118,
    0x4040004,    0x13435350,    0x37C7F3F4,    0x21C1E1E0,
    0x3DCDF1FC,    0x36467274,    0x2F0F232C,    0x27072324,
    0x3080B0B0,     0xB8B8388,     0xE0E020C,    0x2B8BA3A8,
    0x2282A2A0,    0x2E4E626C,    0x13839390,     0xD4D414C,
    0x29496168,    0x3C4C707C,     0x9090108,     0xA0A0208,
    0x3F8FB3BC,    0x2FCFE3EC,    0x33C3F3F0,     0x5C5C1C4,
    0x7878384,    0x14041014,    0x3ECEF2FC,    0x24446064,
    0x1ECED2DC,    0x2E0E222C,     0xB4B4348,    0x1A0A1218,
    0x6060204,    0x21012120,    0x2B4B6368,    0x26466264,
    0x2020200,    0x35C5F1F4,    0x12829290,     0xA8A8288,
    0xC0C000C,    0x3383B3B0,    0x3E4E727C,    0x10C0D0D0,
    0x3A4A7278,     0x7474344,    0x16869294,    0x25C5E1E4,
    0x26062224,      0x808080,    0x2D8DA1AC,    0x1FCFD3DC,
    0x2181A1A0,    0x30003030,    0x37073334,    0x2E8EA2AC,
    0x36063234,    0x15051114,    0x22022220,    0x38083038,
    0x34C4F0F4,    0x2787A3A4,     0x5454144,     0xC4C404C,
    0x1818180,    0x29C9E1E8,     0x4848084,    0x17879394,
    0x35053134,     0xBCBC3C8,     0xECEC2CC,    0x3C0C303C,
    0x31417170,    0x11011110,     0x7C7C3C4,     0x9898188,
    0x35457174,    0x3BCBF3F8,    0x1ACAD2D8,    0x38C8F0F8,
    0x14849094,    0x19495158,     0x2828280,     0x4C4C0C4,
    0x3FCFF3FC,     0x9494148,    0x39093138,    0x27476364,
    0xC0C0C0,     0xFCFC3CC,    0x17C7D3D4,    0x3888B0B8,
    0xF0F030C,     0xE8E828C,     0x2424240,    0x23032320,
    0x11819190,    0x2C4C606C,    0x1BCBD3D8,    0x2484A0A4,
    0x34043034,    0x31C1F1F0,     0x8484048,     0x2C2C2C0,
    0x2F4F636C,    0x3D0D313C,    0x2D0D212C,      0x404040,
    0x3E8EB2BC,    0x3E0E323C,    0x3C8CB0BC,     0x1C1C1C0,
    0x2A8AA2A8,    0x3A8AB2B8,     0xE4E424C,    0x15455154,
    0x3B0B3338,    0x1CCCD0DC,    0x28486068,    0x3F4F737C,
    0x1C8C909C,    0x18C8D0D8,     0xA4A4248,    0x16465254,
    0x37477374,    0x2080A0A0,    0x2DCDE1EC,     0x6464244,
    0x3585B1B4,    0x2B0B2328,    0x25456164,    0x3ACAF2F8,
    0x23C3E3E0,    0x3989B1B8,    0x3181B1B0,    0x1F8F939C,
    0x1E4E525C,    0x39C9F1F8,    0x26C6E2E4,    0x3282B2B0,
    0x31013130,    0x2ACAE2E8,    0x2D4D616C,    0x1F4F535C,
    0x24C4E0E4,    0x30C0F0F0,     0xDCDC1CC,     0x8888088,
    0x16061214,    0x3A0A3238,    0x18485058,    0x14C4D0D4,
    0x22426260,    0x29092128,     0x7070304,    0x33033330,
    0x28C8E0E8,    0x1B0B1318,     0x5050104,    0x39497178,
    0x10809090,    0x2A4A6268,    0x2A0A2228,    0x1A8A9298
};

static const unsigned ss1[] = {
    0x38380830,    0xE828C8E0,    0x2C2D0D21,    0xA42686A2,
    0xCC0FCFC3,    0xDC1ECED2,    0xB03383B3,    0xB83888B0,
    0xAC2F8FA3,    0x60204060,    0x54154551,    0xC407C7C3,
    0x44044440,    0x6C2F4F63,    0x682B4B63,    0x581B4B53,
    0xC003C3C3,    0x60224262,    0x30330333,    0xB43585B1,
    0x28290921,    0xA02080A0,    0xE022C2E2,    0xA42787A3,
    0xD013C3D3,    0x90118191,    0x10110111,     0x4060602,
    0x1C1C0C10,    0xBC3C8CB0,    0x34360632,    0x480B4B43,
    0xEC2FCFE3,    0x88088880,    0x6C2C4C60,    0xA82888A0,
    0x14170713,    0xC404C4C0,    0x14160612,    0xF434C4F0,
    0xC002C2C2,    0x44054541,    0xE021C1E1,    0xD416C6D2,
    0x3C3F0F33,    0x3C3D0D31,    0x8C0E8E82,    0x98188890,
    0x28280820,    0x4C0E4E42,    0xF436C6F2,    0x3C3E0E32,
    0xA42585A1,    0xF839C9F1,     0xC0D0D01,    0xDC1FCFD3,
    0xD818C8D0,    0x282B0B23,    0x64264662,    0x783A4A72,
    0x24270723,    0x2C2F0F23,    0xF031C1F1,    0x70324272,
    0x40024242,    0xD414C4D0,    0x40014141,    0xC000C0C0,
    0x70334373,    0x64274763,    0xAC2C8CA0,    0x880B8B83,
    0xF437C7F3,    0xAC2D8DA1,    0x80008080,    0x1C1F0F13,
    0xC80ACAC2,    0x2C2C0C20,    0xA82A8AA2,    0x34340430,
    0xD012C2D2,     0x80B0B03,    0xEC2ECEE2,    0xE829C9E1,
    0x5C1D4D51,    0x94148490,    0x18180810,    0xF838C8F0,
    0x54174753,    0xAC2E8EA2,     0x8080800,    0xC405C5C1,
    0x10130313,    0xCC0DCDC1,    0x84068682,    0xB83989B1,
    0xFC3FCFF3,    0x7C3D4D71,    0xC001C1C1,    0x30310131,
    0xF435C5F1,    0x880A8A82,    0x682A4A62,    0xB03181B1,
    0xD011C1D1,    0x20200020,    0xD417C7D3,       0x20202,
    0x20220222,     0x4040400,    0x68284860,    0x70314171,
    0x4070703,    0xD81BCBD3,    0x9C1D8D91,    0x98198991,
    0x60214161,    0xBC3E8EB2,    0xE426C6E2,    0x58194951,
    0xDC1DCDD1,    0x50114151,    0x90108090,    0xDC1CCCD0,
    0x981A8A92,    0xA02383A3,    0xA82B8BA3,    0xD010C0D0,
    0x80018181,     0xC0F0F03,    0x44074743,    0x181A0A12,
    0xE023C3E3,    0xEC2CCCE0,    0x8C0D8D81,    0xBC3F8FB3,
    0x94168692,    0x783B4B73,    0x5C1C4C50,    0xA02282A2,
    0xA02181A1,    0x60234363,    0x20230323,    0x4C0D4D41,
    0xC808C8C0,    0x9C1E8E92,    0x9C1C8C90,    0x383A0A32,
    0xC0C0C00,    0x2C2E0E22,    0xB83A8AB2,    0x6C2E4E62,
    0x9C1F8F93,    0x581A4A52,    0xF032C2F2,    0x90128292,
    0xF033C3F3,    0x48094941,    0x78384870,    0xCC0CCCC0,
    0x14150511,    0xF83BCBF3,    0x70304070,    0x74354571,
    0x7C3F4F73,    0x34350531,    0x10100010,       0x30303,
    0x64244460,    0x6C2D4D61,    0xC406C6C2,    0x74344470,
    0xD415C5D1,    0xB43484B0,    0xE82ACAE2,     0x8090901,
    0x74364672,    0x18190911,    0xFC3ECEF2,    0x40004040,
    0x10120212,    0xE020C0E0,    0xBC3D8DB1,     0x4050501,
    0xF83ACAF2,       0x10101,    0xF030C0F0,    0x282A0A22,
    0x5C1E4E52,    0xA82989A1,    0x54164652,    0x40034343,
    0x84058581,    0x14140410,    0x88098981,    0x981B8B93,
    0xB03080B0,    0xE425C5E1,    0x48084840,    0x78394971,
    0x94178793,    0xFC3CCCF0,    0x1C1E0E12,    0x80028282,
    0x20210121,    0x8C0C8C80,    0x181B0B13,    0x5C1F4F53,
    0x74374773,    0x54144450,    0xB03282B2,    0x1C1D0D11,
    0x24250521,    0x4C0F4F43,           0x0,    0x44064642,
    0xEC2DCDE1,    0x58184850,    0x50124252,    0xE82BCBE3,
    0x7C3E4E72,    0xD81ACAD2,    0xC809C9C1,    0xFC3DCDF1,
    0x30300030,    0x94158591,    0x64254561,    0x3C3C0C30,
    0xB43686B2,    0xE424C4E0,    0xB83B8BB3,    0x7C3C4C70,
    0xC0E0E02,    0x50104050,    0x38390931,    0x24260622,
    0x30320232,    0x84048480,    0x68294961,    0x90138393,
    0x34370733,    0xE427C7E3,    0x24240420,    0xA42484A0,
    0xC80BCBC3,    0x50134353,     0x80A0A02,    0x84078783,
    0xD819C9D1,    0x4C0C4C40,    0x80038383,    0x8C0F8F83,
    0xCC0ECEC2,    0x383B0B33,    0x480A4A42,    0xB43787B3
};

static const unsigned ss2[] = {
    0xA1A82989,    0x81840585,    0xD2D416C6,    0xD3D013C3,
    0x50541444,    0x111C1D0D,    0xA0AC2C8C,    0x21242505,
    0x515C1D4D,    0x43400343,    0x10181808,    0x121C1E0E,
    0x51501141,    0xF0FC3CCC,    0xC2C80ACA,    0x63602343,
    0x20282808,    0x40440444,    0x20202000,    0x919C1D8D,
    0xE0E020C0,    0xE2E022C2,    0xC0C808C8,    0x13141707,
    0xA1A42585,    0x838C0F8F,     0x3000303,    0x73783B4B,
    0xB3B83B8B,    0x13101303,    0xD2D012C2,    0xE2EC2ECE,
    0x70703040,    0x808C0C8C,    0x333C3F0F,    0xA0A82888,
    0x32303202,    0xD1DC1DCD,    0xF2F436C6,    0x70743444,
    0xE0EC2CCC,    0x91941585,     0x3080B0B,    0x53541747,
    0x505C1C4C,    0x53581B4B,    0xB1BC3D8D,     0x1000101,
    0x20242404,    0x101C1C0C,    0x73703343,    0x90981888,
    0x10101000,    0xC0CC0CCC,    0xF2F032C2,    0xD1D819C9,
    0x202C2C0C,    0xE3E427C7,    0x72703242,    0x83800383,
    0x93981B8B,    0xD1D011C1,    0x82840686,    0xC1C809C9,
    0x60602040,    0x50501040,    0xA3A02383,    0xE3E82BCB,
    0x10C0D0D,    0xB2B43686,    0x929C1E8E,    0x434C0F4F,
    0xB3B43787,    0x52581A4A,    0xC2C406C6,    0x70783848,
    0xA2A42686,    0x12101202,    0xA3AC2F8F,    0xD1D415C5,
    0x61602141,    0xC3C003C3,    0xB0B43484,    0x41400141,
    0x52501242,    0x717C3D4D,    0x818C0D8D,       0x80808,
    0x131C1F0F,    0x91981989,           0x0,    0x11181909,
    0x40404,    0x53501343,    0xF3F437C7,    0xE1E021C1,
    0xF1FC3DCD,    0x72743646,    0x232C2F0F,    0x23242707,
    0xB0B03080,    0x83880B8B,     0x20C0E0E,    0xA3A82B8B,
    0xA2A02282,    0x626C2E4E,    0x93901383,    0x414C0D4D,
    0x61682949,    0x707C3C4C,     0x1080909,     0x2080A0A,
    0xB3BC3F8F,    0xE3EC2FCF,    0xF3F033C3,    0xC1C405C5,
    0x83840787,    0x10141404,    0xF2FC3ECE,    0x60642444,
    0xD2DC1ECE,    0x222C2E0E,    0x43480B4B,    0x12181A0A,
    0x2040606,    0x21202101,    0x63682B4B,    0x62642646,
    0x2000202,    0xF1F435C5,    0x92901282,    0x82880A8A,
    0xC0C0C,    0xB3B03383,    0x727C3E4E,    0xD0D010C0,
    0x72783A4A,    0x43440747,    0x92941686,    0xE1E425C5,
    0x22242606,    0x80800080,    0xA1AC2D8D,    0xD3DC1FCF,
    0xA1A02181,    0x30303000,    0x33343707,    0xA2AC2E8E,
    0x32343606,    0x11141505,    0x22202202,    0x30383808,
    0xF0F434C4,    0xA3A42787,    0x41440545,    0x404C0C4C,
    0x81800181,    0xE1E829C9,    0x80840484,    0x93941787,
    0x31343505,    0xC3C80BCB,    0xC2CC0ECE,    0x303C3C0C,
    0x71703141,    0x11101101,    0xC3C407C7,    0x81880989,
    0x71743545,    0xF3F83BCB,    0xD2D81ACA,    0xF0F838C8,
    0x90941484,    0x51581949,    0x82800282,    0xC0C404C4,
    0xF3FC3FCF,    0x41480949,    0x31383909,    0x63642747,
    0xC0C000C0,    0xC3CC0FCF,    0xD3D417C7,    0xB0B83888,
    0x30C0F0F,    0x828C0E8E,    0x42400242,    0x23202303,
    0x91901181,    0x606C2C4C,    0xD3D81BCB,    0xA0A42484,
    0x30343404,    0xF1F031C1,    0x40480848,    0xC2C002C2,
    0x636C2F4F,    0x313C3D0D,    0x212C2D0D,    0x40400040,
    0xB2BC3E8E,    0x323C3E0E,    0xB0BC3C8C,    0xC1C001C1,
    0xA2A82A8A,    0xB2B83A8A,    0x424C0E4E,    0x51541545,
    0x33383B0B,    0xD0DC1CCC,    0x60682848,    0x737C3F4F,
    0x909C1C8C,    0xD0D818C8,    0x42480A4A,    0x52541646,
    0x73743747,    0xA0A02080,    0xE1EC2DCD,    0x42440646,
    0xB1B43585,    0x23282B0B,    0x61642545,    0xF2F83ACA,
    0xE3E023C3,    0xB1B83989,    0xB1B03181,    0x939C1F8F,
    0x525C1E4E,    0xF1F839C9,    0xE2E426C6,    0xB2B03282,
    0x31303101,    0xE2E82ACA,    0x616C2D4D,    0x535C1F4F,
    0xE0E424C4,    0xF0F030C0,    0xC1CC0DCD,    0x80880888,
    0x12141606,    0x32383A0A,    0x50581848,    0xD0D414C4,
    0x62602242,    0x21282909,     0x3040707,    0x33303303,
    0xE0E828C8,    0x13181B0B,     0x1040505,    0x71783949,
    0x90901080,    0x62682A4A,    0x22282A0A,    0x92981A8A
};

static const unsigned ss3[] = {
    0x8303838,    0xC8E0E828,     0xD212C2D,    0x86A2A426,
    0xCFC3CC0F,    0xCED2DC1E,    0x83B3B033,    0x88B0B838,
    0x8FA3AC2F,    0x40606020,    0x45515415,    0xC7C3C407,
    0x44404404,    0x4F636C2F,    0x4B63682B,    0x4B53581B,
    0xC3C3C003,    0x42626022,     0x3333033,    0x85B1B435,
    0x9212829,    0x80A0A020,    0xC2E2E022,    0x87A3A427,
    0xC3D3D013,    0x81919011,     0x1111011,     0x6020406,
    0xC101C1C,    0x8CB0BC3C,     0x6323436,    0x4B43480B,
    0xCFE3EC2F,    0x88808808,    0x4C606C2C,    0x88A0A828,
    0x7131417,    0xC4C0C404,     0x6121416,    0xC4F0F434,
    0xC2C2C002,    0x45414405,    0xC1E1E021,    0xC6D2D416,
    0xF333C3F,     0xD313C3D,    0x8E828C0E,    0x88909818,
    0x8202828,    0x4E424C0E,    0xC6F2F436,     0xE323C3E,
    0x85A1A425,    0xC9F1F839,     0xD010C0D,    0xCFD3DC1F,
    0xC8D0D818,     0xB23282B,    0x46626426,    0x4A72783A,
    0x7232427,     0xF232C2F,    0xC1F1F031,    0x42727032,
    0x42424002,    0xC4D0D414,    0x41414001,    0xC0C0C000,
    0x43737033,    0x47636427,    0x8CA0AC2C,    0x8B83880B,
    0xC7F3F437,    0x8DA1AC2D,    0x80808000,     0xF131C1F,
    0xCAC2C80A,     0xC202C2C,    0x8AA2A82A,     0x4303434,
    0xC2D2D012,     0xB03080B,    0xCEE2EC2E,    0xC9E1E829,
    0x4D515C1D,    0x84909414,     0x8101818,    0xC8F0F838,
    0x47535417,    0x8EA2AC2E,     0x8000808,    0xC5C1C405,
    0x3131013,    0xCDC1CC0D,    0x86828406,    0x89B1B839,
    0xCFF3FC3F,    0x4D717C3D,    0xC1C1C001,     0x1313031,
    0xC5F1F435,    0x8A82880A,    0x4A62682A,    0x81B1B031,
    0xC1D1D011,      0x202020,    0xC7D3D417,     0x2020002,
    0x2222022,     0x4000404,    0x48606828,    0x41717031,
    0x7030407,    0xCBD3D81B,    0x8D919C1D,    0x89919819,
    0x41616021,    0x8EB2BC3E,    0xC6E2E426,    0x49515819,
    0xCDD1DC1D,    0x41515011,    0x80909010,    0xCCD0DC1C,
    0x8A92981A,    0x83A3A023,    0x8BA3A82B,    0xC0D0D010,
    0x81818001,     0xF030C0F,    0x47434407,     0xA12181A,
    0xC3E3E023,    0xCCE0EC2C,    0x8D818C0D,    0x8FB3BC3F,
    0x86929416,    0x4B73783B,    0x4C505C1C,    0x82A2A022,
    0x81A1A021,    0x43636023,     0x3232023,    0x4D414C0D,
    0xC8C0C808,    0x8E929C1E,    0x8C909C1C,     0xA32383A,
    0xC000C0C,     0xE222C2E,    0x8AB2B83A,    0x4E626C2E,
    0x8F939C1F,    0x4A52581A,    0xC2F2F032,    0x82929012,
    0xC3F3F033,    0x49414809,    0x48707838,    0xCCC0CC0C,
    0x5111415,    0xCBF3F83B,    0x40707030,    0x45717435,
    0x4F737C3F,     0x5313435,      0x101010,     0x3030003,
    0x44606424,    0x4D616C2D,    0xC6C2C406,    0x44707434,
    0xC5D1D415,    0x84B0B434,    0xCAE2E82A,     0x9010809,
    0x46727436,     0x9111819,    0xCEF2FC3E,    0x40404000,
    0x2121012,    0xC0E0E020,    0x8DB1BC3D,     0x5010405,
    0xCAF2F83A,     0x1010001,    0xC0F0F030,     0xA22282A,
    0x4E525C1E,    0x89A1A829,    0x46525416,    0x43434003,
    0x85818405,     0x4101414,    0x89818809,    0x8B93981B,
    0x80B0B030,    0xC5E1E425,    0x48404808,    0x49717839,
    0x87939417,    0xCCF0FC3C,     0xE121C1E,    0x82828002,
    0x1212021,    0x8C808C0C,     0xB13181B,    0x4F535C1F,
    0x47737437,    0x44505414,    0x82B2B032,     0xD111C1D,
    0x5212425,    0x4F434C0F,           0x0,    0x46424406,
    0xCDE1EC2D,    0x48505818,    0x42525012,    0xCBE3E82B,
    0x4E727C3E,    0xCAD2D81A,    0xC9C1C809,    0xCDF1FC3D,
    0x303030,    0x85919415,    0x45616425,     0xC303C3C,
    0x86B2B436,    0xC4E0E424,    0x8BB3B83B,    0x4C707C3C,
    0xE020C0E,    0x40505010,     0x9313839,     0x6222426,
    0x2323032,    0x84808404,    0x49616829,    0x83939013,
    0x7333437,    0xC7E3E427,     0x4202424,    0x84A0A424,
    0xCBC3C80B,    0x43535013,     0xA02080A,    0x87838407,
    0xC9D1D819,    0x4C404C0C,    0x83838003,    0x8F838C0F,
    0xCEC2CC0E,     0xB33383B,    0x4A42480A,    0x87B3B437
};

static const unsigned seed_ks[] = {
    0x9e3779b9, 0x3c6ef373, 0x78dde6e6, 0xf1bbcdcc,
    0xe3779b99, 0xc6ef3733, 0x8dde6e67, 0x1bbcdccf,
    0x3779b99e, 0x6ef3733c, 0xdde6e678, 0xbbcdccf1,
    0x779b99e3, 0xef3733c6, 0xde6e678d, 0xbcdccf1b
};

SEED::SEED()
{
    memset(this->key, 0, sizeof(this->key));
    memset(this->init_vector, 0, sizeof(this->init_vector));
    memset(this->subkeys, 0, sizeof(this->subkeys));

    this->inBuffer = NULL;
    this->inBufferSize = 0;
    this->outBuffer = NULL;
    this->outBufferSize = 0;
}

SEED::~SEED()
{
    memset(this->key, 0, sizeof(this->key));
    memset(this->init_vector, 0, sizeof(this->init_vector));
    memset(this->subkeys, 0, sizeof(this->subkeys));

    if (this->inBuffer) {
        delete[] this->inBuffer;
        this->inBuffer = nullptr;
    }

    if (this->outBuffer) {
        delete[] this->outBuffer;
        this->outBuffer = nullptr;
    }
}

int SEED::Initialize(const void* key, const void* iv)
{
    memcpy(this->key, key, sizeof(this->key));
    memset(this->init_vector, 0, sizeof(this->init_vector));
    if (iv) {
        memcpy(this->init_vector, iv, sizeof(this->init_vector));
    }

    // Generate the round keys.
    unsigned key0 = REVERSE( this->key[0] );
    unsigned key1 = REVERSE( this->key[1] );
    unsigned key2 = REVERSE( this->key[2] );
    unsigned key3 = REVERSE( this->key[3] );

    memset(this->subkeys, 0, sizeof(this->subkeys));

    for (unsigned i = 0; i < 16; i++) {
        unsigned index = i << 1;

        this->subkeys[index] = SSBOX(key0 + key2 - seed_ks[i]);
        this->subkeys[index + 1] = SSBOX(key1 - key3 + seed_ks[i]);

        if (i & 0x1) {
            unsigned t = key2;
            key2 = (key2 << 8) ^ (key3 >> 24);
            key3 = (key3 << 8) ^ (t >> 24);
        }
        else {
            unsigned t = key0;
            key0 = (key0 >> 8) ^ (key1 << 24);
            key1 = (key1 >> 8) ^ (t << 24);
        }
    }

    return 0;
}

int SEED::CreateBuffers(size_t insize, size_t outsize)
{
    if (!this->inBuffer || insize > this->inBufferSize) {
        if (this->inBuffer)
            delete[] this->inBuffer;

        this->inBuffer = new unsigned char[insize];
        if (!this->inBuffer)
            return ERR_NO_MEMORY;
        this->inBufferSize = insize;
    }

    if (!this->outBuffer || outsize > this->outBufferSize) {

        if (this->outBuffer)
            delete[] this->outBuffer;

        this->outBuffer = new unsigned char[outsize];
        if (!this->outBuffer)
            return ERR_NO_MEMORY;
        this->outBufferSize = outsize;
    }

    return ERR_OK;
}

void SEED::ClearBuffers()
{
    if (this->inBuffer)
        memset(this->inBuffer, 0, this->inBufferSize);

    if (this->outBuffer)
        memset(this->outBuffer, 0, this->outBufferSize);
}

void SEED::EncryptBlock(const void* block, void* outblock)
{
    unsigned* in = (unsigned*)block;

    unsigned R0 = REVERSE(in[2]);
    unsigned R1 = REVERSE(in[3]);
    unsigned L0 = REVERSE(in[0]);
    unsigned L1 = REVERSE(in[1]);

    unsigned* lv1 = &R0;
    unsigned* lv2 = &R1;

    for (unsigned i = 0; i < 16; i++) {
        unsigned keyIndex = i << 1;
        unsigned index1 = subkeys[keyIndex] ^ *lv1;
        unsigned index2 = SSBOX(subkeys[keyIndex + 1] ^ index1 ^ *lv2);
        index1 = SSBOX(index1 + index2);
        index2 = SSBOX(index1 + index2);

        if (i & 0x1) {
            lv1 = &R0;
            lv2 = &R1;
        }
        else {
            lv1 = &L0;
            lv2 = &L1;
        }

        *lv1 ^= index1 + index2;
        *lv2 ^= index2;
    }

    R0 = REVERSE(R0);
    R1 = REVERSE(R1);
    L0 = REVERSE(L0);
    L1 = REVERSE(L1);

    unsigned* out = (unsigned*)outblock;
    out[0] = R0;
    out[1] = R1;
    out[2] = L0;
    out[3] = L1;
}

int SEED::Encrypt(const void* in, size_t insize, void* out, size_t outsize, size_t* bytesWritten)
{
    size_t alignedSize = insize;
    if (alignedSize & 0xf) {
        alignedSize = (alignedSize & 0xfffffff0) + 16;
    }

    if (!out) {
        *bytesWritten = alignedSize;
        return ERR_OK;
    }

    if (outsize < alignedSize) {
        return ERR_BUFFER_TOO_SMALL;
    }

    if (int err = CreateBuffers(alignedSize, alignedSize)) {
        return err;
    }

    ClearBuffers();

    for (unsigned i = 0; i < insize; i++) {
        this->inBuffer[i] = ((unsigned char*)in)[i];
    }

    unsigned* xor_values = this->init_vector;
    unsigned* inPtr = (unsigned*)this->inBuffer;
    unsigned* outPtr = (unsigned*)this->outBuffer;
    size_t numBlocks = alignedSize >> 4;
    size_t blocksLeft = numBlocks;

    while (blocksLeft) {
        for (unsigned i = 0; i < 4; i++) {
            outPtr[i] = inPtr[i] ^ xor_values[i];
        }

        EncryptBlock(outPtr, outPtr);

        xor_values = outPtr;

        inPtr += 4;
        outPtr += 4;
        blocksLeft--;
    }

    memcpy(this->init_vector, xor_values, sizeof(this->init_vector));

    for (unsigned i = 0; i < (numBlocks << 4); i++) {
        ((unsigned char*)out)[i] = this->outBuffer[i];
    }

    if (bytesWritten)
        *bytesWritten = alignedSize;

    ClearBuffers();

    return ERR_OK;
}

void SEED::DecryptBlock(const void* block, void* outblock)
{
    unsigned* in = (unsigned*)block;
    
    unsigned R0 = REVERSE(in[2]);
    unsigned R1 = REVERSE(in[3]);
    unsigned L0 = REVERSE(in[0]);
    unsigned L1 = REVERSE(in[1]);

    unsigned* lv1 = &R0;
    unsigned* lv2 = &R1;

    for (unsigned i = 0; i < 16; i++) {
        unsigned keyIndex = (16 - i - 1) << 1;
        unsigned index1 = subkeys[keyIndex] ^ *lv1;
        unsigned index2 = SSBOX(subkeys[keyIndex + 1] ^ index1 ^ *lv2);
        index1 = SSBOX(index1 + index2);
        index2 = SSBOX(index1 + index2);

        if (i & 0x1) {
            lv1 = &R0;
            lv2 = &R1;
        }
        else {
            lv1 = &L0;
            lv2 = &L1;
        }

        *lv1 ^= index1 + index2;
        *lv2 ^= index2;
    }

    R0 = REVERSE(R0);
    R1 = REVERSE(R1);
    L0 = REVERSE(L0);
    L1 = REVERSE(L1);

    unsigned* out = (unsigned*)outblock;
    out[0] = R0;
    out[1] = R1;
    out[2] = L0;
    out[3] = L1;
}

int SEED::Decrypt(const void* in, size_t insize, void* out, size_t outsize, size_t* bytesWritten)
{
    size_t alignedSize = insize & 0xfffffff0;

    if (int err = CreateBuffers(alignedSize, alignedSize)) {
        return err;
    }

    ClearBuffers();

    for (unsigned i = 0; i < alignedSize; i++) {
        this->inBuffer[i] = ((unsigned char*)in)[i];
    }

    unsigned* xor_values = this->init_vector;
    unsigned* inPtr = (unsigned*)this->inBuffer;
    unsigned* outPtr = (unsigned*)this->outBuffer;
    size_t numBlocks = alignedSize >> 4;
    size_t blocksLeft = numBlocks;

    while (blocksLeft) {
        DecryptBlock(inPtr, outPtr);

        for (unsigned i = 0; i < 4; i++) {
            outPtr[i] ^= xor_values[i];
        }

        xor_values = inPtr;

        inPtr += 4;
        outPtr += 4;
        blocksLeft--;
    }

    memcpy(this->init_vector, xor_values, sizeof(this->init_vector));
    
    if (bytesWritten)
        *bytesWritten = 0;

    for (unsigned i = 0; i < alignedSize && i < outsize; i++) {
        ((unsigned char*)out)[i] = this->outBuffer[i];

        if (bytesWritten)
            *bytesWritten = (*bytesWritten) + 1;
    }

    ClearBuffers();

    return ERR_OK;
}
