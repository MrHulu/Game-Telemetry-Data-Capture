#pragma once

#include "Game/Game.h"

class GameWithUdp : public Game
{
    Q_OBJECT
public:
    explicit GameWithUdp(QObject *parent = nullptr);
};

