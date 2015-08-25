#pragma once;
enum TileType {
		GRASS = 0x01,
		ROAD = 0x02,
		SIDEWALK = 0x03,
		DIRT = 0x04,
		CONCRETE = 0x05,
		LINOLEUM = 0x06,
		GLASS = 0x07,
		STEEL = 0x08,
		DEBRIS = 0x09,
		WOOD = 0x0a,
		TREE = 0x0b,
		CONCRETEBARRIER = 0x0c,
		WATER = 0x0d,
		OPENDOOR = 0x10,
		CLOSEDDOOR = 0x11,
		CHAINLINKFENCE,
		WOODFENCE
		
};
enum SoundSource {
	HUMANSOUND = 0x01,
	DOGSOUND   = 0x02,
	LIVESTOCKSOUND = 0x03,
	VERMINSOUND    = 0x05,
	ZOMBIESOUND    = 0x07,
	WILDPREDATORSOUND = 0x08,
	WILDPREYSOUND    = 0x09,
	GUNSOUND		= 0x0a,
	EXPLOSIONSOUND   = 0x0b,
	CLANGSOUND   =     0x0c,
	CRASHSOUND   =     0x0d,
	CREAKSOUND   =     0x10,
	BANGSOUND   =     0x11,
	THUMPSOUND   =     0x12,
	CRUNCHSOUND   =     0x13,
};
enum ScentSource {
	HUMANSCENT = 0x01,
	DOGSCENT   = 0x02,
	LIVESTOCKSCENT = 0x03,
	UNNATURALSCENT = 0x04,
	VERMINSCENT    = 0x05,
	DECAYSCENT     = 0x06,
	ZOMBIESCENT    = 0x07,
	WILDPREDATORSCENT = 0x08,
	WILDPREYSCENT    = 0x09
};
enum DamageSource {
	UNARMED = 0x01,
	BLUNT = 0x02,
	PIERCING = 0x03,
	DISEASED = 0x04,
	EXPLOSIVE = 0x05,
	INCENDIARY = 0x06,
	RADIOACTIVE = 0x07
};

union PassedValue
{
	bool		mode;
    int         iValue1; 
    int         iValue2;
    double      dValue;  
};
