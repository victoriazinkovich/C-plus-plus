#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
public:

	using particle_t = std::shared_ptr < Particle > ;

public:

	Particle() noexcept = default;

	explicit Particle(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f force,
		sf::Vector2f previous_force, float radius) noexcept : m_position(position),
		m_velocity(velocity), m_radius(radius), m_force(force), 
		m_previous_force(previous_force)
	{}

	~Particle() noexcept = default;

public:

	const auto position() const noexcept
	{
		return m_position;
	}

	const auto velocity() const noexcept
	{
		return m_velocity;
	}

	const auto force() const noexcept
	{
		return m_force;
	}

	const auto previous_force() const noexcept
	{
		return m_previous_force;
	}

	const auto radius() const noexcept
	{
		return m_radius;
	}

public:

	void set_x(float x) noexcept
	{
		m_position.x = x;
	}

	void set_y(float y) noexcept
	{
		m_position.y = y;
	}

	void v_set_x(float x) noexcept
	{
		m_velocity.x = x;
	}

	void v_set_y(float y) noexcept
	{
		m_velocity.y = y;
	}

	void f_set_x(float x) noexcept
	{
		m_force.x = x;
	}

	void f_set_y(float y) noexcept
	{
		m_force.y = y;
	}

	void f_add_x(float x) noexcept
	{
		m_force.x += x;
	}

	void f_add_y(float y) noexcept
	{
		m_force.y += y;
	}

public:

	void move(sf::Vector2f delta);

public:

	void update_position(float dt);

	void update_velocity(float dt);

	void update_force(particle_t particle);

	void update_force();

private:

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

	float m_radius;

	sf::Vector2f m_previous_force;
	sf::Vector2f m_force;

private:

	const double k = 1;
	const double q = 1;
	const double m = 1;
	const double T = 1;
};
