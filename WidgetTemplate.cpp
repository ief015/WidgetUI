#include "WidgetTemplate.hpp"


WidgetTemplate::WidgetTemplate()
{

}


WidgetTemplate::~WidgetTemplate()
{

}



void WidgetTemplate::onUpdate(double dt)
{
	Widget::onUpdate(dt);
}


void WidgetTemplate::onDraw(double scrx, double scry, void* udata)
{
	Widget::onDraw(scrx, scry, udata);
}



void WidgetTemplate::onMouseDown(double x, double y, unsigned int b)
{
	Widget::onMouseDown(x, y, b);
}


void WidgetTemplate::onMouseUp(double x, double y, unsigned int b)
{
	Widget::onMouseUp(x, y, b);
}


void WidgetTemplate::onMouseWheel(double x, double y, int d)
{
	Widget::onMouseWheel(x, y, d);
}


void WidgetTemplate::onMouseMove(double x, double y, double dx, double dy)
{
	Widget::onMouseMove(x, y, dx, dy);
}


void WidgetTemplate::onKeyDown(int key)
{
	Widget::onKeyDown(key);
}


void WidgetTemplate::onKeyUp(int key)
{
	Widget::onKeyUp(key);
}


void WidgetTemplate::onKeyText(unsigned int ch)
{
	Widget::onKeyText(ch);
}



void WidgetTemplate::onMove(double dx, double dy)
{

}


void WidgetTemplate::onResize()
{

}


void WidgetTemplate::onPress(double x, double y, unsigned int b)
{
	
}


void WidgetTemplate::onRelease(double x, double y, unsigned int b)
{

}


void WidgetTemplate::onClick(double x, double y, unsigned int b)
{
	
}


void WidgetTemplate::onFocusGained()
{
	
}


void WidgetTemplate::onFocusLost()
{
	
}


void WidgetTemplate::onMouseEnter(double x, double y)
{

}


void WidgetTemplate::onMouseLeave(double x, double y)
{

}


void WidgetTemplate::onAdopt(Widget& child)
{

}


void WidgetTemplate::onDisown(Widget& child)
{

}


void WidgetTemplate::onAdopted(Widget& parent)
{

}


void WidgetTemplate::onDisowned(Widget& parent)
{

}
