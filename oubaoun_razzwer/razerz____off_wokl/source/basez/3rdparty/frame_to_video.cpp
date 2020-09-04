/*

void saveFramebuffer()
modfied from  https://github.com/yzhong52/OpenGLFramebufferAsVideo
 *		This Code Was Created By Jeff Molofee 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing The Base Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 */

#include "frame_to_video.hpp"

  int         multiframe_capturer::fid= 0;
  GLFWwindow* multiframe_capturer::curr_window = nullptr;
  int         multiframe_capturer::total_frame=0;
  std::string multiframe_capturer::file_name="\0";

   void multiframe_capturer::set_paramz(GLFWwindow* in_window,int f_length, std::string in_file_name)
  {
   curr_window  =in_window;
   total_frame =f_length;
   file_name =in_file_name;
  }

   void multiframe_capturer::export_framebuff_avi(bool* out_compleate)
  {
    bool cv_pass = false;

  if( fid==0 ) {

    glfwGetFramebufferSize(curr_window,&width,&height);
    std::string file_to_write= file_name+".avi";


    cv_pass = outputVideo.open(file_to_write.c_str(),
    cv::VideoWriter::fourcc('P','I','M','1'),                         /* fourcc */
  	24.0f,
    cv::Size( width, height),
    true);
    if(cv_pass ==false)
    {
      std::cerr <<"cv_fialed to open";
      exit(-2);
    }

    std::cout <<"insize fid =0;\n";
  //  exit(-1);
  }
  else if (fid<total_frame)
  {
    std::cout <<"insize fid;"<< fid << '\n';
    cv::Mat pixels( /* num of rows */ height, /* num of cols */ width, CV_8UC3);
		glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data );
		cv::Mat cv_pixels( /* num of rows */ height, /* num of cols */ width, CV_8UC3 );

    for( int y=0; y<height; y++ ) for( int x=0; x<width; x++ )
		{
			cv_pixels.at<cv::Vec3b>(y,x)[2] = pixels.at<cv::Vec3b>(height-y-1,x)[0];
			cv_pixels.at<cv::Vec3b>(y,x)[1] = pixels.at<cv::Vec3b>(height-y-1,x)[1];
			cv_pixels.at<cv::Vec3b>(y,x)[0] = pixels.at<cv::Vec3b>(height-y-1,x)[2];
		}
		outputVideo << cv_pixels;
  }
  else if(fid == total_frame)
  {
    std::cout <<"videofine\n";
    *out_compleate = true;
    outputVideo.release();
    //exit(1);
  }
  std::cout << "frame cout::ontake::" <<fid <<'\n';
fid++;
}
