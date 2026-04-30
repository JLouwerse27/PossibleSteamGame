#include "jClientLogic.h"
#include "jVariables.h"
#include <thread>
#include <chrono>
#include <iostream>

void JGameLogic::runGameLogic(JPlayer* jpl) {
    uint32_t height = 1;//measured in blocks, not pixels
    atEdge[0] = false; atEdge[1] = false; atEdge[2] = false; atEdge[3] = false;
    goingThisDirection[0] = false; 
    goingThisDirection[1] = false; 
    //goingThisDirection[2] = false; 
    goingThisDirection[3] = false;//up, left, down, right
    //while (jRunning) {

    if (tick % 1 == 0) {

		inAir = false;

        if(isGoingDownNextTick){
            if (jWorldA[(jpl->y/jBlockHeight + yIncrement) * WORLD_WIDTH + jpl->x/jBlockWidth] != 1) {
                jpl->y += yIncrement;
                yIncrement++;
                isGoingDownNextTick = false;
            }
            else {
                for(int i = yIncrement; i > 0; i--) {
                    if (jWorldA[(jpl->y / jBlockHeight + i) * WORLD_WIDTH + jpl->x / jBlockWidth] != 1) {
                        jpl->y += i;
                        yIncrement = 1;
                        isGoingDownNextTick = false;
                        break;
                    }
				}
            }
		}
        if (isGoingUpNextTick) {
            jpl->y-=yIncrement;
			yIncrement++;
            if(yIncrement > 3) {
                yIncrement = 3;
			}
			isGoingUpNextTick = false;
        }

        if (jIsMousePressed[0]) {
            if (mouseX >= 0 && mouseX < WINDOW_WIDTH && mouseY >= 0 && mouseY < WINDOW_HEIGHT) {
                int blockX = (static_cast<float>(mouseX + (jpl->x % jBlockWidth)) / static_cast<float>(jBlockWidth)) * (static_cast<float>(ORIGINAL_WINDOW_WIDTH) / static_cast<float>(WINDOW_WIDTH));
                int blockY = (static_cast<float>(mouseY + (jpl->y % jBlockHeight)) / static_cast<float>(jBlockHeight)) * (static_cast<float>(ORIGINAL_WINDOW_HEIGHT) / static_cast<float>(WINDOW_HEIGHT));
                int worldX = blockX + jX;
                int worldY = blockY + jY;
                if (worldX >= 0 && worldX < WORLD_WIDTH && worldY >= 0 && worldY < WORLD_HEIGHT) {
                    int extraBlockRight = 0;
					int extraBlockDown = 0;
                    //if (jpl->x % jBlockWidth != 0) extraBlockRight = 1;
                    //if (jpl->y % jBlockHeight != 0) extraBlockDown = 1;

                    jWorldA[(worldY + extraBlockDown) * WORLD_WIDTH + worldX + extraBlockRight] = 0;
                    jWorldB[(worldY + extraBlockDown) * WORLD_WIDTH + worldX + extraBlockRight] = 0;
                }
            }
        }


        if (jIsKeyPressed[0] && jY > 0) {
            bool canGoUp = true;
            if (jpl->x % jBlockWidth != 0) {
                if (jWorldA[(jpl->y / jBlockHeight + 1) * WORLD_WIDTH + jpl->x / jBlockWidth + 1] == 1) {
                    if (jWorldA[(jpl->y / jBlockHeight - 1) * WORLD_WIDTH + jpl->x / jBlockWidth + 1] != 1) {
                        if (!goingThisDirection[0]) {
                            canGoUp = true;
                        }
                    }
                    else {
                        canGoUp = false;
                        goingThisDirection[0] = false;
						tickJumpStarted = -3000;
                    }
                }//if there isn't a block below and one right of the player and he/she presses W, then don't do anything
                //because there might be a block directly below the player to jump from
            }
            
            if (jWorldA[(jpl->y / jBlockHeight + 1) * WORLD_WIDTH + jpl->x / jBlockWidth] == 1 && canGoUp) {
                if (jWorldA[(jpl->y / jBlockHeight - 1) * WORLD_WIDTH + jpl->x / jBlockWidth] != 1) {
                    if (!goingThisDirection[0]) {
                        goingThisDirection[0] = true;
                        tickJumpStarted = tick;
                    }
                }
                else {
					canGoUp = false;
                    goingThisDirection[0] = false;
                    tickJumpStarted = -3000;
                }
            }
            else {
                canGoUp = false;
            }
            
            if (canGoUp) {
                jpl->y -= yIncrement;
                goingThisDirection[0] = true;
                tickJumpStarted = tick;
            }

        }
        if (jIsKeyPressed[2] && jY < WORLD_HEIGHT - jYBlocksInCameraView) {
            //jY++;
        }
        if (jIsKeyPressed[1] && jX > 0) {
            bool canGoLeft = true;
            if (jpl->y % jBlockHeight != 0) {
                if (jpl->x % jBlockWidth != 0) {
                    if (jWorldA[(jpl->y / jBlockHeight + 1) * WORLD_WIDTH + jpl->x / jBlockWidth - 1 + 1] != 1) {
                        if ((jpl->x % jBlockWidth) < (jBlockWidth / speedMod)) {
                            canGoLeft = false;
                        }
                    }
                    else {
                        canGoLeft = false;
                    }
                }
                else {
                    if (jWorldA[(jpl->y / jBlockHeight + 1) * WORLD_WIDTH + jpl->x / jBlockWidth - 1] != 1) {
                        //canGoLeft = true;
                    }
                    else {
						canGoLeft = false;
                    }
                }
            }
            if (jpl->x % jBlockWidth != 0) {
                if (jWorldA[(jpl->y / jBlockHeight) * WORLD_WIDTH + jpl->x / jBlockWidth - 1 + 1] != 1) {
                    if ((jpl->x % jBlockWidth) >= (jBlockWidth / speedMod)) {
                        //canGoLeft = true;
                    }
                    else {
                        canGoLeft = false;
                    }
                }
                else {
                    canGoLeft = false;
                }
            }
            else {
                if (jWorldA[(jpl->y / jBlockHeight) * WORLD_WIDTH + jpl->x / jBlockWidth - 1] != 1) {
					//canGoLeft = true;
                }
                else {
                    canGoLeft = false;
                }
            }
            if (canGoLeft) {
                jpl->x -= jBlockWidth / speedMod;
                goingThisDirection[1] = true;
            }
        }

        if (jIsKeyPressed[3] && jX < WORLD_WIDTH - jXBlocksInCameraView) {
            bool canGoRight = true;
            if (jpl->y % jBlockHeight != 0) {
                if (jpl->x % jBlockWidth != 0) {
                    if (jWorldA[(jpl->y / jBlockHeight + 1) * WORLD_WIDTH + jpl->x / jBlockWidth + 1] != 1) {
                        if (jBlockWidth - (jpl->x % jBlockWidth) < (jBlockWidth / speedMod)) {
                            canGoRight = false;
                        }
                    }
                    else {
                        canGoRight = false;
                    }
                }
                else {
                    if (jWorldA[(jpl->y / jBlockHeight + 1) * WORLD_WIDTH + jpl->x / jBlockWidth + 1] == 1) {
                        canGoRight = false;
                    }
                }
            }
            //do not put else here, we need to check for the block to the right of the player in both cases
            if (jpl->x % jBlockWidth != 0) {
                if (jWorldA[(jpl->y / jBlockHeight) * WORLD_WIDTH + jpl->x / jBlockWidth + 1] != 1) {
                    if (jBlockWidth - (jpl->x % jBlockWidth) < (jBlockWidth / speedMod)) {
                        canGoRight = false;
                    }
                }
                else {
                    canGoRight = false;
                }
            }
            else {
                if (jWorldA[(jpl->y / jBlockHeight) * WORLD_WIDTH + jpl->x / jBlockWidth + 1] != 1) {
                    //canGoRight = true;
                }
                else {
                    canGoRight = false;
                }
            }
            if (canGoRight) {
                jpl->x += jBlockWidth / speedMod;
                goingThisDirection[3] = true;
            }
        }

        if (jWorldA[(jpl->y / jBlockHeight + 1) * WORLD_WIDTH + jpl->x / jBlockWidth] != 1) {
            inAir = true;
        }

        if(jpl-> x % jBlockWidth != 0 && inAir) {
            if (jWorldA[(jpl->y / jBlockHeight + 1) * WORLD_WIDTH + jpl->x / jBlockWidth + 1] != 1) {
                inAir = true;
            }
            else {
				inAir = false;
            }
		}
        
        if (inAir) {
            if (tickJumpStarted + timeInAir <= tick) {
                //check the block "directly" (could be slightly to the left) below the    
                if (jWorldA[(jpl->y / jBlockHeight + 1) * WORLD_WIDTH + jpl->x / jBlockWidth] != 1) {
                    bool canGoDown = true;
                    if (jpl->x % jBlockWidth != 0) {
                        if (jWorldA[(jpl->y / jBlockHeight + 1) * WORLD_WIDTH + jpl->x / jBlockWidth + 1] != 1) {
                            canGoDown = true;
                        }
                        else {
                            canGoDown = false;
                        }
                    }
                    if (tick % 2 == 0 && canGoDown) {
                        isGoingDownNextTick = true;
                        goingThisDirection[0] = false;
                        goingThisDirection[2] = true;
                    }
                } 
            }
            else if (tickJumpStarted + timeInAir > tick) {
                if (jpl->y % jBlockHeight != 0) {
                    bool canGoUp = true;
                    if (jpl->x % jBlockWidth != 0) {
                        //check the block above and to the right of the player if the player isn't perfectly aligned with x axis
                        if (jWorldA[(jpl->y / jBlockHeight - 1) * WORLD_WIDTH + jpl->x / jBlockWidth + 1] == 1) {
                            if (jpl->y % jBlockHeight < yIncrement) {
								yIncrement = jpl->y % jBlockHeight;
                            }
                        }
                    }
                    //check the block directly above the player regardless
                    if (jWorldA[(jpl->y / jBlockHeight - 1) * WORLD_WIDTH + jpl->x / jBlockWidth] == 1) {
                        if (jpl->y % jBlockHeight < yIncrement) {
                            yIncrement = jpl->y % jBlockHeight;
                        }
                    }

                    if (canGoUp) {
                        if (tick % 3 == 0) {
                            isGoingUpNextTick = true;
                            goingThisDirection[0] = true;
                            goingThisDirection[2] = false;
                        }
                    }
                    else {
                        isGoingUpNextTick = false;
                        goingThisDirection[0] = false;
                    }
                }
                else {
                    bool canGoUp = true;
                    if (jWorldA[(jpl->y / jBlockHeight - 1) * WORLD_WIDTH + jpl->x / jBlockWidth] != 1) {
                        if (jpl->x % jBlockWidth != 0) {
                            if (jWorldA[(jpl->y / jBlockHeight - 1) * WORLD_WIDTH + jpl->x / jBlockWidth + 1] == 1) {
                                canGoUp = false;
                            }
                        }
                        if (jWorldA[(jpl->y / jBlockHeight - 1) * WORLD_WIDTH + jpl->x / jBlockWidth] == 1) {
                            canGoUp = false;
                        }
                            
                    }
                    else {
                        canGoUp = false;
                    }
                    if (canGoUp) {
                        if (tick % 3 == 0) {
                            isGoingUpNextTick = true;
                            goingThisDirection[0] = true;
                            goingThisDirection[2] = false;
                        }
                    }
                    else {
                        isGoingUpNextTick = false;
                        goingThisDirection[0] = false;
                    }
                }
            }

            if (jpl->y % jBlockHeight == 0) {
                if (jpl->x % jBlockWidth != 0) {
                    if (jWorldA[(jpl->y / jBlockHeight + 1) * WORLD_WIDTH + jpl->x / jBlockWidth + 1] == 1 && tickJumpStarted + timeInAir <= tick) {
                        inAir = false;
                        goingThisDirection[2] = false;
                        yIncrement = 1;
                    }
                }
                if (jWorldA[(jpl->y / jBlockHeight + 1) * WORLD_WIDTH + jpl->x / jBlockWidth] == 1 && tickJumpStarted + timeInAir <= tick) {
                    inAir = false;
                    goingThisDirection[2] = false;
                    yIncrement = 1;
                }
            }
        }

        //edges
        /*if (jIsKeyPressed[0] && jpl->y > 0) {
            if (jY > 0 + jYBlocksInCameraView) {
                jY--;
                atEdge[0] = false;
            }
            else {
                atEdge[0] = true;
                jpl->y--;
            }
        }

        if (jIsKeyPressed[2] && jpl->y < WORLD_HEIGHT) {
            if (jY < WORLD_HEIGHT - jYBlocksInCameraView) {
                jY++;
                atEdge[2] = false;
            }
            else {
                atEdge[2] = true;
                jpl->y++;
            }
        }

        if (jIsKeyPressed[1] && jpl->x > 0) {
            if (jX > 0 && !atEdge[3]) {
                jX--;
                atEdge[1] = false;
            }
            else{
                if (jX < 0) jX = 0;
                if (jX == 0) {
                    atEdge[1] = true;
                    if (jpl->x > 0) {
                        jpl->x--;
                    }
                }
                else {
                    if (jpl->x <= WORLD_WIDTH - jXBlocksInCameraView/2) {
                        jX--;
                    }
                    if (jpl->x > 0) {
                        jpl->x--;
                    }
                }
            }
        }

        if (jIsKeyPressed[3] && jpl->x < WORLD_WIDTH) {
            if (jX < WORLD_WIDTH - jXBlocksInCameraView && !atEdge[1]) {
                jX++;
                atEdge[3] = false;
            }
            else {
                if (jX > WORLD_WIDTH - jXBlocksInCameraView) jX = WORLD_WIDTH - jXBlocksInCameraView;
                if (jX == WORLD_WIDTH - jXBlocksInCameraView) {
                    atEdge[3] = true;
                    if (jpl->x < WORLD_WIDTH) {
                        jpl->x++;
                    }
                }
                else {
                    if (jpl->x >= jXBlocksInCameraView / 2) {
                        atEdge[1] = false;
                        jX++;
                    }
                    if (jpl->x < WORLD_WIDTH) {
                        jpl->x++;
                    }
                }
            }
        }*/

        //if (!atEdge[0] && !atEdge[1] && !atEdge[2] && !atEdge[3]) {
        //jpl->x = ((jX + jXBlocksInCameraView / 2));
        //jpl->y = ((jY + jYBlocksInCameraView / 2 - 1));
        //}
        jX = ((jpl->x / jBlockWidth - jXBlocksInCameraView / 2));
        jY = ((jpl->y / jBlockHeight- jYBlocksInCameraView / 2));
    }
    tick++;
}
