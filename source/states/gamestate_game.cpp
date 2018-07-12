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
    mActiveBoard = nullptr;
    mFlagMode = FALSE;

}
GameState_Game::~GameState_Game( VOID )
{
    std::cout << "GameState_Game - Destroyed " << std::endl;

}

VOID GameState_Game::OnEnter( VOID )
{
    std::cout << "GameState_Game::OnEnter " << std::endl;

    DWORD bombCount = 20;
    mActiveBoard = new GameBoard(32.0f, 15, 10, bombCount);
    if( mActiveBoard ) {
        mActiveBoard->SetCenter( 320.0f, 180.0f );
    }

    mGameClock.SetPosition( 0.0f, 65.0f );
    mGameClock.SetLimit( 9.0f );

    mBombsLeft = new AnalogDisplay(3, bombCount);
    if( mBombsLeft ) {
        mBombsLeft->SetPosition(0.0f, 0.0f);
    }
}
VOID GameState_Game::HandleEvent( const SDL_Event& event)
{
    if( event.type == SDL_FINGERDOWN )
    {
        // Convert the screen cordinations to pixels
        FLOAT x = event.tfinger.x * ((Game*)mpAppContext)->GetWidth();
        FLOAT y = event.tfinger.y * ((Game*)mpAppContext)->GetHeight();

        if( mActiveBoard && event.tfinger.fingerId == 0 ) {
            if( mFlagMode == TRUE ) {
                mActiveBoard->ToggleFlag( x, y );
            } else {
                mActiveBoard->CheckForTouch( x, y );
            }
        }
    }
}
VOID GameState_Game::HandleInput( VOID )
{
    Strata::InputManager& input = ((Game*)mpAppContext)->GetInputManager();

    mFlagMode = input.IsKeyDown( KEY_A );
}

VOID GameState_Game::Update(FLOAT elapsedTime)
{
    mGameClock.Tick(elapsedTime);
    if( mGameClock.AtLimit() == TRUE ) {
        mGameClock.Reset();
    }
}

VOID GameState_Game::Draw( VOID )
{
    mSpriteRenderer.BeginDraw( Strata::SpriteRenderer::SORTTYPE::SORTTYPE_BACKTOFRONT );

    // Draw some text
    Strata::SpriteFont font = ((Game*)mpAppContext)->GetFont();

    font.SetScale( 0.25f );
    font.SetColor( 255, 255, 255, 255 );
    font.DrawText(mSpriteRenderer, 0.0f, 55.0f, SPRITEFONT_ALIGN_LEFT, 2, "Time:" );

    // Draw borad
    if( mActiveBoard ) mActiveBoard->Draw( mSpriteRenderer, 1);
    if( mBombsLeft ) mBombsLeft->Draw( mSpriteRenderer, 2);

    mGameClock.Draw( mSpriteRenderer, 2 );

    mSpriteRenderer.EndDraw();
    mSpriteRenderer.Render();
}