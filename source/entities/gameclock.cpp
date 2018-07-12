#include "gameclock.h"


GameClock::GameClock( VOID ) : 
    AnalogDisplay( 3UL, 0UL )
{
    mLimit = 100.0f;
    mTime = 0.0f;
}
GameClock::~GameClock( VOID )
{
    
}

VOID GameClock::Tick( FLOAT elapsedTime )
{
    mTime += elapsedTime;
    SetValue((DWORD)mTime);
}

VOID GameClock::SetLimit( FLOAT limit )
{
    mLimit = limit;
}

BOOL GameClock::AtLimit( VOID )
{
    if( mTime > mLimit + 1 ) return TRUE;
    return FALSE;
}

VOID GameClock::Reset( VOID )
{
    mTime = 0.0f;
}

