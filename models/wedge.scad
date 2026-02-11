include <BOSL2/std.scad>
include <BOSL2/screws.scad>

module wedge_with_screw(angle,size,screw_spec) {
  difference() {
    wedge([size,size,size],center=true);
    translate([size/2,0,size/2])
    wedge_screw(screw_spec,size);
  }
}

module wedge_screw(screw_spec,length) {
  screw_hole(screw_spec,anchor=TOP,thread=true,length=length);
}
