# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.0.1" -D "JUCE_APP_VERSION_HEX=0x1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../JUCE/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.0.1" -D "JUCE_APP_VERSION_HEX=0x1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../JUCE/modules
  TARGET := timbre_research
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -std=c++11 -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.0.1" -D "JUCE_APP_VERSION_HEX=0x1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../JUCE/modules
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lGL -lX11 -lXext -lXinerama -lasound -ldl -lfreetype -lpthread -lrt 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.0.1" -D "JUCE_APP_VERSION_HEX=0x1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../JUCE/modules
  TARGET := timbre_research
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/base_2d36e443.o \
  $(OBJDIR)/exceptions_f38e2436.o \
  $(OBJDIR)/graph_a29df966.o \
  $(OBJDIR)/helpers_d53a1e5d.o \
  $(OBJDIR)/parameter_e0b65cc1.o \
  $(OBJDIR)/adsr_70cfcc9.o \
  $(OBJDIR)/add_58a952b5.o \
  $(OBJDIR)/multiply_a6efca5a.o \
  $(OBJDIR)/phasor_1e9aabe4.o \
  $(OBJDIR)/table_interpolate_4_bf0c1518.o \
  $(OBJDIR)/primitive_base_fffe40c4.o \
  $(OBJDIR)/sample_buffer_1d88820d.o \
  $(OBJDIR)/kiss_fft_eaf1f82e.o \
  $(OBJDIR)/main_8d1161a2.o \
  $(OBJDIR)/juce_audio_basics_181b4cb.o \
  $(OBJDIR)/juce_audio_devices_2d9302c9.o \
  $(OBJDIR)/juce_audio_formats_5c144c69.o \
  $(OBJDIR)/juce_audio_processors_a9c69383.o \
  $(OBJDIR)/juce_core_9d6b33ad.o \
  $(OBJDIR)/juce_cryptography_306b807.o \
  $(OBJDIR)/juce_data_structures_dcd877a9.o \
  $(OBJDIR)/juce_events_e5b201a1.o \
  $(OBJDIR)/juce_graphics_a34b2885.o \
  $(OBJDIR)/juce_gui_basics_3e4cc581.o \
  $(OBJDIR)/juce_gui_extra_20746349.o \
  $(OBJDIR)/juce_opengl_a5fa29cd.o \
  $(OBJDIR)/juce_video_7b52df69.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking timbre_research
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning timbre_research
	@$(CLEANCMD)

strip:
	@echo Stripping timbre_research
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/base_2d36e443.o: ../../Source/cdsp/base.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling base.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/exceptions_f38e2436.o: ../../Source/cdsp/exceptions.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling exceptions.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/graph_a29df966.o: ../../Source/cdsp/graph.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling graph.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/helpers_d53a1e5d.o: ../../Source/cdsp/helpers.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling helpers.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/parameter_e0b65cc1.o: ../../Source/cdsp/parameter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling parameter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/adsr_70cfcc9.o: ../../Source/cdsp/primitives/envelopes/adsr.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling adsr.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/add_58a952b5.o: ../../Source/cdsp/primitives/math/add.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling add.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/multiply_a6efca5a.o: ../../Source/cdsp/primitives/math/multiply.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling multiply.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/phasor_1e9aabe4.o: ../../Source/cdsp/primitives/oscillators/phasor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling phasor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/table_interpolate_4_bf0c1518.o: ../../Source/cdsp/primitives/oscillators/table_interpolate_4.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling table_interpolate_4.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/primitive_base_fffe40c4.o: ../../Source/cdsp/primitives/primitive_base.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling primitive_base.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sample_buffer_1d88820d.o: ../../Source/cdsp/sample_buffer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sample_buffer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/kiss_fft_eaf1f82e.o: ../../Source/dependencies/kiss_fft130/kiss_fft.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling kiss_fft.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/main_8d1161a2.o: ../../Source/main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_181b4cb.o: ../../../JUCE/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_devices_2d9302c9.o: ../../../JUCE/modules/juce_audio_devices/juce_audio_devices.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_devices.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_formats_5c144c69.o: ../../../JUCE/modules/juce_audio_formats/juce_audio_formats.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_formats.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_a9c69383.o: ../../../JUCE/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_9d6b33ad.o: ../../../JUCE/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_cryptography_306b807.o: ../../../JUCE/modules/juce_cryptography/juce_cryptography.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_cryptography.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_dcd877a9.o: ../../../JUCE/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_e5b201a1.o: ../../../JUCE/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_a34b2885.o: ../../../JUCE/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_3e4cc581.o: ../../../JUCE/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_20746349.o: ../../../JUCE/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_opengl_a5fa29cd.o: ../../../JUCE/modules/juce_opengl/juce_opengl.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_opengl.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_video_7b52df69.o: ../../../JUCE/modules/juce_video/juce_video.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_video.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
