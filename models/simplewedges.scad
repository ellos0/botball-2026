include <BOSL2/std.scad>

handle_size = 58;

module proto1(size,indent_side_length,height_ratio,screw_width,screw_distance) {
  difference() {
    union() {
      disk_claw(size);
      handle1(size);
    }
    screw_holes2(size, screw_width,screw_distance);
  }
}

module proto2(size,indent_side_length,height_ratio,screw_width,screw_distance) {
  difference() {
    union() {
      rotate([0,0,180])
        disk_claw(size);
      handle2(size);
    }
    screw_holes1(size,screw_width,screw_distance);
  }
}

module handle1(size) {
  translate([0,-size.y*2/3,0])
    cuboid([handle_size,handle_size/3,10],anchor=BOTTOM);
}

module handle2(size) {
  translate([0,size.y*2/3,0])
    cuboid([handle_size,handle_size/5,30],anchor=BOTTOM);
}

module disk_claw(size) {
  difference() {
    cylinder(d=size.x+10,h=10,anchor=BOTTOM);
    down(0.5)
      cuboid([size.x,size.y,11],anchor=FRONT+BOTTOM);
    down(0.5)
    cylinder(d=size.x,h=11,anchor=BOTTOM);
  }
}

module screw_holes1(size,screw_width,screw_distance) {
  translate([24,size.y,18])
    for(i = [0:1:3]) {
      translate([screw_distance*i*-1,0,0])
      rotate([90,0,0])
        cylinder(r=screw_width/2,h=100,center=true);
    }
}

module screw_holes2(size,screw_width,screw_distance) {
  translate([24,-size.y*2/3,0])
    for(i = [0:1:3]) {
      translate([screw_distance*i*-1,0,0])
        cylinder(r=screw_width/2,h=size.y,center=true);
    }
}
