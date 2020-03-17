/*
void saveFramebuffer()
modfied from  https://github.com/yzhong52/OpenGLFramebufferAsVideo
 *		This Code Was Created By Jeff Molofee 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing The Base Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 */

/*
TO USE, setup callback fucntions->
bool take_frame_video = false;
void (*vid_cap_callback)(GLFWwindow*,int,std::string);

in main or wehever caputre goes::->
multiframe_capturer mf_c;
vid_cap_callback = &multiframe_capturer::set_paramz;

call capture_frame_buff_avi(the window, vid_cap_callback);
*/

#pragma once

#include <opencv2/core.hpp>     // Basic OpenCV structures (cv::Mat, Scalar)
#include <opencv2/imgproc.hpp>  // Gaussian Blur
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>  // OpenCV window I/O
#include <opencv2/video.hpp>
#include <opencv2/imgcodecs.hpp>
#pragma comment(lib, "opencv_core243.lib")
#pragma comment(lib, "opencv_highgui243.lib")

#include "../gl_lib_z.hpp"

typedef struct _RECTw {
  long left;
  long top;
  long right;
  long bottom;
} rectw, *ptr_rectw;

struct multiframe_capturer
{
  static int fid;
   cv::VideoWriter outputVideo;
   int height, width;
static  GLFWwindow* curr_window;
static  int  total_frame;
static  std::string file_name;

  static void set_paramz(GLFWwindow* in_window,int f_length, std::string in_file_name);
  void export_framebuff_avi(bool* out_compleate);

};
