#include "angler.h"
#include "contest.h"
#include <iostream>

void AnglerEnor::next()
{
    if(!(_end=_tt.end()))
    {
        _cur.contest=_tt.current().id;
        _cur.atLeastTwo=false;
        int cnt=0;
        for( ; !_tt.end() && _tt.current().id == _cur.contest; _tt.next() ){
            if(_tt.current().caughtCarp)
                cnt++;
        }
        _cur.atLeastTwo = (cnt>=2);
    }
    
}
