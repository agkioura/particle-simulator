#include "../include/qtree.h"

QuadTree::QuadTree(Box boundary) {
    this->boundary = boundary;
    this->nw = nullptr;
    this->ne = nullptr;
    this->sw = nullptr;
    this->se = nullptr;
    isDivided = false;
}

QuadTree::QuadTree() {
    this->boundary = (Box) {WIDTH / 2, HEIGHT / 2, WIDTH / 2};
    this->nw = nullptr;
    this->ne = nullptr;
    this->sw = nullptr;
    this->se = nullptr;
    isDivided = false;
}

bool QuadTree::insert(Particle p) {
    if (!boundary.containsPoint(p.currentPos)) 
        return false;

    if ((const int) particleList.size() < capacity && !isDivided){
        particleList.push_back(p);
        return true;
    }
    
    if (!isDivided) {
        subdivide();
        isDivided = true;
    }
    
    if (nw->insert(p)) return true;
    if (ne->insert(p)) return true;
    if (sw->insert(p)) return true;
    if (se->insert(p)) return true;

    return false;
}

void QuadTree::subdivide() {
    float x = this->boundary.center.x;
    float y = this->boundary.center.y;
    float hd = this->boundary.halfDimension;

    Box nw = Box(x - hd / 2, y - hd / 2, hd / 2);
    this->nw = new QuadTree(nw);
    Box ne = Box(x + hd / 2, y - hd / 2, hd / 2);
    this->ne = new QuadTree(ne);
    Box sw = Box(x - hd / 2, y + hd / 2, hd / 2);
    this->sw = new QuadTree(sw);
    Box se = Box(x + hd / 2, y + hd / 2, hd / 2);
    this->se = new QuadTree(se);
}

std::vector<Particle> QuadTree::queryRange(Box range) {
    std::vector<Particle> particlesInRange;
     
    if (!boundary.intersectsBox(range))
        return particlesInRange;
    
    for (auto &p : particleList) {
        if (range.containsPoint(p.currentPos))
            particlesInRange.push_back(p);
    }

    if (nw == nullptr)
        return particlesInRange;
    
    std::vector<Particle> newPoints;

    newPoints = nw->queryRange(range);
    particlesInRange.insert(particlesInRange.end(), newPoints.begin(), newPoints.end());
    newPoints = ne->queryRange(range);
    particlesInRange.insert(particlesInRange.end(), newPoints.begin(), newPoints.end());
    newPoints = sw->queryRange(range);
    particlesInRange.insert(particlesInRange.end(), newPoints.begin(), newPoints.end());
    newPoints = se->queryRange(range);
    particlesInRange.insert(particlesInRange.end(), newPoints.begin(), newPoints.end());
     
    return particlesInRange;
}


void QuadTree::show() {
    DrawRectangleLinesEx(
        (Rectangle)
        {this->boundary.center.x - this->boundary.halfDimension, 
        this->boundary.center.y - this->boundary.halfDimension, 
        this->boundary.halfDimension * 2,
        this->boundary.halfDimension * 2}, 1, WHITE
    );
    if (isDivided) {
        this->nw->show();
        this->ne->show();
        this->sw->show();
        this->se->show();
    }
}