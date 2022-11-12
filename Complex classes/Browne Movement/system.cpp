#include "system.hpp"

void System::initialize()
{
	const auto size = std::size(m_particles);

	for (auto i = 0U; i < size; ++i)
	{
		for (auto j = i + 1; j < size; ++j)
		{
			m_particles[i]->update_force(m_particles[j]);
		}
	}
}

void System::push(const sf::Vector2f force) const
{
	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		m_particles[i]->move(force);
	}
}

void System::update(const float dt) const
{
	const auto size = std::size(m_particles);

	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		m_particles[i]->update_position(dt);

		if (m_particles[i]->position().y + m_particles[i]->radius() > m_max_point.y)
		{
			m_particles[i]->set_y(m_max_point.y - m_particles[i]->radius());
			m_particles[i]->v_set_y(-m_particles[i]->velocity().y);
		}

		if (m_particles[i]->position().y - m_particles[i]->radius() < m_min_point.y)
		{
			m_particles[i]->set_y(m_min_point.y + m_particles[i]->radius());
			m_particles[i]->v_set_y(-m_particles[i]->velocity().y);
		}

		if (m_particles[i]->position().x + m_particles[i]->radius() > m_max_point.x)
		{
			m_particles[i]->set_x(m_max_point.x - m_particles[i]->radius());
			m_particles[i]->v_set_x(-m_particles[i]->velocity().x);
		}

		if (m_particles[i]->position().x - m_particles[i]->radius() < m_min_point.x)
		{
			m_particles[i]->set_x(m_min_point.x + m_particles[i]->radius());
			m_particles[i]->v_set_x(-m_particles[i]->velocity().x);
		}
	}

	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		m_particles[i]->update_force();
	}

	for (auto i = 0U; i < size; ++i)
	{
		for (auto j = i + 1; j < size; ++j)
		{
			m_particles[i]->update_force(m_particles[j]);
		}
	}

	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		m_particles[i]->update_velocity(dt);
	}
}
