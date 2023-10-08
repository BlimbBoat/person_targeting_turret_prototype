#include "Controller.h"
#include "Point.h"

#include <Arduino.h>

namespace TurretSystem
{
    Controller::Controller()
    {
        //Do nothing
    }

    Controller::Controller(int baud_rate, int pin_horizontal, int pin_vertical, int pin_trigger)
    {
        Attach(baud_rate, pin_horizontal, pin_vertical, pin_trigger);
    }

    void Controller::Attach(int baud_rate, int pin_horizontal, int pin_vertical, int pin_trigger)
    {
        aiming_mechanism.Attach(pin_horizontal, pin_vertical);
        firing_mechanism.Attach(pin_trigger);

        message = new char[max_message_size];

        current_state = TurretStates::Setup;

        target = Point(0,0);

        serial_communication.Open(baud_rate);

        start_time = millis();
    }

    void Controller::Run()
    {
        switch(current_state)
        {
            case TurretStates::Setup:
            {
                aiming_mechanism.Reset();
                firing_mechanism.Reset();

                //Moving out of case
                current_state = TurretStates::Idle;
                break;
            }
            case TurretStates::Idle:
            {
                start_time = millis();
                //Moving out of case
                current_state = TurretStates::Surveillance;
                break;
            }
            case TurretStates::Surveillance:
            {
                bool move_left = true;
                Point position;
                while(!serial_communication.MessageReceived())
                {
                    elapsed_time = millis() - start_time;
                    if(elapsed_time >= time_difference)
                    {
                        start_time = millis();
                        position = aiming_mechanism.ReturnServoPosition();
                        if(position.x <= aiming_mechanism.ReturnMinPosition())
                        {
                            move_left = false;
                        }
                        else if(position.x >= aiming_mechanism.ReturnMaxPosition())
                        {
                            move_left = true;
                        }

                        if(move_left)
                        {
                            position.x -= surveillance_movement;
                        }
                        else
                        {
                            position.x += surveillance_movement;
                        }
                        
                        aiming_mechanism.MoveByDegrees(position);
                    }
                }
                //Moving out of case
                current_state = TurretStates::HandleReceivedMessage;
                break;
            }
            case TurretStates::HandleReceivedMessage:  
            {
                serial_communication.ReadIncomingMessage(message);
                target = serial_communication.ReturnPointFromMessage(message);      
                
                current_state = TurretStates::Aiming;
                break;
            }
            case TurretStates::Aiming:
            {
                aiming_mechanism.MoveToPoint(target);
                //WriteResponse();
                serial_communication.Flush();
                //Moving out of case
                current_state = TurretStates::Firing;
                break;
            }
            case TurretStates::Firing:
            {
                firing_mechanism.FireOnce();
                serial_communication.Flush();
                //Moving out of case
                current_state = TurretStates::Idle;
                break;
            }
            default:
                break;
        }
    }

    void Controller::WriteResponse()
    {
        serial_communication.WriteMessage(&messsage_response);
    }
}