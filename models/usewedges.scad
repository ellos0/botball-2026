include <BOSL2/std.scad>
include <wedge.scad>

cone_width = 56;

screw_spec = "#6";


xdistribute(spacing=1.2) {
	wedge_with_screw(45,cone_width,screw_spec);

	wedge_with_screw(45,cone_width,screw_spec);

	wedge_with_screw(20,cone_width,screw_spec);

	wedge_with_screw(20,cone_width,screw_spec);
}
