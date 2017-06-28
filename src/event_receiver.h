#include <irrlicht.h>
#include <IEventReceiver.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

IrrlichtDevice* plotdevice = 0;

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
      plotdevice->closeDevice();
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