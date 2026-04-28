#pragma once

#include <atomic>
#include <cstdint>
#include <vector>
#include <cstdint>

extern bool jEditing;
extern std::atomic<bool> jRunning;

extern int jDirtLevel;

extern int jBlockWidth;
extern int jBlockHeight;
extern int jXBlocksInCameraView;
extern int jYBlocksInCameraView;

extern std::atomic<uint32_t> jX;
extern std::atomic<uint32_t> jY;

extern bool jIsKeyPressed[32];
extern bool jIsMousePressed[5];

extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
const extern int ORIGINAL_WINDOW_WIDTH;
const extern int ORIGINAL_WINDOW_HEIGHT;

const int WORLD_WIDTH = 400;
const int WORLD_HEIGHT = 300;
const int WORLD_SIZE = WORLD_WIDTH * WORLD_HEIGHT;

extern unsigned char jWorldA[WORLD_SIZE];
extern unsigned char jWorldB[WORLD_SIZE];

extern std::atomic<unsigned char*> jRenderWorld;
extern unsigned char* jLogicWorld;

extern bool jNextTurn;

extern int mouseX;
extern int mouseY;
