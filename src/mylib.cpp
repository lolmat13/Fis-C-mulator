#include "myLib.h"

std::vector<VerletParticle> particles;
std::vector<Link> links;

int SUB_TICKS = 1;
double dt = (double)1/SUB_TICKS;
Vector2 gravity = {0.0f, 1.0f};

double min(double a, double b) {
    if (a<b) return a;
    return b;
}

VerletParticle::VerletParticle(Vector2 current, double radius, bool dyn) {
    pos = current;
    posPrev = current;
    accel = Vector2Zero();
    r = radius;
    m = radius*radius*PI;
    dynamic = dyn;
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
    return pos - posPrev;
}

double VerletParticle::getRadius() {
    return r;
}

double VerletParticle::getMass() {
    return m;
}

bool VerletParticle::isDynamic() {
    return dynamic;
}

void VerletParticle::setPosition(Vector2 posCurrent){
    pos = posCurrent;
}

void VerletParticle::setVelocity(Vector2 vel) {
    if (!dynamic) return;
    posPrev = pos - vel*dt;
}

void VerletParticle::setMass(double mass) {
    m = mass;
}

void VerletParticle::setAcceleration(Vector2 acceleration) {
    if (!dynamic) return;
    accel = acceleration;
}

void VerletParticle::applyForce(Vector2 force) {
    if (!dynamic) return;
    accel+=force;
}

void VerletParticle::updatePos() {
    if (!dynamic) return;
    Vector2 temp = pos;
    pos = pos*2 - posPrev + accel*dt*dt;
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
    double cRadius = min(WIDTH, HEIGHT)/2;
    Vector2 disp = pos - cCenter;
    double dist = Vector2Length(disp);
    if (dist > cRadius - r /*&& pos.x < WIDTH/2*/) {
        constrainDistance(cCenter, cRadius-getRadius());
        posPrev = pos-Vector2Reflect(vel, Vector2Normalize(disp));
    }
}

void VerletParticle::constrainDistance(Vector2 anchor, double distance) {
    if (!dynamic) return;
    pos = Vector2Normalize(pos - anchor) * distance + anchor;
}

void initParticle(VerletParticle particle, Vector2 vel) {
    particle.setVelocity(vel);
    particles.push_back(particle);
}

void initLink(size_t a, size_t b, double distance) {
    if (a==b) return;
    // links.push_back({a, b, distance});
    links.push_back({b, a, distance});
}

void initSquare(Vector2 Center, float sideLength, Vector2 velocity) { //im so sorry
    sideLength *= 0.5f;
    initParticle(VerletParticle({Center.x - sideLength, Center.y -sideLength}, 1, 1), Vector2Zero());
    initParticle(VerletParticle({Center.x + sideLength, Center.y -sideLength}, 1, 1), Vector2Zero());
    initParticle(VerletParticle({Center.x - sideLength, Center.y +sideLength}, 1, 1), Vector2Zero());
    initParticle(VerletParticle({Center.x + sideLength, Center.y +sideLength}, 1, 1), Vector2Zero());
    particles[particles.size()-1].setMass(sideLength*sideLength/4);
    particles[particles.size()-2].setMass(sideLength*sideLength/4);
    particles[particles.size()-3].setMass(sideLength*sideLength/4);
    particles[particles.size()-4].setMass(sideLength*sideLength/4);
    particles[particles.size()-1].setVelocity(velocity);
    particles[particles.size()-2].setVelocity(velocity);
    particles[particles.size()-3].setVelocity(velocity);
    particles[particles.size()-4].setVelocity(velocity);
    initLink(particles.size()-4, particles.size()-3, Vector2Distance(particles[particles.size()-4].getCurrentPosition(), particles[particles.size()-3].getCurrentPosition()));
    initLink(particles.size()-3, particles.size()-2, Vector2Distance(particles[particles.size()-3].getCurrentPosition(), particles[particles.size()-2].getCurrentPosition()));
    initLink(particles.size()-2, particles.size()-1, Vector2Distance(particles[particles.size()-2].getCurrentPosition(), particles[particles.size()-1].getCurrentPosition()));
    initLink(particles.size()-1, particles.size()-4, Vector2Distance(particles[particles.size()-1].getCurrentPosition(), particles[particles.size()-4].getCurrentPosition()));
    initLink(particles.size()-4, particles.size()-2, Vector2Distance(particles[particles.size()-4].getCurrentPosition(), particles[particles.size()-2].getCurrentPosition()));
    initLink(particles.size()-3, particles.size()-1, Vector2Distance(particles[particles.size()-3].getCurrentPosition(), particles[particles.size()-1].getCurrentPosition()));
}

