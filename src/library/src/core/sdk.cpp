#include <core/sdk.hpp>

#include <windows.h>

Sdk::Sdk() {
  if (GetModuleHandleA("StarRail.exe"))
    InitStarRail();
  else
    InitGenshinImpact();
}

void Sdk::InitGenshinImpact() {
  const auto mod = (uintptr_t)GetModuleHandleA(nullptr);

  funcs_.set_field_of_view = mod + 0x1027470;
  funcs_.set_target_frame_rate = mod + 0x123dd80;
  funcs_.quit = mod + 0x102be90;
  funcs_.set_vsync_count = mod + 0x8918b0;
  funcs_.set_fog = mod + 0x890920;

  is_star_rail_ = false;
}

void Sdk::InitStarRail() {
  const auto game_assembly = (uintptr_t)GetModuleHandleA("GameAssembly.dll");
  const auto unity_player = (uintptr_t)GetModuleHandleA("UnityPlayer.dll");

  funcs_.set_field_of_view = unity_player + 0xf28c00;
  funcs_.set_target_frame_rate = game_assembly + 0x154c9910;
  funcs_.quit = game_assembly + 0x154c9440;
  funcs_.set_vsync_count = game_assembly + 0x1550a870;
  funcs_.enter = game_assembly + 0x7497160;
  funcs_.leave = game_assembly + 0x749ad70;

  is_star_rail_ = true;
}
