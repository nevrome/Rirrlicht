#include <Rcpp.h>
#include <cstdlib>
#include <unistd.h>
#include "event_receiver.h"
#include "geom_vector_calc.h"

using namespace Rcpp;
using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

//' Irrlicht 3D plot
//' @description
//' Creates a 3D plot using the Irrlicht engine.
//' 
//' @param points_df optional - data.frame with coordinates and attributes 
//' of scattered points 
//' @param raster_paths_cv troooeeeet
//' @param raster_corners_list huuuup
//' @param mesh_cv floet
//' @param doomhud fluet
//' @param video_driver
//' \itemize{
//'   \item{"a": }{OPENGL (default)} 
//'   \item{"b": }{DIRECT3D9}
//'   \item{"c": }{DIRECT3D8}
//'   \item{"d": }{BURNINGSVIDEO}
//'   \item{"e": }{SOFTWARE}
//'   \item{"f": }{NULL}
//' }
//'
//' @return boolean value - side effect; irrlicht window is relevant
//'
//' @examples
//' \dontrun{
//' plot_irr(
//'   points = data.frame(
//'     x = rnorm(500)*200, 
//'     y = rnorm(500)*200, 
//'     z = rnorm(500)*200,
//'     size = rnorm(500)*10 
//'   ),
//'   raster_paths_cv = c("data-raw/berries.png")
//' )
//' }
//'
//' @export
// [[Rcpp::export]]
bool plot_irr(
  Nullable<DataFrame> points_df = R_NilValue,
  Nullable<CharacterVector> raster_paths_cv = R_NilValue,
  Nullable<DataFrame> raster_corners_list = R_NilValue,
  Nullable<CharacterVector> mesh_cv = R_NilValue,
  bool doomhud = false, 
  char video_driver = 'a'
){
  
  // driver selection
  E_DRIVER_TYPE driverType;
  switch (video_driver) {
    case 'a': driverType = video::EDT_OPENGL;        break;
    case 'b': driverType = video::EDT_DIRECT3D9;     break;
    case 'c': driverType = video::EDT_DIRECT3D8;     break;
    case 'd': driverType = video::EDT_BURNINGSVIDEO; break;
    case 'e': driverType = video::EDT_SOFTWARE;      break;
    case 'f': driverType = video::EDT_NULL;          break;
    default: return 1;
  }
  
  // start up the engine   
  plotdevice = createDevice(
    driverType,
    core::dimension2d<u32>(1000,700)
  );
  
  // test if engine is running
  if (!plotdevice) {return true;}
  
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

  
  // add stuff to scene
    
  // add points 
  if (points_df.isNotNull()) {
 
    DataFrame points = as<DataFrame>(points_df);
    
    // coordinates
    NumericVector x = points["x"];
    NumericVector y = points["y"];
    NumericVector z = points["z"];
    
    // check for other variables
    CharacterVector points_attributes = points.attr("names");
    
    // define default point size
    NumericVector size = rep(NumericVector::create(1), points.nrow());
    
    for (auto pas : points_attributes) {
      // set point size from input
      if (pas == "size") {
        size = points["size"];
      }
    }
 
    // create first scenenode from first point
    scene::ISceneNode* node = 
      scenemgr->addSphereSceneNode(size(0), 16, 0, -1, core::vector3df(x(0),y(0),z(0)));
    
    // add scenenodes for every following point
    for (int i=1; i<x.size(); i++) {
      scenemgr->
        addSphereSceneNode(size(i), 16, 0, -1, core::vector3df(x(i),y(i),z(i)));
    }
  }
  
  // add lines
  
  // TODO?
  
  // add rasters
  if (raster_paths_cv.isNotNull() && raster_corners_list.isNotNull()) {

    //TODO: check, if length if path cv and corners_list is identical
    
    // transform input to not nullable
    CharacterVector raster_paths_cv_not_nullable = as<CharacterVector>(raster_paths_cv);
    List raster_corners_list_not_nullable = as<List>(raster_corners_list);
    
    // loop to deal with every picture
    for(int i = 0; i<2; i++) {
      
      // extract DataFrames with corner positions from List
      SEXP rcdf_sexp = raster_corners_list_not_nullable[i];
      DataFrame rcdf = as<DataFrame>(rcdf_sexp);
      
      // calc position and normal vector
      vector3df position = position_calc(rcdf);
      vector3df normal = normal_calc(rcdf);
      
      // prepare raster image
      std::string blubb = as<std::string>(raster_paths_cv_not_nullable[i]);
      core::string<fschar_t> blubb2 = blubb.c_str();
      
      // add raster to scene
      scene::ISceneNode * picturenode = scenemgr->addCubeSceneNode();
      
      if (picturenode) {
        // position: mean of coordinates
        picturenode->setPosition(position);
        
        double a;
        if(i == 0){a = 0;}else{a = 90;}
        double b; 
        if(i == 0){b = 0;}else{b = 45;}
        double c; 
        if(i == 0){c = 0;}else{c = 90;}
        
        //rotation
        picturenode->setRotation(core::vector3df(
          a,b,c
          // normal(0),
          // normal(1),
          // normal(2)
        ));
        //scale
        picturenode->setScale(core::vector3df(
          10, 0.1, 10
        ));
        // texture
        picturenode->setMaterialTexture(0, driver->getTexture(
          blubb2
        ));
        // light (off)
        picturenode->setMaterialFlag(video::EMF_LIGHTING, false);
      }
    }
  }
  
  // add meshes
  if (mesh_cv.isNotNull()) {
    
    //convert from Nullable to CharacterVector
    CharacterVector mesh_cv_not_nullable = as<CharacterVector>(mesh_cv);
    
    // loop through all strings
    for (auto mesh_string_pointer : mesh_cv_not_nullable) {

      //write string to temporary file
      std::string mesh_string = Rcpp::as<std::string>(mesh_string_pointer);
      const void * a = mesh_string.c_str();
      char filename[] = "/tmp/mytemp.XXXXXX.ply";
      int fd = mkstemps(filename, 4); 
      if (fd == -1) return 1;
      if (write(fd, a, mesh_string.length()) == -1) {
        Rcout << "Error in the creation of a temporary file.\n";
      } 
      
      //load mesh from file and add it to the scene
      scene::ISceneNode* node =
        scenemgr->addAnimatedMeshSceneNode(scenemgr->getMesh(filename));
  
      // close file connection and remove temporary file 
      close(fd);
      unlink(filename); 
      
      // if everything worked, add a texture and disable lighting
      // if (node) {
      //   node->setMaterialTexture(0, driver->getTexture(pathtexturestr.c_str()));
      //   node->setMaterialFlag(video::EMF_LIGHTING, false);
      // }
    }
  }
  
  // add doomhud  
  if (doomhud) {
    float width = driver->getViewPort().getWidth();
    float height = driver->getViewPort().getHeight();
    
    ITexture* tex = driver->getTexture("data-raw/doomhud.png");
    
    IGUIImage* img;
    
    img = guienv->addImage(core::rect<s32>(0, 400, width, height));
    img->setImage(tex);
    img->setScaleImage(true);
    driver->removeTexture(tex);
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
  // Key map added to allow multiple keys for actions such as
  // movement. ie Arrow keys & W,S,A,D.
  SKeyMap keyMap[8];
  keyMap[0].Action = EKA_MOVE_FORWARD;
  keyMap[0].KeyCode = KEY_UP;
  keyMap[1].Action = EKA_MOVE_FORWARD;
  keyMap[1].KeyCode = KEY_KEY_W;
  
  keyMap[2].Action = EKA_MOVE_BACKWARD;
  keyMap[2].KeyCode = KEY_DOWN;
  keyMap[3].Action = EKA_MOVE_BACKWARD;
  keyMap[3].KeyCode = KEY_KEY_S;
  
  keyMap[4].Action = EKA_STRAFE_LEFT;
  keyMap[4].KeyCode = KEY_LEFT;
  keyMap[5].Action = EKA_STRAFE_LEFT;
  keyMap[5].KeyCode = KEY_KEY_A;
  
  keyMap[6].Action = EKA_STRAFE_RIGHT;
  keyMap[6].KeyCode = KEY_RIGHT;
  keyMap[7].Action = EKA_STRAFE_RIGHT;
  keyMap[7].KeyCode = KEY_KEY_D;
  
  ICameraSceneNode *camera = scenemgr->addCameraSceneNodeFPS(
    0, 100.0f, 0.5f, -1, keyMap, 8
  );

  // global light
  //scenemgr->setAmbientLight(video::SColorf(0.3,0.3,0.3,1));
  
  // draw everything (run-loop)
  while (plotdevice->run() && driver) {
    // set scene with background color
    driver->beginScene(true, true, video::SColor(255,255,255,255));
    // add fixed text
    if (font) {
      font->draw(L"This is a plot.",
                 core::rect<s32>(130,10,300,50),
                 video::SColor(255,0,0,0));
    }
    // draw coordinate system axis
    // driver->draw3DLine(vector3df(-1000, 0, 0), vector3df(1000, 0, 0));
    // driver->draw3DLine(vector3df(0, -1000, 0), vector3df(0, 1000, 0));
    // driver->draw3DLine(vector3df(0, 0, -1000), vector3df(0, 0, 1000));
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