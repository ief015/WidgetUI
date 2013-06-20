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

	virtual void onMouseDown(int x, int y, unsigned int b);
	virtual void onMouseUp(int x, int y, unsigned int b);
	virtual void onMouseWheel(int x, int y, int d);
	virtual void onMouseMove(int x, int y, int dx, int dy);
	virtual void onKeyDown(int key);
	virtual void onKeyUp(int key);
	virtual void onKeyText(unsigned int ch);

	virtual void onMove(double dx, double dy);
	virtual void onResize();
	virtual void onPress(int x, int y, unsigned int b);
	virtual void onRelease(int x, int y, unsigned int b);
	virtual void onClick(int x, int y, unsigned int b);
	virtual void onFocusGained();
	virtual void onFocusLost();
	virtual void onMouseEnter(int x, int y);
	virtual void onMouseLeave(int x, int y);
	virtual void onAdopt(Widget& child);
	virtual void onDisown(Widget& child);
	virtual void onAdopted(Widget& parent);
	virtual void onDisowned(Widget& parent);

};

#endif