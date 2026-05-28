#include "myLib.h"

std::vector<VerletParticle> particles;
std::vector<Link> links;

int SUB_TICKS = 1000;
float dt = (float)1/SUB_TICKS;
Vector2 gravity = {0, 0};

float min(float a, float b) {
    if (a<b) return a;
    return b;
}

VerletParticle::VerletParticle(Vector2 current, float radius) {
    pos = current;
    posPrev = current;
    accel = Vector2Zero();
    r = radius;
    m = 1;
}

VerletParticle::~VerletParticle() {}

Vector2 VerletParticle::getCurrentPosition() {
    return pos;
}

Vector2 VerletParticle::getPreviousPosition() {
    return posPrev;
}

Vector2 VerletParticle::getAcceleration() {
    return accel;
}

Vector2 VerletParticle::getVelocity() {
    return Vector2Subtract(pos, posPrev);
}

float VerletParticle::getRadius() {
    return r;
}

float VerletParticle::getMass() {
    return m;
}

void VerletParticle::setVelocity(Vector2 vel) {
    posPrev = Vector2Subtract(pos, Vector2Scale(vel, dt));
}

void VerletParticle::setMass(float mass) {
    m = mass;
}

void VerletParticle::applyForce(Vector2 force) {
    accel = Vector2Scale(force, 1/m);
}

void VerletParticle::updatePos() {
    Vector2 temp = pos;
    pos = Vector2Add(Vector2Subtract(Vector2Scale(pos, 2), posPrev), Vector2Scale(accel, dt*dt));
    posPrev = temp;
}

void VerletParticle::constrain() { 
    //Box
    Vector2 vel = getVelocity();
    if (pos.x < 0 + r) {
        pos.x = 0 + r;
        posPrev.x = pos.x + vel.x;
    }
    if (pos.x > WIDTH - r) {
        pos.x = WIDTH - r;
        posPrev.x = pos.x + vel.x;
    }
    if (pos.y < 0 + r) {
        pos.y = 0 + r;
        posPrev.y = pos.y + vel.y;
    }
    if (pos.y > HEIGHT - r) {
        pos.y = HEIGHT - r;
        posPrev.y = pos.y + vel.y;
    }

    //Circle
    Vector2 cCenter = {WIDTH/2, HEIGHT/2};
    float cRadius = min(WIDTH, HEIGHT)/2;
    Vector2 disp = Vector2Subtract(pos, cCenter);
    float dist = Vector2Length(disp);
    if (dist > cRadius - r && pos.x < WIDTH/2) {
        constrainDistance(cCenter, cRadius-getRadius());
        setVelocity(Vector2Reflect(vel, Vector2Normalize(Vector2Subtract(cCenter, pos))));
        
    }
}

void VerletParticle::constrainDistance(Vector2 anchor, float distance) {
    pos = Vector2Add(Vector2Scale(Vector2Normalize(Vector2Subtract(pos, anchor)), distance), anchor);
}

void VerletParticle::step() {
    updatePos();
    constrain();
}

void initParticle(VerletParticle particle, Vector2 vel) {
    particle.setVelocity(vel);
    particles.push_back(particle);
}

void initLink(size_t a, size_t b, float distance) {
    links.push_back({a, b, distance});
}

void initSquare(Vector2 Center, float sideLength) {
    sideLength *= 0.5f;
    initParticle(VerletParticle({Center.x - sideLength, Center.y -sideLength}, 1), Vector2Zero());
    initParticle(VerletParticle({Center.x + sideLength, Center.y -sideLength}, 1), Vector2Zero());
    initParticle(VerletParticle({Center.x - sideLength, Center.y +sideLength}, 1), Vector2Zero());
    initParticle(VerletParticle({Center.x + sideLength, Center.y +sideLength}, 1), Vector2Zero());
    initLink(particles.size()-4, particles.size()-3, Vector2Distance(particles[particles.size()-4].getCurrentPosition(), particles[particles.size()-3].getCurrentPosition()));
    initLink(particles.size()-3, particles.size()-2, Vector2Distance(particles[particles.size()-3].getCurrentPosition(), particles[particles.size()-2].getCurrentPosition()));
    initLink(particles.size()-2, particles.size()-1, Vector2Distance(particles[particles.size()-2].getCurrentPosition(), particles[particles.size()-1].getCurrentPosition()));
    initLink(particles.size()-1, particles.size()-4, Vector2Distance(particles[particles.size()-1].getCurrentPosition(), particles[particles.size()-4].getCurrentPosition()));
    initLink(particles.size()-4, particles.size()-2, Vector2Distance(particles[particles.size()-4].getCurrentPosition(), particles[particles.size()-2].getCurrentPosition()));
    initLink(particles.size()-3, particles.size()-1, Vector2Distance(particles[particles.size()-3].getCurrentPosition(), particles[particles.size()-1].getCurrentPosition()));
}

