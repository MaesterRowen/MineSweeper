#include "gameboard.h"

GameBoard::GameBoard( FLOAT tileSize, DWORD boardWidth, DWORD boardHeight, DWORD bombCount )
{
    // Store board configuration
    mTileSize = tileSize;
    mBoardHeight = boardHeight;
    mBoardWidth = boardWidth;
    mTotalBombCount = bombCount;

    mCenterX = 0.0f;
    mCenterY = 0.0f;

    // Build our board objects
    mTileCount = boardWidth * boardHeight;
    mBlocks = new BLOCK[mTileCount];
    memset( mBlocks, 0, sizeof(BLOCK) * mTileCount );

    // Set data for each block
    for( DWORD idx = 0; idx < mTileCount; idx++ )
    {
        mBlocks[idx].Flagged = FALSE;
        mBlocks[idx].Revealed = FALSE;
        mBlocks[idx].PosX = (idx % mBoardWidth) * tileSize;
        mBlocks[idx].PosY = (idx / mBoardWidth) * tileSize;
        mBlocks[idx].TileID = TILETYPE::BOARD_HIDDEN;
        mBlocks[idx].BlockType = BLOCKTYPE::BLOCK_EMPTY;
    }

    // Seed our random number generator
    u64 timeStamp = 0ULL;
    timeGetCurrentTime(TimeType_Default, &timeStamp );
    std::cout << "Time:  " << (unsigned int)timeStamp << std::endl;
    srand( (unsigned int)timeStamp );

    // Next, loop through the array and randomly add bombs
    for( DWORD idx = 0; idx < bombCount; idx++ )
    {
        // Select a random index on the board
        bool loop = true;
        do
        {
            int idx = rand() % mTileCount;
            if( mBlocks[idx].BlockType != BLOCKTYPE::BLOCK_BOMB )
            {
                mBlocks[idx].BlockType = BLOCKTYPE::BLOCK_BOMB;
                loop = false;
            }
        } while( loop == true );
    }

    // Finally, Add numbers
    for( DWORD idx = 0; idx < mTileCount; idx++ )
    {
        int count = CountAdjacentBombs(idx);
             if( count == 1 ) mBlocks[idx].BlockType = BLOCKTYPE::BLOCK_ONE;
        else if( count == 2 ) mBlocks[idx].BlockType = BLOCKTYPE::BLOCK_TWO;
        else if( count == 3 ) mBlocks[idx].BlockType = BLOCKTYPE::BLOCK_THREE;
        else if( count == 4 ) mBlocks[idx].BlockType = BLOCKTYPE::BLOCK_FOUR;
        else if( count == 5 ) mBlocks[idx].BlockType = BLOCKTYPE::BLOCK_FIVE;
        else if( count == 6 ) mBlocks[idx].BlockType = BLOCKTYPE::BLOCK_SIX;
        else if( count == 7 ) mBlocks[idx].BlockType = BLOCKTYPE::BLOCK_SEVEN;
        else if( count == 8 ) mBlocks[idx].BlockType = BLOCKTYPE::BLOCK_EIGHT;

        UpdateGraphic(idx);
    }

    // Store our texture handle
    mTileAtlasHandle = Strata::ResourceManager::GetTextureHandle("Sprites");

    // Save our color factor
    mColorFactor.AsDWORD = MAKE_RGBA(255, 255, 255, 255);

    // Load all of our texture handles
    LoadTextureHandles();
}
GameBoard::~GameBoard( VOID )
{
    // Delete our block array
    delete [] mBlocks;
    mBlocks = NULL;
}

