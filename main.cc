#include <GL/gl.h>
#include <GL/glut.h>

#include "qhull.h"

void Resize(int width,int height)
{
  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.,(GLdouble)width/(GLdouble)height,1,100);
}

void sortByConnectPoints(std::vector<Point>& hullPoints)
{
  Point tmp;
  for (int i = 0; i < hullPoints.size() -1; ++i)
  {
    int j= i+ 1;
    for (; j < hullPoints.size(); ++j)
    {
      bool b = false;       
      for (int k = i+1; k < hullPoints.size() && !b; ++k)
        b = (j != k) && SideOfLine(hullPoints[i], hullPoints[j], hullPoints[k]) > 0;
      if(!b) break;
    }
    if(j != i +1)
    {
      tmp = hullPoints[i+1];
      hullPoints[i+1] = hullPoints[j];
      hullPoints[j] = tmp;
    }
  } 
}

void drawQHull()
{
    //Generate and obtain Points
  const size_t number_of_points = 100;
  std::vector<Point> points;
  points.reserve(number_of_points);
  std::vector<Point> hullPoints;

  unsigned int seed(0);
  for(int i=0;i<number_of_points;i++)
  {
    Point pt;
    pt.x = 25 + (rand_r(&seed)%300);
    pt.y = 25 + (rand_r(&seed)%300);

    points.push_back(pt);
  }


  glPointSize(5);

    //Red color for inside points
  glColor3f(1,0,0);
  glBegin(GL_POINTS);
  for(int i=0;i<points.size();i++)
  {
    glVertex2f(points[i].x,points[i].y);
  }
  glEnd();



   // Sort points so that we can find min and max
  std::sort(points.begin(), points.end());
  // Find convex hull points and place them into hullPoints
  QuickHull(points, hullPoints);

  // Save all points to a file
  {
    FILE *fp = fopen("points.csv", "w");
    for (const auto &pt : points) {
      fprintf(fp, "%.1f,%.1f\n", pt.x, pt.y);
    }
    fclose(fp);
  }

  // Save only convex hull points
  {
    FILE *fp = fopen("hull.csv", "w");
    for (const auto &pt : hullPoints) {
      fprintf(fp, "%.1f,%.1f\n", pt.x, pt.y);
    }
    fclose(fp);
  }

  glColor3f(0,1,0);
  glBegin(GL_POINTS);
  for(int i=0;i<hullPoints.size();i++)
  {
    glVertex2f(hullPoints[i].x,hullPoints[i].y);
  }
  glEnd();  
  sortByConnectPoints(hullPoints);
  int j;
  for(int i=0;i<hullPoints.size();++i)
  {
    j = (i+1)%hullPoints.size();
    glLineWidth(2.5);
    glColor3f(0,1,0);
    glBegin(GL_LINES);
    glVertex2f(hullPoints[i].x,hullPoints[i].y);
    glVertex2f(hullPoints[j].x,hullPoints[j].y);
    glEnd();
  }
}

void display()
{
  glLoadIdentity();
  glOrtho( 0,400,400,0,0.0f,100.0f);
  glClearColor( 1,1,1,1);
  glClearDepth( 1.0f);
  glClear(GL_COLOR_BUFFER_BIT |GL_DEPTH_BUFFER_BIT);

    //display the Quick hull process
  drawQHull();

  glutSwapBuffers();
}

int main(int argc,char* argv[])
{
  glutInit(&argc,argv);
  glutInitWindowSize(400,400);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
  glutCreateWindow("Quick Hull 2d Implementation");
  glutDisplayFunc(display);
  glutReshapeFunc(Resize);

  glutMainLoop();
  return 0;
}
