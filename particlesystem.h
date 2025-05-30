#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H
#include <SFML/Graphics.hpp>
#include <random>


class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:
    ParticleSystem(unsigned int count);

    void setEmitter(sf::Vector2f position);

    void update(sf::Time elapsed);

private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    struct Particle
    {
        sf::Vector2f velocity;
        sf::Time     lifetime;
    };

    void resetParticle(std::size_t index);

    std::vector<Particle> m_particles;
    sf::VertexArray       m_vertices;
    sf::Time              m_lifetime{sf::seconds(6)};
    sf::Vector2f          m_emitter;
};

#endif // PARTICLESYSTEM_H