DWORD GameBoard::CountAdjacentBombs(DWORD index)
{
    // Do some sanity checking
    if (index < 0 || index > mTileCount - 1) return 0;
    if (mBlocks[index].BlockType == BLOCKTYPE::BLOCK_BOMB) return 0;

    // Convert index to coorindates
    DWORD x = index % mBoardWidth;
    DWORD y = index / mBoardWidth;

    DWORD counter = 0;

    // Check Top
    if (y < mBoardHeight - 1)
    {
        DWORD cx = x;
        DWORD cy = y + 1;

        if (mBlocks[cy * mBoardWidth + cx].BlockType == BLOCKTYPE::BLOCK_BOMB) counter++;
    }

    // Check Top Right
    if (y < mBoardHeight - 1 && x != mBoardWidth - 1)
    {
        DWORD cx = x + 1;
        DWORD cy = y + 1;
        if (mBlocks[cy * mBoardWidth + cx].BlockType == BLOCKTYPE::BLOCK_BOMB) counter++;
    }

    // Check Right
    if (x < mBoardWidth - 1)
    {
        DWORD cx = x + 1;
        DWORD cy = y;
        if (mBlocks[cy * mBoardWidth + cx].BlockType == BLOCKTYPE::BLOCK_BOMB) counter++;
    }

    // Check Bottom Right
    if (y > 0 && x != mBoardWidth - 1)
    {
        DWORD cx = x + 1;
        DWORD cy = y - 1;
        if (mBlocks[cy * mBoardWidth + cx].BlockType == BLOCKTYPE::BLOCK_BOMB) counter++;
    }

    // Check Bottom
    if (y > 0)
    {
        DWORD cx = x;
        DWORD cy = y - 1;
        if (mBlocks[cy * mBoardWidth + cx].BlockType == BLOCKTYPE::BLOCK_BOMB) counter++;
    }

    // Check Bottom Left
    if (y > 0 && x > 0)
    {
        DWORD cx = x - 1;
        DWORD cy = y - 1;
        if (mBlocks[cy * mBoardWidth + cx].BlockType == BLOCKTYPE::BLOCK_BOMB) counter++;
    }

    // Check Left
    if (x > 0)
    {
        DWORD cx = x - 1;
        DWORD cy = y;
        if (mBlocks[cy * mBoardWidth + cx].BlockType == BLOCKTYPE::BLOCK_BOMB) counter++;
    }

    // Check Top Left
    if (x > 0 && y < mBoardHeight - 1)
    {
        DWORD cx = x - 1;
        DWORD cy = y + 1;
        if (mBlocks[cy * mBoardWidth + cx].BlockType == BLOCKTYPE::BLOCK_BOMB) counter++;
    }

    return counter;
}


VOID GameBoard::SetCenter( FLOAT x, FLOAT y)
{
    mCenterX = x;
    mCenterY = y;
}

VOID GameBoard::LoadTextureHandles( VOID )
{
    mTextureHandles[BOARD_EMPTY] = Strata::ResourceManager::GetTextureHandle( mTileAtlasHandle, "Board_Empty");
    mTextureHandles[BOARD_ONE] = Strata::ResourceManager::GetTextureHandle( mTileAtlasHandle, "Board_1");
    mTextureHandles[BOARD_TWO] = Strata::ResourceManager::GetTextureHandle( mTileAtlasHandle, "Board_2");
    mTextureHandles[BOARD_THREE] = Strata::ResourceManager::GetTextureHandle( mTileAtlasHandle, "Board_3");
    mTextureHandles[BOARD_FOUR] = Strata::ResourceManager::GetTextureHandle( mTileAtlasHandle, "Board_4");
    mTextureHandles[BOARD_FIVE] = Strata::ResourceManager::GetTextureHandle( mTileAtlasHandle, "Board_5");
    mTextureHandles[BOARD_SIX] = Strata::ResourceManager::GetTextureHandle( mTileAtlasHandle, "Board_6");
    mTextureHandles[BOARD_SEVEN] = Strata::ResourceManager::GetTextureHandle( mTileAtlasHandle, "Board_7");
    mTextureHandles[BOARD_EIGHT] = Strata::ResourceManager::GetTextureHandle( mTileAtlasHandle, "Board_8");
    mTextureHandles[BOARD_HIDDEN] = Strata::ResourceManager::GetTextureHandle( mTileAtlasHandle, "Board_Hidden");
    mTextureHandles[BOARD_BOMB] = Strata::ResourceManager::GetTextureHandle( mTileAtlasHandle, "Board_Bomb" );
    mTextureHandles[BOARD_BOMB_WRONG] = Strata::ResourceManager::GetTextureHandle( mTileAtlasHandle, "Board_Bomb_Wrong" );
    mTextureHandles[BOARD_BOMB_EXPLODE] = Strata::ResourceManager::GetTextureHandle( mTileAtlasHandle, "Board_Bomb_Explode" );
    mTextureHandles[BOARD_QUESTION ] = Strata::ResourceManager::GetTextureHandle( mTileAtlasHandle, "Board_Question" );
    mTextureHandles[BOARD_FLAG ] = Strata::ResourceManager::GetTextureHandle( mTileAtlasHandle, "Board_Flag" );
}

VOID GameBoard::UpdateGraphic( DWORD idx )
{
    if( idx >= mTileCount ) return;

    BLOCK& block = mBlocks[idx];
    
    if( block.Revealed == true && block.BlockType == BLOCKTYPE::BLOCK_BOMB )
    {
        if( block.Flagged == true ) 
        {
            block.TileID = TILETYPE::BOARD_BOMB;
        }
        else 
        {
            block.TileID = TILETYPE::BOARD_BOMB_WRONG;
        }
    }
    else if( block.Revealed == true )
    {
        block.TileID = (TILETYPE)block.BlockType;
    }
    else if( block.Flagged == true )
    {
        block.TileID = TILETYPE::BOARD_FLAG;
    }
    else 
    {
        block.TileID = TILETYPE::BOARD_HIDDEN;
    }
}