void initRope(size_t a, size_t b) {
    Vector2 posA = particles[a].getCurrentPosition();
    Vector2 posB = particles[b].getCurrentPosition();
    double distance = Vector2Distance(posA, posB);
    int segments = 8;
    distance = distance/segments;
    Vector2 step = Vector2Normalize(posB-posA)*distance;
    for (int i=1; i<segments; i++) {
        initParticle(VerletParticle(posA+step*(i), 1, 1), Vector2Zero());
        particles[particles.size()-1].setMass(0.00000000000000000000000000000001f);
        if (i!=1) {
            initLink(particles.size()-2, particles.size()-1, distance);
        }
        if (i==1) {
            initLink(a, particles.size()-1, distance);
            continue;
        }
        if (i==segments-1) {
            initLink(b, particles.size()-1, distance);
            continue;
        }
        
    }
}

bool isPointOnLine(Vector2 s, Vector2 e, Vector2 p) {
    double distS = Vector2Distance(s, p);
    double distE = Vector2Distance(e, p);
    double len = Vector2Distance(s, e);
    if (distS+distE == len) return 1;
    return 0;
}

bool isCircleLineCollision(Vector2 start, Vector2 end, Vector2 pos, double r) {
    double dot = Vector2DotProduct(pos - start, end - start) / Vector2DotProduct(end - start, end - start);
    Vector2 closest = start + (end - start) * dot;
    bool onLine = isPointOnLine(start, end, closest);
    if (!onLine) return 0;

    double dist = Vector2Distance(closest, pos);
    if(dist <= r) return 1;
    return 0;
}

void applyLinkConstraints() {
    for (Link link : links) {
        size_t p1 = link.a;
        size_t p2 = link.b;
        Vector2 pos1 = particles[p1].getCurrentPosition();
        Vector2 pos2 = particles[p2].getCurrentPosition();
        
        if (!particles[p1].isDynamic()){
            particles[p2].constrainDistance(pos1, link.distance);
            continue;
        }
        if (!particles[p2].isDynamic()){
            particles[p1].constrainDistance(pos2, link.distance);
            continue;
        }

        double diff = link.distance - Vector2Length(pos2-pos1);
        double sumMass = particles[p1].getMass() + particles[link.b].getMass();
        particles[p1].constrainDistance(pos2, link.distance - diff*(particles[p2].getMass()/sumMass));
        particles[p2].constrainDistance(pos1, link.distance - diff*(particles[p1].getMass()/sumMass));
    }
}

void resolveLinkParticleCollision(size_t a, size_t b, size_t p){ //pass index of involved particles
    Vector2 posA = particles[a].getCurrentPosition();
    Vector2 posB = particles[b].getCurrentPosition();
    Vector2 posP = particles[p].getCurrentPosition();
    double dot = Vector2DotProduct(posP - posA, posB - posA) / Vector2DotProduct(posB - posA, posB - posA);
    Vector2 closest = posA + (posB - posA) * dot;
    Vector2 vel = particles[p].getVelocity();
    particles[p].constrainDistance(closest, particles[p].getRadius());
    particles[p].setVelocity(Vector2Reflect(vel, Vector2Normalize(posP-closest))/dt);
}

