#pragma once

#define BASIC_BLOKS 14
#define WINDOW_WIDTH 1400
#define WINDOW_HEIGHT 1000

#define SHAPE_WIDTH 85.f
#define SHAPE_HEIGHT 85.f

#define DEFUALT_DISTANCE -1

enum class Situation
{
	GameBegin,
	LevelRunnig,
	LevelSucced,
	LevelFailed,
	GameFinished,
};