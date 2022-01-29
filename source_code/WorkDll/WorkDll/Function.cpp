#include <opencv.hpp>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "glcm.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "svm-predict.h"
#include "svm-scale.h"

using namespace cv;
using namespace std;

#ifdef WORKDLL_EXPORTS  
#define WORKDLL_API __declspec(dllexport)   
#else  
#define WORKDLL_API __declspec(dllimport)   
#endif  

char restoreFile[] = "train.tr.range";
const char tobeScaled[] = "..\\silkworm_data.txt";
const char scaled[] = "silkworm_data.scale";

const char tobePredicted[] = "silkworm_data.scale";
const char modelFile[] = "train.tr.model";
const char predictResult[] = "silkworm.predict";

char saveFile[] = "train.tr.range";
const char trainTobeScaled[] = "..\\train_data.txt";
const char trainScaled[] = "train.tr";

const string easypyPath = "..\\libsvm-3.21\\tools\\easy.py";


struct AreaCmp {
	AreaCmp(const vector<float>& _areas) : areas(&_areas) {}
	bool operator()(int a, int b) const { return (*areas)[a] > (*areas)[b]; }
	const vector<float>* areas;
};
//
Mat src, bitImage;
const int Gray_Levels = 32;
int thresh = 200;
const string libsvm_data = "../silkworm_data.txt";
const int attributes_num = 9;
bool First = 1;

void silkworm_features(const string& imageName, bool flag,string save_path) {
	if ((src = imread(imageName, IMREAD_GRAYSCALE)).empty()) {
		cerr << "\nFeatures\n"
			<< "Cannot read image file:\n"
			<< imageName << " image\n"
			<< endl;
		return;
	}

	threshold(src, bitImage, thresh, 255, THRESH_BINARY_INV);

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(bitImage, contours, hierarchy, RETR_TREE, CHAIN_APPROX_NONE, Point());

	vector<int> sortIdx(contours.size());
	vector<float> areas(contours.size());
	for (int n = 0; n < (int)contours.size(); n++) {
		sortIdx[n] = n;
		areas[n] = contourArea(contours[n], false);
	}
	// sort contours so that the largest contours go first
	std::sort(sortIdx.begin(), sortIdx.end(), AreaCmp(areas));
	int idx = sortIdx[0];

	vector<float> features;
	//周长
	float perimeter = arcLength(contours[idx], true), area = contourArea(contours[idx], false);
	features.push_back(perimeter);
	features.push_back(area);
	features.push_back(4 * M_PI * area / (perimeter * perimeter));

	RotatedRect rRect = fitEllipse(contours[idx]);
	float a, b;
	if (rRect.size.width > rRect.size.height) { a = rRect.size.width / 2; b = rRect.size.height / 2; }
	else { a = rRect.size.height / 2; b = rRect.size.width / 2; }
	features.push_back(sqrt(1.0 - pow(b / a, 2)));

	/*
周长
面积
圆形度
偏心率
对比度
逆差矩
能量
熵
相关度
	*/
	glcm matrix(src, Gray_Levels, bitImage);
	features.push_back(matrix.contrast());
	features.push_back(matrix.hom());
	features.push_back(matrix.energy());
	features.push_back(matrix.entropy());
	features.push_back(matrix.correlation());

	if (save_path != libsvm_data) {
		if (First) {
			system("del ..\\train_data.txt");
			First = 0;
		}
		ofstream out(save_path, ofstream::app);//, 
		if (!out.is_open()) {
			cerr << "fail to open " << save_path << endl;
			return;
		}

		if (flag == true) { out << 1 << " "; }
		else { out << -1 << " "; }

		for (int i = 0; i < attributes_num; ++i) { out << i + 1 << ":" << features[i] << " "; }
		//for (int i = 0; i < attributes_num; ++i) { out << features[i] << " "; }
		//out << endl;
		//out << "1:" << features[2] << " ";
		out << endl;
	}else{
		ofstream out(save_path);// , ofstream::app);//, ofstream::app);
											   //else ofstream out(save_path, ofstream::app);

		if (!out.is_open()) {
			cerr << "fail to open " << save_path << endl;
			return;
		}

		if (flag == true) { out << 1 << " "; }
		else { out << -1 << " "; }

		for (int i = 0; i < attributes_num; ++i) { out << i + 1 << ":" << features[i] << " "; }

		out << endl;
	}
}

 
extern "C" int  _declspec(dllexport) WorkFunction(char *Path)
{
	silkworm_features(Path,false, libsvm_data);//提取特征

	//归一化
	//system("..\\libsvm-3.21\\windows\\svm-scale -r train.tr.range ..\\silkworm_data.txt > silkworm_data.scale");
	my_svm_scale(tobeScaled, scaled, restoreFile);
	//预测
	//system("..\\libsvm-3.21\\windows\\svm-predict silkworm_data.scale train.tr.model silkworm.predict");
	my_svm_predict(tobePredicted, modelFile, predictResult);
	

	int x = 0;
	ifstream file;
	file.open("silkworm.predict");
	file >> x;

	return x;
}

extern "C" void WORKDLL_API getFeatures(char *Path, int flag) {
	string aim_data = "../train_data.txt";
	silkworm_features(Path, flag, aim_data);
}

extern "C" void WORKDLL_API TrainFunction(int tot) {
	//int train_num = tot / 5 * 4;
	//int train_num = tot;
	//string s = to_string(train_num);
	//string path = "python ..\\libsvm-3.21\\tools\\subset.py ..\\train_data.txt "
	//	+ s
	//	+ " train.tr test.te";

	//char ss[100];
	//for (int i = 0; i < path.length(); i++)ss[i] = path[i];
	//ss[path.length()] = '\0';
	//system(ss);
	my_svm_scale(trainTobeScaled, trainScaled, NULL, saveFile);



	string cmd = "python " + easypyPath + " " + trainScaled;
	const char* c_cmd = cmd.c_str();
	//FILE* cmdtxt = fopen("cmdtxt", "w");
	//fprintf(cmdtxt, c_cmd);
	//fclose(cmdtxt);

	//system(c_cmd);
	system(c_cmd);

}
