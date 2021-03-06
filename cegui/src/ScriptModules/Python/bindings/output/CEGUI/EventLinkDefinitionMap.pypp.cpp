// This file has been generated by Py++.

#include "boost/python.hpp"
#include "indexing_suite/container_suite.hpp"
#include "indexing_suite/map.hpp"
#include "generators/include/python_CEGUI.h"
#include "EventLinkDefinitionMap.pypp.hpp"

namespace bp = boost::python;

void register_EventLinkDefinitionMap_class(){

    { //::std::map<CEGUI::String, CEGUI::EventLinkDefinition*, CEGUI::StringFastLessCompare, std::allocator<std::pair<CEGUI::String const, CEGUI::EventLinkDefinition*> > >
        typedef bp::class_< std::map<CEGUI::String, CEGUI::EventLinkDefinition*, CEGUI::StringFastLessCompare, std::allocator<std::pair<CEGUI::String const, CEGUI::EventLinkDefinition*> > > > EventLinkDefinitionMap_exposer_t;
        EventLinkDefinitionMap_exposer_t EventLinkDefinitionMap_exposer = EventLinkDefinitionMap_exposer_t( "EventLinkDefinitionMap" );
        bp::scope EventLinkDefinitionMap_scope( EventLinkDefinitionMap_exposer );
        EventLinkDefinitionMap_exposer.def( bp::indexing::map_suite< std::map<CEGUI::String, CEGUI::EventLinkDefinition*, CEGUI::StringFastLessCompare, std::allocator<std::pair<CEGUI::String const, CEGUI::EventLinkDefinition*> > > >() );
    }

}
