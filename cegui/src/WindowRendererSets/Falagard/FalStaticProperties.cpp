/***********************************************************************
	filename: 	FalStaticProperties.cpp
	created:	Sat Sep 18 2005
	author:		Tomas Lindquist Olsen (based on code by Paul D Turner)
	
	purpose:	Implements property classes for the FalagardStatic widget.
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2006 Paul D Turner & The CEGUI Development Team
 *
 *   Permission is hereby granted, free of charge, to any person obtaining
 *   a copy of this software and associated documentation files (the
 *   "Software"), to deal in the Software without restriction, including
 *   without limitation the rights to use, copy, modify, merge, publish,
 *   distribute, sublicense, and/or sell copies of the Software, and to
 *   permit persons to whom the Software is furnished to do so, subject to
 *   the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *   OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************/
#include "FalStatic.h"
#include "CEGUIPropertyHelper.h"


// Start of CEGUI namespace section
namespace CEGUI
{

// Start of FalagardStaticProperties namespace section
namespace FalagardStaticProperties
{

String	FrameEnabled::get(const PropertyReceiver* receiver) const
{
    FalagardStatic* wr = static_cast<FalagardStatic*>(
    static_cast<const Window*>(receiver)->getWindowRenderer());
    return PropertyHelper<bool>::toString(wr->isFrameEnabled());
}


void	FrameEnabled::set(PropertyReceiver* receiver, const String& value)
{
    FalagardStatic* wr = static_cast<FalagardStatic*>(
    static_cast<Window*>(receiver)->getWindowRenderer());
    wr->setFrameEnabled(PropertyHelper<bool>::fromString(value));
}


String	BackgroundEnabled::get(const PropertyReceiver* receiver) const
{
    FalagardStatic* wr = static_cast<FalagardStatic*>(
    static_cast<const Window*>(receiver)->getWindowRenderer());
    return PropertyHelper<bool>::toString(wr->isBackgroundEnabled());
}


void	BackgroundEnabled::set(PropertyReceiver* receiver, const String& value)
{
    FalagardStatic* wr = static_cast<FalagardStatic*>(
    static_cast<Window*>(receiver)->getWindowRenderer());
    wr->setBackgroundEnabled(PropertyHelper<bool>::fromString(value));
}

} // End of  FalagardStaticProperties namespace section

} // End of  CEGUI namespace section