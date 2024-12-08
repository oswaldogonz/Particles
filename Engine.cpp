// The Engine constructor
Engine();

Call create on m_Window to populate the RenderWindow member variable
You can assign a custom resolution or you can call VideoMode::getDesktopMode() to get the screen resolution
// Run will call all the private functions
void run();
// A regular RenderWindow
RenderWindow m_Window;
//vector for Particles
vector<Particle> m_particles;
// Private functions for internal use only
void input();
void update(float dtAsSeconds);
void draw();