void resolveCollisions() {
    //Particle on Particle
    for (size_t i = 0; i < particles.size(); i++) {
        for (size_t j = i+1; j < particles.size(); j++) { //j = i+1 to not check particle pairs that have already been iterated through
            Vector2 pos1 = particles[i].getCurrentPosition();
            Vector2 pos2 = particles[j].getCurrentPosition();
            double dist = Vector2Distance(pos1, pos2);
            double sumRadii = particles[i].getRadius() + particles[j].getRadius();
            if (dist < sumRadii) {
                double diff = sumRadii - dist;

                Vector2 v2 = particles[j].getVelocity();
                if (!particles[i].isDynamic()){
                    particles[j].constrainDistance(pos1, sumRadii);
                    particles[j].setVelocity(Vector2Reflect(v2, Vector2Normalize(pos2-pos1))/dt);
                    continue;
                }

                Vector2 v1 = particles[i].getVelocity();
                if (!particles[j].isDynamic()){
                    particles[i].constrainDistance(pos1, sumRadii);
                    particles[i].setVelocity(Vector2Reflect(v1, Vector2Normalize(pos1-pos2))/dt);
                    continue;
                }

                double m1 = particles[i].getMass();
                double m2 = particles[j].getMass();
                double sumMass = m1 + m2;
                particles[i].constrainDistance(pos2, sumRadii - diff*(m2/sumMass));
                particles[i].setVelocity((v1*(m1-m2)+v2*2*m2)/sumMass/dt);
                particles[j].constrainDistance(pos1, sumRadii - diff*(m1/sumMass));
                particles[j].setVelocity((v2*(m2-m1)+v1*2*m1)/sumMass/dt);
                
            }
        }   
    }

    //goodbye any semblance of optimization. if this fucks up my runtime im just dividing the subticks by 10
    //Particle on Line
    for (auto& link : links) {
        Vector2 lineStart = particles[link.a].getCurrentPosition();
        Vector2 lineEnd = particles[link.b].getCurrentPosition();
        for(size_t i=0; i<particles.size(); i++) {
            if (i==link.a || i==link.b) continue; //Dont Collide with particles that form the link
            if (!isCircleLineCollision(lineStart, lineEnd, particles[i].getCurrentPosition(), particles[i].getRadius())) continue; 
            //Resolve collision
            resolveLinkParticleCollision(link.a, link.b, i);
        }
    }
}   

