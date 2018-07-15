#include "gamestate_menu.h"
#include "../game.h"

GameState_Menu::GameState_Menu( Strata::Application * appContext ) : 
    Strata::GameState(appContext)
{

}
GameState_Menu::~GameState_Menu( VOID )
{

}

VOID GameState_Menu::OnEnter( VOID )
{

}
VOID GameState_Menu::HandleEvent( const SDL_Event& event)
{

}
VOID GameState_Menu::HandleInput( VOID )
{

}
VOID GameState_Menu::Update(FLOAT elapsedTime)
{

}
VOID GameState_Menu::Draw( VOID )
{
    mSpriteRenderer.BeginDraw();

    Strata::SpriteFont& mFont = ((Game*)mpAppContext)->GetFont();

    // Set our font style
    mFont.SetColor( 255, 255, 255, 255 );
    mFont.SetScale( 0.35f );

    mFont.DrawText( mSpriteRenderer, 320.0f, 140.0f, SPRITEFONT_ALIGN_CENTER, 3, "Easy (6x6)" );
    mFont.DrawText( mSpriteRenderer, 320.0f, 190.0f, SPRITEFONT_ALIGN_CENTER, 3, "Normal (10x10)" );
    mFont.DrawText( mSpriteRenderer, 320.0f, 240.0f, SPRITEFONT_ALIGN_CENTER, 3, "Hard (15x10)" );

    mSpriteRenderer.EndDraw();
    mSpriteRenderer.Render();
}