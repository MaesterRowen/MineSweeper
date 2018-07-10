// MineSweeper
// Copyright (C) 2018 MaesterRowen
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#include <iostream>
#include "gamestate_game.h"

    
GameState_Game::GameState_Game( Strata::Application * appContext ) : 
    GameState(appContext)
{

}
GameState_Game::~GameState_Game( VOID )
{
    std::cout << "GameState_Game - Destroyed " << std::endl;

}

VOID GameState_Game::OnEnter( VOID )
{
    std::cout << "GameState_Game::OnEnter " << std::endl;

    // Initialize our sprites
    mBlank[0].Initialize( 32.0f, 32.0f, 32.0f, 32.0f, 1, Strata::ResourceManager::GetTextureHandle("Sprites.Piece_Empty"));
    mBlank[1].Initialize( 64.0f, 32.0f, 32.0f, 32.0f, 1, Strata::ResourceManager::GetTextureHandle("Sprites.Piece_1"));
    mBlank[2].Initialize( 96.0f, 32.0f, 32.0f, 32.0f, 1, Strata::ResourceManager::GetTextureHandle("Sprites.Piece_2"));
    mBlank[3].Initialize( 128.0f, 32.0f, 32.0f, 32.0f, 1, Strata::ResourceManager::GetTextureHandle("Sprites.Piece_3"));
    mBlank[4].Initialize( 160.0f, 32.0f, 32.0f, 32.0f, 1, Strata::ResourceManager::GetTextureHandle("Sprites.Piece_4"));
    mBlank[5].Initialize( 192.0f, 32.0f, 32.0f, 32.0f, 1, Strata::ResourceManager::GetTextureHandle("Sprites.Piece_5"));
    mBlank[6].Initialize( 224.0f, 32.0f, 32.0f, 32.0f, 1, Strata::ResourceManager::GetTextureHandle("Sprites.Piece_6"));
    mBlank[7].Initialize( 256.0f, 32.0f, 32.0f, 32.0f, 1, Strata::ResourceManager::GetTextureHandle("Sprites.Piece_7"));
    mBlank[8].Initialize( 288.0f, 32.0f, 32.0f, 32.0f, 1, Strata::ResourceManager::GetTextureHandle("Sprites.Piece_8"));

    mBlock.Initialize( 0, 0, 32.0f, 32.0f, 1, Strata::ResourceManager::GetTextureHandle("Sprites.Block"));

}

VOID GameState_Game::HandleInput( VOID )
{

}

VOID GameState_Game::Update(FLOAT elapsedTime)
{
}

VOID GameState_Game::Draw( VOID )
{
    mSpriteRenderer.BeginDraw( Strata::SpriteRenderer::SORTTYPE::SORTTYPE_BACKTOFRONT );

    // Draw borad
    for( int y = 0; y < 10; y++ )
    {
        for( int x = 0; x < 15; x++ )
        {
            mBlock.Translate( x * 32.0f + 80.0f, y * 32.0f + 20.0f );
            mBlock.Draw(mSpriteRenderer);
        }
    }

    mSpriteRenderer.EndDraw();
    mSpriteRenderer.Render();
}