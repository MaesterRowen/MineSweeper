#ifndef _GAMEBOARD_H_
#define _GAMEBOARD_H_

#include <strata/strata.h>

typedef enum _BLOCKTYPE {
    BLOCK_EMPTY,
    BLOCK_ONE,
    BLOCK_TWO,
    BLOCK_THREE,
    BLOCK_FOUR,
    BLOCK_FIVE,
    BLOCK_SIX,
    BLOCK_SEVEN,
    BLOCK_EIGHT,
    BLOCK_BOMB
} BLOCKTYPE;

typedef enum _TILETYPE
{
    BOARD_EMPTY, BOARD_ONE, BOARD_TWO, BOARD_THREE, BOARD_FOUR, BOARD_FIVE, BOARD_SIX, BOARD_SEVEN, BOARD_EIGHT, BOARD_HIDDEN, 
    BOARD_BOMB, BOARD_BOMB_WRONG, BOARD_BOMB_EXPLODE,
    BOARD_QUESTION, BOARD_FLAG,
    DISPLAY_FIRST, 
    DISPLAY_ZERO = DISPLAY_FIRST,
    DISPLAY_ONE,
    DISPLAY_TWO,
    DISPLAY_THREE,
    DISPLAY_FOUR,
    DISPLAY_FIVE,
    DISPLAY_SIX,
    DISPLAY_SEVEN,
    DISPLAY_EIGHT,
    DISPLAY_NINE,
    DISPLAY_LAST = DISPLAY_NINE,
    STATUS_SMILE, STATUS_SHOCKED, STATUS_SAD, STATUS_COOL, STATUS_PRESSED,
    TILETYPE_COUNT,
} TILETYPE;

class GameBoard
{
public:
    GameBoard( float tileSize, DWORD boardWidth, DWORD boardHeight, DWORD bombCount );
    ~GameBoard( VOID );
    
    VOID UpdateGraphic( DWORD idx );
    VOID SetCenter( FLOAT x, FLOAT y );
    BOOL CheckForTouch( FLOAT x, FLOAT y );
    BOOL ToggleFlag( FLOAT x, FLOAT y );
    VOID Draw( Strata::SpriteRenderer& renderer, DWORD layer );

private:
    // Private methods
    VOID LoadTextureHandles( VOID );
    DWORD CountAdjacentBombs(DWORD index);
    BOOL RevealBlocks( DWORD idx );
    BLOCKTYPE RevealItem( DWORD idx );

    typedef struct {
        FLOAT PosX;
        FLOAT PosY;
        TILETYPE TileID;
        BLOCKTYPE BlockType;
        BOOL Flagged;
        BOOL Revealed;
    } BLOCK;

    DWORD mTextureHandles[TILETYPE_COUNT];

    BLOCK * mBlocks;

    FLOAT mCenterX, mCenterY;

    Strata::COLOR mColorFactor;
    DWORD mBoardWidth;
    DWORD mBoardHeight;
    DWORD mTileCount;
    FLOAT mTileSize;
    DWORD mTotalBombCount;

    DWORD mTileAtlasHandle;
};

#endif