bool PointCircle(Vector2 p, Vector2 c, float r) { //is point p inside circle of center c and radius r
  Vector2 dist = Vector2Subtract(c, p);
  float distance = Vector2Length(dist);
  if (distance <= r) {
    return 1;
  }
  return 0;
}

bool PointLine(Vector2 s, Vector2 e, Vector2 p) { //is point p on line s->e
    float distS = Vector2Distance(s, p);
    float distE = Vector2Distance(e, p);
    float len = Vector2Distance(s, e);
    if (len-0.1f <= distS+distE && distS+distE <= len+0.1f) return 1;
    return 0;
}

bool isCircleLineCollision(Vector2 start, Vector2 end, Vector2 pos, float r) { //does circle center pos radius r collide with line start->end
    bool insideStart = PointCircle(start, pos, r);
    bool insideEnd = PointCircle(end, pos, r);
    if (insideStart || insideEnd) return 1; //check if start/end of line is in circle

    float len = Vector2Distance(start, end);
    float dot = Vector2DotProduct(Vector2Subtract(pos, start), Vector2Subtract(end, start)) / len*len;

    Vector2 closest = Vector2Add(start, Vector2Scale(Vector2Subtract(end, start), dot));
    bool onLine = PointLine(start, end, closest);
    if (!onLine) return 0;

    float dist = Vector2Distance(closest, pos);
    if(dist <= r) return 1;
    return 0;
}

void applyLinkConstraints() {
    for (Link link : links) {
        Vector2 disp = Vector2Subtract(particles[link.b].getCurrentPosition(), particles[link.a].getCurrentPosition());
        float dist = Vector2Length(disp);
        float diff = link.distance - dist;
        if (diff != 0) {
            Vector2 temp = particles[link.a].getCurrentPosition();
            particles[link.a].constrainDistance(particles[link.b].getCurrentPosition(), link.distance - diff/2);
            particles[link.b].constrainDistance(temp, link.distance - diff/2);
        }
    }
}

void resolveCollisions() {
    for (uint i = 0; i < particles.size(); i++) {
        for (uint j = i+1; j < particles.size(); j++) {
            float dist = Vector2Distance(particles[i].getCurrentPosition(), particles[j].getCurrentPosition());
            float sumRadii = particles[i].getRadius() + particles[j].getRadius();
            if (dist < sumRadii) {
                Vector2 temp = particles[i].getCurrentPosition();
                particles[i].constrainDistance(particles[j].getCurrentPosition(), sumRadii);
                particles[j].constrainDistance(temp, sumRadii);
            }
        }   
    }

    //goodbye any semblance of optimization. if this fucks up my runtime im just dividing the subticks by 10

    for (auto& link : links) {
        Vector2 lineStart = particles[link.a].getCurrentPosition();
        Vector2 lineEnd = particles[link.b].getCurrentPosition();
        for(size_t i=0; i<particles.size(); i++) {
            if (i==link.a || i==link.b) continue; //Dont Collide with particles that form the link
            if (!isCircleLineCollision(lineStart, lineEnd, particles[i].getCurrentPosition(), particles[i].getRadius())) continue;

            //Resolve collision

        }
    }
}   

void resolveCircleLineCollision() {

}

void simulationStep() {
    for (auto& particle : particles) {
        particle.applyForce(gravity);
        particle.updatePos();
    }
    resolveCollisions();
    applyLinkConstraints();
    for (auto& particle : particles) {
        particle.constrain();
    }
}

void drawFrame() {
    for (auto& particle : particles) {
        DrawCircleV(particle.getCurrentPosition(), particle.getRadius(), GRAY);
    }
    for (auto& link : links) {
        DrawLineV(particles[link.a].getCurrentPosition(), particles[link.b].getCurrentPosition(), GRAY);
    }
}

int main() {
    initParticle(VerletParticle({800, 300}, 10), {-2, 0});
    initParticle(VerletParticle({800, 350}, 10), {-2, 0});
    initParticle(VerletParticle({800, 400}, 10), {-2, 0});
    initSquare({350, 350}, 100);
    initSquare({550, 350}, 100);

    InitWindow(WIDTH, HEIGHT, "Fis-C-mulator");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        for (int i=0; i<SUB_TICKS; i++) {
            simulationStep();
        }
        ClearBackground(BLACK);
        DrawCircleSectorLines({WIDTH/2, HEIGHT/2}, min(WIDTH, HEIGHT)/2, 270, 90, 32, GRAY);
        // DrawCircleLinesV({WIDTH/2, HEIGHT/2}, min(WIDTH, HEIGHT)/2, GRAY);
        drawFrame();
        DrawFPS(5,5);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
