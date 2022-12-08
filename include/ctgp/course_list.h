#pragma once

#include <cafe.h>

namespace ctgp {

struct CourseEntry {
    char* m_DirName;   // e.g "Gwii_MarioCircuit"
    wchar_t* m_Retro;  // e.g L"Wii" or nullptr
    wchar_t* m_Name;   // e.g L"Mario Circuit"
    wchar_t* m_Author; // e.g L"TrackAuthor420" or nullptr
};

struct CupEntry {
    int m_PageIdx;
    int m_CupIdx;
    char* m_PicPath;
    wchar_t* m_CupName;
    CourseEntry m_Tracks[4];
};

static CupEntry g_CustomTrackList[] = {
    { 1,
      0,
      "Golden_Dash_Cup",
      L"Golden Dash Cup",
      {
          { "Ginvalid", L"Tour", L"Paris Promenade", L"" },
          { "Ginvalid", L"3DS", L"Toad Circuit", L"" },
          { "Ginvalid", L"N64", L"Choco Mountain", L"" },
          { "Ginvalid", L"Wii", L"Coconut Mall", L"" },
      } },
    { 1,
      1,
      "Lucky_Cat_Cup",
      L"Lucky Cat Cup",
      {
          { "Ginvalid", L"Tour", L"Tokyo Blur", L"" },
          { "Ginvalid", L"3DS", L"Shroom Ridge", L"" },
          { "Ginvalid", L"GBA", L"Sky Garden", L"" },
          { "Ginvalid", L"Tour", L"Ninja Hideaway", L"" },
      } },
    { 1,
      2,
      "Turnip_Cup",
      L"Turnip Cup",
      {
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
      } },
    { 1,
      3,
      "Propeller_Cup",
      L"Propeller Cup",
      {
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
      } },
    { 1,
      4,
      "Fruit_Cup",
      L"Fruit Cup",
      {
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
      } },
    { 1,
      5,
      "Boomerang_Cup",
      L"Boomerang Cup",
      {
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
      } },
    { 1,
      6,
      "Feather_Cup",
      L"Feather Cup",
      {
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
      } },
    { 1,
      7,
      "Cherry_Cup",
      L"Cherry Cup",
      {
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
      } },
    { 1,
      8,
      "Rock_Cup",
      L"Rock Cup",
      {
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
      } },
    { 1,
      9,
      "Acorn_Cup",
      L"Acorn Cup",
      {
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
      } },
    { 1,
      10,
      "Moon_Cup",
      L"Moon Cup",
      {
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
      } },
    { 1,
      11,
      "Spiny_Cup",
      L"Spiny Cup",
      {
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
          { "Ginvalid", L"", L"", L"" },
      } },
    { 2,
      0,
      "1UP_Cup",
      L"1UP Cup",
      {
          { "Gu_SplashCourse", L"", L"Splash Circuit", L"" },
          { "Gu_RvlCanyon", L"", L"Canyon Run", L"" },
          { "Gu_Kentakara", L"", L"Kentakara Raceway", L"" },
          { "Gu_RustyHills", L"", L"Rusty Hills", L"" },
      } },
    { 2,
      1,
      "Hammer_Cup",
      L"Hammer Cup",
      {
          { "Gu_PdftLikeTheWind", L"", L"PDFT LIKE THE WIND", L"" },
          { "Gu_Vancouver", L"", L"Vancouver Velocity", L"" },
          { "Gds_BowserCastle", L"DS", L"Bowser Castle", L"" },
          { "Gu_SkyArena", L"", L"Sky Arena", L"" },
      } },
    { 2,
      4,
      "Pickaxe_Cup",
      L"Pickaxe Cup",
      {
          { "G3ds_DaisyHills", L"3DS", L"Daisy Hills", L"" },
          { "Gwii_KongSummit", L"Wii", L"DK Summit", L"" },
          { "Gwii_MapleTreeway", L"Wii", L"Maple Treeway", L"" },
          { "G3ds_Wuhu", L"3DS", L"Wuhu Loop", L"" },
      } },
    { 2,
      5,
      "Stamp_Cup",
      L"Stamp Cup",
      {
          { "G64_BowserCastle", L"N64", L"Bowser Castle", L"" },
          { "Gwii_MarioCircuit", L"Wii", L"Mario Circuit", L"" },
          { "Gds_DesertHills", L"DS", L"Desert Hills", L"" },
          { "G64_MarioRaceway", L"N64", L"Mario Raceway", L"" },
      } },
    { 2,
      2,
      "Bomb_Cup",
      L"Bomb Cup",
      {
          { "Gwii_Coconut", L"Wii", L"Coconut Mall", L"" },
          { "Gu_DivBowser", L"", L"Bowser's Castle", L"" },
          { "Gu_PacMountain", L"", L"PAC-Mountain", L"" },
          { "Gu_NinjaHideaway", L"", L"Ninja Hideaway", L"" },
      } },
};

} // namespace ctgp
