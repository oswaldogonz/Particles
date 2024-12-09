#include "Engine.h"

// The Engine constructor
Engine::Engine()
{
  m_Window.create(VideoMode(VideoMode::getDesktopMode().width, VideoMode::getDesktopMode().height), "Particles");
}

// Run will call all the private functions
void Engine::run()
{
  Clock clock;
  cout << "Starting Particle unit tests..." << endl;
  Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
  p.unitTests();
  cout << "Unit tests complete.  Starting engine..." << endl;
  while(m_Window.isOpen())
  {
    Time dt=clock.restart();
    float sec=dt.asSeconds();
    input();
    update(sec);
    draw();
  }
}

void Engine::input()
{
  Event event;
  while(m_Window.pollEvent(event))
  {
    if(event.type==Event::Closed)
		{
			m_Window.close();
		}
    if(event.type==Event::MouseButtonPressed)
    {
      if(event.mouseButton.button==Mouse::Left)
      {
        for(int i=0;i<5;i++)
        {
          int numP=rand()%26+25;
          Vector2i mouseP={event.mouseButton.x, event.mouseButton.y};
          Particle p(m_Window, numP, mouseP);
          m_particles.push_back(p);
        }
      }
    }
  }
  if (Keyboard::isKeyPressed(Keyboard::Escape))
	{
	  m_Window.close();
	}
}

void Engine::update(float dtAsSeconds)
{
  vector<Particle>::iterator iter;
  for (iter=m_particles.begin(); iter!=m_particles.end();)
  {
    if(iter->getTTL()>0.0)
    {
      iter->update(dtAsSeconds);
      iter++;
    }
    else
    {
      iter=m_particles.erase(iter);
    }
  }

}
void Engine::draw()
{
  m_Window.clear();
  for(int i=0;i<m_particles.size();i++)
  {
    m_Window.draw(m_particles[i]);
  }
  m_Window.display();
}
