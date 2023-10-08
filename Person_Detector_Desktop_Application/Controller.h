#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "PersonDetector.h"
#include "Serial.h"

#include <opencv2/opencv.hpp>

#include "States.h"

namespace PersonDetection
{
	class Controller
	{
	public:
		Serial serial;
		States state;

		Controller(DWORD baud_rate, std::string serial_port, std::string class_list_path, std::string model_path);
		~Controller() = default;
		
		int WriteSerialMessage(cv::Point point);
		cv::Point GetCenterPointFromImage();
	private:
		//Serial
		DWORD baud_rate;
		std::string serial_port;

		//Serial Communication
		const char begin_char = '$';
		const char end_char = '%';
		const char seperator_char = ':';
		
		//Person Detection
		PersonDetector person_detector;

		std::string class_list_path;
		std::string model_path;
	};
}

#endif // !CONTROLLER_H

