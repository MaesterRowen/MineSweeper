// Invaders NX
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
#include "game.h"
#include "states/gamestate_game.h"


BOOL Game::Initialize( VOID )
{
    // Load our texturemap
    Strata::ResourceManager::AddTexture( "Sprites", 144.0f, 81.0f, "romfs:/textures/spritesheet.png", "romfs:/textures/spritesheet.map" );

    // Initialize our font
    mFont.LoadFont( "FontTexture", "romfs:/fonts/segoe_ui.fnt", "romfs:/fonts/segoe_ui.png");

    
    // Move to our first state
    mDirector.Add("Game", new GameState_Game(this));
    mDirector.PushState("Game");

    // Initialize Inputmnager
    mInputManager.Initialize( CONTROLLER_P1_AUTO );

    // Set our clear color
    SetClearColor( 0xFF, 0x22, 0x22, 0x22 );

    // Return succesfully
    return TRUE;
}

Game::~Game( VOID )
{
}

VOID Game::HandleEvent( const SDL_Event& event )
{
    mDirector.HandleEvent(event);
}

DWORD Game::Update( FLOAT elapsedTime )
{
    // Let the director know we are starting a new frame
    mDirector.FrameBegin();

    // Clamp our elapsed time
    if( elapsedTime > 0.2f ) elapsedTime = 0.2f;
	if( elapsedTime < 0.0f ) elapsedTime = 0.0f;

    // Pool for input
    mInputManager.Poll();

    // If the + button is pressed, then exit
    if( mInputManager.IsKeyPressed( KEY_MINUS )) {
        mRunning = false;
        return 0UL;
    }

    // Pass control over to the director
    mDirector.HandleInput();
    mDirector.Update( elapsedTime );
    
    return 1UL;

}
DWORD Game::Render( VOID )
{
    // Draw our game state
    mDirector.Draw();

    // Draw our frame rate
    #ifdef NXDEBUG
        mSpriteRenderer.BeginDraw( Strata::SpriteRenderer::SORTTYPE_BACKTOFRONT );
        mFont.SetColor( 255, 255, 255, 192 );
        mFont.SetScale( 0.1875 );
        mFont.DrawText(mSpriteRenderer, 10, 10, SPRITEFONT_ALIGN_LEFT, 6, "Debug Mode" );
        mFont.DrawText(mSpriteRenderer, GetWidth() / 2.0f, 10, SPRITEFONT_ALIGN_CENTER, 6, GetTitle().c_str() );
        mFont.DrawText(mSpriteRenderer, GetWidth() - 10.0f, 10, SPRITEFONT_ALIGN_RIGHT, 6, "FPS:  %4.2f", Time.GetFrameRate() );
        mSpriteRenderer.EndDraw();
        mSpriteRenderer.Render();
    #endif

    // Let the director know that we have finisehd a complete frame
    mDirector.FrameEnd();

    return 1UL;
}