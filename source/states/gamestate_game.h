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

#ifndef _GAMESTATE_TEST_H_
#define _GAMESTATE_TEST_H_

#include <strata/strata.h>
#include "../game.h"
#include "../entities/gameboard.h"
#include "../entities/analogdisplay.h"
#include "../entities/gameclock.h"

class GameState_Game : public Strata::GameState
{
public: 
    GameState_Game( Strata::Application * appContext );
    ~GameState_Game( VOID );

    VOID OnEnter( VOID );
    VOID HandleEvent( const SDL_Event& event);
    VOID HandleInput( VOID );
    VOID Update(FLOAT elapsedTime);
    VOID Draw( VOID );

private:
    BOOL mFlagMode;

    FLOAT mTouchDownX, mTouchDownY;
    Strata::SpriteFont fontSpr;
    Strata::SpriteRenderer mSpriteRenderer;

    Strata::Sprite mBlank[9];
    Strata::Sprite mBlock;

    GameBoard * mActiveBoard;
    AnalogDisplay * mBombsLeft;
    GameClock mGameClock;

};

#endif