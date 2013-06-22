#ifndef _WIDGETTEMPLATE_HPP_INCLUDED
#define _WIDGETTEMPLATE_HPP_INCLUDED

#include <Widget.hpp>

/*********************************************************************
 * This is a basic sample widget that works with the Widget system.  *
 *********************************************************************/


class WidgetTemplate : public Widget
{
private:


public:
	WidgetTemplate();
	virtual ~WidgetTemplate();

protected:
	virtual void onUpdate(double dt);
	virtual void onDraw(double scrx, double scry, void* udata = NULL);

	virtual void onMouseDown(double x, double y, unsigned int b);
	virtual void onMouseUp(double x, double y, unsigned int b);
	virtual void onMouseWheel(double x, double y, int d);
	virtual void onMouseMove(double x, double y, double dx, double dy);
	virtual void onKeyDown(int key);
	virtual void onKeyUp(int key);
	virtual void onKeyText(unsigned int ch);

	virtual void onMove(double dx, double dy);
	virtual void onResize();
	virtual void onPress(double x, double y, unsigned int b);
	virtual void onRelease(double x, double y, unsigned int b);
	virtual void onClick(double x, double y, unsigned int b);
	virtual void onFocusGained();
	virtual void onFocusLost();
	virtual void onMouseEnter(double x, double y);
	virtual void onMouseLeave(double x, double y);
	virtual void onAdopt(Widget& child);
	virtual void onDisown(Widget& child);
	virtual void onAdopted(Widget& parent);
	virtual void onDisowned(Widget& parent);

};

#endif