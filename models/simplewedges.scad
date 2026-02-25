include <BOSL2/std.scad>

module proto1(size,indent_side_length,height_ratio,screw_width) {
  difference() {
    wedge2(size,indent_side_length,height_ratio);
    screw_holes1(size, screw_width);
  }
}

module proto2(size,indent_side_length,height_ratio,screw_width) {
  difference() {
    wedge2(size,indent_side_length,height_ratio);
    screw_holes2(size,screw_width);
  }
}

module wedge2(size,indent_side_length,height_ratio) {
  difference() {
    wedge(size);
    //trough
    translate([size.x/2,size.y/1.5,size.z/5])
      cube([size.x*1.01,indent_side_length,size.z],anchor=BOTTOM);
    //cutoff
    translate([-1/16,-1/16,size.z*height_ratio])
      cube([size.x+1/8,size.y+1/8,size.z/2]);
  }
}

module screw_holes1(size,screw_width) {
  translate([size.x-screw_width,10,18])
    for(i = [0:1:3]) {
      translate([screw_width*4*i*-1,0,0])
      rotate([90,0,0])
        cylinder(r=screw_width/2,h=size.y,center=true);
    }
}

module screw_holes2(size,screw_width) {
  translate([size.x-screw_width,37,0])
    for(i = [0:1:3]) {
      translate([screw_width*4*i*-1,0,0])
        cylinder(r=screw_width/2,h=size.y,center=true);
    }
}
