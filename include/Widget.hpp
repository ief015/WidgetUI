/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  Widget.hpp                                                                       *
 *  Simple hierarchy-style UI widget system.                                         *
 *                                                                                   *
 *  Authors: Nathan Cousins                                                          *
 *  Last Update: Jun 19, 2013                                                        *
 *                                                                                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                                   *
 *	Copyright © 2013 Nathan Cousins                                                  *
 *                                                                                   *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy     *
 *  of this software and associated documentation files (the “Software”), to deal    *
 *  in the Software without restriction, including without limitation the rights     *
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell        *
 *  copies of the Software, and to permit persons to whom the Software is            *
 *  furnished to do so, subject to the following conditions:                         *
 *                                                                                   *
 *  The above copyright notice and this permission notice shall be included in       *
 *  all copies or substantial portions of the Software.                              *
 *                                                                                   *
 *  THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS          *
 *  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      *
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE      *
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER           *
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,    *
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN        *
 *  THE SOFTWARE.                                                                    *
 *                                                                                   *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

 
#ifndef _WIDGET_HPP_INCLUDED
#define _WIDGET_HPP_INCLUDED

#include <vector>


class Widget
{
private:
	std::vector<Widget*> m_widgets; /* Back-most widget is focused and/or top. */
	Widget* m_parent;
	
	bool m_down;
	unsigned int m_downBtn;
	bool m_testInsideChild;
	Widget* m_hover;
	int m_mouseX, m_mouseY;
	bool m_hidden;
	
protected:
	
	// These are protected so Widget classes can work with these internally.
	// Modifying these will not call onMove/onResize, you must call these events manually when appropriate.
	double x, y, width, height;
	
public:
	
	/* *** Contruction/Deconstruction *** */
	
	Widget()
	: m_parent(NULL)
	, m_hover(NULL)
	, m_down(false)
	, m_downBtn(0)
	, m_hidden(false)
	{
		x = 0.; y = 0.;
		width = 0.; height = 0.;
		m_mouseX = 0; m_mouseY = 0;
	}
	
	
	virtual ~Widget()
	{
		
	}
	
	
	/* *** Transformation *** */
	
	void move(double movex, double movey)
	{
		x += movex;
		y += movey;
	
		this->onMove(movex, movey);
	}
	
	void setPosition(double posx, double posy)
	{
		double oldx = x, oldy = y;
		x = posx;
		y = posy;
	
		this->onMove(x - oldx, y - oldy);
	}
	
	inline void getPosition(double& out_x, double& out_y) const
	{
		out_x = x;
		out_y = y; 
	}
	
	inline double getPositionX() const
	{
		return x;
	}
	
	inline double getPositionY() const
	{
		return y;
	}
	
	
	void setSize(double sizewidth, double sizeheight)
	{
		width = sizewidth;
		height = sizeheight;
		
		this->onResize();
	}
	
	inline void getSize(double& out_width, double& out_height) const
	{
		out_width = width;
		out_height = height;
	}
	
	inline double getWidth() const
	{
		return width;
	}
	
	inline double getHeight() const
	{
		return height;
	}
	
	
	/* *** Visibility *** */
	
	// Check if we're hidden or if our parents are hidden.
	bool isHidden() const
	{
		const Widget* cur = this;
		
		// Check if we're hidden, or if our higher-level parents are hidden.
		do
		{
			if (cur->m_hidden)
				return true;
			
			// Process the next parent.
			cur = cur->m_parent;
		}
		while (cur);
		
		return false;
	}
	
	// Hide this widget and children.
	void hide(bool hidden = true)
	{
		m_hidden = hidden;
	}
	
	
	/* *** Modify children *** */
	
	// Add a child widget to this widget.
	void addWidget(Widget* widget)
	{
		// Push the new child to the back. (It will become the focused widget)
		m_widgets.push_back(widget);
		widget->m_parent = this;
		
		// Call widget Adopt events.
		this->onAdopt(*widget);
		widget->onAdopted(*this);
	}
	
