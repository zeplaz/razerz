
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgcodecs.hpp>
#include <iostream>
#include <string>
#include <vector>

enum  Error_Code{
  IMAGE_FILE_INVAILD = -2
};
const std::string cl_vaild_cmdz {"help | | stuff... use dload"};

int main(int argc, char *argv[])
{

 //cv::CommandLineParser cv_cmd_parser( argc, argv, cl_vaild_cmdz);
//   cv_cmd_parser.about("");
  //    if (cv_cmd_parser.has("help")){
  //        cv_cmd_parser.printMessage();
  //        return 0;
  //      }

cv::Mat source_image;

std::string cmd_in = argv[1];//cv_cmd_parser.get<std::string>(0);
if(cmd_in == "dload")
{
  std::cout <<"loading defultfilename defafult.png " <<'\n';
  cmd_in = "default.png";
}

source_image = cv::imread(cmd_in,cv::IMREAD_COLOR);
if(source_image.empty())
{
  std::cerr << "\n####ERROR FILE not loaded proeprly" <<'\n';
  return IMAGE_FILE_INVAILD;
}

cv::Mat grayscale_img;

cv::cvtColor(source_image,grayscale_img,cv::COLOR_BGR2GRAY);

int scan_threshold = 100;

cv::Mat binaryz_img = scan_threshold < 128?(grayscale_img<scan_threshold) :(grayscale_img>scan_threshold);
cv::Mat labeled_image;
cv::Mat stats,centroids;

int numlabelz = cv::connectedComponentsWithStats(binaryz_img, labeled_image, stats, centroids, 8, CV_32S);


std::vector<cv::Vec3b> sector_colourz(numlabelz);
sector_colourz[0]= cv::Vec3b(0,0,0);

std::cout << "num_sectorz__detected::" << numlabelz << '\n' << '\n';


for(int label =1; label<numlabelz;label++)

{
  sector_colourz[label] = cv::Vec3b((std::rand()&255),(std::rand()&255),0);
  std::cout << "sector::" << label << '\n';
  std::cout << "CC_STAT_LEFT   = " << stats.at<int>(label,cv::CC_STAT_LEFT) << std::endl;
  std::cout << "CC_STAT_TOP    = " << stats.at<int>(label,cv::CC_STAT_TOP) << std::endl;
  std::cout << "CC_STAT_WIDTH  = " << stats.at<int>(label,cv::CC_STAT_WIDTH) << std::endl;
  std::cout << "CC_STAT_HEIGHT = " << stats.at<int>(label,cv::CC_STAT_HEIGHT) << std::endl;
  std::cout << "CC_STAT_AREA   = " << stats.at<int>(label,cv::CC_STAT_AREA) << std::endl;
  std::cout << "centroids      = (" << centroids.at<double>(label, 0) <<","<< centroids.at<double>(label, 1) << ")"<< std::endl << std::endl;
}

cv::Mat out_maped_image(grayscale_img.size(),CV_8UC3);

for (int row =0; row<out_maped_image.rows; ++row)
{
  for(int colum = 0; colum < out_maped_image.cols; ++colum)
  {
    int current_label = labeled_image.at<int>(row,colum);
    cv::Vec3b &pixel = out_maped_image.at<cv::Vec3b>(row,colum);
    pixel = sector_colourz[current_label];
  }
}


    cv::imshow( "Source", source_image );
    cv::imshow( "Connected Components", out_maped_image );

    bool result = false;
    try
    {
        result = imwrite("out_image_sectorz.png", out_maped_image);
    }
    catch (const cv::Exception& ex)
    {
        fprintf(stderr, "Exception converting image to PNG format: %s\n", ex.what());
    }
    if (result)
        printf("Saved PNG file with secorz data.\n");
    else
        printf("ERROR: Can't save PNG file.\n");
    cv::waitKey(0);

return 0;
};
