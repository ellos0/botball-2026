include <BOSL2/std.scad>

module wedge2(size,indent_side_length) {
  difference() {
    wedge(size);
    translate([size.x/1.2,size.y/3,size.z/4])
    cube([indent_side_length,indent_side_length,size.x/20],center=true);
  }
}
