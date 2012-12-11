#ifndef WAYPOINT_STRUCTURE_INCLUDED
#define WAYPOINT_STRUCTURE_INCLUDED
/**
 * Waypoint is just a simple data structure
 *  to hold the next pose for the robot.
 *
 * @author Josh Gillham
 * @version 12-9-12
 */
struct Waypoint {
  public:
    /** Holds the angle and coordinate. */
    double theta, x, y;
};
#endif // WAYPOINT_STRUCTURE_INCLUDED
