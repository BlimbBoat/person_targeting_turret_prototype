#include "Controller.h"
#include "States.h"

#include <iostream>


namespace PersonDetection
{
    Controller::Controller(DWORD baud_rate, std::string serial_port, std::string class_list_path, std::string model_path)
    {
        serial.Open(serial_port.c_str(), baud_rate);
        person_detector.Create(class_list_path, model_path);
        state = States::Send;
    }

    int Controller::WriteSerialMessage(cv::Point point)
    {
        if (point.x == 0 && point.y == 0)
        {
            return -1;
        }

        cout << "Send Message with values:";

        std::vector<char> temp_buffer;

        std::string temp_x_string = std::to_string(point.x);
        std::string temp_y_string = std::to_string(point.y);

        cout << point.x << ", " << point.y <<endl;

        size_t num_digits_x = temp_x_string.size();
        size_t num_digits_y = temp_y_string.size();

        temp_buffer.push_back(begin_char);

        for (size_t i = 0; i < num_digits_x; i++)
        {
            temp_buffer.push_back(temp_x_string.at(i));
        }

        temp_buffer.push_back(seperator_char);

        for (size_t i = 0; i < num_digits_y; i++)
        {
            temp_buffer.push_back(temp_y_string.at(i));
        }

        temp_buffer.push_back(end_char);

        for (size_t i = 0; i < temp_buffer.size(); i++)
        {
            serial.Write(temp_buffer[i]);
        }
        return 1;
    }

    cv::Point Controller::GetCenterPointFromImage()
    {
        return person_detector.ReturnCenterOfBoundingBox();
    }
}

int main()
{
    DWORD baud_rate = 9600;
    std::string serial_port = "COM3"; //Adjust
    std::string class_list_path = "C:\\project\\yolov6\\coco.names";
    std::string model_path = "C:\\project\\yolov6\\yolov6n.onnx";

    PersonDetection::Controller controller(baud_rate, serial_port, class_list_path, model_path);
    cv::Point point;

    uint8_t buffer[1];
    while (true)
    {   
        /*switch (controller.state)
        {
            case PersonDetection::States::Send:
                if (controller.WriteSerialMessage(controller.GetCenterPointFromImage()) == 1)
                {
                    controller.state = PersonDetection::States::Received;
                }
                break;
            case PersonDetection::States::Received:
                while (controller.serial.Available())
                {
                    controller.serial.Get_SensorData(buffer, 1);
                    cout << buffer[0] << endl;
                }
                controller.state = PersonDetection::States::Send;
                break;
            
        }*/
        controller.WriteSerialMessage(controller.GetCenterPointFromImage());
    }
}

