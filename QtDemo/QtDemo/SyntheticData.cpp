#include "SyntheticData.h"
#define WIDTH 227
#define LENGTH 227
#define DIM_X 100
#define DIM_Y 100
#define SMALL_FLOAT 1.0e-5

SyntheticData::SyntheticData(){

}

void SyntheticData::test(){
	// Create black empty images
	cv::Mat image = cv::Mat::zeros(227, 227, CV_8UC3);
	image.setTo(cv::Scalar(77, 179, 33));
	// Draw a line 
	//draw road
	cv::rectangle(image,
		cv::Point(103, 0),
		cv::Point(123, 227),
		cv::Scalar(61, 199, 209),
		-1,
		0);
	cv::imshow("Image", image);
	cv::imwrite("../output/exmaple.png", image);
}
void SyntheticData::generateSyntheticData(int roadType, int numScenarios, const QString& output_dir, const std::pair<float, float>& roadBaseOrientationRange, const std::pair<float, float>& roadWidthRange, const std::pair<float, float>& sideWidthRange, const std::pair<float, float>& frontWidthRange, const std::pair<int, int>& numStoriesRange, const std::pair<float, float>& xBuildingDimRange, const std::pair<float, float>& yBuildingDimRange, const std::pair<float, float>& buildingDisRange){
	if (QDir(output_dir).exists()) {
		std::cout << "Removing existing files in the output directory...";
		QDir(output_dir).removeRecursively();
		std::cout << " done." << std::endl;
	}
	QDir().mkpath(output_dir);
	std::cout << "  side: " << roadWidthRange.first << ", " << roadWidthRange.second << std::endl;
	std::cout << "  side: " << sideWidthRange.first << ", " << sideWidthRange.second << std::endl;
	std::cout << "  front: " << frontWidthRange.first << ", " << frontWidthRange.second << std::endl;
	std::cout << "  x_dim: " << xBuildingDimRange.first << ", " << xBuildingDimRange.second << std::endl;
	std::cout << "  y_dim: " << yBuildingDimRange.first << ", " << yBuildingDimRange.second << std::endl;
	std::cout << "  building_dis: " << buildingDisRange.first << ", " << buildingDisRange.second << std::endl;
	for (int iter = 0; iter < numScenarios; ++iter) {
		std::cout << "Generating scenarios: " << iter + 1 << std::endl;

		// set random seed
		srand((unsigned)time(NULL) + iter);

		// warm up the random numbers
		for (int i = 0; i < 100; ++i) rand();

		// set the parameter values
		G::global()["road_type"] = roadType;
		G::global()["road_base_orientation"] = genRand(roadBaseOrientationRange.first, roadBaseOrientationRange.second);
		if (G::getInt("road_type") == 0 || G::getInt("road_type") == 1)
			G::global()["block_1"] = genRand(numStoriesRange.first, numStoriesRange.second);
		if (G::getInt("road_type") == 2 || G::getInt("road_type") == 3)
			G::global()["block_1"] = genRand(numStoriesRange.first, 2 * numStoriesRange.second);
		if (G::getInt("road_type") == 0 || G::getInt("road_type") == 1)
			G::global()["block_2"] = genRand(numStoriesRange.first, numStoriesRange.second);
		if (G::getInt("road_type") == 2 || G::getInt("road_type") == 3)
			G::global()["block_2"] = genRand(numStoriesRange.first, 2 * numStoriesRange.second);
		if (G::getInt("road_type") == 0)
			G::global()["block_3"] = genRand(numStoriesRange.first, numStoriesRange.second);
		if (G::getInt("road_type") == 1)
			G::global()["block_3"] = genRand(numStoriesRange.first, 2 * numStoriesRange.second);
		if (G::getInt("road_type") == 0)
			G::global()["block_4"] = genRand(numStoriesRange.first, numStoriesRange.second);
		// generate a scenario
		generateData(output_dir, roadWidthRange, sideWidthRange, frontWidthRange, xBuildingDimRange, yBuildingDimRange, buildingDisRange, iter);
		
	}
}

