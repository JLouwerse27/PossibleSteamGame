#include "jVariables.h"

bool jEditing = false;
std::atomic<bool> jRunning = true;

int jDirtLevel = 100;

int jBlockSize = 15;
int jXBlocksInCameraView = WINDOW_WIDTH / jBlockSize;
int jYBlocksInCameraView = WINDOW_HEIGHT / jBlockSize;

std::atomic<uint32_t> jX = WORLD_WIDTH/2 - jXBlocksInCameraView/2;
std::atomic<uint32_t> jY = jDirtLevel - jYBlocksInCameraView/2;

bool jIsKeyPressed[32] = {};
bool jIsMousePressed[5] = {};

int WINDOW_WIDTH = 600;
int WINDOW_HEIGHT = 450;

unsigned char jWorldA[WORLD_SIZE] = {};
unsigned char jWorldB[WORLD_SIZE] = {};


std::atomic<unsigned char*> jRenderWorld = nullptr;
unsigned char* jLogicWorld = nullptr;

bool jNextTurn = false;