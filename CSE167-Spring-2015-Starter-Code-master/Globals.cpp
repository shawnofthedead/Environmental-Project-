#include "Globals.h"

Camera* Globals::camera = new Camera();
Skybox* Globals::skybox = new Skybox(500.0);
Cylinder* Globals::cylinder = new Cylinder(0, 1, 10000, 2);
Group Globals::root = Group();
Robot* Globals::robot = new Robot();
Terrain* Globals::terrain = new Terrain();
Sphere* Globals::sphere = new Sphere(10.0, 30.0, 30.0);



Light* Globals::light = new Light();

DrawData Globals::drawData = DrawData();
UpdateData Globals::updateData = UpdateData();

int Globals::view = 0;


Rasterizer Globals::rasterizer = Rasterizer();
Drawable* Globals::object[7];
