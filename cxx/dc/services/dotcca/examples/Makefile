# this is an xml testing dir we like to have around,
# but is not part of stuff that gets built.
# probably some of this goes to cca-xml-spec sometime.
XMLLINT=/usr/bin/xmllint

VALIDATE= \
ccafe_examples_minimal.depl.cca \
ccafe_examples.depl.cca \
LinearFunction.desc.cca \
LinearFunction.impl.cca \
LinearFunction.depl.cca \
MonteCarloIntegrator.depl.cca


all:
	@echo 'So read the makefile and see what you want to do'

# the following doesn't seem to do what i want. or maybe it does
# and the input is just bogus...
validate:
	for i in $(VALIDATE) ; do \
		$(XMLLINT) --dtdvalid ../componentStaticInformation.xsd --valid $$i > $$i.vout 2>$$i.verr; \
	done

clean:
	$(RM) *.vout *.verr
