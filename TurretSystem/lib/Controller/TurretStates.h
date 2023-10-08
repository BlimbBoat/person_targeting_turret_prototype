#ifndef TURRETSTATES_H
#define TURRETSTATES_H

namespace TurretSystem
{
    enum class TurretStates
    {
        Setup,
        Idle,
        Surveillance,
        HandleReceivedMessage,
        Aiming,
        Firing,
        ResettingPosition,
        Error
    };
}

#endif