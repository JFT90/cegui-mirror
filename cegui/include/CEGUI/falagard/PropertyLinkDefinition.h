/***********************************************************************
    filename:   CEGUIPropertyLinkDefinition.h
    created:    Sat Oct 8 2005
    author:     Paul D Turner <paul@cegui.org.uk>
*************************************************************************/
/***************************************************************************
 *   Copyright (C) 2004 - 2010 Paul D Turner & The CEGUI Development Team
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
#ifndef _CEGUIFalPropertyLinkDefinition_h_
#define _CEGUIFalPropertyLinkDefinition_h_

#include "./PropertyDefinitionBase.h"
#include "../IteratorBase.h"

#include <vector>

#if defined (_MSC_VER)
#	pragma warning(push)
#	pragma warning(disable : 4251)
#endif

// Start of CEGUI namespace section
namespace CEGUI
{
    extern const String S_parentIdentifier;

    /*!
    \brief
        Class representing a property that links to another property defined on
        an attached child widget.
    */
    template <typename T>
    class PropertyLinkDefinition : public PropertyDefinitionBase<T>
    {
    public:
        typedef typename TypedProperty<T>::Helper Helper;
        PropertyLinkDefinition(const String& propertyName,
                               const String& widgetName,
                               const String& targetProperty,
                               const String& initialValue,
                               const String& origin,
                               bool redrawOnWrite,
                               bool layoutOnWrite,
                               const String& fireEvent,
                               const String& eventNamespace)
        : PropertyDefinitionBase<T>(propertyName,
                                    "Falagard property link definition - links a "
                                        "property on this window to properties "
                                        "defined on one or more child windows, or "
                                        "the parent window.",
                                    initialValue, origin,
                                    redrawOnWrite, layoutOnWrite,
                                    fireEvent, eventNamespace)
        {
            // add initial target if it was specified via constructor
            // (typically meaning it came via XML attributes)
            if (!widgetName.empty() || !targetProperty.empty())
                addLinkTarget(widgetName, targetProperty);
        }

        virtual ~PropertyLinkDefinition() {}

        //! add a new link target to \a property on \a widget (name).
        void addLinkTarget(const String& widget, const String& property)
        {
            d_targets.push_back(std::make_pair(widget,property));
        }

        //! clear all link targets from this link definition.
        void clearLinkTargets()
        {
            d_targets.clear();
        }

        // return whether a the given widget / property pair is a target of this property link.
        bool isTargetProperty(const String& widget, const String& property) const
        {
            LinkTargetCollection::const_iterator i = d_targets.begin();
            for (; i != d_targets.end(); ++i)
            {
                if (property == i->second && widget == i->first)
                    return true;
            }

            return false;
        }

        virtual void initialisePropertyReceiver(PropertyReceiver* receiver) const
        {
            updateLinkTargets(receiver, Helper::fromString(this->d_default));
        }

        virtual Property* clone() const
        {
            return CEGUI_NEW_AO PropertyLinkDefinition<T>(*this);
        }

    protected:
        // override members from PropertyDefinitionBase
        typename Helper::safe_method_return_type getNative_impl(const PropertyReceiver* receiver) const
        {
            const LinkTargetCollection::const_iterator i(d_targets.begin());

            const Window* const target_wnd =
                getTargetWindow(receiver, i->first);

            // if no target, or target (currently) invalid, return the default value
            if (d_targets.empty() || !target_wnd)
                return Helper::fromString(TypedProperty<T>::d_default);

            // otherwise return the value of the property for first target, since
            // this is considered the 'master' target for get operations.
            return Helper::fromString(target_wnd->getProperty(i->second.empty() ?
                    TypedProperty<T>::d_name : i->second));
        }
        void setNative_impl(PropertyReceiver* receiver,typename Helper::pass_type value)
        {
            updateLinkTargets(receiver, value);

            // base handles things like ensuring redraws and such happen
            PropertyDefinitionBase<T>::setNative_impl(receiver, value);
        }

        void updateLinkTargets(PropertyReceiver* receiver, typename Helper::pass_type value) const
        {
            LinkTargetCollection::const_iterator i = d_targets.begin();
            for ( ; i != d_targets.end(); ++i)
            {
                Window* target_wnd = getTargetWindow(receiver, i->first);

                // only try to set property if target is currently valid.
                if (target_wnd)
                    target_wnd->setProperty(i->second.empty() ?
                        TypedProperty<T>::d_name : i->second, Helper::toString(value));
            }
        }

        void writeFalagardXMLElementType(XMLSerializer& xml_stream) const
        {
            xml_stream.openTag("PropertyLinkDefinition");
        }

        void writeFalagardXMLAttributes(XMLSerializer& xml_stream) const
        {
            PropertyDefinitionBase<T>::writeFalagardXMLAttributes(xml_stream);

            // HACK: Here we abuse some intimate knowledge in that we know it's
            // safe to write our sub-elements out although the function is named
            // for writing attributes.  The alternative was to repeat code from the
            // base class, also demonstrating intimate knowledge ;)

            LinkTargetCollection::const_iterator i(d_targets.begin());

            // if there is one target only, write it out as attributes
            if (d_targets.size() == 1)
            {
                if (!i->first.empty())
                    xml_stream.attribute("widget", i->first);

                if (!i->second.empty())
                    xml_stream.attribute("targetProperty", i->second);
            }
            // we have multiple targets, so write them as PropertyLinkTarget tags
            else
            {
                for ( ; i != d_targets.end(); ++i)
                {
                    xml_stream.openTag("PropertyLinkTarget");

                    if (!i->first.empty())
                        xml_stream.attribute("widget", i->first);

                    if (!i->second.empty())
                        xml_stream.attribute("property", i->second);

                    xml_stream.closeTag();
                }
            }
        }

        /*!
        \brief
            return a pointer to the window containing the target property to
            be accessed.

        \exception UnknownObjectException
            thrown if no such target window exists within the system.

        */
        //! Return a pointer to the target window with the given name.
        const Window* getTargetWindow(const PropertyReceiver* receiver,
                                      const String& name) const
        {
            if (name.empty())
                return static_cast<const Window*>(receiver);

            // handle link back to parent.  Return receiver if no parent.
            if (name== S_parentIdentifier)
                return static_cast<const Window*>(receiver)->getParent();

            return static_cast<const Window*>(receiver)->getChild(name);
        }

        //! Return a pointer to the target window with the given name.
        Window* getTargetWindow(PropertyReceiver* receiver,
                                const String& name) const
        {
            return const_cast<Window*>(
                getTargetWindow(static_cast<const PropertyReceiver*>(receiver), name));
        }

        typedef std::pair<String,String> StringPair;
        //! type used for the collection of targets.
        typedef std::vector<StringPair CEGUI_VECTOR_ALLOC(StringPair)> LinkTargetCollection;

        //! collection of targets for this PropertyLinkDefinition.
        LinkTargetCollection d_targets;
    public:
        typedef ConstVectorIterator<LinkTargetCollection> LinkTargetIterator;

        LinkTargetIterator getLinkTargetIterator() const
        {
            return LinkTargetIterator(d_targets.begin(),d_targets.end());
        }


    };

} // End of  CEGUI namespace section

#if defined (_MSC_VER)
#	pragma warning(pop)
#endif

#endif  // end of guard _CEGUIFalPropertyLinkDefinition_h_
