#include "Engine.h"

// The Engine constructor
Engine::Engine() {
	m_Window.create(VideoMode(VideoMode::getDesktopMode().width / 2, VideoMode::getDesktopMode().height / 2), "Particle Engine", Style::Default);
}

// Run will call all the private functions
void Engine::run() {
	Clock runClock;
	

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen())
	{
		
		//runClock.restart();
		
		Engine::input();
		float dt = runClock.restart().asSeconds();
		///Update

		Engine::update(dt);

		///Draw
		Engine::draw();
	}

}

void Engine::input() {//private
	///Input
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::KeyPressed)
		{
			// Handle the player quitting
			if (event.key.code == Keyboard::Escape)
			{
				m_Window.close();
			}

		}

		if (event.type == Event::Closed)
		{
			m_Window.close();
		}

		if (event.type == Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == Mouse::Left)
			{
				for (int i = 0; i < 5; i++)
				{
					Particle p(m_Window, 25 + std::rand() % 26, {event.mouseButton.x,event.mouseButton.y});
					m_particles.push_back(p);
				}
			}
		}
	}
}

void Engine::update(float dtAsSeconds) {//private
	for (vector<Particle>::iterator it = m_particles.begin(); it != m_particles.end();) {
		if (it->getTTL() > 0.0) {
			it->update(dtAsSeconds);
			++it;
		}
		else {
			it = m_particles.erase(it);
		}
	}
}
void Engine::draw() {//private
	m_Window.clear();

	for (const auto& p : m_particles)
	{
		m_Window.draw(p);
	}

	m_Window.display();
}