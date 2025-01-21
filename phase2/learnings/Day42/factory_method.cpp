#include <iostream>
#include <memory>

class shape{
    public:
    virtual void draw()=0;
    virtual ~shape(){}

};
class circle : public shape{
    public:
       void draw() override{
        std::cout << "drawing a circle \n";
       }
       };
class rectangle : public shape{
    public:
    void draw() override{
        std::cout << "drawing a  rectangle \n";
        }
    };

    class shapefactory{
    public:
    static shape* createshape(const std::string& type){
    if(type == "circle")
        return new circle();
        if(type == "rectangle")
        return new rectangle();
        return nullptr;
        }
        };
    int main (){
    std::string shapetype;
    std::cout << "enter the shape type (circle/rectangle):";
    std::cin>> shapetype;
    shape* shape = shapefactory::createshape(shapetype);
    if(shape){
    shape->draw();
    delete shape;
    }
    else
    {
       std::cout << "invalid shape type\n";

    }
    return 0;
    }
