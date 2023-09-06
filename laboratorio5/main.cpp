#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

struct Point
{
			int x;
			int y;
};

class Shape
{
			public:
						class NoPointsException{};
						class NoShapeException{};
						Point point(int i) const;
						int number_of_points() const{ return points.size(); }
						Shape(const Shape& arg)=delete;
						Shape& operator=(const Shape& arg)=delete;
						virtual double area()=0;//<---funziona mettendola virtuale pura
						virtual ~Shape(){}
			protected:
						Shape(){}
						Shape(initializer_list<Point> ls)
						{
									for(initializer_list<Point>::iterator iter=ls.begin(); iter!=ls.end();iter++)
									{
												Point p;
												p.x=iter->x;
												p.y=iter->y;
												points.push_back(p);
									}
						}
						void add(Point p){ points.push_back(p);}
						void set_point(int i, Point p){ points[i]=p;}
			private:
						vector<Point> points;
};


Point Shape::point(int i) const
{
			if(points.size()>0)
						return points[i];
			throw new NoPointsException();
}

class Rectangle : public Shape
{
			public:
						class NoRectangleEception{};
						Rectangle(initializer_list<Point> ls):Shape::Shape(ls)
						{	}
						double area() override
						{	
									if(number_of_points()!=4)
												{	throw new NoRectangleEception(); }

									Point p1=point(0);
									Point p2=point(1);
									int x2=(p2.x-p1.x)*(p2.x-p1.x);
									int y2=(p2.y-p1.y)*(p2.y-p1.y);
									int b= sqrt(x2+y2);
									p1=point(1);
									p2=point(2);
									x2=(p2.x-p1.x)*(p2.x-p1.x);
									y2=(p2.y-p1.y)*(p2.y-p1.y);
									int h= sqrt(x2+y2);
									return b*h;
						}
						~Rectangle(){}
};

class Square : public Shape
{
			public:
						class NoSquareleEception{};
						Square(initializer_list<Point> ls):Shape(ls)
						{	}
						double area() override
						{	
									if(number_of_points()!=4)
									{	throw new NoSquareleEception(); }

												Point p1=point(0);
												Point p2=point(1);
												int x2=(p2.x-p1.x)*(p2.x-p1.x);
												int y2=(p2.y-p1.y)*(p2.y-p1.y);
												int l= sqrt(x2+y2);
												return l*l;
						}
						~Square(){}
};

class Circle : public Shape
{
			public:
						Circle(int R)
						{	r=R;}
						double area() override
						{	
									const double pi=3.14;
									return pi*r*r ;
						}
						~Circle(){}
			private:
						int r;
};

int main(void)
{
			//il costruttore protetto di default ci deve sempre essere
			//warning se si invocano if senza {} di una sola riga
			Point p1;
			p1.x=0;
			p1.y=0;
			Point p2;
			p2.x=4;
			p2.y=0;
			Point p3;
			p3.x=4;
			p3.y=2;
			Point p4;
			p4.x=0;
			p4.y=2;
			Rectangle r1={p1,p2,p3,p4};
			cout<<"L'area è: "<<r1.area()<<"\n";
			p1.x=0;
			p1.y=0;
			p2.x=4;
			p2.y=0;
			p3.x=4;
			p3.y=4;
			p4.x=0;
			p4.y=4;
			Square s1={p1,p2,p3,p4};
			cout<<"L'area è: "<<s1.area()<<"\n";
			Circle c1(2);
			cout<<"L'area è: "<<c1.area()<<"\n";
			
			return 0;
}
