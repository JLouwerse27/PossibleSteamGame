#pragma once

#include <atomic>
#include <cstdint>

extern bool jEditing;
extern std::atomic<bool> jRunning;

extern int jDirtLevel;

extern int jBlockSize;
extern int jXBlocksInCameraView;
extern int jYBlocksInCameraView;

extern std::atomic<uint32_t> jX;
extern std::atomic<uint32_t> jY;

extern bool jIsKeyPressed[32];

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int WORLD_WIDTH = 400;
const int WORLD_HEIGHT = 300;
const int WORLD_SIZE = WORLD_WIDTH * WORLD_HEIGHT;

extern unsigned char jWorldA[WORLD_SIZE];
extern unsigned char jWorldB[WORLD_SIZE];

extern std::atomic<unsigned char*> jRenderWorld;
extern unsigned char* jLogicWorld;

extern bool jNextTurn;
