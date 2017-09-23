#pragma once
#include "../src_headers.h"
class CBaseCombatWeapon{
public:
    int GetAmmoInClip(){
        return util::readptr<int>(this, 0x3204);
    }
};