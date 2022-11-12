#include "system.hpp"
#include <iostream>

void System::initialize()
{
	const auto N = std::size(m_particles);

	const auto M = std::size(m_particles[0]);

	for (auto i = 0; i < N; ++i)
	{
		for (auto j = 0; j < M; ++j)
		{
			if (j + 1 < M)
			{
				m_links.push_back(Link(particle(i, j), particle(i, j + 1), 0.5f));
			}
			if (i + 1 < N)
			{
				m_links.push_back(Link(particle(i, j), particle(i + 1, j), 0.5f));
			}
			if (i + 1 < N and j + 1 < M)
			{
				m_links.push_back(Link(particle(i, j), particle(i + 1, j + 1), 0.5f));
			}

			if (i + 1 >= 0 and j - 1 >= 0 and i + 1 < N and j + 1 < M)
			{
				m_links.push_back(Link(particle(i, j), particle(i + 1, j - 1), 0.5f));
			}
		}
	}
}

void System::push(const sf::Vector2f force) const
{
	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		for (auto j = 0U; j < std::size(m_particles[0]); ++j)
		{
			m_particles[i][j]->move(force);
		}
	}
}

void System::update() const
{
	for (auto i = 0U; i < std::size(m_particles); ++i)
	{
		for (auto j = 0U; j < std::size(m_particles[0]); ++j)
		{
			m_particles[i][j]->move(0.25f);

			if (m_particles[i][j]->position().y + m_particles[i][j]->radius() > m_max_point.y)
			{
				m_particles[i][j]->set_y(m_max_point.y - m_particles[i][j]->radius());
			}

			if (m_particles[i][j]->position().y - m_particles[i][j]->radius() < m_min_point.y)
			{
				m_particles[i][j]->set_y(m_min_point.y + m_particles[i][j]->radius());
			}

			if (m_particles[i][j]->position().x + m_particles[i][j]->radius() > m_max_point.x)
			{
				m_particles[i][j]->set_x(m_max_point.x - m_particles[i][j]->radius());
			}

			if (m_particles[i][j]->position().x - m_particles[i][j]->radius() < m_min_point.x)
			{
				m_particles[i][j]->set_x(m_min_point.x + m_particles[i][j]->radius());
			}
		}
	}

	for (auto i = 0U; i < std::size(m_links); ++i)
	{
		m_links[i].update();
	}
}
