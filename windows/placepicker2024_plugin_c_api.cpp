#include "include/placepicker2024/placepicker2024_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "placepicker2024_plugin.h"

void Placepicker2024PluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  placepicker2024::Placepicker2024Plugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
