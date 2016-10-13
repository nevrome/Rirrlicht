#include <Rcpp.h>
#include <cstdlib>
#include <iostream>
#include <irrlicht.h>
#include <IEventReceiver.h>

using namespace Rcpp;
using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

IrrlichtDevice* device = 0;

// event receiver class
class MyEventReceiver : public IEventReceiver {
  public:
    virtual bool OnEvent(const SEvent& event) {
      // Remember whether each key is down or up
      if (event.EventType == EET_KEY_INPUT_EVENT){
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
      } 
      // closing event
      if (event.EventType == EET_KEY_INPUT_EVENT && event.KeyInput.Key == KEY_ESCAPE && event.KeyInput.PressedDown){
        device->closeDevice();
      }
      return false;
    }
    
    // This is used to check whether a key is being held down
    virtual bool IsKeyDown(EKEY_CODE keyCode) const {
      return KeyIsDown[keyCode];
    }
    
    MyEventReceiver() {
      for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
        KeyIsDown[i] = false;
    }
    
  private:
    // We use this array to store the current state of each key
    bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

//' test
//'
//' @description
//' test
//'
//' @param driverselect
//'
//' @return test
//'
//' @examples
//' 1+1
//'
//' @export
// [[Rcpp::export]]
DataFrame testirr1(char driverselect){

  // driver selection
  E_DRIVER_TYPE driverType;
  
  switch(driverselect){
    case 'a': driverType = video::EDT_OPENGL;   break;
    case 'b': driverType = video::EDT_DIRECT3D9;break;
    case 'c': driverType = video::EDT_DIRECT3D8;break;
    case 'd': driverType = video::EDT_BURNINGSVIDEO;break;
    case 'e': driverType = video::EDT_SOFTWARE; break;
    case 'f': driverType = video::EDT_NULL;     break;
    default: return 1;
  }
  
  // start up the engine   
  device = createDevice(
    driverType,
    core::dimension2d<u32>(1000,700)
  );
  
  if (!device)
    return 1;
  
  video::IVideoDriver* driver = device->getVideoDriver();
  scene::ISceneManager* scenemgr = device->getSceneManager();
  IGUIEnvironment* guienv = device->getGUIEnvironment();
  
  // set window title
  device->setWindowCaption(L"irrlicht - Plot");
  // make cursor invisible
  device->getCursorControl()->setVisible(false);
  
  // create event receiver
  device->setEventReceiver(new MyEventReceiver());
  
  // load and show test .md2 model
  scene::ISceneNode* node = scenemgr->
    addAnimatedMeshSceneNode(scenemgr->getMesh("data-raw/farao.md2"));
  
  // if everything worked, add a texture and disable lighting
  if (node) {
     node->setMaterialTexture(0, driver->getTexture("data-raw/farao.bmp"));
     node->setMaterialFlag(video::EMF_LIGHTING, false);
  }

  // add cube and sphere
  scenemgr->
    addSphereSceneNode(50.0f, 16, 0, -1, core::vector3df(200,100,10));
  
  scenemgr->
    addSphereSceneNode(50.0f, 16, 0, -1, core::vector3df(100,30,100));
  
  for (int i=0; i<=10; i++) {
    scenemgr->
      addSphereSceneNode(50.0f, 16, 0, -1, core::vector3df(i*100,i*30,100));
  }
  
  // add a first person shooter style user controlled camera
  ICameraSceneNode *camera = scenemgr->addCameraSceneNodeFPS();
  camera->setTarget(node->getAbsolutePosition());
  
  // draw everything
  while(device->run() && driver)
  {
    driver->beginScene(true, true, video::SColor(255,255,255,255));
    scenemgr->drawAll();
    guienv->drawAll();
    driver->endScene();
  }
  
  // delete device
  device->drop();
  
  return 0;
}