#include <iostream>
#include <math.h>

using namespace std;

struct ShapeVtable;           //struct containing the virtual function that will be changed based on the shape

struct Shape                  //that struct represent the class which will be aggregated to it is a substitution to parent class
{
    ShapeVtable* vTable;      //it contains the virtual function
};

struct ShapeVtable
{
    double (*GetArea)(Shape*);      //This function represents all shape area functions based on the parameter Shape* which will be casted based on the shape type
    void (*PrintInfo)(Shape*);      // print shape info.
    void (*Destroy)(Shape*);        // Free shape memory which was allocated
};

double GetArea(Shape* shape)        //An abstract GetArea function
{
    return shape->vTable->GetArea(shape);  //call the virtual function of the shape aggregated class to access the virtual function from the vTable
}

void PrintInfo(Shape* shape) //An abstract PrintInfo function
{
    shape->vTable->PrintInfo(shape); //call the virtual function of the shape aggregated class to access the virtual function from the vTable
}


void ShapeDestroy(Shape* shape)  // An abstract Destroy function
{
    shape->vTable->Destroy(shape); //call the virtual function of the shape aggregated class to access the virtual function from the vTable
}

struct Circle                       //struct that represent the circle class
{
    Shape parent;                   //aggregation with the super class shape which substitutes the inheritance
    int radius;
};

double CircleGetArea(Circle* circle)                    //function that calculates the area of the circle
{
    double pi=3.14;
    double area=pi*circle->radius*circle->radius;       //area= pi*r^2
    return area;
}

void CirclePrintInfo(Circle* circle)          //function that prints the circle info
{
    cout << "Shape Type-> Circle." << endl;
    cout << "Radius of the Circle = " << circle->radius << endl;
    cout << "Area of the Circle= " << CircleGetArea(circle) << endl << endl;
}

void CircleDestroy(Circle* circle)             // Free circle memory which was allocated.
{
    delete circle;
}

ShapeVtable circleTable=                       //the virtual table which contains the overridden abstract GetArea, PrintInfo, ShapeDestroy functions
{
    (double(*)(Shape*)) CircleGetArea,         //casting CircleGetArea function to match the dataType of abstract GetArea function
    (void(*)(Shape*)) CirclePrintInfo,         //casting CirclePrintInfo function to match the dataType of abstract PrintInfo function
    (void(*)(Shape*)) CircleDestroy            //casting CircleDestroy function to match the dataType of abstract ShapeDestroy function
};

void CircleInitialize(Circle* circle, int radius)        //circle constructor
{
    circle->parent.vTable=&circleTable;                  //initialize super class virtual function to the overridden circleGetArea
    circle->radius=radius;                               //initialize the circle radius
}

struct Rectangle          //struct that represent the rectangle class
{
    Shape parent;         //aggregation with the super class shape which substitutes the inheritance
    int height,width;
};

double RectangleGetArea(Rectangle* rectangle)           //function that calculates the area of the rectangle
{
    double area = rectangle->height*rectangle->width;   //area = height*width
    return area;
}

void RectanglePrintInfo(Rectangle* rectangle)       //function that prints the rectangle info
{
    cout << "Shape Type-> Rectangle." << endl;
    cout << "Length of the Rectangle= " << rectangle->height << endl;
    cout << "Width of the Rectangle= " << rectangle->width << endl;
    cout << "Area of the Rectangle= " << RectangleGetArea(rectangle) << endl << endl;
}

void RectangleDestroy(Rectangle* rectangle)        // Free rectangle memory which was allocated.
{
    delete rectangle;
}

ShapeVtable rectangleTable=                       //the virtual table which contains the overridden abstract GetArea, PrintInfo, ShapeDestroy functions
{
    (double(*)(Shape*)) RectangleGetArea,         //casting RectangleGetArea function to match the dataType of abstract GetArea function
    (void (*)(Shape*)) RectanglePrintInfo,        //casting RectanglePrintInfo function to match the dataType of abstract PrintInfo function
    (void (*)(Shape*)) RectangleDestroy           //casting RectangleDestroy function to match the dataType of abstract ShapeDestroy function

};

void RectangleInitialize(Rectangle* rectangle, int height, int width)      //rectangle constructor
{
    rectangle->parent.vTable = &rectangleTable;                //initialize super class virtual function to the overridden RectangleGetArea
    rectangle->height=height;                                  // initialize the rectangle's height and width
    rectangle->width=width;
}

struct Ellipse            //struct that represent the Ellipse class;
{
    Shape parent;         //aggregation with the super class shape which substitutes the inheritance
    int horizontal,vertical;
};
double EllipseGetArea(Ellipse* ellipse)       //function that calculates the area of the Ellipse
{
    double pi=3.14;
    double area=pi*ellipse->horizontal*ellipse->vertical;   //area=pi*horizontal radius*vertical radius
    return area;
}


void EllipsePrintInfo(Ellipse* ellipse)       //function that prints the Ellipse info
{
    cout << "Shape Type-> Ellipse." << endl;
    cout << "Horizontal of the Ellipse= " << ellipse->horizontal << endl;
    cout << "Vertical of the Ellipse= " << ellipse->vertical << endl;
    cout << "Ellipse area = " << EllipseGetArea(ellipse) << endl << endl;
}

void EllipseDestroy(Ellipse* ellipse)         // Free Ellipse memory which was allocated.
{
    delete ellipse;
}

ShapeVtable ellipseTable=                     //the virtual table which contains the overridden abstract GetArea, PrintInfo, ShapeDestroy functions
{
    (double(*)(Shape*)) EllipseGetArea,       //casting EllipseGetArea function to match the dataType of abstract GetArea function
    (void (*) (Shape*)) EllipsePrintInfo,     //casting EllipsePrintInfo function to match the dataType of abstract PrintInfo function
    (void (*) (Shape*)) EllipseDestroy        //casting EllipseDestroy function to match the dataType of abstract ShapeDestroy function

};

EllipseInitialize(Ellipse* ellipse, int X, int Y)    //Ellipse constructor
{
    ellipse->parent.vTable = &ellipseTable;          //initialize super class virtual function to the overridden EllipseGetArea
    ellipse->horizontal=X;                           //initialize the Ellipse's horizontal and vertical
    ellipse->vertical=Y;
}

int main()
{
    Circle circle;
    CircleInitialize(&circle, 10); // circle with radius 10

    Rectangle rectangle;
    RectangleInitialize(&rectangle, 3, 5); // rectangle with width 3 and height 5

    Ellipse ellipse;
    EllipseInitialize(&ellipse, 10, 12); // Ellipse with radius lengths: 10,12

    Shape* shapes[3];
    shapes[0]=(Shape*)&circle;
    shapes[1]=(Shape*)&rectangle;
    shapes[2]=(Shape*)&ellipse;

    double total_area=0;

    int i;
    for(i=0;i<3;i++)
    {
        double d=GetArea(shapes[i]);
        total_area+=d;
        PrintInfo(shapes[i]); // prints (cout) the radius if circle, width and height if rectangle, ... etc
    }
    cout<<total_area<<endl; // check if the value is correct
return 0;
}
