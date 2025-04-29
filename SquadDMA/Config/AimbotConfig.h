#pragma once
#include "pch.h"
class AimbotConfig
{
    std::string ConfigName;

public:
    AimbotConfig(const std::string& name)
    {
        ConfigName = name;
    }
    bool Enable = true;
    bool DrawFov = false;
    int Fov = 90;
    int Key = 0x46;
    json ToJson()
    {
        json j;
        j[ConfigName][LIT("Enable")] = Enable;
        j[ConfigName][LIT("DrawFov")] = DrawFov;
        j[ConfigName][LIT("Fov")] = Fov;
        j[ConfigName][LIT("Key")] = Key;
        return j;
    }
    void FromJson(const json& j)
    {
        if (!j.contains(ConfigName))
            return;
        if (j[ConfigName].contains(LIT("Enable")))
            Enable = j[ConfigName][LIT("Enable")];
        if (j[ConfigName].contains(LIT("DrawFov")))
            DrawFov = j[ConfigName][LIT("DrawFov")];
        if (j[ConfigName].contains(LIT("Fov")))
            Fov = j[ConfigName][LIT("Fov")];
        if (j[ConfigName].contains(LIT("Key")))
            Key = j[ConfigName][LIT("Key")];
    }
};

