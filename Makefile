# Project Stuff
NAME :=          mandroid
PROJNAME :=      man-droid
TARGET_FRMWRK := netcoreapp3.1
SRC :=           $(wildcard src/*.cs)

# Technically this is cross-platform, but we want it on the beaglebone :)
RUNTIME :=       linux-arm

$(NAME) : $(SRC)
	dotnet publish $(PROJNAME).csproj \
	    -f $(TARGET_FRMWRK) -p:PublishSingleFile=true -r $(RUNTIME)
	cp bin/Debug/$(TARGET_FRMWRK)/$(RUNTIME)/publish/$(PROJNAME) ./$(NAME)
	chmod +x $(NAME)

.PHONY : clean
clean :
	rm -rf bin
	rm -rf obj
	rm -rf $(NAME)
