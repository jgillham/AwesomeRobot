#ifndef MAP_CLASS_INCLUDED
#define MAP_CLASS_INCLUDED
#include <vector>
class MapObject {
  public:

};
/**
 * Contains map objects and provides extra functinality
 *  such as drawing.
 */
class GameMap : public std::vector< MapObject > {
  public:
    /**
     * Draws all objects in the game map.
     */
    void draw();
};

#endif // MAP_CLASS_INCLUDED

