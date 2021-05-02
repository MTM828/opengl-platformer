#include "libraries.h"

class Settings {
    public:
        static float gravity;
        static float jumpHeight;
        static float acceleration;
        static float maxSpeed;
        static float friction;

        static void init();
};
Settings settings;
class Physics {
    public:
        static float timeTaken;
        static float oldTime;
        static float deltaTime;

        static float gravity;
        static float jumpHeight;
        static float acceleration;
        static float maxSpeed;
        static float friction;

        static bool rectCol(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2);

        static void init();
};
Physics physics;
class Player {
    public:
        static float x;
        static float y;
        static float xVel;
        static float yVel;
        static bool colliding();

        static void update();
        static void render();
};
Player player;
class Renderer {
    public:
        static SDL_Renderer *renderer;
        static void init();
        static void render();
        static void setColour(int r, int g, int b, int a = 255);
        static void drawRect(int x, int y, int width, int height);
};
Renderer renderer;
class Win {
    public:
        static int width;
        static int height;
        static int fps;
        static std::string title;
        static bool quit;

        static SDL_Window *window;
        static SDL_Event event;

        static void init();
        static void update();
        static void mainLoop();
};
Win win;
class Keys {
    public:
        static bool left;
        static bool right;
        static bool up;
        static bool down;

        static void update();
};
Keys keys;
class Platform {
    public:
        int x;
        int y;
        Platform(int xPos, int yPos) {
            x = xPos;
            y = yPos;
        }
};
class Platforms {
    public:
        static char x;
        static char p;
        static char _;
        static std::vector<std::vector<char>> level;
        static std::vector<Platform> platforms;
        static void init();

        static void render();
};
Platforms platforms;

float Settings::gravity;
float Settings::jumpHeight;
float Settings::acceleration;
float Settings::maxSpeed;
float Settings::friction;
void Settings::init() {
    // Edit the values below to change the game's settings.
    // The description of each setting is written next to it.
    // 100 is the default value. All settings will be set to their defaults.
    //     The more you decrease that 100, the more the value increases.
    //     The more you increase that 100, the more the value decreases.
    gravity      = 100; // Gravity
    jumpHeight   = 100; // Player jump height
    acceleration = 100; // Player movement speed
    maxSpeed     = 100; // Player maximum movement speed
    friction     = 100; // Friction
    // Leave the rest of the code as it is, the game may not function as intended if you do.
    gravity      = (100 * 0.5) / gravity;
    jumpHeight   = (100 * 18 ) / jumpHeight;
    acceleration = (100 * 1.5) / acceleration;
    maxSpeed     = (100 * 5  ) / maxSpeed;
    friction     = (100 * 1.2) / friction;
    physics.init();
}

float Physics::timeTaken = 0;
float Physics::oldTime = 0;
float Physics::deltaTime = 1;
float Physics::gravity = settings.gravity;
float Physics::jumpHeight = settings.jumpHeight;
float Physics::acceleration = settings.acceleration;
float Physics::maxSpeed = settings.maxSpeed;
float Physics::friction = settings.friction;
bool Physics::rectCol(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    return x1 + w1 > x2 && x1 < x2 + w2 && y1 + h1 > y2 && y1 < y2 + h2;
}
void Physics::init() {
    gravity      = settings.gravity;
    jumpHeight   = settings.jumpHeight;
    acceleration = settings.acceleration;
    maxSpeed     = settings.maxSpeed;
    friction     = settings.friction;
}

float Player::x = 0;
float Player::y = 0;
float Player::xVel = 0;
float Player::yVel = 0;
bool Player::colliding() {
    bool colliding = false;
    for (i = 0; i < platforms.platforms.size(); i++) {
        if (physics.rectCol(x, y, 100, 100, platforms.platforms.at(i).x, platforms.platforms.at(i).y, 100, 100)) {
            colliding = true;
        }
    }
    delete &colliding;
    return colliding;
}
void Player::render() {
    renderer.setColour(0, 0, 255);
    renderer.drawRect(x, y, 100, 100);
}
void Player::update() {
    yVel += physics.gravity;
    y += yVel * physics.deltaTime;
    if (colliding()) {
        while (colliding()) {
            if (yVel > 0) {
                y -= 0.1;
            } else {
                y += 0.1;
            }
        }
        if (keys.up && yVel > 0) {
            player.yVel = -physics.jumpHeight;
        } else {
            yVel = 0;
        }
    }
    xVel /= physics.friction;
    if (keys.right && physics.acceleration < physics.maxSpeed) {xVel += physics.acceleration;}
    if (keys.left && physics.acceleration > -physics.maxSpeed) {xVel -= physics.acceleration;}
    x += xVel;
    if (colliding()) {
        while (colliding()) {
            if (xVel > 0) {
                x -= 1;
            } else {
                x += 1;
            }
        }
        xVel = 0;
    }
}

