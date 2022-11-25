#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace cv;
using namespace std;

string getPixel(Mat_<Vec3b> image, int y, int x)
{
    stringstream ss;
    ss << image(y, x);
    string temp;
    string pixel = "";
    while (ss >> temp)
    {
        pixel += temp;
    }
    ss.clear();
    return pixel;
}

void writeToFile(unordered_map<string, int> umap, string path, const char *outpath)
{
    ofstream myfile;
    std::string file_name = path.substr(path.find_last_of("/") + 1);
    std::string::size_type const p(file_name.find_last_of('.'));
    std::string base_file_name = file_name.substr(0, p);

    string output_file = string(outpath) + "/" + base_file_name + ".txt";
    myfile.open(output_file);
    myfile << "Pixel\t\t\tCount\n";
    for (auto x : umap)
    {
        myfile << setw(20) << setfill(' ') << left << x.first;
        myfile << x.second << endl;
    }
    myfile.close();
}

void writeToFile(unordered_map<string, int> gmap, const char *outpath)
{
    ofstream myfile;
    string output_file = string(outpath) + "/" + "AggregateOutput.txt";
    myfile.open(output_file);
    myfile << "Pixel\t\t\tCount\n";
    for (auto x : gmap)
    {
        myfile << setw(20) << setfill(' ') << left << x.first;
        myfile << x.second << endl;
    }
    myfile.close();
}

int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: ./app input_folder output_folder" << std::endl;
        return -1;
    }

    vector<cv::String> filepath;
    string image_dir = string(argv[1]) + "/*.bmp";
    glob(image_dir, filepath, false);
    unordered_map<string, int> gmap;
    bool started = false;
    for (auto f : filepath)
    {
        Mat_<Vec3b> in_image = imread(f);

        if (!in_image.data)
        {
            std::cout << "Could not load input image!!!" << std::endl;
            return -1;
        }

        if (in_image.channels() != 3)
        {
            std::cout << "Image does not have 3 channels!!! " << in_image.depth() << std::endl;
            return -1;
        }

        int width = in_image.cols;
        int height = in_image.rows;

        string pixel;
        unordered_map<string, int> umap;
        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                pixel = getPixel(in_image, row, col);
                umap[pixel]++;
                gmap[pixel]++;
            }
        }
        if (!started)
        {
            cout << "Writing to files..." << endl;
            started = true;
        }
        writeToFile(umap, f, argv[2]);
    }
    writeToFile(gmap, argv[2]);
    cout << "FINISHED" << endl;
    return 0;
}