	// Remove a child widget from this widget.
	bool removeWidget(Widget* widget)
	{
		Widget* child;
		
		// Find widget.
		for (size_t i = m_widgets.size(); i--;)
		{
			child = m_widgets[i];
			if (child == widget)
			{
				// Remove it from children.
				child->m_parent = NULL;
				m_widgets.erase(m_widgets.begin() + i);
				
				// Call widget Disown events.
				this->onDisown(*child);
				child->onDisowned(*this);
				
				return true;
			}
		}
		
		return false;
	}
	
	// Check if this widget parents a specific child widget.
	bool hasWidget(const Widget& widget) const
	{
		// Find widget.
		for (size_t i = m_widgets.size(); i--;)
		{
			if (m_widgets[i] == &widget)
				return true;
		}
		
		return false;
	}
	
	
	/* *** Widget parent *** */
	
	// Does this widget have a parent?
	bool hasParent() const
	{
		return m_parent != NULL;
	}
	
	// Returns the parent widget. Returns NULL if no parent.
	Widget* getParent()
	{
		return m_parent;
	}
	
	// Returns the parent widget. Returns NULL if no parent.
	const Widget* getParent() const
	{
		return m_parent;
	}
	
	
	/* *** Widget children *** */
	
	// Does this widget contain children widgets?
	bool hasChildren() const
	{
		return m_widgets.size() > 0;
	}
	
	// Get a child as specific index. Index must valid (in bounds).
	Widget* getChild(size_t idx)
	{
		return m_widgets[idx];
	}
	
	// Get a child as specific index. Index must valid (in bounds).
	const Widget* getChild(size_t idx) const
	{
		return m_widgets[idx];
	}
	
	// Get the number of children this widget parents.
	size_t getNumOfChildren() const
	{
		return m_widgets.size();
	}
	
	
	/* *** Widget focus *** */
	
	// Force child at index to be the focused widget. This function does nothing if index is not valid (not in bounds).
	void setFocus(size_t idx)
	{
		Widget* widget;
		
		if (idx >= m_widgets.size())
			return;
		
		widget = m_widgets[idx];
		
		// Don't do anything if widget is already focused.
		if (widget->isFocusedChild())
			return;
		
		// Make it the focused object.
		m_widgets.push_back(widget);
		m_widgets.erase(m_widgets.begin()+idx);
		
		// Call lost/gained focus events.
		m_widgets[m_widgets.size()-2]->onFocusLost();
		widget->onFocusGained();
	}
	
	// Force child to be the focused widget. The child must be a child of this widget, else this function does nothing.
	void setFocus(const Widget* child)
	{
		Widget* widget;
		
		// Find child.
		for (size_t i = m_widgets.size(); i--;)
		{
			widget = m_widgets[i];
			
			if (widget == child)
			{
				// Don't do anything if widget is already focused.
				if (widget->isFocused())
					return;
				
				// Make it the focused object.
				m_widgets.push_back(widget);
				m_widgets.erase(m_widgets.begin()+i);
				
				// Call lost/gained focus events.
				m_widgets[m_widgets.size()-2]->onFocusLost();
				widget->onFocusGained();
			}
		}
	}
	
	// Get the focused child. Returns NULL if no children are present.
	Widget* getFocused()
	{
		// Return NULL if empty.
		if (m_widgets.empty())
			return NULL;
		
		// The back widget is the focused component.
		return m_widgets.back();
	}
	
	// Get the focused child. Returns NULL if no children are present.
	const Widget* getFocused() const
	{
		// Return NULL if empty.
		if (m_widgets.empty())
			return NULL;
		
		// The back widget is the focused component.
		return m_widgets.back();
	}
	
	// Is this widget the focused widget of the parent? Always returns true if no parent is present.
	bool isFocused() const
	{
		const Widget* cur = this;
		
		do
		{
			if (cur->isFocusedChild())
			{
				// Process the parent if this is the focused child.
				cur = cur->m_parent;
			}
			else
			{
				// Always return false if this is not the focused child.
				return false;
			}
		}
		while (cur);
		
		// Always return true if there's no parent.
		return true;
	}
	
	// Is this widget the focused widget of the parent? Always returns true if no parent is present.
	bool isFocusedChild() const
	{
		// Check if we're the parent's focused child.
		if (m_parent)
			return m_parent->getFocused() == this;
		
		// Always return true if no parent.
		return true;
	}
	
