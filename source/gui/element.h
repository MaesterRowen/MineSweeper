#ifndef _STRATA_GUI_ELEMENT_H_
#define _STRATA_GUI_ELEMENT_H_

#include <strata/strata.h>
#include <vector>

class GUIElement 
{
public:
    GUIElement( VOID ) { }
    virtual ~GUIElement( VOID ) { }

    VOID AddChild( GUIElement * child ) {
        if( child ) {
            mChildren.push_back( child );
        }
    }

    VOID Draw( Strata::SpriteRenderer& renderer )
    {
        
    }

private:
    FLOAT mPosX;
    FLOAT mPosY;
    FLOAT mWidth;
    FLOAT mHeight;

    std::vector<GUIElement*> mChildren;
};

#endif