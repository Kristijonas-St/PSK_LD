#pragma once
#include "../player_blueprint.h"

class Computer : public PlayerBlueprint
{
private:
    void initializeFixedBoatsPlacement();

public:
    Computer() {
        initializeFixedBoatsPlacement();    
    }

    int shootUserAt();
};