BOOL GameBoard::RevealBlocks( DWORD idx )
{
    if( idx >= mTileCount ) return FALSE;
    BLOCK& block = mBlocks[idx];   

    if( block.Revealed == TRUE ) return FALSE;

    // Reveal item
    RevealItem(idx);

    // Convert index to coordinates
    DWORD x = idx % mBoardWidth;
    DWORD y = idx / mBoardWidth;

    // Check Top
    if (y < mBoardHeight - 1)
    {
        DWORD cx = x;
        DWORD cy = y + 1;

        if (mBlocks[cy * mBoardWidth + cx].BlockType == BLOCKTYPE::BLOCK_EMPTY && mBlocks[cy * mBoardWidth + cx].Flagged == FALSE)
        {
            RevealBlocks(cy * mBoardWidth + cx);
            RevealItem(cy * mBoardWidth + cx);
        }
        else if (mBlocks[cy * mBoardWidth + cx].BlockType >= BLOCKTYPE::BLOCK_ONE)
            RevealItem(cy * mBoardWidth + cx);
    }

    // Check Top Right
    if (y < mBoardHeight - 1 && x != mBoardWidth - 1)
    {
        DWORD cx = x + 1;
        DWORD cy = y + 1;

        if (mBlocks[cy * mBoardWidth + cx].BlockType == BLOCKTYPE::BLOCK_EMPTY && mBlocks[cy * mBoardWidth + cx].Flagged == FALSE)
        {
            RevealBlocks(cy * mBoardWidth + cx);
            RevealItem(cy * mBoardWidth + cx);
        }
        else if (mBlocks[cy * mBoardWidth + cx].BlockType >= BLOCKTYPE::BLOCK_ONE)
            RevealItem(cy * mBoardWidth + cx);
    }

    // Check Right
    if (x < mBoardWidth - 1)
    {
        DWORD cx = x + 1;
        DWORD cy = y;
        if (mBlocks[cy * mBoardWidth + cx].BlockType == BLOCKTYPE::BLOCK_EMPTY && mBlocks[cy * mBoardWidth + cx].Flagged == FALSE)
        {
            RevealBlocks(cy * mBoardWidth + cx);
            RevealItem(cy * mBoardWidth + cx);
        }
        else if (mBlocks[cy * mBoardWidth + cx].BlockType >= BLOCKTYPE::BLOCK_ONE)
            RevealItem(cy * mBoardWidth + cx);
    }

    // Check Bottom Right
    if (y > 0 && x != mBoardWidth - 1)
    {
        DWORD cx = x + 1;
        DWORD cy = y - 1;
        if (mBlocks[cy * mBoardWidth + cx].BlockType == BLOCKTYPE::BLOCK_EMPTY && mBlocks[cy * mBoardWidth + cx].Flagged == FALSE)
        {
            RevealBlocks(cy * mBoardWidth + cx);
            RevealItem(cy * mBoardWidth + cx);
        }
        else if (mBlocks[cy * mBoardWidth + cx].BlockType >= BLOCKTYPE::BLOCK_ONE)
            RevealItem(cy * mBoardWidth + cx);
    }

    // Check Bottom
    if (y > 0)
    {
        DWORD cx = x;
        DWORD cy = y - 1;
        if (mBlocks[cy * mBoardWidth + cx].BlockType == BLOCKTYPE::BLOCK_EMPTY && mBlocks[cy * mBoardWidth + cx].Flagged == FALSE)
        {
            RevealBlocks(cy * mBoardWidth + cx);
            RevealItem(cy * mBoardWidth + cx);
        }
        else if (mBlocks[cy * mBoardWidth + cx].BlockType >= BLOCKTYPE::BLOCK_ONE)
            RevealItem(cy * mBoardWidth + cx);
    }

    // Check Bottom Left
    if (y > 0 && x > 0)
    {
        DWORD cx = x - 1;
        DWORD cy = y - 1;
        if (mBlocks[cy * mBoardWidth + cx].BlockType == BLOCKTYPE::BLOCK_EMPTY && mBlocks[cy * mBoardWidth + cx].Flagged == FALSE)
        {
            RevealBlocks(cy * mBoardWidth + cx);
            RevealItem(cy * mBoardWidth + cx);
        }
        else if (mBlocks[cy * mBoardWidth + cx].BlockType >= BLOCKTYPE::BLOCK_ONE)
            RevealItem(cy * mBoardWidth + cx);
    }

    // Check Left
    if (x > 0)
    {
        DWORD cx = x - 1;
        DWORD cy = y;
        if (mBlocks[cy * mBoardWidth + cx].BlockType == BLOCKTYPE::BLOCK_EMPTY && mBlocks[cy * mBoardWidth + cx].Flagged == FALSE)
        {
            RevealBlocks(cy * mBoardWidth + cx);
            RevealItem(cy * mBoardWidth + cx);
        }
        else if (mBlocks[cy * mBoardWidth + cx].BlockType >= BLOCKTYPE::BLOCK_ONE)
            RevealItem(cy * mBoardWidth + cx);
    }

    // Check Top Left
    if (x > 0 && y < mBoardHeight - 1)
    {
        DWORD cx = x - 1;
        DWORD cy = y + 1;
        if (mBlocks[cy * mBoardWidth + cx].BlockType == BLOCKTYPE::BLOCK_EMPTY && mBlocks[cy * mBoardWidth + cx].Flagged == FALSE)
        {
            RevealBlocks(cy * mBoardWidth + cx);
            RevealItem(cy * mBoardWidth + cx);
        }
        else if (mBlocks[cy * mBoardWidth + cx].BlockType >= BLOCKTYPE::BLOCK_ONE)
            RevealItem(cy * mBoardWidth + cx);
    }

    return TRUE;

}
BLOCKTYPE GameBoard::RevealItem( DWORD idx )
{
    if( idx >= mTileCount ) return BLOCKTYPE::BLOCK_EMPTY;
    BLOCK& block = mBlocks[idx];

    if( block.Revealed == false ) {
        block.Revealed = true;
    }

    // Update hte visual state of hte block
    UpdateGraphic(idx);

    // Return the blcok type that was revealed
    return block.BlockType;
}