SDL_Renderer *Renderer::renderer;
void Renderer::init() {
    renderer = SDL_CreateRenderer(win.window, -1, SDL_RENDERER_ACCELERATED);
}
void Renderer::render() {
    setColour(255, 255, 255);
    SDL_RenderClear(renderer);
    platforms.render();
    player.render();
    SDL_RenderPresent(renderer);
}
void Renderer::setColour(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}
void Renderer::drawRect(int x, int y, int width, int height) {
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &rect);
    delete &rect;
}

int Win::width = 1000;
int Win::height = 500;
std::string Win::title = "Platformer";
int Win::fps = 60;
bool Win::quit = false;
SDL_Window *Win::window;
SDL_Event Win::event;
void Win::init() {
    physics.timeTaken = 1;
    physics.oldTime = 0;

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
}
void Win::update() {
    //physics.timeTaken = glutGet(GLUT_ELAPSED_TIME);
    //physics.deltaTime = (physics.timeTaken - physics.oldTime) / 20;
    //physics.oldTime = physics.timeTaken;
    player.update();
    renderer.render();
    SDL_UpdateWindowSurface(window);
    SDL_Delay(1000 / fps);
}
void Win::mainLoop() {
    while (!quit) {
        update();
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
                break;
            }
            keys.update();
        }
    }
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer.renderer);
    SDL_Quit();
}

bool Keys::right = false;
bool Keys::left = false;
bool Keys::up = false;
bool Keys::down = false;
void Keys::update() {
    if (win.event.type == SDL_KEYDOWN) {
        if (win.event.key.keysym.sym == SDLK_RIGHT) {right = true;}
        if (win.event.key.keysym.sym == SDLK_LEFT ) {left  = true;}
        if (win.event.key.keysym.sym == SDLK_UP   ) {up    = true;}
        if (win.event.key.keysym.sym == SDLK_DOWN ) {down  = true;}
    }
    if (win.event.type == SDL_KEYUP  ) {
        if (win.event.key.keysym.sym == SDLK_RIGHT) {right = false;}
        if (win.event.key.keysym.sym == SDLK_LEFT ) {left  = false;}
        if (win.event.key.keysym.sym == SDLK_UP   ) {up    = false;}
        if (win.event.key.keysym.sym == SDLK_DOWN ) {down  = false;}
    }
}

char Platforms::x = 'x';
char Platforms::p = 'p';
char Platforms::_ = '_';
std::vector<std::vector<char>> Platforms::level = {
    {p, p, p, p, p, p, p, p, p, p},
    {p, x, _, _, _, p, _, _, _, p},
    {p, p, _, _, _, _, _, p, p, p},
    {p, p, p, p, _, _, _, _, _, p},
    {p, p, p, p, p, p, p, p, p, p}
};
std::vector<Platform> Platforms::platforms = {};
void Platforms::init() {
    i = 0;
    for (auto it = level.begin(); it != level.end(); it++) {
        j = 0;
        for (auto secondIt = level.at(i).begin(); secondIt != level.at(i).end(); secondIt++) {
            switch (level.at(i).at(j)) {
                case 'x':
                    player.x = j * 100;
                    player.y = i * 100;
                    break;
                case 'p':
                    platforms.push_back(Platform(j * 100, i * 100));
                    break;
                case '_':
                    break;
            }
            j++;
        }
        i++;
    }
}
void Platforms::render() {
    renderer.setColour(0, 0, 0);
    for (i = 0; i < platforms.size(); i++) {
        renderer.drawRect(platforms[i].x, platforms[i].y, 100, 100);
    }
}

int main(int argc, char *argv[]) {
    settings.init();
    platforms.init();

    SDL_Init(SDL_INIT_EVERYTHING);
    win.init();
    renderer.init();

    win.mainLoop();
    return EXIT_SUCCESS;
}