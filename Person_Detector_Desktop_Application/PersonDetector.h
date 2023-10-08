#ifndef PERSONDETECTOR_H
#define PERSONDETECTOR_H

#include <opencv2/opencv.hpp>

// Namespaces.
using namespace std;

namespace PersonDetection
{
	class PersonDetector
	{
	public:			
		PersonDetector();
		PersonDetector(std::string class_list_path, std::string model_path);
		~PersonDetector();
		void Create(std::string class_list_path, std::string model_path);
		cv::Point ReturnCenterOfBoundingBox();
	private:
		// Constants.
		const float INPUT_WIDTH = 640.0;
		const float INPUT_HEIGHT = 640.0;
		const float SCORE_THRESHOLD = 0.5;
		const float NMS_THRESHOLD = 0.45;
		const float CONFIDENCE_THRESHOLD = 0.45;

		cv::VideoCapture cap;
		cv::dnn::Net net;
		cv::UMat image;

		const int camera_index = 1;

		// Text parameters.
		const float FONT_SCALE = 0.7;
		const int FONT_FACE = cv::FONT_HERSHEY_SIMPLEX;
		const int THICKNESS = 1;

		// Colors.
		const cv::Scalar BLACK = cv::Scalar(0, 0, 0);
		const cv::Scalar BLUE = cv::Scalar(255, 178, 50);
		const cv::Scalar YELLOW = cv::Scalar(0, 255, 255);
		const cv::Scalar RED = cv::Scalar(0, 0, 255);

		vector<string> class_list;

		vector<cv::UMat> PreProcess(cv::UMat& input_image, cv::dnn::Net& net);
		cv::UMat PostProcess(cv::UMat& input_image, vector<cv::UMat>& outputs, const vector<std::string>& class_name, cv::Point* center_point);
		cv::Point CalculateCenterOfBox(int x, int y, int width, int height);
	};
}

#endif //PERSONDETECTOR_H

