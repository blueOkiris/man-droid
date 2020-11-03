# Project setup
OBJNAME :=  mandroid
CPPC :=     g++
CPPFLAGS := -Werror -Wall -std=c++17 -g
LD :=       g++
LDFLAGS :=  -lSDL2 -lSDL2_mixer \
            -L/usr/lib/python3.7/config-3.7m-arm-linux-gnueabihf -lpython3.7
SRC :=      $(wildcard src/*.cpp)
INCDIRS :=  include /usr/include/python3.7 /usr/include/python3.7m

# Helper Targets
.PHONY : all
all : $(OBJNAME)

.PHONY : clean
clean :
	rm -rf obj
	rm -rf $(OBJNAME)
	rm -rf pkg
	rm -rf src/__pycache__

# Autogenerated stuff
INC :=      $(addprefix -I,$(INCDIRS))
OBJS :=     $(subst cpp,o,$(subst src,obj,$(SRC)))

obj/main.o : src/main.cpp include/Tests.hpp
	mkdir -p obj
	$(CPPC) $(CPPFLAGS) $(INC) -o $@ -c $<

obj/%.o : src/%.cpp
	mkdir -p obj
	$(CPPC) $(CPPFLAGS) $(INC) -o $@ -c $<

# Main targets
$(OBJNAME) : $(OBJS)
	$(LD) -o $@ $(OBJS) $(LDFLAGS)

pkg/mandroid.deb : $(OBJNAME) $(wildcard src/*.py) $(wildcard src/install/*) $(wildcard audio/*)
	rm -rf pkg
	mkdir -p pkg
	mkdir -p pkg/mandroid
	mkdir -p pkg/mandroid/DEBIAN
	cp src/install/control pkg/mandroid/DEBIAN
	cp src/install/postinst pkg/mandroid/DEBIAN
	chmod 0555 pkg/mandroid/DEBIAN/postinst
	mkdir -p pkg/mandroid/opt/mandroid
	mkdir -p pkg/mandroid/opt/mandroid/src
	mkdir -p pkg/mandroid/etc/systemd/system
	cp $(OBJNAME) pkg/mandroid/opt/mandroid
	cp -rf audio pkg/mandroid/opt/mandroid
	cp src/pwm.py pkg/mandroid/opt/mandroid/src
	cp src/listen.py pkg/mandroid/opt/mandroid/src
	cp dict.txt pkg/mandroid/opt/mandroid
	cp src/install/mandroid.service pkg/mandroid/etc/systemd/system
	chmod 644 pkg/mandroid/etc/systemd/system/mandroid.service
	cd pkg; dpkg-deb --build mandroid

.PHONY : install
install : $(OBJNAME)
	mkdir -p /opt/mandroid
	mkdir -p /opt/mandroid/src
	cp $(OBJNAME) /opt/mandroid/
	cp -rf audio /opt/mandroid
	cp src/pwm.py /opt/mandroid/src
	cp src/listen.py /opt/mandroid/src
	cp dict.txt /opt/mandroid
	ln -s /opt/mandroid/$(OBJNAME) /usr/bin/$(OBJNAME)
	cp src/install/mandroid.service /etc/systemd/system
	chmod 644 /etc/systemd/system/mandroid.service
	systemctl enable mandroid.service

.PHONY : uninstall
uninstall :
	rm -rf /opt/mandroid
	rm -rf /usr/bin/mandroid
	rm -rf /var/mandroid.log
	systemctl disable mandroid.service
