Here we have what are currently ccaffeine-specific port definitions
that we believe would be useful if cca-blessed and framework-recognized
across most frameworks.

portInterfaces:

GoPort -- make it compute button provided by components.

PrintfPort -- output port used by components (gov.cca.PrintfService)


supportInterfaces:

ParameterPort -- presents an abstract api for configurable components
                 to communicate their input needs to frameworks.
                 It assumes the Parameter library and jc++.

ConfigurableParameterFactory -- an abstract factory used for creating
                                parameter ports in components that
                                provide them.
                                It assumes the Parameter library and jc++.
                                (gov.cca.ParameterPortFactoryService)
