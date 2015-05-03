// This file has been generated by Py++.

#include "boost/python.hpp"
#include "indexing_suite/container_suite.hpp"
#include "indexing_suite/map.hpp"
#include "generators/include/python_CEGUI.h"
#include "PropertyInitialiserMap.pypp.hpp"

namespace bp = boost::python;

void register_PropertyInitialiserMap_class(){

    { //::std::map<CEGUI::String, CEGUI::PropertyInitialiser*, CEGUI::StringFastLessCompare, std::allocator<std::pair<CEGUI::String const, CEGUI::PropertyInitialiser*> > >
        typedef bp::class_< std::map<CEGUI::String, CEGUI::PropertyInitialiser*, CEGUI::StringFastLessCompare, std::allocator<std::pair<CEGUI::String const, CEGUI::PropertyInitialiser*> > > > PropertyInitialiserMap_exposer_t;
        PropertyInitialiserMap_exposer_t PropertyInitialiserMap_exposer = PropertyInitialiserMap_exposer_t( "PropertyInitialiserMap" );
        bp::scope PropertyInitialiserMap_scope( PropertyInitialiserMap_exposer );
        PropertyInitialiserMap_exposer.def( bp::indexing::map_suite< std::map<CEGUI::String, CEGUI::PropertyInitialiser*, CEGUI::StringFastLessCompare, std::allocator<std::pair<CEGUI::String const, CEGUI::PropertyInitialiser*> > > >() );
    }

}
