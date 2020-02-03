#include "RootState.h"

RootState GetInitialState()
{
    RootState s;

	s.ecu = nullptr;
    
    s.gaugeMin = -225;
    s.gaugeMax = 45;

    return s;
}
