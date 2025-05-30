#include "particlesystem.h"


ParticleSystem::ParticleSystem(unsigned int count) : m_particles(count), m_vertices(sf::PrimitiveType::Points, count)
{
    for (std::size_t i = 0; i < m_particles.size(); ++i)
    {
        static std::random_device rd;
        static std::mt19937       rng(rd());

        const sf::Angle angle       = sf::radians(0.f);
        const float     speed       = 0;
        m_particles[i].velocity = sf::Vector2f(speed, angle);
        m_particles[i].lifetime = sf::milliseconds(std::uniform_int_distribution(1000, 3000)(rng));

        m_vertices[i].position = m_emitter;
    }
}

void ParticleSystem::setEmitter(sf::Vector2f position)
{
    m_emitter = position;
}

void ParticleSystem::update(sf::Time elapsed)
{
    for (std::size_t i = 0; i < m_particles.size(); ++i)
    {
        Particle& p = m_particles[i];
        p.lifetime -= elapsed;

        if (p.lifetime <= sf::Time::Zero)
            resetParticle(i);

        m_vertices[i].position += p.velocity * elapsed.asSeconds();

        float ratio           = p.lifetime.asSeconds() / m_lifetime.asSeconds();
        m_vertices[i].color.a = static_cast<std::uint8_t>(ratio * 255);
    }
}

void ParticleSystem::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    states.texture = nullptr;

    target.draw(m_vertices, states);
}

void ParticleSystem::resetParticle(std::size_t index)
{
    static std::random_device rd;
    static std::mt19937       rng(rd());

    const sf::Angle angle       = sf::degrees(std::uniform_real_distribution(0.f, 360.f)(rng));
    const float     speed       = std::uniform_real_distribution(20.f, 40.f)(rng);
    m_particles[index].velocity = sf::Vector2f(speed, angle);
    m_particles[index].lifetime = sf::milliseconds(std::uniform_int_distribution(1000, 3000)(rng));

    m_vertices[index].position = m_emitter;
}
