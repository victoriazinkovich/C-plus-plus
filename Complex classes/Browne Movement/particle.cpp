#include "particle.hpp"
#include "functions.hpp"

#include <iostream>

void Particle::move(sf::Vector2f delta)
{
	m_position += delta;
}

void Particle::update_position(const float dt)
{
	m_position = sf::Vector2f(m_position.x + m_velocity.x * dt + m_force.x / m * dt * dt / 2, 
		m_position.y + m_velocity.y * dt + m_force.y / m * dt * dt / 2);
}

void Particle::update_force()
{
	m_previous_force = m_force;
	m_force.x = 0;
	m_force.y = 0;
}

void Particle::update_force(particle_t particle)
{
	auto r = distance(m_position, particle->position());

	m_force += sf::Vector2f(k * q * q / std::pow((r), 3) *
		(m_position.x - particle->position().x),
		k * q * q / std::pow((r), 3) *
		(m_position.y - particle->position().y));

	particle->f_add_x(-m_force.x);
	particle->f_add_y(-m_force.y);
}

void Particle::update_velocity(const float dt)
{
	m_velocity = sf::Vector2f(m_velocity.x + (m_force.x + m_previous_force.x) / m * dt / 2,
		m_velocity.y + (m_force.y + m_previous_force.y) / m * dt / 2);
}
