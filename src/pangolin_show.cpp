#include <iostream>
#include <string>
#include <pangolin/pangolin.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace pangolin;
using namespace cv;

float ViewpointF = 500;
float ViewpointX = 0;
float ViewpointY = -0.7;
float ViewpointZ = -1.8;

int main(int argc, char **argv){
    if ( argc != 3 )
    {
        cerr<<" Usage: "<<argv[0]<<" image !"<<endl;
    }

    pangolin::CreateWindowAndBind("Plane_Slam: Map Viewer",1024,768);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::CreatePanel("menu").SetBounds(0.0,1.0,0.0,pangolin::Attach::Pix(175));

    pangolin::Var<bool> menu("menu.test", true, true);
    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024,768, ViewpointF, ViewpointF, 512,389,0.1,1000),
            pangolin::ModelViewLookAt(ViewpointX,ViewpointY,ViewpointZ, 0,0,0,0.0,-1.0, 0.0)
    );
    pangolin::View &d_cam = pangolin::CreateDisplay()
                                .SetBounds(0.0, 1.0, 0.2, 1.0, -1024.0f / 768.0f)
                                .SetHandler(new pangolin::Handler3D(s_cam));
    pangolin::OpenGlMatrix Twc;
    Twc.SetIdentity();

    pangolin::View &left_image = pangolin::Display("left")
                                    .SetBounds(0,0.2,0.2,0.4,1024.0f/768.0f)
                                    .SetLock(pangolin::LockLeft, pangolin::LockBottom);
    pangolin::View &right_image = pangolin::Display("right")
                                    .SetBounds(0,0.2,0.4,0.6,1024.0f/768.0f)
                                    .SetLock(pangolin::LockLeft, pangolin::LockBottom);
    pangolin::GlTexture imageTexture(640, 480, GL_RGB, false, 0, GL_BGR, GL_UNSIGNED_BYTE);
    int id = 1;
    while (true)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        // 画点云数据
        /*code*/
        
        string left_name = string(argv[1])+"/"+to_string(id)+".png";
        string right_name = string(argv[2])+"/"+to_string(id)+".png";
        // 画图像
        cv::Mat rgb = imread(left_name, -1);
        imageTexture.Upload(rgb.data, GL_BGR, GL_UNSIGNED_BYTE);
        left_image.Activate();
        glColor3f(1.0, 1.0, 1.0);
        imageTexture.RenderToViewportFlipXFlipY();

        rgb = imread(right_name, -1);
        imageTexture.Upload(rgb.data, GL_BGR, GL_UNSIGNED_BYTE);
        right_image.Activate();
        glColor3f(1.0, 1.0, 1.0);
        imageTexture.RenderToViewportFlipXFlipY();
        pangolin::FinishFrame();
        id++;   
        if (id > 5){
            id = 1;
        }
    }
    
    return 0;
}