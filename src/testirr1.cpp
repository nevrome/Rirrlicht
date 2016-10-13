#include <Rcpp.h>
#include <cstdlib>
#include <iostream>
#include <irrlicht.h>

using namespace Rcpp;
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//' test
//'
//' @description
//' test
//'
//' @param test
//'
//' @return test
//'
//' @examples
//' 1+1
//'
//' @export
// [[Rcpp::export]]
DataFrame testirr1(){

  // start up the engine   
  IrrlichtDevice *device = createDevice(video::EDT_OPENGL,
                                        core::dimension2d<u32>(1000,700));
  
  video::IVideoDriver* driver = device->getVideoDriver();
  scene::ISceneManager* scenemgr = device->getSceneManager();
  
  device->setWindowCaption(L"Hello World!");
  
  // load and show test .md2 model
  scene::ISceneNode* node = scenemgr->addAnimatedMeshSceneNode(
    scenemgr->getMesh("data-raw/farao.md2"));
  
  // if everything worked, add a texture and disable lighting
  if (node)
  {
    node->setMaterialTexture(0, driver->getTexture("data-raw/farao.bmp"));
    node->setMaterialFlag(video::EMF_LIGHTING, false);
  }
  
  // add a first person shooter style user controlled camera
  scenemgr->addCameraSceneNodeFPS();
  
  // draw everything
  while(device->run() && driver)
  {
    driver->beginScene(true, true, video::SColor(255,0,0,255));
    scenemgr->drawAll();
    driver->endScene();
  }
  
  // delete device
  device->drop();
  return 0;
}