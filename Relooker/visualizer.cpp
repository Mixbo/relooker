#include "visualizer.h"
#include <QPainter>

using namespace std;
Visualizer::Visualizer(QWidget *parent) :
    QWidget(parent)
{
    setMouseTracking(true);

    this->mode = 0;
    this->tdim = NULL;
    this->itemsCol = 16;
    this->itemSize = 5;
}

int Visualizer::getHeight()
{
    int height = 0;

    if(this->mode == 1)
    {
        if(this->tdim)
        {
            int size = this->tdim->getSize();       
            height = size/this->itemsCol*this->itemSize+50;
        }
    }
    return height;
}

void Visualizer::setMode(int mode)
{
    this->mode = mode;
}

void Visualizer::paintEvent(QPaintEvent *)
{
    switch(this->mode)
    {
            case 0:
                    this->paintDefault();
                    break;
            case 1:
                    this->paintTwoD();
                    break;
    } 
}
void Visualizer::mouseMoveEvent(QMouseEvent* event)
{
    int x = event->x();
    int y = event->y();
    //cout << x << ":" << y << endl;
    int index = x/5 + y/5*16;
    //cout << index<<endl;
    this->index = index;
}

int Visualizer::getIndex()
{
    return this->index;
}

void Visualizer::set2(TwoDimension* tdim)
{
    this->tdim = tdim;
}

void Visualizer::paintDefault()
{
    QPainter painter(this);
    QPen framepen(Qt::red);
    framepen.setWidth(1);

    painter.setPen(framepen);
    painter.setBrush(Qt::red);
    painter.drawRect(1,1,5,5);
}

void Visualizer::paintTwoD()
{
    if(this->tdim)
    {
        int * items = this->tdim->getRange();
        int size = this->tdim->getSize();
        //this->resize(this->width(),size/itemsCol*itemSize+50);//size/itemsCol*itemSize+10);

        QPainter painter(this);
        QPen framepen(Qt::black);
        framepen.setWidth(1);
        for(int i = 0;i< size;++i)
        {
           switch(items[i])
           {
                case 0:
                        framepen.setColor(Qt::black);
                        painter.setBrush(Qt::black);
                        break;
                case 1:
                        framepen.setColor(Qt::white);
                        painter.setBrush(Qt::white);
                        break;
                case 2:
                        framepen.setColor(Qt::blue);
                        painter.setBrush(Qt::blue);
                        break;
                case 3:
                        framepen.setColor(Qt::green);
                        painter.setBrush(Qt::green);
                        break;
                case 4:
                        framepen.setColor(Qt::magenta);
                        painter.setBrush(Qt::magenta);
                        break;
           }
           painter.setPen(framepen);
           painter.drawRect(i%this->itemsCol * this->itemSize /*+ 2*i%itemsCol*/,i/this->itemsCol*this->itemSize,this->itemSize,this->itemSize);
        }

        //this->resize(this->width(),size/itemsCol*itemSize+50);//size/itemsCol*itemSize+10);
        //this->update();
    }
}