#ifndef KART_TIRE_H
#define KART_TIRE_H

#define MK8_KART_TIRE_CTOR 0x021AA9B4

namespace object {
class KartTire {
public:
  int field_00;
  int field_04;
  int field_08;
  int field_0C;
  int field_10;
  int field_14;
  int field_18;
  int field_1C;
  int field_20;
  int field_24;
  int field_28;
  int field_2C;
  int field_30;
  int field_34;
  int field_38;
  int field_3C;
  int field_40;
  int field_44;
  int field_48;
  int field_4C;
  int field_50;
  int field_54;
  int field_58;
  int field_5C;
  int field_60;
  int field_64;
  int field_68;
  int field_6C;
  int field_70;
  int field_74;
  int field_78;
  int field_7C;
  int field_80;
  int field_84;
  int field_88;
  int field_8C;
  int field_90;
  int field_94;
  int field_98;
  int field_9C;
  int field_A0;
  int field_A4;
  int field_A8;
  int field_AC;
  int field_B0;
  int field_B4;
  int field_B8;
  int field_BC;
  int field_C0;
  int field_C4;
  int field_C8;
  int field_CC;
  int field_D0;
  int field_D4;
  int field_D8;
  int field_DC;
  int field_E0;
  int field_E4;
  int field_E8;
  int field_EC;
  int field_F0;
  int field_F4;
  int field_F8;
  int field_FC;
  int field_100;
  int field_104;
  int field_108;
  int field_10C;
  int field_110;
  int field_114;
  int field_118;
  int field_11C;
  int field_120;
  int field_124;
  int field_128;
  int field_12C;
  int field_130;
  int field_134;
  int field_138;
  int field_13C;
  int field_140;
  int field_144;
  int field_148;
};
} // namespace object

static_assert(sizeof(object::KartTire) == 0x14C,
              "Class doesn't match game class size");

#endif