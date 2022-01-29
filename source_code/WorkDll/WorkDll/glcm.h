#pragma once


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <cmath>
#include <utility>

//Gray Level Co-ocurrency Matrix
class glcm {
public:

	glcm(const cv::Mat& src, int levels, const cv::Mat& mask);

	//constrast group
	float contrast() const { return _contrast; }
	float hom() const { return _hom; } //Homogeneity, also called inverse difference moment(IDM)


									   //orderliness group
	float energy() const { return _energy; }//angular second moments(asm)
	float entropy() const { return _entropy; }

	//stats group
	float correlation() const { return _correlation; }

private:
	void grade(const cv::Mat& src, cv::Mat& dst, int levels);
	std::pair<float, float> mean(const cv::Mat& src);
	std::pair<float, float> variance(const cv::Mat& src, float u_i, float u_j);

	//textrue features
	float _contrast = 0.0, _hom = 0.0, _energy = 0.0, _entropy = 0.0, _correlation = 0.0;
};

inline
glcm::glcm(const cv::Mat& src, int levels, const cv::Mat& mask) {
	cv::Mat src_graded = cv::Mat::zeros(src.size(), src.type());
	cv::Mat GLCM = cv::Mat::zeros(levels, levels, CV_32FC1);

	grade(src, src_graded, levels);

	int rows = src_graded.rows, cols = src_graded.cols;
	for (int i = 1; i < rows - 1; ++i) { //ignore the border
		const uchar *current = src_graded.ptr<uchar>(i);
		const uchar *next = src_graded.ptr<uchar>(i + 1);
		const uchar *current_mask = mask.ptr<uchar>(i);
		const uchar *next_mask = mask.ptr<uchar>(i + 1);
		++current; ++next; ++current_mask; ++next_mask;

		for (int j = 1; j < cols - 1; ++j) {
			if (*current_mask > 0 && *(current_mask + 1) > 0 &&
				*next_mask > 0 && *(next_mask - 1) > 0 &&
				*(next_mask + 1) > 0) {

				++GLCM.at<float>(*current, *(current + 1)); //horizontal
				++GLCM.at<float>(*current, *next);          //vertical
				++GLCM.at<float>(*current, *(next - 1));    //diagnal1
				++GLCM.at<float>(*current, *(next + 1));    //diagnal2
			}
			++current; ++next; ++current_mask; ++next_mask;
		}
	}

	GLCM += GLCM.t();
	GLCM /= sum(GLCM)[0];

	//The next three blocks is prepared for calculating _correlation
	//calculate GLCM mean in x direction and in y direction, respectively
	auto muon = mean(GLCM);
	float muon_i = muon.first, muon_j = muon.second;

	//calculate GLCM variance
	auto v = variance(GLCM, muon.first, muon.second);
	float sigma_i_square = v.first, sigma_j_square = v.second;

	//calculate standard deviation
	float sigma_i = std::sqrt(sigma_i_square), sigma_j = std::sqrt(sigma_j_square);

	//Texture Features!
	for (int i = 0; i < levels; ++i) {
		const float *data = GLCM.ptr<float>(i);
		for (int j = 0; j < levels; ++j) {
			_contrast += *data * (i - j) * (i - j);
			_hom += *data / (1 + (i - j) * (i - j));
			_energy += *data * *data;
			_entropy -= *data * (*data == 0 ? 0 : std::log10(*data));
			_correlation += *data * (i - muon_i) * (j - muon_j) / (sigma_i * sigma_j);
			data++;
		}
	}

}

inline
void glcm::grade(const cv::Mat& src, cv::Mat& dst, int levels) {
	cv::Mat lookup(1, 256, CV_8U);
	uchar *p = lookup.data;
	int level_size = 256 / levels;
	for (int i = 0; i < 256; ++i) {
		*p++ = i / level_size;
	}
	LUT(src, lookup, dst);
}

inline
std::pair<float, float> glcm::mean(const cv::Mat& src) {
	std::pair<float, float> muon;
	for (int i = 0; i < src.rows; ++i) {
		const float *data = src.ptr<float>(i);
		for (int j = 0; j < src.cols; ++j) {
			muon.first += *data * i;
			muon.second += *data * j;
			data++;
		}
	}

	return muon;
}

inline
std::pair<float, float> glcm::variance(const cv::Mat& src, float muon_i, float muon_j) {
	std::pair<float, float> v;
	for (int i = 0; i < src.rows; ++i) {
		const float *data = src.ptr<float>(i);
		for (int j = 0; j < src.cols; ++j) {
			v.first += *data * (i - muon_i) * (i - muon_i);
			v.second += *data * (j - muon_j) * (j - muon_i);
			data++;
		}
	}

	return v;
}