	// Try to pop this widget out of focus and make the next sibling widget in focus instead.
	void popFocus()
	{
		// This should be the focused child.
		if (!this->isFocusedChild())
			return;
		
		// Can't pop if there is no parent.
		if (!m_parent)
			return;
		
		// Can't pop if this is the only child.
		if (m_parent->m_widgets.size() < 2)
			return;
		
		// Set the second child into focus.
		m_parent->setFocus(m_parent->m_widgets.size()-2);
	}
	
	
	/* *** Mouse interactivity *** */
	
	// Is the mouse holding this widget? Optionally, it will return which mouse button is holding the widget down via `btn'.
	bool isHeldDown(unsigned int* btn = NULL) const
	{
		if (m_down)
		{
			*btn = m_downBtn;
			return true;
		}
		return false;
	}
	
	// Is the mouse hovering over this widget?
	bool isMouseHovering() const
	{
		// Check if the hovering component is this widget.
		if (m_parent)
			return m_parent->m_hover == this;
		
		// Always return false if no m_parent.
		return false;
	}
	
	// Get the relative mouse position.
	int getRelativeMouseX() const
	{
		return m_mouseX;
	}
	
	// Get the relative mouse position.
	int getRelativeMouseY() const
	{
		return m_mouseY;
	}
	
	// Get relative mouse position.
	void getRelatieMousePos(int& x, int& y) const
	{
		x = m_mouseX;
		y = m_mouseY;
	}
	
	
	/* *** Invoke events *** */
	
	// Update this and child widgets.
	void update(double dt)
	{
		this->onUpdate(dt);
	}
	
	// Render this and child widgets.
	void draw(void* udata = NULL)
	{
		this->onDraw(this->x, this->y, udata);
	}
	
	// Call this to invoke Mouse-Down related events.
	// Mouse positions [x, y] must be relative to the position of the widget.
	void mouseDown(int x, int y, unsigned int b)
	{
		if (m_hidden)
			return;
		
		this->onMouseDown(x, y, b);
		
		if (m_testInsideChild)
			return;
		
		if (static_cast<double>(x) >= this->x && static_cast<double>(x) < this->x + this->width &&
			static_cast<double>(y) >= this->y && static_cast<double>(y) < this->y + this->height )
		{
			// Widget is being held down.
			if (!m_down)
			{
				m_down = true;
				m_downBtn = b;
			}
			
			// Mouse pressed.
			this->onPress(static_cast<int>(x - this->x),  static_cast<int>(y - this->y), b);
		}
	}
	
	// Call this to invoke Mouse-Up related events.
	// Mouse positions [x, y] must be relative to the position of the widget.
	void mouseUp(int x, int y, unsigned int b)
	{
		if (m_hidden)
			return;
		
		this->onMouseUp(x, y, b);
		
		if (m_down && m_downBtn == b)
		{
			// No longer held down.
			m_down = false;
			
			// Mouse released this widget.
			this->onRelease(static_cast<int>(x - this->x), static_cast<int>(y - this->y), b);
			
			if (m_testInsideChild)
				return;
			
			// Check if mouse was inside.
			if (static_cast<double>(x) >= this->x && static_cast<double>(x) < this->x + this->width &&
				static_cast<double>(y) >= this->y && static_cast<double>(y) < this->y + this->height )
			{
				// Widget was clicked.
				this->onClick(static_cast<int>(x - this->x), static_cast<int>(y - this->y), b);
			}
		}
	}
	
	// Call this to invoke Mouse-Wheel related events.
	// Mouse positions [x, y] must be relative to the position of the widget.
	void mouseWheel(int x, int y, int d)
	{
		this->onMouseWheel(x, y, d);
	}
	
	// Call this to invoke Mouse-Move related events.
	// Mouse positions [x, y] must be relative to the position of the widget.
	void mouseMove(int x, int y, int dx, int dy)
	{
		this->onMouseMove(x, y, dx, dy);
	}
	
	
	// Call this to invoke Key-Down related events.
	void keyDown(int key)
	{
		this->onKeyDown(key);
	}
	
