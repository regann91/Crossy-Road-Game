//
//// Destructor
//River::~River() {
//    for (const auto& obj : movingObjects) {
//        delete& obj;
//    }
//}
//
//// Constructor implementation
//River::River(int roadY) : Way(roadY) {}
//
//
//// draw implementation
//void River::draw() const {
//    // Custom drawing for the road (gray rectangle)
//    glColor3f(0.5, 0.5, 0.5);  // Set color to gray
//    glBegin(GL_QUADS);
//    glVertex2f(x, y);
//    glVertex2f(x + width, y);
//    glVertex2f(x + width, y + height);
//    glVertex2f(x, y + height);
//    glEnd();
//
//    // Draw the dotted line down the middle
//    glColor3f(1.0, 1.0, 1.0);  // Set color to white for the line
//    glLineStipple(1, 0xAAAA);  // Set line stipple pattern for dots
//    glEnable(GL_LINE_STIPPLE);  // Enable line stipple
//    glBegin(GL_LINES);
//    // Draw the dotted line in the middle of the road
//    float middleY = y + height / 2.0;
//    glVertex2f(x, middleY);
//    glVertex2f(x + width, middleY);
//    glEnd();
//    glDisable(GL_LINE_STIPPLE);  // Disable line stipple
//
//    for (const auto& obj : movingObjects) {
//        obj->draw();
//    }
//}
//
//// There is collision on a River when a moving object is not touched while in River
//bool River::collided(Character player) {
//    // check is player is in River
//    if (player.collidesWith(*this)) {
//        
//    }
//    // No river
//    return false;
//}