void simulationStep() {
    for (auto& particle : particles) {
        particle.updatePos();
        particle.setAcceleration(gravity);
    }
    resolveCollisions();
    applyLinkConstraints();
    applyLinkConstraints();
    // applyLinkConstraints();
    // applyLinkConstraints();
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

    // //Static Particle Tests
    // //P on P
    // initParticle(VerletParticle({400, 400}, 20, 1), {3, 3});
    // initParticle(VerletParticle({600, 600}, 10, 0), {0, 0});
    // //Link Test
    // initParticle(VerletParticle({400, 400}, 10, 0), {0, 0});
    // initParticle(VerletParticle({600, 400}, 10, 1), {0, 0});
    // initLink(0, 1, 200);
    // //Rope Test
    // initParticle(VerletParticle({400, 400}, 50, 0), {0, 0});
    // initParticle(VerletParticle({300, 250}, 5, 1), {0, 0});
    // initParticle(VerletParticle({500, 250}, 5, 1), {0, 0});
    // initRope(1,2);

    // //Mass test
    // initParticle(VerletParticle({400, 400}, 20), {3, 0});
    // initParticle(VerletParticle({600, 400}, 10), {0, 0});

    // //Circular Constraint Test
    // initParticle(VerletParticle({800, 200}, 10), {-3, 0});
    // initParticle(VerletParticle({800, 250}, 10), {-3, 0});
    // initParticle(VerletParticle({800, 300}, 10), {-3, 0});
    // initParticle(VerletParticle({800, 350}, 10), {-3, 0});
    // initParticle(VerletParticle({800, 400}, 10), {-3, 0});
    // initParticle(VerletParticle({800, 450}, 10), {-3, 0});
    // initParticle(VerletParticle({800, 500}, 10), {-3, 0});
    // initParticle(VerletParticle({800, 550}, 10), {-3, 0});
    // initParticle(VerletParticle({800, 600}, 10), {-3, 0});

    // //Stress Test
    Vector2 c = {200, 200};
    int square = 35;
    float r = 2;
    for (int i = 0; i < square; i++) {
        for (int j = 0; j < square; j++) {
            initParticle(VerletParticle(Vector2Add(c, {i*r*2, j*r*2}), r, 1), {0, 0});
        }
    }
    // c = {200, 400};
    // for (int i = 0; i < 5; i++) {
    //     for (int j = 0; j < 5; j++) {
    //         initParticle(VerletParticle(Vector2Add(c, {i*40.0f, j*40.0f}), 20, 1), {0, 0});
    //     }
    // }

    // //Link Test
    // initParticle(VerletParticle({600, 300}, 10), {3, 0});
    // initParticle(VerletParticle({600, 500}, 10), {-3, 0});
    // initLink(0, 1, 200);

    // //Link Mass Test
    // initParticle(VerletParticle({300, 400}, 15, 1), {0, -3});
    // initParticle(VerletParticle({500, 400}, 10, 1), {0, 3});
    // initLink(0, 1, 200);

    // //Cloth Stress Test
    // Vector2 c = {WIDTH/4, HEIGHT/4};
    // int side = 6;
    // for (int i = 0; i < side; i++) {
    //     for (int j = 0; j < side; j++) {
    //         if (j!=0) initParticle(VerletParticle(Vector2Add(c, {i*20.0f, j*20.0f}), 5, 1), {0, 0});
    //         else initParticle(VerletParticle(Vector2Add(c, {i*20.0f, j*20.0f}), 5, 0), {0, 0});
    //     }
    // }
    // for (int i = 0; i < side; i++) {
    //     for (int j = 0; j < side; j++) {
    //         if (i!=side-1 && j!=side-1){
    //             initLink(i+j*side, i+j*side+1, Vector2Distance(particles[i+j*side].getCurrentPosition(), particles[i+j*side+1].getCurrentPosition()));
    //             initLink(i+j*side, i+j*side+side, Vector2Distance(particles[i+j*side].getCurrentPosition(), particles[i+j*side+side].getCurrentPosition()));
    //             // initLink(i+j*side, i+j*side+(side+1), Vector2Distance(particles[i+j*side].getCurrentPosition(), particles[i+j*side+(side+1)].getCurrentPosition()));
    //         }
    //         if (i==side-1 && j!=side-1){
    //             initLink(i+j*side, i+j*side+side, Vector2Distance(particles[i+j*side].getCurrentPosition(), particles[i+j*side+side].getCurrentPosition()));
    //         }
    //         if (j==side-1 && i!=side-1){
    //             initLink(i+j*side, i+j*side+1, Vector2Distance(particles[i+j*side].getCurrentPosition(), particles[i+j*side+1].getCurrentPosition()));
    //         }
    //     }
    // }
    // initParticle(VerletParticle({500, 400}, 30, 1), {-20, -20});

    // //Compound Shape on Compound Shape Test
    // initSquare({350, 400}, 100, {3, 0});
    // initSquare({550, 400}, 100, {0, 0});

    // //Compound Shape on Particle Test
    // initSquare({400, 400}, 100, {0, 0});
    // initParticle(VerletParticle({650, 350}, 50, 1), {-2, 0});

    // //Particle on Link Particle Test
    // initParticle(VerletParticle({400, 300}, 10, 1), {0, 0});
    // initParticle(VerletParticle({400, 500}, 10, 1), {0, 0});
    // initParticle(VerletParticle({600, 300}, 10, 1), {-2, 0});
    // initParticle(VerletParticle({200, 500}, 10, 1), {2, 0});
    // initLink(0, 1, 200);

    // //Rope Test
    // initParticle(VerletParticle({400, 400}, 100, 0), {0, 0});
    // initParticle(VerletParticle({200, 250}, 1, 1), {0, 1});
    // initParticle(VerletParticle({600, 250}, 1, 1), {0, 1});
    // initRope(1,2);

    // //Manual Rope Test
    // initParticle(VerletParticle({200, 250}, 1, 1), {0, 0});
    // initParticle(VerletParticle({250, 250}, 1, 1), {0, 0});
    // initParticle(VerletParticle({300, 250}, 1, 1), {0, 0});
    // initParticle(VerletParticle({350, 250}, 1, 1), {0, 0});
    // initParticle(VerletParticle({400, 250}, 1, 1), {0, 0});
    // initParticle(VerletParticle({450, 250}, 1, 1), {0, 0});
    // initParticle(VerletParticle({500, 250}, 1, 1), {0, 0});
    // initParticle(VerletParticle({550, 250}, 1, 1), {0, 0});
    // initParticle(VerletParticle({600, 250}, 1, 1), {0, 0});
    // initLink(0, 1, 50);
    // initLink(1, 2, 50);
    // initLink(2, 3, 50);
    // initLink(3, 4, 50);
    // initLink(4, 5, 50);
    // initLink(5, 6, 50);
    // initLink(6, 7, 50);
    // initLink(7, 8, 50);
    // initParticle(VerletParticle({400, 400}, 100, 0), {0, 0});

    // //Static Surface Test
    // initParticle(VerletParticle({50, 400}, 1, 0), {0, 0});
    // initParticle(VerletParticle({400, 750}, 1, 0), {0, 0});
    // initLink(0, 1, 565);
    // initParticle(VerletParticle({500, 550}, 20, 1), {-3, 0});


    InitWindow(WIDTH, HEIGHT, "Fis-C-mulator");
    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        BeginDrawing();
        for (int i=0; i<SUB_TICKS; i++) {
            simulationStep();
        }
        ClearBackground(BLACK);
        DrawCircleLinesV({WIDTH/2, HEIGHT/2}, min(WIDTH, HEIGHT)/2, GRAY);
        drawFrame();
        DrawFPS(5,5);
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
