#include "jVariables.h"

bool jEditing = false;
std::atomic<bool> jRunning = true;

int jDirtLevel = 100;

int jBlockWidth = 8;
int jBlockHeight = 8;
int jXBlocksInCameraView = WINDOW_WIDTH / jBlockWidth;
int jYBlocksInCameraView = WINDOW_HEIGHT / jBlockHeight;

std::atomic<uint32_t> jX = WORLD_WIDTH/2 - jXBlocksInCameraView/2;
std::atomic<uint32_t> jY = jDirtLevel - jYBlocksInCameraView/2;

bool jIsKeyPressed[32] = {};//w,a,s,d,shift,space,tab,.,,
bool jIsMousePressed[5] = {};//left, right, middle, x1, x2

const int ORIGINAL_WINDOW_WIDTH = 600;
const int ORIGINAL_WINDOW_HEIGHT = 480;

int WINDOW_WIDTH = ORIGINAL_WINDOW_WIDTH;
int WINDOW_HEIGHT = ORIGINAL_WINDOW_HEIGHT;

unsigned char jWorldA[WORLD_SIZE] = {};
unsigned char jWorldB[WORLD_SIZE] = {};


std::atomic<unsigned char*> jRenderWorld = nullptr;
unsigned char* jLogicWorld = nullptr;

bool jNextTurn = false;

int mouseX = 0;
int mouseY = 0;