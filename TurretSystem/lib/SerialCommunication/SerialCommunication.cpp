#include "SerialCommunication.h"

#include "Arduino.h"

namespace TurretSystem
{
    SerialCommunication::SerialCommunication()
    {
        //Nothing
    }

    SerialCommunication::SerialCommunication(int baud_rate)
    {
        Open(baud_rate);
    }

    void SerialCommunication::Open(int baud_rate)
    {
        Serial.begin(baud_rate);
    }

    bool SerialCommunication::MessageReceived()
    {
        return Serial.available() > 0;
    }

    void SerialCommunication::WriteMessage(char* message)
    {
        Serial.print(*message);
    }

    void SerialCommunication::ReadIncomingMessage(char* message)
    {
        bool start_received = false;
        bool message_read = false;
        char received_char;
        int index = 0;

        while(Serial.available() > 0 && message_read == false)
        {
            received_char = Serial.read();
            if(start_received)
            {
                if(received_char != end_char)
                {
                    message[index] = received_char;
                    index++;
                }
                else
                {
                    message[index] = '\0';
                    message_read = true;
                    Serial.println();
                }
            }
            if(received_char == start_char)
            {
                start_received = true;
            }
        }
    }

    Point SerialCommunication::ReturnPointFromMessage(char* message)
    {
        Point received_point;
        char* strtok_index;
        // Make a copy of the original message
        char message_copy[strlen(message) + 1];
        strcpy(message_copy, message);

        // Tokenize the copy of the message
        strtok_index = strtok(message_copy, ":");
        received_point.x = atoi(strtok_index);

        strtok_index = strtok(NULL, ":");
        received_point.y = atoi(strtok_index);

        return received_point;
    }

    void SerialCommunication::Flush()
    {
        Serial.flush();
    }
}