//less print time bcause im lazy

include <simplewedges.scad>

size = 56;

ydistribute(spacing=size*1.2) {
  wedge2([size,size,size],13,0.7);
}
