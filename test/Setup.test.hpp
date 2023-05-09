// Copyright © Loft Orbital Solutions Inc.

#include <Global.test.hpp>


namespace ostk
{
namespace math
{
namespace test
{


namespace global
{


std::string someGlobalString ;


}


class Environment : public testing::Environment
{

    public:

                                Environment                                 (   const   std::string&                aCommandLineArg                     )
                                :   commandLineArg_(aCommandLineArg)
        {

            if (commandLineArg_ != "")
            {
                global::someGlobalString = commandLineArg_ ;
            }
            else
            {
                global::someGlobalString = "World" ;
            }

        }

        virtual                 ~Environment                                ( )
        {

        }

        virtual void            SetUp                                       ( )
        {

        }

        virtual void            TearDown                                    ( )
        {

        }

    private:

        std::string             commandLineArg_ ;

} ;


}
}
}

