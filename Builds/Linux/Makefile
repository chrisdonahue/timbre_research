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
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0 -I ../../Source/dependencies/libcmaes/ -I ../../Source/dependencies/libcmaes/src/ -I /usr/include/eigen3
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -L/usr/X11R6/lib/ -lX11 -lasound -ldl -lpthread -lrt -lcmaes
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
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os -I ../../Source/dependencies/libcmaes/ -I ../../Source/dependencies/libcmaes/src/ -I /usr/include/eigen3
  CXXFLAGS += $(CFLAGS)
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -fvisibility=hidden -L/usr/X11R6/lib/ -lX11 -lasound -ldl -lpthread -lrt -lcmaes
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -D "JUCE_APP_VERSION=0.0.1" -D "JUCE_APP_VERSION_HEX=0x1" -I /usr/include -I /usr/include/freetype2 -I ../../JuceLibraryCode -I ../../../JUCE/modules
  TARGET := timbre_research
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/pm_voice_9e567676.o \
  $(OBJDIR)/base_c255018e.o \
  $(OBJDIR)/exceptions_4e55dd41.o \
  $(OBJDIR)/graph_b143857b.o \
  $(OBJDIR)/helpers_d0acf932.o \
  $(OBJDIR)/parameter_caddd656.o \
  $(OBJDIR)/adsr_ac5e.o \
  $(OBJDIR)/envelopes_base_794bcf49.o \
  $(OBJDIR)/interpolate_linear_975b95ff.o \
  $(OBJDIR)/fm_feedback_edf7f14a.o \
  $(OBJDIR)/add_af9632bb.o \
  $(OBJDIR)/multiply_b4bfe14.o \
  $(OBJDIR)/operators_base_7b155f1.o \
  $(OBJDIR)/phasor_105288f9.o \
  $(OBJDIR)/primitives_base_48bf43de.o \
  $(OBJDIR)/table_function_3274afed.o \
  $(OBJDIR)/table_oscillator_bdbf78b5.o \
  $(OBJDIR)/table_phasor_4505922.o \
  $(OBJDIR)/tables_base_62082771.o \
  $(OBJDIR)/sample_buffer_4d7f2922.o \
  $(OBJDIR)/kiss_fft_eaf1f82e.o \
  $(OBJDIR)/evaluation_158dd2a5.o \
  $(OBJDIR)/main_8d1161a2.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_audio_basics_181b4cb.o \
  $(OBJDIR)/juce_audio_devices_2d9302c9.o \
  $(OBJDIR)/juce_audio_formats_5c144c69.o \
  $(OBJDIR)/juce_core_9d6b33ad.o \
  $(OBJDIR)/juce_cryptography_306b807.o \
  $(OBJDIR)/juce_data_structures_dcd877a9.o \
  $(OBJDIR)/juce_events_e5b201a1.o \

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

$(OBJDIR)/pm_voice_9e567676.o: ../../Source/cdsp/src/abstraction/pm_voice.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pm_voice.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/base_c255018e.o: ../../Source/cdsp/src/base.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling base.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/exceptions_4e55dd41.o: ../../Source/cdsp/src/exceptions.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling exceptions.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/graph_b143857b.o: ../../Source/cdsp/src/graph.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling graph.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/helpers_d0acf932.o: ../../Source/cdsp/src/helpers.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling helpers.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/parameter_caddd656.o: ../../Source/cdsp/src/parameter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling parameter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/adsr_ac5e.o: ../../Source/cdsp/src/primitives/envelopes/adsr.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling adsr.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/envelopes_base_794bcf49.o: ../../Source/cdsp/src/primitives/envelopes/envelopes_base.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling envelopes_base.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/interpolate_linear_975b95ff.o: ../../Source/cdsp/src/primitives/envelopes/interpolate_linear.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling interpolate_linear.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/fm_feedback_edf7f14a.o: ../../Source/cdsp/src/primitives/misc/fm_feedback.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling fm_feedback.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/add_af9632bb.o: ../../Source/cdsp/src/primitives/operators/add.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling add.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/multiply_b4bfe14.o: ../../Source/cdsp/src/primitives/operators/multiply.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling multiply.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/operators_base_7b155f1.o: ../../Source/cdsp/src/primitives/operators/operators_base.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling operators_base.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/phasor_105288f9.o: ../../Source/cdsp/src/primitives/oscillators/phasor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling phasor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/primitives_base_48bf43de.o: ../../Source/cdsp/src/primitives/primitives_base.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling primitives_base.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/table_function_3274afed.o: ../../Source/cdsp/src/primitives/tables/table_function.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling table_function.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/table_oscillator_bdbf78b5.o: ../../Source/cdsp/src/primitives/tables/table_oscillator.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling table_oscillator.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/table_phasor_4505922.o: ../../Source/cdsp/src/primitives/tables/table_phasor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling table_phasor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/tables_base_62082771.o: ../../Source/cdsp/src/primitives/tables/tables_base.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling tables_base.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sample_buffer_4d7f2922.o: ../../Source/cdsp/src/sample_buffer.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sample_buffer.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/kiss_fft_eaf1f82e.o: ../../Source/dependencies/kiss_fft130/kiss_fft.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling kiss_fft.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/evaluation_158dd2a5.o: ../../Source/evaluation.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling evaluation.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/main_8d1161a2.o: ../../Source/main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
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

-include $(OBJECTS:%.o=%.d)
