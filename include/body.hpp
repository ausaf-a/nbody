#ifndef body_hpp
#define body_hpp

#include <SDL2/SDL.h>
#include <vector>

class Body
{
public:
    std::vector<float> pos{0, 0}, vel{0, 0}, accel{0, 0};
    float mass;

    Body(float x, float y, float vx, float vy, double m)
    {
        mass = m;
        pos[0] = x;
        pos[1] = y;
        vel[0] = vx;
        vel[1] = vy;
    };

    ~Body(){};

    void applyGForce(Body other)
    {
        //find normalized direction vector
        std::vector<float> dir{other.pos[0] - pos[0], other.pos[1] - pos[1]};
        // std::cout << dir[0] << "," << dir[1] << std::endl;
        float mag = std::sqrt(dir[0] * dir[0] + dir[1] * dir[1]);
        float force = 0.001; //* (other.mass * mass) / (mag*mag);

        dir[0] /= mag;
        dir[1] /= mag;

        accel[0] = force * dir[0] / mass;
        accel[1] = force * dir[1] / mass;
    };

    void update()
    {

        for (int i = 0; i < 2; i++)
        {
            vel[i] += accel[i];
            pos[i] += vel[i];
        }
    }

    void draw(SDL_Renderer *renderer)
    {
        SDL_RenderDrawPoint(renderer, pos[0], pos[1]);
    };

private:
};

#endif /* body_hpp */