void SyntheticData::generateData(const QString& output_dir, const std::pair<float, float>& roadWidthRange, const std::pair<float, float>& sideWidthRange, const std::pair<float, float>& frontWidthRange, const std::pair<float, float>& xBuildingDimRange, const std::pair<float, float>& yBuildingDimRange, const std::pair<float, float>& buildingDisRange, int iter){
	//{
	//	//test intersection
	//	//line1
	//	cv::Point p1 =  cv::Point(1, 0);
	//	cv::Point p2 = cv::Point(1, 10);
	//	//line2
	//	cv::Point p3 = cv::Point(0, 0);
	//	cv::Point p4 = cv::Point(5, 10);
	//	//
	//	cv::Point result = intersection(p1, p2, p3, p4);
	//	std::cout << result.x << ", " << result.y << std::endl;

	//}
	//{
	//	//test get_point
	//	cv::Point2f p1 = cv::Point2f(1.0f, 0.0f);
	//	cv::Point2f result = get_point(p1, glm::pi<float>() / 6, 1);
	//	std::cout << result.x << ", " << result.y << std::endl;
	//}
	//return;
	// open a file to save the parameter values
	QFile file_params(output_dir + QString("/parameter_%1.txt").arg(iter + 1, 6, 10, QChar('0')));
	if (!file_params.open(QIODevice::WriteOnly)) {
		std::cerr << "Cannot open file for writing: " << file_params.fileName().toUtf8().constData() << std::endl;
		return;
	}
	QTextStream out_params(&file_params);

	// generate a scenario
	QString filename_buildings_image = output_dir + QString("/buildings_image_%1.png").arg(iter + 1, 6, 10, QChar('0'));

	int road_type = G::getInt("road_type");
	cv::Mat image = cv::Mat::zeros(WIDTH, LENGTH , CV_8UC3);
	image.setTo(cv::Scalar(77, 179, 33));//road color
	//cross road
	if (road_type == 0){

		float road_width_h = genRand(roadWidthRange.first, roadWidthRange.second);
		float road_width_v = genRand(roadWidthRange.first, roadWidthRange.second);
		float delta_h = genRand(-10.0f, 10.0f);
		float delta_v_up = genRand(-10.0f, 10.0f);
		float delta_v_down = genRand(-10.0f, 10.0f);
		//
		std::cout << "  road_type: " << G::getInt("road_type") << std::endl;
		std::cout << "  road_base_orientation: " << G::getFloat("road_base_orientation") << std::endl;
		std::cout << "  road_width_v: " << road_width_v << std::endl;
		std::cout << "  road_width_h: " << road_width_h << std::endl;
		std::cout << "  delta_v_up: " << delta_v_up << std::endl;
		std::cout << "  delta_v_down: " << delta_v_down << std::endl;
		std::cout << "  delta_h: " << delta_h << std::endl;
		std::cout << "  block_1: " << G::getInt("block_1") << std::endl;
		std::cout << "  block_2: " << G::getInt("block_2") << std::endl;
		std::cout << "  block_3: " << G::getInt("block_3") << std::endl;
		std::cout << "  block_4: " << G::getInt("block_4") << std::endl;
		// write the header to the file
		out_params << "No." << ",";
		out_params << "road_type" << ",";
		out_params << "road_base_orientation" << ",";
		out_params << "road_width_h" << ",";
		out_params << "road_width_v" << ",";
		out_params << "block_1" << ",";
		out_params << "block_2" << ",";
		out_params << "block_3" << ",";
		out_params << "block_4" << "\n";
		//draw roads
		int p1_x = (int)((0.5 * DIM_X - road_width_v * 0.5 + delta_v_up) / DIM_X * WIDTH);
		int p1_y = 0;
		int p2_x = (int)((0.5 * DIM_X + road_width_v * 0.5 + delta_v_up) / DIM_X * WIDTH);
		int p2_y = 0;
		int p3_x = (int)((0.5 * DIM_X - road_width_v * 0.5 + delta_v_down) / DIM_X * WIDTH);
		int p3_y = 226;
		int p4_x = (int)((0.5 * DIM_X + road_width_v * 0.5 + delta_v_down) / DIM_X * WIDTH);
		int p4_y = 226;

		std::vector<cv::Point> points;
		points.push_back(cv::Point(p1_x, p1_y));  //point1
		points.push_back(cv::Point(p2_x, p2_y));  //point2
		points.push_back(cv::Point(p4_x, p4_y));  //point3
		points.push_back(cv::Point(p3_x, p3_y));  //point4
		cv::fillConvexPoly(image,               //Image to be drawn on
			points,                 //C-Style array of points
			cv::Scalar(61, 199, 209),  //Color , BGR form
			CV_AA,             // connectedness, 4 or 8
			0);
		//
		std::vector<cv::Point2f> points_l1;

		points_l1.push_back(cv::Point2f(0.5 * DIM_X - road_width_v * 0.5 + delta_v_up, 0));  //point1
		points_l1.push_back(cv::Point2f(0.5 * DIM_X + road_width_v * 0.5 + delta_v_up, 0));  //point2
		points_l1.push_back(cv::Point2f(0.5 * DIM_X + road_width_v * 0.5 + delta_v_down, 100));  //point3
		points_l1.push_back(cv::Point2f(0.5 * DIM_X - road_width_v * 0.5 + delta_v_down, 100));  //point4
		//
		std::vector<cv::Point2f> points_l2;
		p1_x = 0;
		p1_y = (int)((0.5 * DIM_Y - road_width_h * 0.5 + delta_h) / DIM_Y * LENGTH);
		p2_x = 226;
		p2_y = (int)((0.5 * DIM_Y - road_width_h * 0.5 + delta_h) / DIM_Y * LENGTH);
		p3_x = 226;
		p3_y = (int)((0.5 * DIM_Y + road_width_h * 0.5 + delta_h) / DIM_Y * LENGTH);
		p4_x = 0;
		p4_y = (int)((0.5 * DIM_Y + road_width_h * 0.5 + delta_h) / DIM_Y * LENGTH);
		points_l2.push_back(cv::Point2f(0, 0.5 * DIM_Y - road_width_h * 0.5 + delta_h));  //point1
		points_l2.push_back(cv::Point2f(100, 0.5 * DIM_Y - road_width_h * 0.5 + delta_h));  //point2
		points_l2.push_back(cv::Point2f(100, 0.5 * DIM_Y + road_width_h * 0.5 + delta_h));  //point3
		points_l2.push_back(cv::Point2f(0, 0.5 * DIM_Y + road_width_h * 0.5 + delta_h));  //point4
		cv::rectangle(image,
			cv::Point(p1_x, p1_y),
			cv::Point(p3_x, p3_y),
			cv::Scalar(61, 199, 209),
			-1,
			0);
		//draw buildings
		std::vector<std::pair<float, float>> vertices;
		std::vector<std::pair<int, int>> pixes;
		//4 blocks
		float dis_side = 0.0f;
		float dis_front = 0.0f;
		float base_x = 0.0f;
		float base_y = 0.0f;
		float x_dim = 0.0f;
		float y_dim = 0.0f;
		float setback_side = 0;
		float setback_rear = 0;
		float setback_front = 0;
		int stories[4] = { G::getInt("block_1"), G::getInt("block_2"), G::getInt("block_3"), G::getInt("block_4") };
		int buildings = 0;
		//block1
		cv::Point2f intersect = intersection(points_l2.at(0), points_l2.at(1), points_l1.at(0), points_l1.at(3));
		base_x = intersect.x;
		base_y = intersect.y;
		std::cout << intersect.x << ", " << intersect.y << std::endl;
		setback_side = genRand(sideWidthRange.first, sideWidthRange.second);
		setback_front = genRand(frontWidthRange.first, frontWidthRange.second);
		dis_side = setback_side;
		dis_front = setback_front;
		buildings = stories[0];
		for (int i = 0; i < buildings; i++){
			float r_value = genRand(buildingDisRange.first, buildingDisRange.second);
			x_dim = genRand(xBuildingDimRange.first, xBuildingDimRange.second);
			y_dim = genRand(yBuildingDimRange.first, yBuildingDimRange.second);
			//first point
			float tmp_1_x = base_x - dis_side - x_dim;
			float tmp_1_y = base_y - dis_front - y_dim;
			//fourth
			float tmp_2_x = base_x - dis_side;
			float tmp_2_y = base_y - dis_front;
			if (tmp_1_x < 0 || tmp_1_y < 0 || tmp_2_x < 0 || tmp_2_y < 0)
			{
				G::global()["block_1"] = i;
				break;
			}
			std::pair<float, float> p1 = std::make_pair(tmp_1_x, tmp_1_y);
			vertices.push_back(p1);
			std::pair<float, float> p2 = std::make_pair(tmp_2_x, tmp_2_y);
			vertices.push_back(p2);

			// add x_dim and distance between buildings
			dis_side = dis_side + x_dim + r_value;
		}
		////block2
		intersect = intersection(points_l2.at(0), points_l2.at(1), points_l1.at(1), points_l1.at(2));
		base_x = intersect.x;
		base_y = intersect.y;
		setback_side = genRand(sideWidthRange.first, sideWidthRange.second);
		setback_front = genRand(frontWidthRange.first, frontWidthRange.second);
		dis_side = setback_side;
		dis_front = setback_front;
		buildings = stories[1];
		for (int i = 0; i < buildings; i++){
			float r_value = genRand(buildingDisRange.first, buildingDisRange.second);
			x_dim = genRand(xBuildingDimRange.first, xBuildingDimRange.second);
			y_dim = genRand(yBuildingDimRange.first, yBuildingDimRange.second);
			//first point
			float tmp_1_x = base_x + dis_side + x_dim;
			float tmp_1_y = base_y - dis_front - y_dim;
			//fourth
			float tmp_2_x = base_x + dis_side;
			float tmp_2_y = base_y - dis_front;
			if (tmp_1_x >= DIM_X || tmp_1_y < 0 || tmp_2_x >= DIM_X || tmp_2_y < 0)
			{
				G::global()["block_2"] = i;
				break;
			}
			std::pair<float, float> p1 = std::make_pair(tmp_1_x, tmp_1_y);
			vertices.push_back(p1);
			std::pair<float, float> p2 = std::make_pair(tmp_2_x, tmp_2_y);
			vertices.push_back(p2);

			// add x_dim and distance between buildings
			dis_side = dis_side + x_dim + r_value;
		}
		////block3
		intersect = intersection(points_l2.at(2), points_l2.at(3), points_l1.at(0), points_l1.at(3));
		base_x = intersect.x;
		base_y = intersect.y;
		setback_side = genRand(sideWidthRange.first, sideWidthRange.second);
		setback_front = genRand(frontWidthRange.first, frontWidthRange.second);
		dis_side = setback_side;
		dis_front = setback_front;
		buildings = stories[2];
		for (int i = 0; i < buildings; i++){
			float r_value = genRand(buildingDisRange.first, buildingDisRange.second);
			x_dim = genRand(xBuildingDimRange.first, xBuildingDimRange.second);
			y_dim = genRand(yBuildingDimRange.first, yBuildingDimRange.second);
			//first point
			float tmp_1_x = base_x - dis_side - x_dim;
			float tmp_1_y = base_y + dis_front + y_dim;
			//fourth
			float tmp_2_x = base_x - dis_side;
			float tmp_2_y = base_y + dis_front;
			if (tmp_1_x < 0 || tmp_1_y >= DIM_Y || tmp_2_x < 0 || tmp_2_y >= DIM_Y)
			{
				G::global()["block_3"] = i;
				break;
			}
			std::pair<float, float> p1 = std::make_pair(tmp_1_x, tmp_1_y);
			vertices.push_back(p1);
			std::pair<float, float> p2 = std::make_pair(tmp_2_x, tmp_2_y);
			vertices.push_back(p2);

			// add x_dim and distance between buildings
			dis_side = dis_side + x_dim + r_value;
		}
		//block4
		intersect = intersection(points_l2.at(2), points_l2.at(3), points_l1.at(1), points_l1.at(2));
		base_x = intersect.x;
		base_y = intersect.y;
		setback_side = genRand(sideWidthRange.first, sideWidthRange.second);
		setback_front = genRand(frontWidthRange.first, frontWidthRange.second);
		dis_side = setback_side;
		dis_front = setback_front;
		buildings = stories[3];
		for (int i = 0; i < buildings; i++){
			float r_value = genRand(buildingDisRange.first, buildingDisRange.second);
			x_dim = genRand(xBuildingDimRange.first, xBuildingDimRange.second);
			y_dim = genRand(yBuildingDimRange.first, yBuildingDimRange.second);
			//first point
			float tmp_1_x = base_x + dis_side + x_dim;
			float tmp_1_y = base_y + dis_front + y_dim;
			//fourth
			float tmp_2_x = base_x + dis_side;
			float tmp_2_y = base_y + dis_front;
			if (tmp_1_x >= DIM_X || tmp_1_y >= DIM_Y || tmp_2_x >= DIM_X || tmp_2_y >= DIM_Y)
			{
				G::global()["block_4"] = i;
				break;
			}
			std::pair<float, float> p1 = std::make_pair(tmp_1_x, tmp_1_y);
			vertices.push_back(p1);
			std::pair<float, float> p2 = std::make_pair(tmp_2_x, tmp_2_y);
			vertices.push_back(p2);

			// add x_dim and distance between buildings
			dis_side = dis_side + x_dim + r_value;
		}
		//
		for (int i = 0; i < vertices.size(); i+=2){
			int p1_x = (int)((vertices.at(i).first) / DIM_X * WIDTH);
			int p1_y = (int)((vertices.at(i).second ) / DIM_Y * LENGTH);
			std::pair<int, int> p1 = std::make_pair(p1_x, p1_y);
			pixes.push_back(p1);
			int p2_x = (int)((vertices.at(i + 1).first) / DIM_X * WIDTH);
			int p2_y = (int)((vertices.at(i + 1).second) / DIM_Y * LENGTH);
			std::pair<int, int> p2 = std::make_pair(p2_x, p2_y);
			pixes.push_back(p2);
		}
		for (int i = 0; i < pixes.size(); i += 2){
			cv::rectangle(image,
				cv::Point(pixes.at(i).first, pixes.at(i).second),
				cv::Point(pixes.at(i+1).first, pixes.at(i+1).second),
				cv::Scalar(255, 0, 0),
				-1,
				0);
		}
		// save the parameter values
		out_params << iter + 1 << ",";
		out_params << G::getFloat("road_type") << ",";
		out_params << G::getFloat("road_base_orientation") << ",";
		out_params << road_width_h << ",";
		out_params << road_width_v << ",";
		out_params << G::getInt("block_1") << ",";
		out_params << G::getInt("block_2") << ",";
		out_params << G::getInt("block_3") << ",";
		out_params << G::getInt("block_4") << "\n";
		out_params.flush();
	}
	//T road
	else if (road_type == 1){
		float road_width_h = genRand(roadWidthRange.first, roadWidthRange.second);
		float road_width_v = genRand(roadWidthRange.first, roadWidthRange.second);
		float delta_h = genRand(-10.0f, 10.0f);
		float delta_v_up = genRand(-10.0f, 10.0f);
		float delta_v_down = genRand(-10.0f, 10.0f);
		//
		std::cout << "  road_type: " << G::getInt("road_type") << std::endl;
		std::cout << "  road_base_orientation: " << G::getFloat("road_base_orientation") << std::endl;
		std::cout << "  road_width_v: " << road_width_v << std::endl;
		std::cout << "  road_width_h: " << road_width_h << std::endl;
		std::cout << "  delta_v_up: " << delta_v_up << std::endl;
		std::cout << "  delta_v_down: " << delta_v_down << std::endl;
		std::cout << "  delta_h: " << delta_h << std::endl;
		std::cout << "  block_1: " << G::getInt("block_1") << std::endl;
		std::cout << "  block_2: " << G::getInt("block_2") << std::endl;
		std::cout << "  block_3: " << G::getInt("block_3") << std::endl;
		// write the header to the file
		out_params << "No." << ",";
		out_params << "road_type" << ",";
		out_params << "road_base_orientation" << ",";
		out_params << "road_width_h" << ",";
		out_params << "road_width_v" << ",";
		out_params << "block_1" << ",";
		out_params << "block_2" << ",";
		out_params << "block_3" << "\n";
		//draw roads
		int p1_x = (int)((0.5 * DIM_X - road_width_v * 0.5 + delta_v_up) / DIM_X * WIDTH);
		int p1_y = 0;
		int p2_x = (int)((0.5 * DIM_X + road_width_v * 0.5 + delta_v_up) / DIM_X * WIDTH);
		int p2_y = 0;
		int p3_x = (int)((0.5 * DIM_X - road_width_v * 0.5 + delta_v_down) / DIM_X * WIDTH);
		int p3_y = 226;
		int p4_x = (int)((0.5 * DIM_X + road_width_v * 0.5 + delta_v_down) / DIM_X * WIDTH);
		int p4_y = 226;

		std::vector<cv::Point> points;
		points.push_back(cv::Point(p1_x, p1_y));  //point1
		points.push_back(cv::Point(p2_x, p2_y));  //point2
		points.push_back(cv::Point(p4_x, p4_y));  //point3
		points.push_back(cv::Point(p3_x, p3_y));  //point4
		cv::fillConvexPoly(image,               //Image to be drawn on
			points,                 //C-Style array of points
			cv::Scalar(61, 199, 209),  //Color , BGR form
			CV_AA,             // connectedness, 4 or 8
			0);
		//
		std::vector<cv::Point2f> points_l1;

		points_l1.push_back(cv::Point2f(0.5 * DIM_X - road_width_v * 0.5 + delta_v_up, 0));  //point1
		points_l1.push_back(cv::Point2f(0.5 * DIM_X + road_width_v * 0.5 + delta_v_up, 0));  //point2
		points_l1.push_back(cv::Point2f(0.5 * DIM_X + road_width_v * 0.5 + delta_v_down, 100));  //point3
		points_l1.push_back(cv::Point2f(0.5 * DIM_X - road_width_v * 0.5 + delta_v_down, 100));  //point4
		//
		p1_x = 0;
		p1_y = (int)((0.5 * DIM_Y - road_width_h * 0.5 + delta_h) / DIM_Y * LENGTH);
		p2_x = 226;
		p2_y = (int)((0.5 * DIM_Y - road_width_h * 0.5 + delta_h) / DIM_Y * LENGTH);
		p3_x = 226;
		p3_y = (int)((0.5 * DIM_Y + road_width_h * 0.5 + delta_h) / DIM_Y * LENGTH);
		p4_x = 0;
		p4_y = (int)((0.5 * DIM_Y + road_width_h * 0.5 + delta_h) / DIM_Y * LENGTH);
		std::vector<cv::Point> tmp;
		tmp.push_back(cv::Point(p1_x, p1_y));  //point1
		tmp.push_back(cv::Point(p2_x, p2_y));  //point2
		tmp.push_back(cv::Point(p3_x, p3_y));  //point3
		tmp.push_back(cv::Point(p4_x, p4_y));  //point4
		cv::Point a = intersection(tmp.at(0), tmp.at(1), points.at(1), points.at(2));
		cv::Point b = intersection(tmp.at(2), tmp.at(3), points.at(1), points.at(2));
		std::vector<cv::Point> points_2;
		points_2.push_back(cv::Point(p1_x, p1_y));  //point1
		points_2.push_back(a);  //point2
		points_2.push_back(b);  //point3
		points_2.push_back(cv::Point(p4_x, p4_y));  //point4
		cv::fillConvexPoly(image,               //Image to be drawn on
			points_2,                 //C-Style array of points
			cv::Scalar(61, 199, 209),  //Color , BGR form
			CV_AA,             // connectedness, 4 or 8
			0);

		std::vector<cv::Point2f> points_l2;
		points_l2.push_back(cv::Point2f(0, 0.5 * DIM_Y - road_width_h * 0.5 + delta_h));  //point1
		points_l2.push_back(cv::Point2f(100, 0.5 * DIM_Y - road_width_h * 0.5 + delta_h));  //point2
		points_l2.push_back(cv::Point2f(100, 0.5 * DIM_Y + road_width_h * 0.5 + delta_h));  //point3
		points_l2.push_back(cv::Point2f(0, 0.5 * DIM_Y + road_width_h * 0.5 + delta_h));  //point4
		//draw buildings
		std::vector<std::pair<float, float>> vertices;
		std::vector<std::pair<int, int>> pixes;
		//draw two small blocks
		float dis_side = 0.0f;
		float dis_front = 0.0f;
		float base_x = 0.0f;
		float base_y = 0.0f;
		float x_dim = 0.0f;
		float y_dim = 0.0f;
		float setback_side = 0;
		float setback_rear = 0;
		float setback_front = 0;
		int stories[3] = { G::getInt("block_1"), G::getInt("block_2"), G::getInt("block_3")};
		int buildings = 0;
		float angle = get_angle(points_l1.at(1), points_l1.at(2));
		float angle_com = angle > glm::pi<float>() * 0.5 ? angle - glm::pi<float>() * 0.5 : angle - glm::pi<float>() * 0.5;
		//block1
		cv::Point2f intersect = intersection(points_l2.at(0), points_l2.at(1), points_l1.at(0), points_l1.at(3));
		cv::line(image, cv::Point(points_l2.at(0).x / DIM_X * WIDTH, points_l2.at(0).y / DIM_Y * LENGTH), cv::Point(intersect.x / DIM_X * WIDTH, intersect.y / DIM_Y * LENGTH), cv::Scalar(0, 0, 225), 2, 8);
		//cv::line(image, cv::Point(points_l2.at(0).x / DIM_X * WIDTH, points_l2.at(0).y / DIM_Y * LENGTH), cv::Point(points_l2.at(1).x / DIM_X * WIDTH, points_l2.at(1).y / DIM_Y * LENGTH), cv::Scalar(0, 0, 225), 2, 8);
		//cv::line(image, cv::Point(points_l1.at(0).x / DIM_X * WIDTH, points_l1.at(0).y / DIM_Y * LENGTH), cv::Point(points_l1.at(3).x / DIM_X * WIDTH, points_l1.at(3).y / DIM_Y * LENGTH), cv::Scalar(0, 0, 225), 2, 8);

		base_x = intersect.x;
		base_y = intersect.y;
		std::cout << intersect.x << ", " << intersect.y << std::endl;
		setback_side = genRand(sideWidthRange.first, sideWidthRange.second);
		setback_front = genRand(frontWidthRange.first, frontWidthRange.second);
		dis_side = setback_side;
		dis_front = setback_front;
		buildings = stories[0];
		for (int i = 0; i < buildings; i++){
			float r_value = genRand(buildingDisRange.first, buildingDisRange.second);
			x_dim = genRand(xBuildingDimRange.first, xBuildingDimRange.second);
			y_dim = genRand(yBuildingDimRange.first, yBuildingDimRange.second);
			//first point
			float tmp_1_x = base_x - dis_side - x_dim;
			float tmp_1_y = base_y - dis_front - y_dim;
			//fourth
			float tmp_2_x = base_x - dis_side;
			float tmp_2_y = base_y - dis_front;
			if (tmp_1_x < 0 || tmp_1_y < 0 || tmp_2_x < 0 || tmp_2_y < 0)
			{
				G::global()["block_1"] = i;
				break;
			}
			std::pair<float, float> p1 = std::make_pair(tmp_1_x, tmp_1_y);
			vertices.push_back(p1);
			std::pair<float, float> p2 = std::make_pair(tmp_2_x, tmp_2_y);
			vertices.push_back(p2);

			// add x_dim and distance between buildings
			dis_side = dis_side + x_dim + r_value;
		}
		////block2
		intersect = intersection(points_l2.at(2), points_l2.at(3), points_l1.at(0), points_l1.at(3));
		base_x = intersect.x;
		base_y = intersect.y;
		setback_side = genRand(sideWidthRange.first, sideWidthRange.second);
		setback_front = genRand(frontWidthRange.first, frontWidthRange.second);
		dis_side = setback_side;
		dis_front = setback_front;
		buildings = stories[1];
		for (int i = 0; i < buildings; i++){
			float r_value = genRand(buildingDisRange.first, buildingDisRange.second);
			x_dim = genRand(xBuildingDimRange.first, xBuildingDimRange.second);
			y_dim = genRand(yBuildingDimRange.first, yBuildingDimRange.second);
			//first point
			float tmp_1_x = base_x - dis_side - x_dim;
			float tmp_1_y = base_y + dis_front + y_dim;
			//fourth
			float tmp_2_x = base_x - dis_side;
			float tmp_2_y = base_y + dis_front;
			if (tmp_1_x < 0 || tmp_1_y >= DIM_Y || tmp_2_x < 0 || tmp_2_y >= DIM_Y)
			{
				G::global()["block_2"] = i;
				break;
			}
			std::pair<float, float> p1 = std::make_pair(tmp_1_x, tmp_1_y);
			vertices.push_back(p1);
			std::pair<float, float> p2 = std::make_pair(tmp_2_x, tmp_2_y);
			vertices.push_back(p2);

			// add x_dim and distance between buildings
			dis_side = dis_side + x_dim + r_value;
		}
		//the big block
		setback_side = genRand(sideWidthRange.first, sideWidthRange.second);
		setback_front = genRand(frontWidthRange.first, frontWidthRange.second);
		base_x = 0.5 * DIM_X + road_width_v * 0.5 + delta_v_up + setback_front / glm::sin(angle);
		base_y = 0;
		dis_side = setback_side;
		dis_front = setback_front;
		buildings = stories[2];
		for (int i = 0; i < buildings; i++){
			float r_value = genRand(buildingDisRange.first, buildingDisRange.second);
			x_dim = genRand(yBuildingDimRange.first, yBuildingDimRange.second);//change the x and y
			y_dim = genRand(xBuildingDimRange.first, xBuildingDimRange.second);
			cv::Point2f tmp = get_point(cv::Point2f(base_x, base_y), angle, dis_side);
			//first point
			float tmp_1_x = tmp.x;
			float tmp_1_y = tmp.y;
			tmp = get_point(cv::Point2f(base_x, base_y), angle, dis_side + y_dim);
			//second point
			float tmp_2_x = tmp.x;
			float tmp_2_y = tmp.y;
			tmp = get_point(cv::Point2f(tmp_2_x, tmp_2_y), angle_com, x_dim);
			//third point
			float tmp_3_x = tmp.x;
			float tmp_3_y = tmp.y;
			tmp = get_point(cv::Point2f(tmp_1_x, tmp_1_y), angle_com, x_dim);
			//fourth
			float tmp_4_x = tmp.x;
			float tmp_4_y = tmp.y;
			if (tmp_1_x >= DIM_X || tmp_1_y >= DIM_Y || tmp_2_x >= DIM_X || tmp_2_y >= DIM_Y)
			{
				G::global()["block_3"] = i;
				break;
			}
			int p1_x = (int)(tmp_1_x / DIM_X * WIDTH);
			int p1_y = (int)(tmp_1_y / DIM_X * LENGTH);
			int p2_x = (int)(tmp_2_x / DIM_X * WIDTH);
			int p2_y = (int)(tmp_2_y / DIM_X * LENGTH);
			int p3_x = (int)(tmp_3_x / DIM_X * WIDTH);
			int p3_y = (int)(tmp_3_y / DIM_X * LENGTH);
			int p4_x = (int)(tmp_4_x / DIM_X * WIDTH);
			int p4_y = (int)(tmp_4_y / DIM_X * LENGTH);

			std::vector<cv::Point> points;
			points.push_back(cv::Point(p1_x, p1_y));  //point1
			points.push_back(cv::Point(p2_x, p2_y));  //point2
			points.push_back(cv::Point(p3_x, p3_y));  //point3
			points.push_back(cv::Point(p4_x, p4_y));  //point4
			cv::fillConvexPoly(image,               //Image to be drawn on
				points,                 //C-Style array of points
				cv::Scalar(255, 0, 0),  //Color , BGR form
				CV_AA,             // connectedness, 4 or 8
				0);
			//

			// add x_dim and distance between buildings
			dis_side = dis_side + y_dim + r_value;
		}
		//
		for (int i = 0; i < vertices.size(); i += 2){
			int p1_x = (int)((vertices.at(i).first) / DIM_X * WIDTH);
			int p1_y = (int)((vertices.at(i).second) / DIM_Y * LENGTH);
			std::pair<int, int> p1 = std::make_pair(p1_x, p1_y);
			pixes.push_back(p1);
			int p2_x = (int)((vertices.at(i + 1).first) / DIM_X * WIDTH);
			int p2_y = (int)((vertices.at(i + 1).second) / DIM_Y * LENGTH);
			std::pair<int, int> p2 = std::make_pair(p2_x, p2_y);
			pixes.push_back(p2);
		}
		for (int i = 0; i < pixes.size(); i += 2){
			cv::rectangle(image,
				cv::Point(pixes.at(i).first, pixes.at(i).second),
				cv::Point(pixes.at(i + 1).first, pixes.at(i + 1).second),
				cv::Scalar(255, 0, 0),
				-1,
				0);
		}
		// save the parameter values
		out_params << iter + 1 << ",";
		out_params << G::getFloat("road_type") << ",";
		out_params << G::getFloat("road_base_orientation") << ",";
		out_params << road_width_h << ",";
		out_params << road_width_v << ",";
		out_params << G::getInt("block_1") << ",";
		out_params << G::getInt("block_2") << ",";
		out_params << G::getInt("block_3") << "\n";
		out_params.flush();
	}
	//single road
	else if (road_type == 2){
		float road_width_h = genRand(roadWidthRange.first, roadWidthRange.second);
		float road_width_v = genRand(roadWidthRange.first, roadWidthRange.second);
		float delta_v_up = genRand(-10.0f, 10.0f);
		float delta_v_down = genRand(-10.0f, 10.0f);
		//
		std::cout << "  road_type: " << G::getInt("road_type") << std::endl;
		std::cout << "  road_base_orientation: " << G::getFloat("road_base_orientation") << std::endl;
		std::cout << "  road_width_v: " << road_width_v << std::endl;
		std::cout << "  road_width_h: " << road_width_h << std::endl;
		std::cout << "  delta_v_up: " << delta_v_up << std::endl;
		std::cout << "  delta_v_down: " << delta_v_down << std::endl;
		std::cout << "  block_1: " << G::getInt("block_1") << std::endl;
		std::cout << "  block_2: " << G::getInt("block_2") << std::endl;
		// write the header to the file
		out_params << "No." << ",";
		out_params << "road_type" << ",";
		out_params << "road_base_orientation" << ",";
		out_params << "road_width_h" << ",";
		out_params << "road_width_v" << ",";
		out_params << "block_1" << ",";
		out_params << "block_2" << "\n";
		int p1_x = (int)((0.5 * DIM_X - road_width_v * 0.5 + delta_v_up) / DIM_X * WIDTH);
		int p1_y = 0;
		int p2_x = (int)((0.5 * DIM_X + road_width_v * 0.5 + delta_v_up) / DIM_X * WIDTH);
		int p2_y = 0;
		int p3_x = (int)((0.5 * DIM_X - road_width_v * 0.5 + delta_v_down) / DIM_X * WIDTH);
		int p3_y = 226;
		int p4_x = (int)((0.5 * DIM_X + road_width_v * 0.5 + delta_v_down) / DIM_X * WIDTH);
		int p4_y = 226;

		std::vector<cv::Point> points;
		points.push_back(cv::Point(p1_x, p1_y));  //point1
		points.push_back(cv::Point(p2_x, p2_y));  //point2
		points.push_back(cv::Point(p4_x, p4_y));  //point3
		points.push_back(cv::Point(p3_x, p3_y));  //point4
		cv::fillConvexPoly(image,               //Image to be drawn on
			points,                 //C-Style array of points
			cv::Scalar(61, 199, 209),  //Color , BGR form
			CV_AA,             // connectedness, 4 or 8
			0);
		//
		std::vector<cv::Point2f> points_l1;

		points_l1.push_back(cv::Point2f(0.5 * DIM_X - road_width_v * 0.5 + delta_v_up, 0));  //point1
		points_l1.push_back(cv::Point2f(0.5 * DIM_X + road_width_v * 0.5 + delta_v_up, 0));  //point2
		points_l1.push_back(cv::Point2f(0.5 * DIM_X + road_width_v * 0.5 + delta_v_down, 100));  //point3
		points_l1.push_back(cv::Point2f(0.5 * DIM_X - road_width_v * 0.5 + delta_v_down, 100));  //point4
		//
		//draw buildings
		float dis_side = 0.0f;
		float dis_front = 0.0f;
		float base_x = 0.0f;
		float base_y = 0.0f;
		float x_dim = 0.0f;
		float y_dim = 0.0f;
		float setback_side = 0;
		float setback_rear = 0;
		float setback_front = 0;
		int stories[2] = { G::getInt("block_1"), G::getInt("block_2")};
		int buildings = 0;
		float angle = get_angle(points_l1.at(0), points_l1.at(3));
		float angle_com = angle - glm::pi<float>() * 0.5;
		//the big block1
		setback_side = genRand(sideWidthRange.first, sideWidthRange.second);
		setback_front = genRand(frontWidthRange.first, frontWidthRange.second);
		base_x = 0.5 * DIM_X - road_width_v * 0.5 + delta_v_up - setback_front / glm::sin(angle);
		base_y = 0;
		dis_side = setback_side;
		dis_front = setback_front;
		buildings = stories[0];
		for (int i = 0; i < buildings; i++){
			float r_value = genRand(buildingDisRange.first, buildingDisRange.second);
			x_dim = genRand(yBuildingDimRange.first, yBuildingDimRange.second);//change the x and y
			y_dim = genRand(xBuildingDimRange.first, xBuildingDimRange.second);
			cv::Point2f tmp = get_point(cv::Point2f(base_x, base_y), angle, dis_side);
			//first point
			float tmp_1_x = tmp.x;
			float tmp_1_y = tmp.y;
			tmp = get_point(cv::Point2f(base_x, base_y), angle,dis_side + y_dim);
			//second point
			float tmp_2_x = tmp.x;
			float tmp_2_y = tmp.y;
			tmp = get_point(cv::Point2f(tmp_2_x, tmp_2_y), angle_com, -x_dim);
			//third point
			float tmp_3_x = tmp.x;
			float tmp_3_y = tmp.y;
			tmp = get_point(cv::Point2f(tmp_1_x, tmp_1_y), angle_com, -x_dim);
			//fourth
			float tmp_4_x = tmp.x;
			float tmp_4_y = tmp.y;
			if (tmp_1_x >= DIM_X || tmp_1_y >= DIM_Y || tmp_2_x >= DIM_X || tmp_2_y >= DIM_Y)
			{
				G::global()["block_1"] = i;
				break;
			}
			int p1_x = (int)(tmp_1_x / DIM_X * WIDTH);
			int p1_y = (int)(tmp_1_y / DIM_X * LENGTH);
			int p2_x = (int)(tmp_2_x / DIM_X * WIDTH);
			int p2_y = (int)(tmp_2_y / DIM_X * LENGTH);
			int p3_x = (int)(tmp_3_x / DIM_X * WIDTH);
			int p3_y = (int)(tmp_3_y / DIM_X * LENGTH);
			int p4_x = (int)(tmp_4_x / DIM_X * WIDTH);
			int p4_y = (int)(tmp_4_y / DIM_X * LENGTH);

			std::vector<cv::Point> points;
			points.push_back(cv::Point(p1_x, p1_y));  //point1
			points.push_back(cv::Point(p2_x, p2_y));  //point2
			points.push_back(cv::Point(p3_x, p3_y));  //point3
			points.push_back(cv::Point(p4_x, p4_y));  //point4
			cv::fillConvexPoly(image,               //Image to be drawn on
				points,                 //C-Style array of points
				cv::Scalar(255, 0, 0),  //Color , BGR form
				CV_AA,             // connectedness, 4 or 8
				0);
			//

			// add x_dim and distance between buildings
			dis_side = dis_side + y_dim + r_value;
		}
		//the big block2
		angle = get_angle(points_l1.at(1), points_l1.at(2));
		angle_com = angle - glm::pi<float>() * 0.5;
		setback_side = genRand(sideWidthRange.first, sideWidthRange.second);
		setback_front = genRand(frontWidthRange.first, frontWidthRange.second);
		base_x = 0.5 * DIM_X + road_width_v * 0.5 + delta_v_up + setback_front / glm::sin(angle);
		base_y = 0;
		dis_side = setback_side;
		dis_front = setback_front;
		buildings = stories[1];
		for (int i = 0; i < buildings; i++){
			float r_value = genRand(buildingDisRange.first, buildingDisRange.second);
			x_dim = genRand(yBuildingDimRange.first, yBuildingDimRange.second);//change the x and y
			y_dim = genRand(xBuildingDimRange.first, xBuildingDimRange.second);
			cv::Point2f tmp = get_point(cv::Point2f(base_x, base_y), angle, dis_side);
			//first point
			float tmp_1_x = tmp.x;
			float tmp_1_y = tmp.y;
			tmp = get_point(cv::Point2f(base_x, base_y), angle, dis_side + y_dim);
			//second point
			float tmp_2_x = tmp.x;
			float tmp_2_y = tmp.y;
			tmp = get_point(cv::Point2f(tmp_2_x, tmp_2_y), angle_com, x_dim);
			//third point
			float tmp_3_x = tmp.x;
			float tmp_3_y = tmp.y;
			tmp = get_point(cv::Point2f(tmp_1_x, tmp_1_y), angle_com, x_dim);
			//fourth
			float tmp_4_x = tmp.x;
			float tmp_4_y = tmp.y;
			if (tmp_1_x >= DIM_X || tmp_1_y >= DIM_Y || tmp_2_x >= DIM_X || tmp_2_y >= DIM_Y)
			{
				G::global()["block_2"] = i;
				break;
			}
			int p1_x = (int)(tmp_1_x / DIM_X * WIDTH);
			int p1_y = (int)(tmp_1_y / DIM_X * LENGTH);
			int p2_x = (int)(tmp_2_x / DIM_X * WIDTH);
			int p2_y = (int)(tmp_2_y / DIM_X * LENGTH);
			int p3_x = (int)(tmp_3_x / DIM_X * WIDTH);
			int p3_y = (int)(tmp_3_y / DIM_X * LENGTH);
			int p4_x = (int)(tmp_4_x / DIM_X * WIDTH);
			int p4_y = (int)(tmp_4_y / DIM_X * LENGTH);

			std::vector<cv::Point> points;
			points.push_back(cv::Point(p1_x, p1_y));  //point1
			points.push_back(cv::Point(p2_x, p2_y));  //point2
			points.push_back(cv::Point(p3_x, p3_y));  //point3
			points.push_back(cv::Point(p4_x, p4_y));  //point4
			cv::fillConvexPoly(image,               //Image to be drawn on
				points,                 //C-Style array of points
				cv::Scalar(255, 0, 0),  //Color , BGR form
				CV_AA,             // connectedness, 4 or 8
				0);
			//

			// add x_dim and distance between buildings
			dis_side = dis_side + y_dim + r_value;
		}
		// save the parameter values
		out_params << iter + 1 << ",";
		out_params << G::getFloat("road_type") << ",";
		out_params << G::getFloat("road_base_orientation") << ",";
		out_params << road_width_h << ",";
		out_params << road_width_v << ",";
		out_params << G::getInt("block_1") << ",";
		out_params << G::getInt("block_2") << "\n";
		out_params.flush();
	}
	else if (road_type == 3){
		float road_width_h = genRand(roadWidthRange.first, roadWidthRange.second);
		float road_width_v = genRand(roadWidthRange.first, roadWidthRange.second);
		float delta_v_up = genRand(-10.0f, 10.0f);
		float delta_v_down = genRand(-10.0f, 10.0f);
		//
		std::cout << "  road_type: " << G::getInt("road_type") << std::endl;
		std::cout << "  road_base_orientation: " << G::getFloat("road_base_orientation") << std::endl;
		std::cout << "  road_width_v: " << road_width_v << std::endl;
		std::cout << "  road_width_h: " << road_width_h << std::endl;
		std::cout << "  delta_v_up: " << delta_v_up << std::endl;
		std::cout << "  delta_v_down: " << delta_v_down << std::endl;
		std::cout << "  block_1: " << G::getInt("block_1") << std::endl;
		std::cout << "  block_2: " << G::getInt("block_2") << std::endl;
		// write the header to the file
		out_params << "No." << ",";
		out_params << "road_type" << ",";
		out_params << "road_base_orientation" << ",";
		out_params << "road_width_h" << ",";
		out_params << "road_width_v" << ",";
		out_params << "block_1" << ",";
		out_params << "block_2" << "\n";
		int p1_x = (int)((0.5 * DIM_X - road_width_v * 0.5 + delta_v_up) / DIM_X * WIDTH);
		int p1_y = (int)(20.0f / DIM_X * WIDTH);
		int p2_x = (int)((0.5 * DIM_X + road_width_v * 0.5 + delta_v_up) / DIM_X * WIDTH);
		int p2_y = (int)(20.0f / DIM_X * WIDTH);
		int p3_x = (int)((0.5 * DIM_X - road_width_v * 0.5 + delta_v_down) / DIM_X * WIDTH);
		int p3_y = 226;
		int p4_x = (int)((0.5 * DIM_X + road_width_v * 0.5 + delta_v_down) / DIM_X * WIDTH);
		int p4_y = 226;

		std::vector<cv::Point> points;
		points.push_back(cv::Point(p1_x, p1_y));  //point1
		points.push_back(cv::Point(p2_x, p2_y));  //point2
		points.push_back(cv::Point(p4_x, p4_y));  //point3
		points.push_back(cv::Point(p3_x, p3_y));  //point4
		cv::fillConvexPoly(image,               //Image to be drawn on
			points,                 //C-Style array of points
			cv::Scalar(61, 199, 209),  //Color , BGR form
			CV_AA,             // connectedness, 4 or 8
			0);
		//
		std::vector<cv::Point2f> points_l1;

		points_l1.push_back(cv::Point2f(0.5 * DIM_X - road_width_v * 0.5 + delta_v_up, 20));  //point1
		points_l1.push_back(cv::Point2f(0.5 * DIM_X + road_width_v * 0.5 + delta_v_up, 20));  //point2
		points_l1.push_back(cv::Point2f(0.5 * DIM_X + road_width_v * 0.5 + delta_v_down, 100));  //point3
		points_l1.push_back(cv::Point2f(0.5 * DIM_X - road_width_v * 0.5 + delta_v_down, 100));  //point4
		//
		//draw buildings
		float dis_side = 0.0f;
		float dis_front = 0.0f;
		float base_x = 0.0f;
		float base_y = 0.0f;
		float x_dim = 0.0f;
		float y_dim = 0.0f;
		float setback_side = 0;
		float setback_rear = 0;
		float setback_front = 0;
		int stories[2] = { G::getInt("block_1"), G::getInt("block_2") };
		int buildings = 0;
		float angle = get_angle(points_l1.at(0), points_l1.at(3));
		float angle_com = angle - glm::pi<float>() * 0.5;
		//the big block1
		setback_side = genRand(sideWidthRange.first, sideWidthRange.second);
		setback_front = genRand(frontWidthRange.first, frontWidthRange.second);
		base_x = 0.5 * DIM_X - road_width_v * 0.5 + delta_v_up - setback_front / glm::sin(angle);
		base_y = 20;
		dis_side = setback_side;
		dis_front = setback_front;
		buildings = stories[0];
		for (int i = 0; i < buildings; i++){
			float r_value = genRand(buildingDisRange.first, buildingDisRange.second);
			x_dim = genRand(yBuildingDimRange.first, yBuildingDimRange.second);//change the x and y
			y_dim = genRand(xBuildingDimRange.first, xBuildingDimRange.second);
			cv::Point2f tmp = get_point(cv::Point2f(base_x, base_y), angle, dis_side);
			//first point
			float tmp_1_x = tmp.x;
			float tmp_1_y = tmp.y;
			tmp = get_point(cv::Point2f(base_x, base_y), angle, dis_side + y_dim);
			//second point
			float tmp_2_x = tmp.x;
			float tmp_2_y = tmp.y;
			tmp = get_point(cv::Point2f(tmp_2_x, tmp_2_y), angle_com, -x_dim);
			//third point
			float tmp_3_x = tmp.x;
			float tmp_3_y = tmp.y;
			tmp = get_point(cv::Point2f(tmp_1_x, tmp_1_y), angle_com, -x_dim);
			//fourth
			float tmp_4_x = tmp.x;
			float tmp_4_y = tmp.y;
			if (tmp_1_x >= DIM_X || tmp_1_y >= DIM_Y || tmp_2_x >= DIM_X || tmp_2_y >= DIM_Y)
			{
				G::global()["block_1"] = i;
				break;
			}
			int p1_x = (int)(tmp_1_x / DIM_X * WIDTH);
			int p1_y = (int)(tmp_1_y / DIM_X * LENGTH);
			int p2_x = (int)(tmp_2_x / DIM_X * WIDTH);
			int p2_y = (int)(tmp_2_y / DIM_X * LENGTH);
			int p3_x = (int)(tmp_3_x / DIM_X * WIDTH);
			int p3_y = (int)(tmp_3_y / DIM_X * LENGTH);
			int p4_x = (int)(tmp_4_x / DIM_X * WIDTH);
			int p4_y = (int)(tmp_4_y / DIM_X * LENGTH);

			std::vector<cv::Point> points;
			points.push_back(cv::Point(p1_x, p1_y));  //point1
			points.push_back(cv::Point(p2_x, p2_y));  //point2
			points.push_back(cv::Point(p3_x, p3_y));  //point3
			points.push_back(cv::Point(p4_x, p4_y));  //point4
			cv::fillConvexPoly(image,               //Image to be drawn on
				points,                 //C-Style array of points
				cv::Scalar(255, 0, 0),  //Color , BGR form
				CV_AA,             // connectedness, 4 or 8
				0);
			//

			// add x_dim and distance between buildings
			dis_side = dis_side + y_dim + r_value;
		}
		//the big block2
		angle = get_angle(points_l1.at(1), points_l1.at(2));
		angle_com = angle - glm::pi<float>() * 0.5;
		setback_side = genRand(sideWidthRange.first, sideWidthRange.second);
		setback_front = genRand(frontWidthRange.first, frontWidthRange.second);
		base_x = 0.5 * DIM_X + road_width_v * 0.5 + delta_v_up + setback_front / glm::sin(angle);
		base_y = 20;
		dis_side = setback_side;
		dis_front = setback_front;
		buildings = stories[1];
		for (int i = 0; i < buildings; i++){
			float r_value = genRand(buildingDisRange.first, buildingDisRange.second);
			x_dim = genRand(yBuildingDimRange.first, yBuildingDimRange.second);//change the x and y
			y_dim = genRand(xBuildingDimRange.first, xBuildingDimRange.second);
			cv::Point2f tmp = get_point(cv::Point2f(base_x, base_y), angle, dis_side);
			//first point
			float tmp_1_x = tmp.x;
			float tmp_1_y = tmp.y;
			tmp = get_point(cv::Point2f(base_x, base_y), angle, dis_side + y_dim);
			//second point
			float tmp_2_x = tmp.x;
			float tmp_2_y = tmp.y;
			tmp = get_point(cv::Point2f(tmp_2_x, tmp_2_y), angle_com, x_dim);
			//third point
			float tmp_3_x = tmp.x;
			float tmp_3_y = tmp.y;
			tmp = get_point(cv::Point2f(tmp_1_x, tmp_1_y), angle_com, x_dim);
			//fourth
			float tmp_4_x = tmp.x;
			float tmp_4_y = tmp.y;
			if (tmp_1_x >= DIM_X || tmp_1_y >= DIM_Y || tmp_2_x >= DIM_X || tmp_2_y >= DIM_Y)
			{
				G::global()["block_2"] = i;
				break;
			}
			int p1_x = (int)(tmp_1_x / DIM_X * WIDTH);
			int p1_y = (int)(tmp_1_y / DIM_X * LENGTH);
			int p2_x = (int)(tmp_2_x / DIM_X * WIDTH);
			int p2_y = (int)(tmp_2_y / DIM_X * LENGTH);
			int p3_x = (int)(tmp_3_x / DIM_X * WIDTH);
			int p3_y = (int)(tmp_3_y / DIM_X * LENGTH);
			int p4_x = (int)(tmp_4_x / DIM_X * WIDTH);
			int p4_y = (int)(tmp_4_y / DIM_X * LENGTH);

			std::vector<cv::Point> points;
			points.push_back(cv::Point(p1_x, p1_y));  //point1
			points.push_back(cv::Point(p2_x, p2_y));  //point2
			points.push_back(cv::Point(p3_x, p3_y));  //point3
			points.push_back(cv::Point(p4_x, p4_y));  //point4
			cv::fillConvexPoly(image,               //Image to be drawn on
				points,                 //C-Style array of points
				cv::Scalar(255, 0, 0),  //Color , BGR form
				CV_AA,             // connectedness, 4 or 8
				0);
			//

			// add x_dim and distance between buildings
			dis_side = dis_side + y_dim + r_value;
		}
		// save the parameter values
		out_params << iter + 1 << ",";
		out_params << G::getFloat("road_type") << ",";
		out_params << G::getFloat("road_base_orientation") << ",";
		out_params << road_width_h << ",";
		out_params << road_width_v << ",";
		out_params << G::getInt("block_1") << ",";
		out_params << G::getInt("block_2") << "\n";
		out_params.flush();
	}
	else{

	}
	cv::imwrite(filename_buildings_image.toUtf8().constData(), image);
}

