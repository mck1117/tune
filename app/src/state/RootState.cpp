#include "RootState.h"

RootState GetInitialState()
{
    RootState s;

    s.ecu = ecu::IEcu::Make();
    
    s.gaugeMin = -225;
    s.gaugeMax = 45;

    return s;
}
