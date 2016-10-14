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

IrrlichtDevice* meshdevice = 0;

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
      meshdevice->closeDevice();
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

//' Irrlicht 3D meshplot
//'
//' @description
//' Creates a 3D meshplot using the Irrlicht engine.
//' 
//' @details
//' For test data see for example \url{https://github.com/inexor-game/data-playground/tree/master/model/map/modelpack2}.
//' 
//' @param pathmesh path to mesh (see supported formats here: \url{http://irrlicht.sourceforge.net/?page_id=45})
//' @param pathtexture path to texture (see supported formats here: \url{http://irrlicht.sourceforge.net/?page_id=45})
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
//' #irrmesh(
//' # "bspmesh.md2", 
//' # "bsptexture.bmp", 
//' # "a"
//' #)
//'
//' @export
// [[Rcpp::export]]
bool irrmesh(SEXP pathmesh, SEXP pathtexture, char driverselect){
  
  std::string pathmeshstr = Rcpp::as<std::string>(pathmesh); 
  std::string pathtexturestr = Rcpp::as<std::string>(pathtexture); 
  
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
  meshdevice = createDevice(
    driverType,
    core::dimension2d<u32>(1000,700)
  );
  
  // test if engine is running
  if (!meshdevice)
    return true;
  
  // initialize videodriver, scenemanager and guienvironment
  video::IVideoDriver* driver = meshdevice->getVideoDriver();
  scene::ISceneManager* scenemgr = meshdevice->getSceneManager();
  IGUIEnvironment* guienv = meshdevice->getGUIEnvironment();
  
  // set window title
  meshdevice->setWindowCaption(L"irrlicht - Plot");
  // make cursor invisible
  meshdevice->getCursorControl()->setVisible(false);
  
  // create event receiver for closing with escape
  meshdevice->setEventReceiver(new MyEventReceiver());
  
  // load and show test .md2 model
  scene::ISceneNode* node = scenemgr->
    addAnimatedMeshSceneNode(scenemgr->getMesh(pathmeshstr.c_str()));
  
  // if everything worked, add a texture and disable lighting
  if (node) {
    node->setMaterialTexture(0, driver->getTexture(pathtexturestr.c_str()));
    node->setMaterialFlag(video::EMF_LIGHTING, false);
  }
  
  // define font
  gui::IGUIFont* font = meshdevice->getGUIEnvironment()->getBuiltInFont();
  
  // add a first person shooter style user controlled camera
  ICameraSceneNode *camera = scenemgr->addCameraSceneNodeFPS();
  
  // draw everything (run-loop)
  while (meshdevice->run() && driver) {
    // set scene with background color
    driver->beginScene(true, true, video::SColor(255,255,255,255));
    // add fixed text
    if (font) {
      font->draw(L"This is a meshplot.",
                 core::rect<s32>(130,10,300,50),
                 video::SColor(255,0,0,0));
    }
    // draw nodes and gui
    scenemgr->drawAll();
    guienv->drawAll();
    // end scene
    driver->endScene();
  }
  
  // delete meshdevice
  meshdevice->drop();
  
  return true;
}