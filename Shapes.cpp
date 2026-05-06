// Names and IDs:
// Bassam Yasser - 20230089
// Mohamed Ashraf - 20230321
// Mariam Ayman - 20230390
// Samaa Mehrez - 20230177

#include <iostream>
#include <cmath>

using namespace std;

// base struct (behavior holder)
struct Shape
{
    double (*GetAreaPtr)(Shape*);
    void (*PrintInfoPtr)(Shape*);
};

// Global interface functions trigger the dynamic call
double GetArea(Shape* s)
{
    return s->GetAreaPtr(s);
}

void PrintInfo(Shape* s)
{
    s->PrintInfoPtr(s);
}

//  Circle Logic 
struct Circle
{
    Shape parent; 
    double radius;
};

double CircleArea(Circle* c)
{
    return 3.14159265358979 * (c->radius * c->radius);
}

void CircleDisplay(Circle* c)
{
    cout << "radius: " << c->radius << endl;
}

void CircleInitialize(Circle* c, double r)
{
    c->radius = r;
    // Bind logic to the base interface pointers
    c->parent.GetAreaPtr = (double (*)(Shape*)) CircleArea;
    c->parent.PrintInfoPtr = (void (*)(Shape*)) CircleDisplay;
}

//  Rectangle Logic 
struct Rectangle
{
    Shape parent;
    double w, h; 
};

double RectArea(Rectangle* r)
{
    return r->w * r->h;
}

void RectDisplay(Rectangle* r)
{
    cout << "width: " << r->w << ", height: " << r->h << endl;
}

void RectangleInitialize(Rectangle* r, double width, double height)
{
    r->w = width;
    r->h = height;
    r->parent.GetAreaPtr = (double (*)(Shape*)) RectArea;
    r->parent.PrintInfoPtr = (void (*)(Shape*)) RectDisplay;
}

//  Ellipse Logic 
struct Ellipse
{
    Shape parent;
    double major, minor; 
};

double EllipseArea(Ellipse* e)
{
    return 3.14159265358979 * e->major * e->minor;
}

void EllipseDisplay(Ellipse* e)
{
    cout << "radius1: " << e->major << ", radius2: " << e->minor << endl;
}

void EllipseInitialize(Ellipse* e, double r1, double r2)
{
    e->major = r1;
    e->minor = r2;
    e->parent.GetAreaPtr = (double (*)(Shape*)) EllipseArea;
    e->parent.PrintInfoPtr = (void (*)(Shape*)) EllipseDisplay;
}

//  Square Logic 
struct Square
{
    Shape parent;
    double sideLen;
};

double SquareArea(Square* s)
{
    return s->sideLen * s->sideLen;
}

void SquareDisplay(Square* s)
{
    cout << "side-length: " << s->sideLen << endl;
}

void SquareInitialize(Square* s, double len)
{
    s->sideLen = len;
    s->parent.GetAreaPtr = (double (*)(Shape*)) SquareArea;
    s->parent.PrintInfoPtr = (void (*)(Shape*)) SquareDisplay;
}

int main()
{
    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10

    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); // rectangle with width 3 and height 5

    Ellipse ellipse;
    EllipseInitialize(&ellipse, 10, 12); // ellipse with radius 10, 12

    Square square;
    SquareInitialize(&square, 7); // square with side-length 7
    
    Circle c2;
    CircleInitialize(&c2, 1.5); // circle with radius 1.5
    
    Circle c3;
    CircleInitialize(&c3, 0.25); // circle with radius 0.25

    Rectangle r2;
    RectangleInitialize(&r2, 10, 10); // A rectangle that is a square width 10 and height 10
    
    Rectangle r3;
    RectangleInitialize(&r3, 0.5, 2.0); // A rectangle with width 0.5 and height 2.0

    Ellipse e2; 
    EllipseInitialize(&e2, 5, 5);  // An ellipse that is a circle with radius 5,5
    
    Ellipse e3; 
    EllipseInitialize(&e3, 1, 10); // An ellipse with radius 1,10

    Square s2; 
    SquareInitialize(&s2, 12.5); // square with side-length 12.5
    
    Square s3; 
    SquareInitialize(&s3, 1); // square with side-length 1
    
    Shape* shapes[12];
    shapes[0]  = (Shape*)&circle;
    shapes[1]  = (Shape*)&rectangle;
    shapes[2]  = (Shape*)&ellipse;
    shapes[3]  = (Shape*)&square;
    shapes[4]  = (Shape*)&c2;
    shapes[5]  = (Shape*)&c3;
    shapes[6]  = (Shape*)&r2;
    shapes[7]  = (Shape*)&r3;
    shapes[8]  = (Shape*)&e2;
    shapes[9]  = (Shape*)&e3;
    shapes[10] = (Shape*)&s2;
    shapes[11] = (Shape*)&s3;

    double total_area=0;

    int i;
    for(i=0;i<12;i++)
    {
        double d=GetArea(shapes[i]);
        total_area+=d;
        PrintInfo(shapes[i]); // prints (cout) the radius if circle, width and height if rectangle, ... etc
    }
    
    cout<<total_area<<endl; // check if the value is correct

    return 0;
}
