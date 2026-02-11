include <simplewedges.scad>

size = 56;

ydistribute(spacing=size*1.2) {
  wedge2([size,size,size],size/2);
  wedge2([size,size,size],size/2);
  wedge2([size,size,size/2],size/2);
  wedge2([size,size,size/2],size/2);
}
