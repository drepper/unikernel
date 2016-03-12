V ?= 0

COMPILE.cc = $(CXX) $(CXXFLAGS) $(DEFINES) -c -o $@ -MT $@ -MMD -MP -MF $(@:.o=.d)
COMPILE.S = $(CC) $(ASFLAGS) $(DEFINES) -c -o $@ -MT $@ -MMD -MP -MF $(@:.o=.d)

Q0 = @echo -e '$(cmd-$(suffix $@)$(suffix $<)) $@\e[0m' &&
Q1 =
Q = $(Q$(V))


.cc.o:
	$(Q)$(COMPILE.cc) $<
.S.o:
	$(Q)$(COMPILE.S) $<

cmd-.o = \e[32;27mLD
cmd-.o.cc = \e[33;27mCXX
cmd-.o.S = \e[34;27mAS
