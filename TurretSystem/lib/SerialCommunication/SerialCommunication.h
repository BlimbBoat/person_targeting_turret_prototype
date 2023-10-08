#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include "Point.h"

namespace TurretSystem
{
    class SerialCommunication
    {
    public:
        SerialCommunication();
        SerialCommunication(int baud_rate);
        ~SerialCommunication() = default;

        void Open(int baud_rate);
        void WriteMessage(char* message);
        bool MessageReceived();
        void ReadIncomingMessage(char* message);
        Point ReturnPointFromMessage(char* message);
        void Flush();
    private:
        const char start_char = '$';
        const char end_char = '%';    
    };
}

#endif