	// Call this to invoke Key-Up related events.
	void keyUp(int key)
	{
		this->onKeyUp(key);
	}
	
	// Call this to invoke Key-Text related events.
	void keyText(unsigned int ch)
	{
		this->onKeyText(ch);
	}
	
protected:
	
	
	/* *** Widget events *** */
	
	// When the widget updates.
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onUpdate(double dt)
	{
		Widget* widget;
		
		// Check for mouse entering/leaving.
		bool hovering = false;
		for (size_t i = m_widgets.size(); i--;)
		{
			widget = m_widgets[i];
			
			if (static_cast<double>(m_mouseX) >= widget->x && static_cast<double>(m_mouseX) < widget->x + widget->width &&
				static_cast<double>(m_mouseY) >= widget->y && static_cast<double>(m_mouseY) < widget->y + widget->height )
			{
				hovering = true;
				
				// If mouse is already hovering, no need to do anything.
				if (m_hover == widget)
					break;
				
				// Change mouse hover to new widget.
				Widget* oldHover = m_hover;
				m_hover = widget;
				
				// Call widget events.
				if (oldHover)
					oldHover->onMouseLeave(m_mouseX, m_mouseY);
				
				widget->onMouseEnter(m_mouseX, m_mouseY);
				
				break;
			}
		}
		
		// If not hovering over anything, leave old hover widget (if any.)
		if (!hovering && this->m_hover)
		{
			m_hover->onMouseLeave(m_mouseX, m_mouseY);
			m_hover = NULL;
		}
		
		// Update all children.
		for (size_t i = 0, sz = m_widgets.size(); i < sz; ++i)
			m_widgets[i]->onUpdate(dt);
	}
	
	// When the widget is supposed to be rendered.
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onDraw(double scrx, double scry, void* udata = NULL)
	{
		if (m_hidden)
			return;
		
		Widget* widget;
		
		// Draw all children.
		for (size_t i = 0, sz = m_widgets.size(); i < sz; ++i)
		{
			widget = m_widgets[i];
			
			if (!widget->m_hidden)
				widget->onDraw(widget->x + scrx, widget->y + scry, udata);
		}
	}
	
	// When a mouse button is down.
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onMouseDown(int x, int y, unsigned int b)
	{
		if (m_hidden)
			return;
		
		Widget* widget;
		
		m_testInsideChild = false;
		
		// Send mouse-down signal to all children.
		for (size_t i = m_widgets.size(); i--;)
		{
			widget = m_widgets[i];
			widget->onMouseDown(static_cast<int>(x - widget->x), static_cast<int>(y - widget->y), b);
		}
		
		// Check for any mouse-downs inside of an object.
		// When found, push to the back, making it the focused widget.
		for (size_t i = m_widgets.size(); i--;)
		{
			widget = m_widgets[i];
			
			if (widget->m_hidden)
				continue;
			
			if (static_cast<double>(x) >= widget->x && static_cast<double>(x) < widget->x + widget->width &&
				static_cast<double>(y) >= widget->y && static_cast<double>(y) < widget->y + widget->height )
			{
				m_testInsideChild = true;
				
				// Widget is being held down.
				if (!widget->m_down)
				{
					widget->m_down = true;
					widget->m_downBtn = b;
				}
				
				// Make this widget the focused child.
				this->setFocus(i);
				
				if (!widget->m_testInsideChild)
				{
					// Mouse pressed.
					widget->onPress(static_cast<int>(x - widget->x),  static_cast<int>(y - widget->y), b);
				}
				
				break;
			}
		}
	}
	
