include <BOSL2/std.scad>

module wedge2(size,indent_side_length,height_ratio) {
  difference() {
    wedge(size);
    translate([size.x-(indent_side_length/2),size.y/1.5,size.z/5])
      cube([indent_side_length*2,indent_side_length,size.z],anchor=BOTTOM);
    translate([-1/16,-1/16,size.z*height_ratio])
      cube([size.x+1/8,size.y+1/8,size.z/2]);
  }
}
