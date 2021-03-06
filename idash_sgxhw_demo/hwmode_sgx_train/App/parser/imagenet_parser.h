#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <time.h>

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include <iostream> // cout
#include <sstream>
#include <fstream>
#include <iomanip> //setw
#include <random>


//using namespace cv;
using namespace std;

/* Weijie: 113*113 = 12634 + 135 */
#define WIDTH 113
#define HEIGHT 113

namespace imagenet
{
	std::string data_name() {return std::string("IMAGENET");}

	bool parse_test_data(std::string &data_path, std::vector<std::vector<float>> &test_records, std::vector<int> &test_labels, 
			float min_val=-1.f, float max_val=1.f, int x_padding=0, int y_padding=0)
	{
		// x_padding = 0;
		// y_padding = 0;
		ifstream label_val(data_path+"val.txt");

		vector<pair<string, int> > lines;
		string line;
		size_t pos;
		int label;

		/* Weijie: parse labels */
		while (getline(label_val, line)) 
		{
			pos = line.find_last_of(' ');
			label = atoi(line.substr(pos + 1).c_str());
			lines.push_back(make_pair(line.substr(0, pos), label));
		}
		//   random_shuffle(lines.begin(), lines.end());
		for (int line_id = 0; line_id < lines.size(); ++line_id) 
		{
			string filename = lines[line_id].first;
			int label = lines[line_id].second;

			string recordpath = data_path+"val/"+filename;

			/* Weijie: new parser core */
			std::ifstream infile_feat(recordpath); //加载数据文件
			std::string feature; //存储读取的每行数据
			float feat_onePoint;  //存储每行按空格分开的每一个float数据
			//std::vector<float> each_line; //存储每行数据
			std::vector<float> the_lines(WIDTH * HEIGHT); //store floats in all lines
			//clear all data in each file
			the_lines.clear();

			//while(!infile_feat.eof()) 
			//{
				/* get each line */
				getline(infile_feat, feature); //get one line every time, but now we only have one line
				stringstream stringin(feature); //使用串流实现对string的输入输出操作
				//line.clear();
				int fn = 0;
				while (stringin >> feat_onePoint) {      
					//按空格一次读取一个数据存入feat_onePoint 
					fn++;
					the_lines.push_back(feat_onePoint); //存储每行按空格分开的数据 
				}
				cout << "total float num: " << fn << endl;
				
				/* Weijie: padding 135 zeros */
				for (int pn = 0; pn < 135; pn++)
					the_lines.push_back(0.0);
			//}

			test_records.push_back(the_lines); //存储所有数据
			infile_feat.close();
			test_labels.push_back(label);
		}
		cout << "finished parsing testing dataset" << endl;
		label_val.close();
		return true;
	}

	bool parse_train_data(std::string &data_path, std::vector<std::vector<float>> &train_records, std::vector<int> &train_labels, 
			float min_val=-1.f, float max_val=1.f, int x_padding=0, int y_padding=0)
	{
		//   x_padding = 0;
		//   y_padding = 0;
		ifstream label_train(data_path+"/train.txt");

		vector<pair<string, int> > lines;
		string line;
		size_t pos;
		int label;
		while (getline(label_train, line)) 
		{
			pos = line.find_last_of(' ');
			label = atoi(line.substr(pos + 1).c_str());
			lines.push_back(make_pair(line.substr(0, pos), label));
		}

		random_shuffle(lines.begin(), lines.end());
		/* here each line means a row in label file, which is one sample */
		for (int line_id = 0; line_id < lines.size(); ++line_id) 
		{
			string filename = lines[line_id].first;
			int label = lines[line_id].second;

			//string imagepath = data_path+"/train/"+filename;
			string recordpath = data_path+"train/"+filename;
			/* Weijie: some output */
			cout << "loading: " << recordpath << endl;

			/* new parser core */
			std::ifstream infile_feat(recordpath); //加载数据文件
			std::string feature; //存储读取的每行数据
			float feat_onePoint;  //存储每行按空格分开的每一个float数据
			//std::vector<float> line; //存储每行数据
			std::vector<float> the_lines(WIDTH * HEIGHT); //store floats in all lines
			//clear all data in each file
			the_lines.clear();

			//while(!infile_feat.eof()) 
			//{	
				/* get each line */
				getline(infile_feat, feature); //actually, only read one line
				stringstream stringin(feature); //使用串流实现对string的输入输出操作
				//if (!stringin)	break;
				int fn = 0;
				while (stringin >> feat_onePoint) {      
					fn++;
					//按空格一次读取一个数据存入feat_onePoint 
					the_lines.push_back(feat_onePoint); //存储每行按空格分开的数据 
				}
				cout << "total float num: " << fn << endl;
                                /* Weijie: padding 135 zeros */
                                for (int pn = 0; pn < 135; pn++)
                                        the_lines.push_back(0.0);

			//}
			
			train_records.push_back(the_lines); //存储所有数据
			infile_feat.close();
			/* store labels */
			train_labels.push_back(label);
		}
		cout<<"finished parsing training dataset"<<endl;
		label_train.close();
		return true;
	}
}
