#pragma once

#include <vector>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <QString>
#include "global.h"
#include "util.hpp"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QProcess>
// Include GLM
#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class SyntheticData {

public:
	SyntheticData();

	void test();
	void generateData(const QString& output_dir, const std::pair<float, float>& roadWidthRange, const std::pair<float, float>& sideWidthRange, const std::pair<float, float>& frontWidthRange, const std::pair<float, float>& xBuildingDimRange, const std::pair<float, float>& yBuildingDimRange, const std::pair<float, float>& buildingDisRange, int iter);
	void generateSyntheticData(int roadType, int numScenarios, const QString& output_dir, const std::pair<float, float>& roadBaseOrientationRange, const std::pair<float, float>& roadWidthRange, const std::pair<float, float>& sideWidthRange, const std::pair<float, float>& frontWidthRange, const std::pair<int, int>& numStoriesRange, const std::pair<float, float>& xBuildingDimRange, const std::pair<float, float>& yBuildingDimRange, const std::pair<float, float>& buildingDisRange);
	float genRand();
	float genRand(float a, float b);
	int genRand(int a, int b);
	cv::Point2f intersection(cv::Point2f p1, cv::Point2f p2, cv::Point2f p3, cv::Point2f p4);
	cv::Point2f get_point(cv::Point2f p1, float angle, float delta);
	float get_angle(cv::Point2f p1, cv::Point2f p2);

};
