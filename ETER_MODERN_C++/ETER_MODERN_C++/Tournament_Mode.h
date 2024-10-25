#pragma once
#include "Game.h"
#include "Wizard_Mode.h"
#include "Elements_Mode.h"

class Tournament_Mode :public Game ,public Wizard_Mode,public Elements_Mode
{

};

