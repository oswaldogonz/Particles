#include "Particle.h"

#define M_PI 3.1415926535897932384626433
const float G = 1000; //Gravity
const float TTL = 5.0; //Time To Live
const float SCALE = 0.999;
using namespace Matrices;
using namespace sf;


Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition): m_A(2, numPoints)
{
  m_ttl=TTL;
  m_numPoints=numPoints;
  m_radiansPerSec=(float)rand()/(RAND_MAX)*PI;
  m_cartesianPlane.setCenter(0,0);
  m_cartesianPlane.setSize(target.getSize().x, (-1.0) * target.getSize().y);
  m_centerCoordinate=target.mapPixelToCoords(mouseClickPosition, m_cartesianPlane);
  m_vx=rand()%401+100;
  m_vy=rand()%401+100;
  m_color1=Color::White;
  m_color2=Color::White;//maybe change

  theta=(float)rand()/(RAND_MAX)*(PI/2);
  dTheta=2*PI/(numPoints-1);
  for(int j=0;j<numPoints;j++)
  {
    int r=rand()%61+20;
    int dx=r*cos(theta);
    int dy=r*sin(theta)
    m_A(0,j)=m_centerCoordinate.x+dx;
    m_A(1,j)=m_centerCoordinate.y+dy;
    theta+=dThat;
  } 
}

virtual void draw(RenderTarget& target, RenderStates states) const override
{
}
This function overrides the virtual function from sf::Drawable to allow our draw function to polymorph
To draw, we will convert our Cartesian matrix coordinates from m_A to pixel coordinates in a VertexArray of primitive type TriangleFan
Take a look at the SFML tutorial regarding the TriangleFanLinks to an external site. and refer to the picture below:
Triangle fan diagram

Construct a VertexArray named lines
Its arguments are TriangleFan, and the number of points numPoints + 1
The + 1 is to account for the center as shown above
Declare a local Vector2f named center
This will be used to store the location on the monitor of the center of our particle
Assign it with the mapping of m_centerCoordinate from Cartesian to pixel / monitor coordinates using target.mapCoordsToPixelLinks to an external site.
Don't forget to pass m_cartesianPlane in as an argument!
Assign lines[0].position with center
Assign lines[0].color with m_color
This will assign m_color to the center of our particle.  If the outer colors are different, the engine will automatically create a cool looking smooth color gradient between the two colors
Loop j from 1 up to and including m_numPoints
Note that the index in lines is 1-off from the index in m_A because lines must contain the pixel coordinate for the center as its first element
Assign lines[j].position with the coordinate from column j - 1 in m_A, mapped from Cartesian to pixel coordinates using target.mapCoordsToPixelLinks to an external site.
Don't forget to pass m_cartesianPlane in as an argument!
Assign lines[j].color with m_Color2
When the loop is finished, draw the VertexArray:
target.draw(lines)
    void update(float dt);
    float getTTL() { return m_ttl; }
    //Functions for unit testing
    bool almostEqual(double a, double b, double eps = 0.0001);
    void unitTests();
  
    ///rotate Particle by theta radians counter-clockwise
    ///construct a RotationMatrix R, left mulitply it to m_A
    void rotate(double theta);
    ///Scale the size of the Particle by factor c
    ///construct a ScalingMatrix S, left multiply it to m_A
    void scale(double c);
    ///shift the Particle by (xShift, yShift) coordinates
    ///construct a TranslationMatrix T, add it to m_A
    void translate(double xShift, double yShift);
};
bool Particle::almostEqual(double a, double b, double eps)
{
  return fabs(a - b) < eps;
}
void Particle::unitTests()
{
  int score = 0;
  cout << "Testing RotationMatrix constructor...";
  double theta = M_PI / 4.0;
  RotationMatrix r(M_PI / 4);
  if (r.getRows()==2 && r.getCols()==2 && almostEqual(r(0,0), cos(theta)) && almostEqual(r(0, 1), -sin(theta)) && almostEqual(r(1,0), sin(theta)) && almostEqual(r(1,1), cos(theta)))
  {
    cout << "Passed. +1" << endl;
    score++;
  }
  else
  {
    cout << "Failed." << endl;
  }
  cout << "Testing ScalingMatrix constructor...";
  ScalingMatrix s(1.5);
  if (s.getRows()==2 && s.getCols()==2 && almostEqual(s(0, 0), 1.5) && almostEqual(s(0, 1), 0) && almostEqual(s(1, 0), 0) && almostEqual(s(1, 1), 1.5))
  {
    cout << "Passed. +1" << endl;
    score++;
  }
  else
  {
    cout << "Failed." << endl;
  }
  cout << "Testing TranslationMatrix constructor...";
  TranslationMatrix t(5, -5, 3);
  if(t.getRows()==2&&t.getCols()==3&&almostEqual(t(0,0),5)&&almostEqual(t(1,0),-5) && almostEqual(t(0,1),5) && almostEqual(t(1,1),-5) && almostEqual(t(0,2),5) && almostEqual(t(1,2),-5))
  {
    cout << "Passed. +1" << endl;
    score++;
  }
  else
  {
    cout << "Failed." << endl;
  }
  cout << "Testing Particles..." << endl;
  cout << "Testing Particle mapping to Cartesian origin..." << endl;
  if (m_centerCoordinate.x != 0 || m_centerCoordinate.y != 0)
  {
    cout << "Failed. Expected (0,0). Received: (" << m_centerCoordinate.x << "," << m_centerCoordinate.y << ")" << endl;
  }
  else
  {
    cout << "Passed. +1" << endl;
    score++;
  }
  cout << "Applying one rotation of 90 degrees about the origin..." << endl;
  Matrix initialCoords = m_A;
  rotate(M_PI / 2.0);
  bool rotationPassed = true;
  for (int j = 0; j < initialCoords.getCols(); j++)
  {
    if (!almostEqual(m_A(0, j), -initialCoords(1, j)) || !almostEqual(m_A(1,j), initialCoords(0, j)))
    {
      cout << "Failed mapping: ";
      cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
      rotationPassed = false;
    }
  }
  if (rotationPassed)
  {
    cout << "Passed. +1" << endl;
    score++;
  }
  else
  {
    cout << "Failed." << endl;
  }
  cout << "Applying a scale of 0.5..." << endl;
  initialCoords = m_A;
  scale(0.5);
  bool scalePassed = true;
  for (int j = 0; j < initialCoords.getCols(); j++)
  {
    if (!almostEqual(m_A(0, j), 0.5 * initialCoords(0,j)) || !almostEqual(m_A(1, j), 0.5 * initialCoords(1, j)))
    {
      cout << "Failed mapping: ";
      cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
      scalePassed = false;
    }
  }
  if (scalePassed)
  {
    cout << "Passed. +1" << endl;
    score++;
  }
  else
  {
    cout << "Failed." << endl;
  }
  cout << "Applying a translation of (10, 5)..." << endl;
  initialCoords = m_A;
  translate(10, 5);
  bool translatePassed = true;
  for (int j = 0; j < initialCoords.getCols(); j++)
  {
    if (!almostEqual(m_A(0, j), 10 + initialCoords(0, j)) || !almostEqual(m_A(1, j), 5 + initialCoords(1, j)))
    {
      cout << "Failed mapping: ";
      cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
      translatePassed = false;
    }
  }
  if (translatePassed)
  {
    cout << "Passed. +1" << endl;
    score++;
  }
  else
  {
    cout << "Failed." << endl;
  }
  cout << "Score: " << score << " / 7" << endl;
}