BOOL GameBoard::ToggleFlag( FLOAT x, FLOAT y )
{
    // Determine bounds of the board
    float leftBound = mCenterX - (mBoardWidth * mTileSize / 2.0f);
    float rightBound = mCenterX + (mBoardWidth * mTileSize / 2.0f);
    float topBound = mCenterY - (mBoardHeight * mTileSize / 2.0f);
    float bottomBound = mCenterY + (mBoardHeight * mTileSize / 2.0f );

    if( x >= leftBound && x <= rightBound && y >= topBound && y <= bottomBound )
    {
        // Translate our screen touch coordinates to board coordinates.
        int boardX = ((x - leftBound) / mTileSize);
        int boardY = ((y - topBound) / mTileSize);

        DWORD idx = boardY * mBoardWidth + boardX;
        if( idx < mTileCount ) {
            
            BLOCK& block = mBlocks[idx];

            if( block.Revealed == false )  {
                block.Flagged = !block.Flagged;
            }

            UpdateGraphic(idx);
        }
    }    

    return TRUE;        
}

BOOL GameBoard::CheckForTouch( FLOAT x, FLOAT y )
{
    

    // Determine bounds of the board
    float leftBound = mCenterX - (mBoardWidth * mTileSize / 2.0f);
    float rightBound = mCenterX + (mBoardWidth * mTileSize / 2.0f);
    float topBound = mCenterY - (mBoardHeight * mTileSize / 2.0f);
    float bottomBound = mCenterY + (mBoardHeight * mTileSize / 2.0f );

    if( x >= leftBound && x <= rightBound && y >= topBound && y <= bottomBound )
    {
        // Translate our screen touch coordinates to board coordinates.
        int boardX = ((x - leftBound) / mTileSize);
        int boardY = ((y - topBound) / mTileSize);

        std::cout << "Touched: (" << boardX << ", " << boardY << ")" << std::endl;

        DWORD idx = boardY * mBoardWidth + boardX;
        if( idx < mTileCount ) {
            BLOCK& block = mBlocks[idx];

            if( block.Flagged == true ) return TRUE;

            BLOCKTYPE type = block.BlockType;
            if( type == BLOCK_EMPTY )
            {
                RevealBlocks(idx);
                RevealItem(idx);
            }
            else if( type == BLOCK_BOMB )
            {
                std::cout << "FAILED!" << std::endl;
            }
            else
            {
                RevealItem(idx);
            }

            // Check for victory

        }
    }

    return TRUE;
}

VOID GameBoard::Draw( Strata::SpriteRenderer& renderer, DWORD layer )
{
    // Loop through each tile and draw to renderer
    for( DWORD idx = 0; idx < mTileCount; idx++ )
    {
        BLOCK& block = mBlocks[idx];

        RECT dstRect;
        dstRect.left = block.PosX + (mCenterX - (mBoardWidth * mTileSize / 2.0f)) ;
        dstRect.right = dstRect.left + mTileSize;
        dstRect.top = block.PosY + (mCenterY - (mBoardHeight * mTileSize / 2.0f));
        dstRect.bottom = dstRect.top + mTileSize;

        DWORD textureId = mTextureHandles[block.TileID];

        renderer.Draw( dstRect, *(RECT*)Strata::ResourceManager::GetTextureRect(textureId), textureId, layer, mColorFactor );
    }
}