	// When a mouse button is up.
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onMouseUp(int x, int y, unsigned int b)
	{
		if (m_hidden)
			return;
		
		Widget* widget;
		
		m_testInsideChild = false;
		
		// Send mouse-up signal to all children.
		for (size_t i = 0, sz = m_widgets.size(); i < sz; ++i)
		{
			widget = m_widgets[i];
			
			widget->onMouseUp(static_cast<int>(x - widget->x), static_cast<int>(y - widget->y), b);
			
			if (!m_testInsideChild)
			{
				m_testInsideChild = (
					static_cast<double>(x) >= widget->x && static_cast<double>(x) < widget->x + widget->width &&
					static_cast<double>(y) >= widget->y && static_cast<double>(y) < widget->y + widget->height );
			}
			
			if (widget->m_down && widget->m_downBtn == b)
			{
				// No longer held down.
				widget->m_down = false;
				
				if (widget->m_hidden)
					continue;
				
				// Mouse released this widget.
				widget->onRelease(static_cast<int>(x - widget->x), static_cast<int>(y - widget->y), b);
				
				if (!widget->m_testInsideChild)
				{
					// Check if mouse was inside.
					if (static_cast<double>(x) >= widget->x && static_cast<double>(x) < widget->x + widget->width &&
						static_cast<double>(y) >= widget->y && static_cast<double>(y) < widget->y + widget->height )
					{
						// Widget was clicked.
						widget->onClick(static_cast<int>(x - widget->x), static_cast<int>(y - widget->y), b);
					}
				}
			}
		}
	}
	
	// When the mouse wheel moves.
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onMouseWheel(int x, int y, int d)
	{
		Widget* widget;
		
		// Send mouse-wheel signal to all children.
		for (size_t i = 0, sz = m_widgets.size(); i < sz; ++i)
		{
			widget = m_widgets[i];
			widget->onMouseWheel(static_cast<int>(x - widget->x), static_cast<int>(y - widget->y), d);
		}
	}
	
	// When the mouse moves.
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onMouseMove(int x, int y, int dx, int dy)
	{
		Widget* widget;
		
		// Update mouse positions.
		m_mouseX = x;
		m_mouseY = y;
		
		// Send mouse-move signal to all children.
		for (size_t i = 0, sz = m_widgets.size(); i < sz; ++i)
		{
			widget = m_widgets[i];
			widget->onMouseMove(static_cast<int>(x - widget->x), static_cast<int>(y - widget->y), dx, dy);
		}
	}
	
	// When a keyboard key is down.
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onKeyDown(int key)
	{
		// Send key-down signal to all children.
		for (size_t i = 0, sz = m_widgets.size(); i < sz; ++i)
			m_widgets[i]->onKeyDown(key);
	}
	
	// When a keyboard key is up.
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onKeyUp(int key)
	{
		// Send key-up signal to all children.
		for (size_t i = 0, sz = m_widgets.size(); i < sz; ++i)
			m_widgets[i]->onKeyUp(key);
	}
	
	// When a character is entered. (Useful for widgets like textboxes)
	// NOTE: Inherited classes should invoke this method for the super-class.
	virtual void onKeyText(unsigned int ch)
	{
		// Send text signal to all children.
		for (size_t i = 0, sz = m_widgets.size(); i < sz; ++i)
			m_widgets[i]->onKeyText(ch);
	}
	
	
	// When this widget has moved.
	virtual void onMove(double dx, double dy)
	{
		
	}
	
	// When the widget is resized.
	virtual void onResize()
	{
		
	}
	
	// When the mouse presses inside this widget.
	virtual void onPress(int x, int y, unsigned int b)
	{
		
	}
	
	// When the mouse releases.
	virtual void onRelease(int x, int y, unsigned int b)
	{
		
	}
	
	// When the mouse clicks this widget. (Useful for widgets like buttons)
	// (When the mouse has pressed this widget and released with the mouse inside.)
	virtual void onClick(int x, int y, unsigned int b)
	{
		
	}
	
	// When the user focuses on this widget.
	virtual void onFocusGained()
	{
		
	}
	
	// When the user defocuses from this widget.
	virtual void onFocusLost()
	{
		
	}
	
	// When the mouse entered inside the widget.
	virtual void onMouseEnter(int x, int y)
	{
		
	}
	
	// When the mouse left outside the widget.
	virtual void onMouseLeave(int x, int y)
	{
		
	}
	
	// When this widget adopts a child widget.
	virtual void onAdopt(Widget& child)
	{
		
	}
	
	// When this widget disowns a child widget.
	virtual void onDisown(Widget& child)
	{
		
	}
	
	// When this widget has been adopted.
	virtual void onAdopted(Widget& parent)
	{
		
	}
	
	// When this widget has been disowned.
	virtual void onDisowned(Widget& parent)
	{
		
	}
	
};

#endif