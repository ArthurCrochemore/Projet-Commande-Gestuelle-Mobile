#include <cstdio>
#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;
using namespace std;
using namespace cv;

struct Element {
	vector<double> caracs;
	int label;
};

class Learning {
private:
	vector<Element> data;

public:
	Learning(const vector<Element>& inputData) : data(inputData) {}

	//K-nearest neigbors
	void learn() {

	}

	int predict(vector<double> elem, int k = 3) {
		vector<pair<long double, int>> distances; // (distance, classe)

		for (const auto& class_element : data) {
			long double distance = 0.0;
			for (size_t idx = 0; idx < elem.size(); ++idx) {
				distance += pow(elem[idx] - class_element.caracs[idx], 2);
			}
			distance = sqrt(distance);
			distances.push_back({ distance, class_element.label });
		}

		sort(distances.begin(), distances.end());

		int max_label = 0;
		for (const auto& element : data) {
			max_label = max(max_label, element.label);
		}

		vector<int> label_count(max_label + 1, 0);

		for (int i = 0; i < k; ++i) {
			label_count[distances[i].second]++;
		}

		return max_element(label_count.begin(), label_count.end()) - label_count.begin();
	}
};

bool checkPath(string str) {
	if (str.empty()) {
		return true;
	}

	if (str[0] == ' ') {
		return true;
	}

	return false;
}

vector<double> open_picture(string imageName) {
	string imagePath = "S:\\Sherbrooke\\Semestre_2\\Projet-Commande-Gestuelle-Mobile\\learning\\database\\" + imageName;
	cout << "Nous chargeans l'image : " << imagePath << endl;	
	Mat image = imread(imagePath);

	if (image.empty()) {
		throw exception("Erreur : impossible de charger l'image !");
	}

	vector<double> pixelValues;

	for (int i = 0; i < image.rows; ++i) {
		for (int j = 0; j < image.cols; ++j)
			pixelValues.push_back(static_cast<double>(image.at<uchar>(i, j)) / 255.0);
	}

	return pixelValues;
}

int main() {
	vector<Element> data = {};
	vector<string> classFolders = { "classe0", "classe1" };
	vector<double> imageVector;
	try {
		int classIdx = 0;
		for (const auto& classFolder : classFolders) {
			string folderPath = "S:\\Sherbrooke\\Semestre_2\\Projet-Commande-Gestuelle-Mobile\\learning\\database\\" + classFolder;

			for (const auto& entry : fs::directory_iterator(folderPath)) {
				if (entry.is_regular_file()) { // Vérifie si c'est un fichier
					string imagePath = entry.path().string();
					imageVector = open_picture(imagePath);
					data.push_back({ imageVector, classIdx });

					cout << "Image " << imagePath << " loaded, classe: " << classFolder << endl;
				}
			}
			classIdx++;
		}

		imageVector = open_picture( "picture_idx.jpg" );
	} 
	catch (exception& e) {
		cerr << e.what() << endl;
		return EXIT_FAILURE;
	}
	catch (...) {
		cerr << "Erreur inconnue" << endl;
		return EXIT_FAILURE;
	}

	Learning system(data);

	cout << "Prediction: " << system.predict(imageVector) << endl;


	return 0;
}