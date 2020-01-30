#include "RootState.h"

RootState GetInitialState()
{
    RootState s;

    s.ecu = ecu::IEcu::Make();

    return s;
}