float SyntheticData::genRand() {
	return rand() / (float(RAND_MAX) + 1);
}

float SyntheticData::genRand(float a, float b) {
	return genRand() * (b - a) + a;
}

int SyntheticData::genRand(int a, int b) {
	return (int)round((genRand() * (b - a))) + a;
}

cv::Point2f SyntheticData::intersection(cv::Point2f p1, cv::Point2f p2, cv::Point2f p3, cv::Point2f p4){
	// Line AB represented as a1x + b1y = c1
	float a1 = p2.y - p1.y;
	float b1 = p1.x - p2.x;
	float c1 = a1*(p1.x) + b1*(p1.y);

	// Line CD represented as a2x + b2y = c2
	float a2 = p4.y - p3.y;
	float b2 = p3.x - p4.x;
	float c2 = a2*(p3.x) + b2*(p3.y);

	float determinant = a1*b2 - a2*b1;

	if (determinant == 0)
	{
		// The lines are parallel. This is simplified
		// by returning a pair of FLT_MAX
		return NULL;
	}
	else
	{
		float x = (b2*c1 - b1*c2) / determinant;
		float y = (a1*c2 - a2*c1) / determinant;
		return cv::Point2f(x, y);
	}

	//// Store the values for fast access and easy
	//// equations-to-code conversion
	//float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
	//float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;

	//float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	//// If d is zero, there is no intersection
	//if (d == 0) return NULL;

	//// Get the x and y
	//float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
	//float x = (pre * (x3 - x4) - (x1 - x2) * post) / d;
	//float y = (pre * (y3 - y4) - (y1 - y2) * post) / d;

	//// Check if the x and y coordinates are within both lines
	//if (x < cv::min(x1, x2) || x > cv::max(x1, x2) ||
	//	x < cv::min(x3, x4) || x > cv::max(x3, x4)) return NULL;
	//if (y < cv::min(y1, y2) || y > cv::max(y1, y2) ||
	//	y < cv::min(y3, y4) || y > cv::max(y3, y4)) return NULL;

	//// Return the point of intersection
	//cv::Point2f ret = cv::Point2f(x, y);
	//return ret;
}
cv::Point2f SyntheticData::get_point(cv::Point2f p1, float angle, float delta){
	float x = p1.x + glm::cos(angle) * delta;
	float y = p1.y + glm::sin(angle) * delta;
	return cv::Point2f(x, y);
}

float SyntheticData::get_angle(cv::Point2f p1, cv::Point2f p2){
	if (glm::abs(p1.x - p2.x) < SMALL_FLOAT)
		return 0.5 * glm::pi<float>();
	else {
		float angle = glm::atan((p2.y - p1.y) / (p2.x - p1.x));
		if (angle < 0)
			return glm::pi<float>() + angle;
		else
			return angle;
	}
}