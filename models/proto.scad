//less print time bcause im lazy

include <simplewedges.scad>

$fn = 100;

size = [40,40,40]; //the size of the wedge in a vector3
screw_width = 4.0 + 0.6; //#6 screw width in millimeters + tolerance
screw_distance = 15.6; //distance between each screw hole

ydistribute(spacing=size.x*1.2) {
  proto1(size,screw_width,screw_distance);
  proto2(size,screw_width,screw_distance);
}
