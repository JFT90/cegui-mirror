// This file has been generated by Py++.

#include "boost/python.hpp"
#include "python_CEGUI.h"
#include "RenderEffectManager.pypp.hpp"

namespace bp = boost::python;

void register_RenderEffectManager_class(){

    { //::CEGUI::RenderEffectManager
        typedef bp::class_< CEGUI::RenderEffectManager, bp::bases< CEGUI::Singleton< CEGUI::RenderEffectManager > >, boost::noncopyable > RenderEffectManager_exposer_t;
        RenderEffectManager_exposer_t RenderEffectManager_exposer = RenderEffectManager_exposer_t( "RenderEffectManager", bp::init< >("! Constructor for RenderEffectManager objects.\n") );
        bp::scope RenderEffectManager_scope( RenderEffectManager_exposer );
        { //::CEGUI::RenderEffectManager::create
        
            typedef ::CEGUI::RenderEffect & ( ::CEGUI::RenderEffectManager::*create_function_type )( ::CEGUI::String const &,::CEGUI::Window * ) ;
            
            RenderEffectManager_exposer.def( 
                "create"
                , create_function_type( &::CEGUI::RenderEffectManager::create )
                , ( bp::arg("name"), bp::arg("window") )
                , bp::return_value_policy< bp::reference_existing_object >()
                , "*!\n\
                \n\
                    Create an instance of the RenderEffect based class identified by the\n\
                    specified name.\n\
            \n\
                @param name\n\
                    String object describing the identifier of the RenderEffect based\n\
                    class that is to be created.\n\
            \n\
                @param window\n\
                    Pointer to a Window object.  Exactly how or if this is used will\n\
                    depend upon the specific effect being created.\n\
            \n\
                @return\n\
                    Reference to the newly created RenderEffect.\n\
            \n\
                @exception UnknownObjectException\n\
                    thrown if no RenderEffect class has been registered using the\n\
                    identifier  name.\n\
                *\n" );
        
        }
        { //::CEGUI::RenderEffectManager::destroy
        
            typedef void ( ::CEGUI::RenderEffectManager::*destroy_function_type )( ::CEGUI::RenderEffect & ) ;
            
            RenderEffectManager_exposer.def( 
                "destroy"
                , destroy_function_type( &::CEGUI::RenderEffectManager::destroy )
                , ( bp::arg("effect") )
                , "*!\n\
                \n\
                    Destroy the given RenderEffect object.\n\
            \n\
                \note\n\
                    This function will only destroy objects that were created via the\n\
                    RenderEffectManager.  Attempts to destroy objects created by other\n\
                    means will result in an InvalidRequestException.  This option was\n\
                    chosen over silently ignoring the request in order to aid application\n\
                    developers in thier debugging.\n\
            \n\
                @param effect\n\
                    Reference to the RenderEffect object that is to be destroyed.\n\
            \n\
                @exception InvalidRequestException\n\
                    thrown if  effect was not created by the RenderEffectManager.\n\
                *\n" );
        
        }
        { //::CEGUI::RenderEffectManager::isEffectAvailable
        
            typedef bool ( ::CEGUI::RenderEffectManager::*isEffectAvailable_function_type )( ::CEGUI::String const & ) const;
            
            RenderEffectManager_exposer.def( 
                "isEffectAvailable"
                , isEffectAvailable_function_type( &::CEGUI::RenderEffectManager::isEffectAvailable )
                , ( bp::arg("name") )
                , "*!\n\
                \n\
                    Return whether a RenderEffect has been registered under the specified\n\
                    name.\n\
            \n\
                @param name\n\
                    String object describing the identifier of a RenderEffect to test for.\n\
            \n\
                @return\n\
                    - true if a RenderEffect with the specified name is registered.\n\
                    - false if no RenderEffect with the specified name is registered.\n\
                *\n" );
        
        }
        { //::CEGUI::RenderEffectManager::removeEffect
        
            typedef void ( ::CEGUI::RenderEffectManager::*removeEffect_function_type )( ::CEGUI::String const & ) ;
            
            RenderEffectManager_exposer.def( 
                "removeEffect"
                , removeEffect_function_type( &::CEGUI::RenderEffectManager::removeEffect )
                , ( bp::arg("name") )
                , "*!\n\
                \n\
                    Remove  unregister any RenderEffect using the specified identifier.\n\
            \n\
                @param name\n\
                    String object describing the identifier of the RenderEffect that is to\n\
                    be removed  unregistered.  If no such RenderEffect is present, no\n\
                    action is taken.\n\
            \n\
                \note\n\
                    You should avoid removing RenderEffect types that are still in use.\n\
                    Internally a factory system is employed for the creation and deletion\n\
                    of RenderEffect objects; if an effect - and therefore it's factory - is\n\
                    removed while instances are still active, it will not be possible to\n\
                    safely delete those RenderEffect object instances.\n\
                *\n" );
        
        }
    }

}
