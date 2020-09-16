//======================================================
//  Select your region
//======================================================

#define CFG_eu868       //  Use this for Europe
//#define CFG_us915     //  Use this for the Americas

//======================================================
//  Values from your TTN dashboard
//======================================================
// LoRaWAN NwkSKey, network session key
// This should be in big-endian (aka msb).
static u1_t NWKSKEY[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
// LoRaWAN AppSKey, application session key
// This should also be in big-endian (aka msb).
static u1_t APPSKEY[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
// LoRaWAN end-device address (DevAddr)
// See http://thethingsnetwork.org/wiki/AddressSpace
// The library converts the address to network byte order as needed, so this should be in big-endian (aka msb) too.
static u4_t DEVADDR = 0x00000000 ; // <-- Change this address for every node!
