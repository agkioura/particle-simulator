#include "../include/box.h"

Box::Box(float x, float y, float halfDimension) {
    this->center = (Vector2) {x, y};
    this->halfDimension = halfDimension;
}

bool Box::containsPoint(Vector2 point) {
    return
        point.x >= center.x - halfDimension &&
        point.x <= center.x + halfDimension &&
        point.y >= center.y - halfDimension &&
        point.y <= center.y + halfDimension;
}

bool Box::intersectsBox(Box other) {
    return 
        center.x + halfDimension >= other.center.x - other.halfDimension ||
        center.x - halfDimension <= other.center.x + other.halfDimension ||
        center.y + halfDimension >= other.center.y - other.halfDimension ||
        center.y - halfDimension <= other.center.y + other.halfDimension;
}
