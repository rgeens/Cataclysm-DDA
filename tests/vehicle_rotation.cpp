#include "avatar.h"
#include "catch/catch.hpp"
#include "game.h"
#include "map.h"
#include "map_helpers.h"
#include "point.h"
#include "tileray.h"
#include "type_id.h"
#include "vehicle.h"
#include "veh_type.h"
#include "vpart_range.h"

TEST_CASE( "rotate_vehicle" )
{
    clear_map();

    const tripoint test_origin( 60, 60, 0 );
    const tripoint vehicle_origin = test_origin;
    vehicle *v = g->m.add_vehicle( vproto_id( "apc" ), vehicle_origin, -90, 0, 0 );

    // TODO: Add extra appendages

    std::cout << "BEGIN VEHICLE" << std::endl;
    std::cout << "Pivot point: " << v->pivot_point() << std::endl;
    std::cout << "Pivot anchor[0]: " << v->pivot_anchor[0] << std::endl;
    std::cout << "Pivot anchor[1]: " << v->pivot_anchor[1] << std::endl;
    std::cout << "Pivot rotation[0]: " << v->pivot_rotation[0] << std::endl;
    std::cout << "Pivot rotation[1]: " << v->pivot_rotation[1] << std::endl;
    std::cout << "BEGIN FACE" << std::endl;
    std::cout << "Dir: " << v->face.dir() << std::endl;
    std::cout << "Mostly vert: " << v->face.mostly_vertical() << std::endl;
    std::cout << "END FACE" << std::endl;
    std::cout << "BEGIN MOVE" << std::endl;
    std::cout << "Dir: " << v->move.dir() << std::endl;
    std::cout << "Mostly vert: " << v->move.mostly_vertical() << std::endl;
    std::cout << "END MOVE" << std::endl;
    std::cout << "END VEHICLE" << std::endl;

    // TODO: Verify there are no holes in the exterior
    // 1. Get vehicle contour from mount points
    // 2. Iterate over contour and record which neighbors are solid
    // 3. After precalcing mount points, check if the neighbor relations still hold
    // 4. If not, duplicate the tile that is on the same X axis as the hole and is
    // closest to the outside of the vehicle on the Y axis.
    // 5. Ideally the duplicate behaves as a pointer / reference to the duplicate part. For
    // collision purposes, it should behave the same as the original. Simultaneously damaging
    // both parts should result in both damage amounts being added together. Removing the part
    // also removes the duplicate.
    for( const vpart_reference &vp: v->get_all_parts() ) {
        std::cout << "BEGIN PART" << std::endl;
        std::cout << vp.info().name() << std::endl;
        std::cout << vp.part().mount << std::endl;
        std::cout << vp.part().direction << std::endl;
        std::cout << vp.part().precalc[0] << std::endl;
        std::cout << vp.part().precalc[1] << std::endl;
        std::cout << "END PART" << std::endl;
    }

    const tileray ray;
    g->m.move_vehicle(*v, tripoint_zero, ray);

    // TODO: Verify there are holes in the rotated vehicle
}
