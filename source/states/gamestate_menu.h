#ifndef _GAMESTATE_MENU_H_
#define _GAMESTATE_MENU_H_

#include <strata/strata.h>

class GameState_Menu  : public Strata::GameState
{
public:
    GameState_Menu( Strata::Application * appContext );
    ~GameState_Menu( VOID );

    VOID OnEnter( VOID );
    VOID HandleEvent( const SDL_Event& event);
    VOID HandleInput( VOID );
    VOID Update(FLOAT elapsedTime);
    VOID Draw( VOID );

private:
    Strata::SpriteRenderer mSpriteRenderer;

};


#endif 