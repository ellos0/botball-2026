//less print time bcause im lazy

include <simplewedges.scad>

$fn = 100;

size = [57,57,57]; //the size of the wedge in a vector3
trough_width = 13; //width of the rectangular cutoff in the middle of the wedge
height_ratio = 0.7; //percentage of the wedge height which will be cut off the top
screw_width = 4.0 + 0.6; //#6 screw width in millimeters + tolerance
screw_distance = 15.6;

ydistribute(spacing=size.x*1.2) {
  proto1(size,trough_width,height_ratio,screw_width,screw_distance);
  proto2(size,trough_width,height_ratio,screw_width,screw_distance);
}
