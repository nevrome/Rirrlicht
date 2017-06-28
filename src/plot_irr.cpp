#include <Rcpp.h>
#include <cstdlib>
#include "event_receiver.h"

using namespace Rcpp;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//' Irrlicht 3D scatterplot
//' @description
//' Creates a 3D scatterplot using the Irrlicht engine.
//' 
//' @param x vector with x-axis coordinates
//' @param y vector with y-axis coordinates
//' @param z vector with z-axis coordinates
//' @param size vector with size values
//' @param driverselect
//'   "a": OPENGL,
//'   "b": DIRECT3D9
//'   "c": DIRECT3D8
//'   "d": BURNINGSVIDEO
//'   "e": SOFTWARE
//'   "f": NULL
//'
//' @return boolean value - side effect irrlicht window is relevant
//'
//' @examples
//' #plot_irr(
//' #  x = rnorm(500)*200, 
//' #  y = rnorm(500)*200, 
//' #  z = rnorm(500)*200, 
//' #  size = rnorm(500)*10, 
//' #  driverselect = "a"
//' #)
//'
//' @export
// [[Rcpp::export]]
bool plot_irr(NumericVector x, NumericVector y, NumericVector z, NumericVector size, char driverselect){
  
  // driver selection
  E_DRIVER_TYPE driverType;
  
  switch (driverselect) {
  case 'a': driverType = video::EDT_OPENGL;       break;
  case 'b': driverType = video::EDT_DIRECT3D9;    break;
  case 'c': driverType = video::EDT_DIRECT3D8;    break;
  case 'd': driverType = video::EDT_BURNINGSVIDEO;break;
  case 'e': driverType = video::EDT_SOFTWARE;     break;
  case 'f': driverType = video::EDT_NULL;         break;
  default: return 1;
  }
  
  // start up the engine   
  plotdevice = createDevice(
    driverType,
    core::dimension2d<u32>(1000,700)
  );
  
  // test if engine is running
  if (!plotdevice)
    return true;
  
  // initialize videodriver, scenemanager and guienvironment
  video::IVideoDriver* driver = plotdevice->getVideoDriver();
  scene::ISceneManager* scenemgr = plotdevice->getSceneManager();
  IGUIEnvironment* guienv = plotdevice->getGUIEnvironment();
  
  // set window title
  plotdevice->setWindowCaption(L"irrlicht - Plot");
  // make cursor invisible
  plotdevice->getCursorControl()->setVisible(false);
  
  // create event receiver for closing with escape
  plotdevice->setEventReceiver(new MyEventReceiver());
  
  // // load and show test .md2 model
  // scene::ISceneNode* node = scenemgr->
  //   addAnimatedMeshSceneNode(scenemgr->getMesh(pathmeshstr.c_str()));
  // 
  // // if everything worked, add a texture and disable lighting
  // if (node) {
  //   node->setMaterialTexture(0, driver->getTexture(pathtexturestr.c_str()));
  //   node->setMaterialFlag(video::EMF_LIGHTING, false);
  // }
  
  // create first scenenode from first point
  scene::ISceneNode* node = scenemgr->
    addSphereSceneNode(size(0), 16, 0, -1, core::vector3df(x(0),y(0),z(0)));
  
  // add scenenodes for every following point
  for (int i=1; i<x.size(); i++) {
    scenemgr->
      addSphereSceneNode(size(i), 16, 0, -1, core::vector3df(x(i),y(i),z(i)));
  }

  // define font
  gui::IGUIFont* font = plotdevice->getGUIEnvironment()->getBuiltInFont();
    
  // coordinate system text
  // scene::IBillboardTextSceneNode* bill = 0;
  // bill = scenemgr->addBillboardTextSceneNode(
  //   font, L"0|0|0",
  //   node, dimension2d<f32>(200, 50),
  //   vector3df(100,100,100)
  // );
  //bill->setTextColor(video::SColor(255,0,0,0));
  
  // add a first person shooter style user controlled camera
  ICameraSceneNode *camera = scenemgr->addCameraSceneNodeFPS();

  // draw everything (run-loop)
  while (plotdevice->run() && driver) {
    // set scene with background color
    driver->beginScene(true, true, video::SColor(255,255,255,255));
    // add fixed text
    if (font) {
      font->draw(L"This is a scatterplot.",
                 core::rect<s32>(130,10,300,50),
                 video::SColor(255,0,0,0));
    }
    // draw coordinate system axis
    driver->draw3DLine(vector3df(-1000, 0, 0), vector3df(1000, 0, 0));
    driver->draw3DLine(vector3df(0, -1000, 0), vector3df(0, 1000, 0));
    driver->draw3DLine(vector3df(0, 0, -1000), vector3df(0, 0, 1000));
    // draw nodes and gui
    scenemgr->drawAll();
    guienv->drawAll();
    // end scene
    driver->endScene();
  }
  
  // delete plotdevice
  plotdevice->drop();
  
  return true;
}